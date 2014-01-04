#include "server/share_memory/main/share_memory.h"
#include "server/share_memory/main/command_thread.h"
#include "server/common/base/log.h"
#include "server/common/base/time_manager.h"
#include "server/common/db/manager.h"
#include "common/base/util.h"
#include "server/share_memory/data/logic_manager.h"
#include "server/common/game/db/struct.h"
#include "server/common/db/data/global.h"
#include "server/common/game/define/all.h"
#include "common/sys/util.h"

ShareMemory g_sharememory;

bool check_saveall_file();
bool check_exitfile();
bool check_start_savelogout();
bool check_stop_savelogout();

int32_t g_cmd_model = -1;
bool g_cmd_input = false;
command_config_t g_command_config;
ExceptionHandler g_exception_handler;

int32_t main(int32_t argc, char* argv[]) {
#if defined(__WINDOWS__)
  _CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);
  system("color 02"); //color green
  system("mode con cols=120"); //cmd size
#endif
  int32_t i;
  //-- command
  if (argc > 1) {
    for (i = 1; i < argc; ++i) {
      if (0 == strcmp(argv[i], "-clear")) {
        g_cmd_model = kCmdModelClearAll;
        printf("cmd model enter clear all%s", LF);
      }
      if (0 == strcmp(argv[i], "-loaddump")) {
        g_cmd_model = kCmdModelLoadDump;
        printf("cmd model enter load dump%s", LF);
      }
      if (0 == strcmp(argv[i], "-enablecmd")) {
        g_cmd_input = true;
      }
      if (0 == strcmp(argv[i], "-ignoreassert")) {
        g_command_assert = 1;
      }
      if (0 == strcmp(argv[i], "-retryassert")) {
        g_command_assert = 2;
      }
      if (0 == strcmp(argv[i], "-ignoremessagebox")) {
        g_command_ignore_message_box = true;
      }
    }
  }
  //command --
  using namespace pap_server_common_base; //using namespace in function!!!
  g_time_manager = new TimeManager();
  g_time_manager->init();

  bool result = false;
  Log::save_log("sharememory", "(###)main...");
  Log::save_log("sharememory", "sharememory start ...");
  result = g_sharememory.init();
  if (false == result) {
    Assert(false);
    return 1;
  }
  result = g_sharememory.loop();
  if (false == result) {
    Assert(false);
    return 1;
  }
  result = g_sharememory.selfexit();
  if (false == result) {
    Assert(false);
    return 1;
  }
  SAFE_DELETE(g_time_manager);
  return 0;
}

ShareMemory::ShareMemory() {
  __ENTER_FUNCTION
    exited_ = false;
  __LEAVE_FUNCTION
}

ShareMemory::~ShareMemory() {
  //do nothing
}

bool ShareMemory::init() {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;
    bool result = true;

    Log::save_log("sharememory", "start read config files");
    result = g_config.init();
    Assert(result);
    Log::save_log("sharememory", "read config files success");

    Log::save_log("sharememory", "start new static manager");
    result = new_staticmanager();
    Assert(result);
    Log::save_log("sharememory", "new static manager success");

    Log::save_log("sharememory", "start init static manager");
    result = init_staticmanager();
    Assert(result);
    Log::save_log("sharememory", "init static manager success");

    return result;
  __LEAVE_FUNCTION
    return false;
}

bool ShareMemory::loop() {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;
    using namespace pap_common_base;
    if (g_cmd_input) {
      g_command_thread.start();
      Log::save_log("sharememory", "g_command_thread.start()");
    }
    Log::save_log("sharememory", "loop ... start");
    for (;;) {
      work();
      util::sleep(1000);
    }
    //Log::save_log("sharememory", "loop ... end");
  __LEAVE_FUNCTION
    return false;
}

