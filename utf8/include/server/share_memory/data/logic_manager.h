/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id logic_manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-4 15:00:18
 * @uses share memory data logic manager template 
 *       class and some data class of game.
 *       cn: 这是一个共享内存的模板类，源文件中放置了游戏中数据的实现类
 */
#ifndef PAP_SERVER_SHARE_MEMORY_DATA_LOGIC_MANAGER_H_
#define PAP_SERVER_SHARE_MEMORY_DATA_LOGIC_MANAGER_H_

#include "server/common/sys/share_memory.h"
#include "server/common/base/time_manager.h"
#include "server/common/base/log.h"
#include "server/share_memory/data/config.h"

extern command_config_t g_command_config;
extern bool g_clean_guild_battle;

template <typename T>
class LogicManager {

 public:
   LogicManager() {
     __ENTER_FUNCTION
       pool_pointer_ = NULL;
       data_ = NULL;
       last_save_time_ = 0;
     __LEAVE_FUNCTION
   };
   ~LogicManager() {
     //do nothing
   };
   bool init(pap_server_common_sys::share_memory::UnitPool<T>* pool) {
     __ENTER_FUNCTION
       if (!pool) return false;
       pool_pointer_ = pool;
       pool_pointer_->set_head_version(0);
       old_check_time_ = g_time_manager->get_run_time();
       old_version_ = 0;
     __LEAVE_FUNCTION
       return false;
   };
   bool heartbeat() {
     __ENTER_FUNCTION
       uint32_t run_time = g_time_manager->get_run_time();
       bool result;
       if (run_time - old_check_time_ > kServerIdleTime) {
         old_check_time_ = run_time;
         uint32_t version = pool_pointer_->get_head_version();
         if (version == old_version_ && old_version_ > 0) {
           old_version_ = 0;
           pap_server_common_base::Log::fast_save_log(
               kShareMemoryLogFile, 
               "[logic manager](heartbeat)" 
               "receive server crash command."); //string wrap i use like this 
           result = save_all();
           pool_pointer->set_head_version(0);
           return result;
         }
         old_version_ = version;
       }
       switch(g_command_config.state.type) {
         case kCmdSaveAll: {
           result = save_all();
           break;
         }
         case kCmdClearAll: {
           result = clear();
           break;
         }
         case kCmdUnkown: {
           result = normal_save();
           break;
         }
         default: {
           result = false;
         }
       }
       return result;
     __LEAVE_FUNCTION
       return false;
   };
   bool save_all(); //stop server save data
   bool normal_save(); //heartbeat save data
   bool clear(); //clear data
   bool post_init(); //data init on server start

 private:
   pap_server_common_sys::share_memory::UnitPool<T>* pool_pointer_;
   T* data_;
   uint32_t last_save_time_;
   bool ready_;
   uint32_t old_version_;
   uint32_t old_check_time_;

};

#endif //PAP_SERVER_SHARE_MEMORY_DATA_LOGIC_MANAGER_H_
