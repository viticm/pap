/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id share_memory.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-3 11:32:43
 * @uses system share memory model
 */
#ifndef PAP_SERVER_SHARE_MEMORY_MAIN_SHARE_MEMROY_H_
#define PAP_SERVER_SHARE_MEMORY_MAIN_SHARE_MEMROY_H_

#include "common/base/type.h"
#include "server/common/game/define.h"
#include "server/common/base/config.h"
#include "server/common/sys/share_memory.h"

class ShareMemory {

 public: //construct and destruct
   ShareMemory();
   ~ShareMemory();

 public: //define extend types
   struct pool_keydata_t {
	   pap_server_common_base::share_memory_key_data_t key_data;
     void* pool;
     pool_keydata_t() {
       pool = NULL;
     }
   };
   struct logicmanager_t {
     void* logic_manager;
     pap_server_common_game::define::type::share_memory::key_enum key_type;
     logicmanager_t() {
       logic_manager = NULL;
	   using namespace pap_server_common_game::define;
	   key_type = type::share_memory::kKeyInvalid;
     }
   };

 public:
   bool init();
   bool loop();
   bool selfexit();
   bool work();
   void consolecommand();

 protected:
   bool new_staticmanager();
   bool init_staticmanager();
   bool release_staticmanager();
   bool check_worldzone_id();

 private:
   pool_keydata_t keydata_pool_[pap_server_common_sys::share_memory::kObjMax];
   logicmanager_t 
       logicmanager_pool_[pap_server_common_sys::share_memory::kObjMax];
   bool exited_;

};

extern ShareMemory g_sharememroy;
extern int32_t g_cmd_model;
extern bool g_cmd_input;

class ExceptionHandler {

 public:
   ExceptionHandler();
   ~ExceptionHandler();

};

extern ExceptionHandler g_exception_handler;

#endif //PAP_SERVER_SHARE_MEMORY_MAIN_SHARE_MEMROY_H_