bool ShareMemory::selfexit() {
  __ENTER_FUNCTION
    release_staticmanager();
    exited_ = true;
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool ShareMemory::work() {
  using namespace pap_server_common_base;
  using namespace pap_common_base;
  using namespace pap_server_common_db;
  using namespace pap_server_common_sys;
  using namespace pap_server_common_game::define; //the type namespace
  using namespace pap_server_common_game::db::share_memory;
  try { //body use try catch then allow not use enter and leave function
    bool exitflag = false;
    uint32_t daytime = g_time_manager->get_day_time();
    if (static_cast<uint32_t>(g_file_name_fix) != daytime) 
      g_file_name_fix = daytime;
    ODBCInterface* odbc_interface =
      g_db_manager->get_interface(kCharacterDatabase);
    Assert(odbc_interface);
    if (!odbc_interface->is_connected()) {
      g_log->fast_save_log(kShareMemoryLogFile, "connect database failed");
      bool connectresult = false;
      connectresult = odbc_interface->connect();
      if (!connectresult) {
        g_log->fast_save_log(kShareMemoryLogFile,
                             "try connect database failed");
        util::sleep(5000);
        if (kCmdUnkown == g_command_thread.command_config.state.type) {
          return false;
        }
      }
      else {
        g_log->fast_save_log(kShareMemoryLogFile, 
                             "try connect database success");
      }
    }

    if (check_saveall_file()) {
      g_command_thread.command_config.state.type = kCmdSaveAll;
      g_log->fast_save_log(kShareMemoryLogFile, "cmd enter save all");
    }
    if (check_exitfile()) {
      g_command_thread.command_config.state.type = kCmdSaveAll;
      exitflag = true;
      g_log->fast_save_log(kShareMemoryLogFile, "cmd enter exit");
    }
    if (check_start_savelogout()) {
      g_log->fast_save_log(kShareMemoryLogFile, "cmd enter start save logout");
    }
    if (check_stop_savelogout()) {
      g_log->fast_save_log(kShareMemoryLogFile, "cmd enter stop save logout");
    }
    if (g_command_thread.command_config.state.type != kCmdUnkown) {
      g_command_config = g_command_thread.command_config;
      g_command_thread.command_config.state.type = kCmdUnkown;
    }
 
    uint32_t i;
    for (i = 0; i < share_memory::kObjMax; ++i) {
      if (logicmanager_pool_[i].logic_manager) {
        type::sharememory::key_enum key_type;
        key_type = logicmanager_pool_[i].key_type;
        switch (key_type) {
          case type::sharememory::kKeyGlobalData: {
            LogicManager<global_data_t>* globaldata_manager =
              static_cast<LogicManager<global_data_t>*>(
                  logicmanager_pool_[i].logic_manager);
            if (globaldata_manager) {
              globaldata_manager->heartbeat();
            }
            else {
              AssertEx(false, "ShareMemory::work run time error");
            }
            break;
          }
          default: {
            AssertEx(false, "ShareMemory::work unkown key type");
          }
        }
      }
    }
   
    if (kCmdClearAll == g_command_config.state.type) {
      exit(0);
    }
    g_command_config.state.type = kCmdUnkown;

    if (exitflag) {
      Log::save_log("sharememory", "share memory need exit");
      exit(0);
    }
    return true;
  }
  catch(...) {
    Log::save_log("sharememroy", "ShareMemory::work is error");
    return false;
  }
}

bool ShareMemory::new_staticmanager() {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;
    using namespace pap_server_common_sys::share_memory;
    using namespace pap_server_common_game::define; //the type namespace
    using namespace pap_server_common_game::db::share_memory;
    using namespace pap_server_common_db;
    bool result = true;
    g_db_manager = new Manager();
    AssertEx(g_db_manager, "new Manager(db) failed");
    Log::save_log("sharememory", "new Manager(db) success");
    uint32_t i;
    for (i = 0; i < g_config.share_memory_info_.obj_count; ++i) {
      keydata_pool_[i].key_data = g_config.share_memory_info_.key_data[i];
      type::sharememory::key_enum key_type;
      key_type = static_cast<type::sharememory::key_enum>(
      g_config.share_memory_info_.key_data[i].type);
      switch (key_type) {
        case type::sharememory::kKeyGlobalData: {
          keydata_pool_[i].pool = 
            new UnitPool<global_data_t>();
          Assert(keydata_pool_[i].pool);
          Log::save_log("sharememory", 
                        "new UnitPool<Global> success");
          logicmanager_pool_[i].logic_manager = 
            new LogicManager<global_data_t>();
          Assert(logicmanager_pool_[i].logic_manager);
          Log::save_log("sharememory", "new LogicManager<Global> success");
          logicmanager_pool_[i].key_type = type::sharememory::kKeyGlobalData;
          break;
        }
        default: {
          break;
        }
      }
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool ShareMemory::init_staticmanager() {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;
    using namespace pap_server_common_sys::share_memory;
    using namespace pap_server_common_game::define; //the type namespace
    using namespace pap_server_common_game::db::share_memory;

    bool result = true;
    Assert(g_db_manager);
    result = g_db_manager->init(kCharacterDatabase); //db character
    Log::save_log("sharememory", 
                  "g_db_manager->init(kCharacterDatabase) %s",
                  result ? "success" : "failed");
    Assert(result);
    uint16_t i;
    uint16_t obj_count = g_config.share_memory_info_.obj_count;
    for (i = 0; i < obj_count; ++i) {
      typedef type::sharememory::key_enum key_enum;
      key_enum key_type;
      key_type = static_cast<key_enum>(
          g_config.share_memory_info_.key_data[i].type);
      switch (key_type) {
        case type::sharememory::kKeyGlobalData: {
          UnitPool<global_data_t>* global_pool;
          global_pool = 
            static_cast<UnitPool<global_data_t>*>(
                keydata_pool_[i].pool);
          Assert(global_pool);
          uint64_t key = keydata_pool_[i].key_data.key;
          result = global_pool->init(1, key, kSmptShareMemory);
          Assert(result);
          LogicManager<global_data_t>* global_logicmanager = 
            static_cast<LogicManager<global_data_t>*>(
                logicmanager_pool_[i].logic_manager);
          Assert(global_logicmanager);
          result = global_logicmanager->init(global_pool);
          Assert(result);
          break;
        }
        default: {
          break;
        }
      }
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool ShareMemory::release_staticmanager() {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;
    using namespace pap_server_common_sys::share_memory;
    using namespace pap_server_common_game::define; //the define namespace
    using namespace pap_server_common_game::db::share_memory;

    bool result = true;
    uint32_t i;
    uint16_t obj_count = g_config.share_memory_info_.obj_count;
    for (i = 0; i < obj_count; ++i) {
      typedef type::sharememory::key_enum key_enum;
      key_enum _type;
      _type = static_cast<key_enum>(
          g_config.share_memory_info_.key_data[i].type);
      switch (_type) {
        case type::sharememory::kKeyGlobalData: {
          UnitPool<global_data_t>* global_pool;
          global_pool = 
            static_cast<UnitPool<global_data_t>*>(
                keydata_pool_[i].pool);
          LogicManager<global_data_t>* global_logicmanager = 
            static_cast<LogicManager<global_data_t>*>(
                logicmanager_pool_[i].logic_manager);
          SAFE_DELETE(global_pool);
          SAFE_DELETE(global_logicmanager);
          break;
        }
        default: {
          break;
        }
      }
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool check_saveall_file() {
  __ENTER_FUNCTION
    bool result = true;
    if (-1 == remove("saveall.cmd")) result = false;
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool check_exitfile() {
  __ENTER_FUNCTION
    bool result = true;
    if (-1 == remove("exit.cmd")) result = false;
    bool g_lock_timeout_enable;
    g_lock_timeout_enable = true;
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool check_start_savelogout() {
  __ENTER_FUNCTION
    bool result = true;
    if (-1 == remove("startsave.cmd")) result = false;
    bool g_need_savelogout;
    g_need_savelogout = true;
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool check_stop_savelogout() {
  __ENTER_FUNCTION
    bool result = true;
    if (-1 == remove("stopsave.cmd")) result = false;
    bool g_need_savelogout;
    g_need_savelogout = true;
    return result;
  __LEAVE_FUNCTION
    return false;
}

void inthandler(int32_t) {
  __ENTER_FUNCTION
    pap_common_sys::util::dumpstack("sharememory_dump", "int exception:");
    exit(0);
  __LEAVE_FUNCTION
}

void termhandler(int32_t) {
  __ENTER_FUNCTION
    pap_common_sys::util::dumpstack("sharememory_dump", "term exception:");
    exit(0);
  __LEAVE_FUNCTION
}

void aborthandler(int32_t) {
  __ENTER_FUNCTION
    pap_common_sys::util::dumpstack("sharememory_dump", "abort exception:");
    exit(0);
  __LEAVE_FUNCTION
}

void illhandler(int32_t) {
  __ENTER_FUNCTION
    pap_common_sys::util::dumpstack("sharememory_dump", "ill exception:");
    exit(0);
  __LEAVE_FUNCTION
}

void fpehandler(int32_t) {
  __ENTER_FUNCTION
    pap_common_sys::util::dumpstack("sharememory_dump", "fpe exception:");
    exit(0);
  __LEAVE_FUNCTION
}

void segvhandler(int32_t) {
  __ENTER_FUNCTION
    pap_common_sys::util::dumpstack("sharememory_dump", "segv exception:");
    exit(0);
  __LEAVE_FUNCTION
}

void xfszhandler(int32_t) {
  __ENTER_FUNCTION
    pap_common_sys::util::dumpstack("sharememory_dump", "xfsz exception:");
    exit(0);
  __LEAVE_FUNCTION
}

ExceptionHandler::ExceptionHandler() {
  __ENTER_FUNCTION
#if defined(__LINUX__)
    signal(SIGSEGV, segvhandler);
    signal(SIGFPE, fpehandler);
    signal(SIGILL, illhandler);
    signal(SIGINT, inthandler);
    signal(SIGTERM, termhandler);
    signal(SIGABRT, aborthandler);
    signal(SIGXFSZ, xfszhandler);
#endif
  __LEAVE_FUNCTION
}
