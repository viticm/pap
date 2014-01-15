#include "server/billing/main/billing.h"
#include "server/billing/main/accounttable.h"
#include "server/billing/connection/pool.h"
#include "server/billing/main/servermanager.h"
#include "server/common/base/time_manager.h"
#include "server/common/base/log.h"
#include "server/common/base/config.h"
#include "common/net/packet/factorymanager.h"

#if defined(__WINDOWS__)
#include "common/sys/minidump.h"
const char* g_dump_exename = "billing";
#endif

Billing g_billing;

int32_t main(int32_t argc, char* argv[]) {
  using namespace pap_server_common_base;
#if defined(__WINDOWS__)
  //如果想用这个调试，请在GBK环境下，而且需要去掉对iconv的调用
  //1去掉库libiconv.lib
  //2注释掉common/base/util.cc的charset_convert方法
  /**
  SetUnhandledExceptionFilter(
      pap_common_sys::minidump::unhandled_exceptionfilter);
  **/ 
  _CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);
  system("color 02"); //color green
  system("mode con cols=120"); //cmd size
#endif
  __ENTER_FUNCTION
    if (argc > 1) {
      uint16_t i;
      for (i = 1; i < argc; ++i) {
        if (0 == strcmp(argv[i],"-ignoreassert")) g_command_assert = 1;
        if (0 == strcmp(argv[i],"-retryassert")) g_command_assert = 2;
        if (0 == strcmp(argv[i],"-ignoremessagebox")) 
          g_command_ignore_message_box = true;
      }
    }
    bool result = false;
    
    g_time_manager = new TimeManager();
    Assert(g_time_manager);
    g_time_manager->init();
    
    g_log = new Log();
    Assert(g_log);
    result = g_log->init();
    Assert(result);
    g_log->save_log("billing", "(###)main ...");
    g_log->save_log("billing", "billing start");

    result = g_billing.init();
    if (false == result) {
      Assert(false);
      return 1;
    }
    result = g_billing.loop();
    if (false == result) {
      Assert(false);
      return 1;
    }
    result = g_billing.exit();
    if (false == result) {
      Assert(false);
      return 1;
    }
    return 0;
  __LEAVE_FUNCTION
    return 1;
}

Billing::Billing() {
  __ENTER_FUNCTION
#if defined(__WINDOWS__)
    WORD versionrequested;
    WSADATA data;
    int32_t error;
    versionrequested = MAKEWORD(2, 2);
    error = WSAStartup(versionrequested, &data);
#endif
  __LEAVE_FUNCTION
}

Billing::~Billing() {
  __ENTER_FUNCTION
#if defined(__WINDOWS__)
    WSACleanup();
#endif
  __LEAVE_FUNCTION
}

bool Billing::init() {
  __ENTER_FUNCTION
    bool result = false;
    g_log->save_log("billing", "start read config files ...");
    result = g_config.init();
    Assert(result);
    g_log->save_log("billing", "read config files...success!");

    g_log->save_log("billing", "start new managers ...");
    result = new_staticmanager();
    Assert(result);
    g_log->save_log("billing", "new managers...success!");

    g_log->save_log("billing", "start init managers ...");
    result = init_staticmanager();
    Assert(result);
    g_log->save_log("billing", "init managers...success!");

    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Billing::loop() {
  __ENTER_FUNCTION
    g_log->save_log("billing", "loop ...");
    g_servermanager->loop();
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool Billing::exit() {
  __ENTER_FUNCTION
    bool result = false;
    g_log->save_log("billing", "start exit ...");
    result = release_staticmanager();
    Assert(result);
    g_log->save_log("billing", "exit success!");
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Billing::new_staticmanager() {
  __ENTER_FUNCTION
    g_servermanager = new ServerManager();
    Assert(g_servermanager);
    g_log->save_log("billing", "new ServerManager()...success!");

    g_connectionpool = new billingconnection::Pool();
    Assert(g_connectionpool);
    g_log->save_log("billing", "new billingconnection::Pool()...success!");

    g_packetfactory_manager = new pap_common_net::packet::FactoryManager;
    Assert(g_packetfactory_manager);
    g_log->save_log("billing", 
                    "new pap_common_net::packet::factorymanager()...success!");
    
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool Billing::init_staticmanager() {
  __ENTER_FUNCTION
    bool result = false;
    result = g_accounttable.init();
    Assert(result);
    g_log->save_log("billing", "g_accounttable.init()...success!");
    
    result = g_servermanager->init();
    Assert(result);
    g_log->save_log("billing", "g_servermanager->init()...success!");

    result = g_connectionpool->init();
    Assert(result);
    g_log->save_log("billing", "g_connectionpool->init()...success!");

    result = g_packetfactory_manager->init();
    Assert(result);
    g_log->save_log("billing", "g_packetfactory_manager->init()...success!");

    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Billing::release_staticmanager() {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;

    SAFE_DELETE(g_log);
    Log::save_log("billing", "g_log release...success!");

    SAFE_DELETE(g_time_manager);
    Log::save_log("billing", "g_time_manager release...success!");
    
    SAFE_DELETE(g_packetfactory_manager);
    Log::save_log("billing", "g_packetfactory_manager release...success!");

    SAFE_DELETE(g_connectionpool);
    Log::save_log("billing", "g_connectionpool release...success!");

    SAFE_DELETE(g_servermanager);
    Log::save_log("billing", "g_servermanager release...success!");
    return true;
  __LEAVE_FUNCTION
    return false;
}
