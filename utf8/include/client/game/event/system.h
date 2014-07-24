/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-25 16:21:53
 * @uses client game event system class
 *       cn: 游戏事件处理器
 */
#ifndef PAP_CLIENT_GAME_EVENT_SYSTEM_H_
#define PAP_CLIENT_GAME_EVENT_SYSTEM_H_

//#include <queue.h>
#include "vengine/game/eventsystem.h"
#include "vengine/game/eventdefine.h"

namespace event {

class System : public vengine_game::EventSystem {

VENGINE_KERNEL_DECLARE_DYNAMIC(event_System);

 public:
   System();
   virtual ~System();
   static System* getself();
 
 //implement for abstract
 public:
   virtual void push(vengine_game::event_id::_enum id, 
                     std::vector<STRING> param);
   virtual void push(vengine_game::event_id::_enum id);
   virtual void push(vengine_game::event_id::_enum id, int32_t arg0);
   virtual void push(vengine_game::event_id::_enum id, const char* arg0);
   virtual void push(vengine_game::event_id::_enum id, 
                     const char* arg0, 
                     const char* arg1);
   virtual void push(vengine_game::event_id::_enum id,
                     const char* arg0,
                     const char* arg1,
                     int32_t arg2);
   virtual void push(vengine_game::event_id::_enum id,
                     int32_t arg0,
                     int32_t arg1);
   virtual void push(vengine_game::event_id::_enum id,
                     int32_t arg0,
                     int32_t arg1,
                     int32_t arg2);
   virtual void push(vengine_game::event_id::_enum id,
                     const char* arg0,
                     const char* arg1,
                     int32_t arg2,
                     int32_t arg3);
   virtual void push(vengine_game::event_id::_enum id,
                     const char* arg0,
                     const char* arg1,
                     const char* arg2);
   //注册事件处理函数
   virtual void registerhandle(const STRING& name,
                               vengine_game::function_eventhandle handle,
                               uint32_t ownerdata = NULL);
   //处理
   virtual void processall();
   //取消注册事件处理函数
   virtual void unregisterhandle(const STRING& name,
                                 vengine_game::function_eventhandle handle,
                                 uint32_t ownerdata);
  //extends
 public:
   virtual void push(vengine_game::event_id::_enum id, float arg0);
   virtual void push(const STRING& eventname, std::vector<STRING> param);
   virtual void push(const STRING& eventname);
   virtual void push(const STRING& eventname, int32_t arg0);
   virtual void push(const STRING& eventname, float arg0);
   virtual void push(const STRING& eventname, const char* arg0);
   virtual void push(const STRING& eventname, 
                     const char* arg0, 
                     const char* arg1);
   virtual void push(const STRING& eventname,
                     const char* arg0,
                     const char* arg1,
                     int32_t arg2);
   virtual void push(const STRING& eventname,
                     int32_t arg0,
                     int32_t arg1);
   virtual void push(const STRING& eventname,
                     const char* arg0,
                     const char* arg1,
                     int32_t arg2,
                     int32_t arg3);
   virtual void push(const STRING& eventname,
                     const char* arg0,
                     const char* arg1,
                     const char* arg2);

 public:
   virtual void init(void*);
   virtual void release();
   virtual void tick();


 protected:
   static System* self_;
   std::map<STRING, vengine_game::eventdefine_t*> index_asname_map_;
   std::map<vengine_game::event_id::_enum, vengine_game::eventdefine_t*>
     index_asid_map_;
   std::list<vengine_game::event_t> queue_;
   std::list<vengine_game::event_t> delayquene_; //慢速队列
   uint32_t last_tickcount_;

 protected:
   void push(const vengine_game::event_t& event); //压入事件
   void process(const vengine_game::event_t& event); //处理事件

};

}; //namespace event

#endif //PAP_CLIENT_GAME_EVENT_SYSTEM_H_
