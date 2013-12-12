#include "server/share_memory/main/share_memory.h"
#include "server/common/base/log.h"
#include "server/common/base/time_manager.h"
#include "server/common/db/manager.h"
#include "server/share_memory/data/logic_manager.h"

ShareMemory g_sharememory;

bool check_allsave_file();
bool check_exitfile();

int32_t main(int32_t argc, char* argv[]) {
using namespace 
#if defined(__WINDOWS__)
  _CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);
#endif
  g_cmd_input = false;
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
    
    Log::save_log("share_memory", "start read config files");
    result = g_config.init();
    Assert(result);
    Log::save_log("share_memory", "read config files success");

    Log::save_log("share_memory", "start new static manager");
    result = new_staticmanager();
    Assert(result);
    Log::save_log("share_memory", "new static manager success");

    Log::save_log("share_memory", "start init static manager");
    result = init_staticmanager();
    Assert(result);
    Log::save_log("share_memory", "init static manager success");

    return result;
  __LEAVE_FUNCTION
    return false;
}
bool ShareMemory::loop() {
  __ENTER_FUNCTION

  __LEAVE_FUNCTION
    return false;
}
