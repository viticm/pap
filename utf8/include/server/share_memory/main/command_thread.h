/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id command_thread.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-3 11:32:43
 * @uses the command thread for share memory
 */
#ifndef PAP_SERVER_SHARE_MEMORY_MAIN_COMMAND_THREAD_H_
#define PAP_SERVER_SHARE_MEMORY_MAIN_COMMAND_THREAD_H_

#include "common/base/type.h"
#include "common/sys/thread.h"
#include "server/share_memory/data/config.h" //use it command struct


class CommandThread : public pap_common_sys::Thread {

 public:
   CommandThread();
   ~CommandThread();

 public:
   command_config_t command_config;

 public:
   virtual void run();
   virtual void stop();
   bool is_active();
 private:
   active_;

};

class CommandParser {

 public:
   CommandThread();
   ~CommandThread();
 
 public:
   static bool handleinput();

 private:
   static command_state_t parser_commandtype(const char* str); 

};

extern CommandThread g_command_thread;

#endif //PAP_SERVER_SHARE_MEMORY_MAIN_COMMAND_THREAD_H_

