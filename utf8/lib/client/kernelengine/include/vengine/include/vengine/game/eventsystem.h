/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id eventsystem.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-25 16:21:53
 * @uses vengine game event system class
 */
#ifndef VENGINE_GAME_EVENTSYSTEM_H_
#define VENGINE_GAME_EVENTSYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

namespace vengine_game {

//引用本模块event_id
namespace event_id {

enum _enum;

}; //namespace event_id

struct event_t;
typedef void (__stdcall* function_eventhandle)
  (const event_t* event, uint32_t ownerdata);

typedef struct {
  typedef std::list<std::pair<function_eventhandle, uint32_t> > registerstruct;
  event_id::_enum id;
  const char* event;
  bool delayprocess;
  registerstruct listenfunction_notify; //监听方法
} eventdefine_t;

struct event_t {
  eventdefine_t* eventdefine;
  std::vector<STRING> args;
  bool operator == (const event_t& other) {
    if (other.eventdefine != eventdefine) return false;
    if (other.args.size() != args.size()) return false;
    register size_t i;
    for (i = 0; i < args.size(); ++i) {
      if (other.args[i] != args[i]) return false;
    }
    return true;
  }
};

class VENGINE_API EventSystem : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(vengine_game_EventSystem);

 public:
   virtual void push(vengine_game::event_id::_enum id, 
                     std::vector<STRING> param) = 0;
   virtual void push(event_id::_enum id) = 0;
   virtual void push(event_id::_enum id, int32_t arg0) = 0;
   virtual void push(event_id::_enum id, const char* arg0) = 0;
   virtual void push(event_id::_enum id, 
                     const char* arg0, 
                     const char* arg1) = 0;
   virtual void push(event_id::_enum id,
                     const char* arg0,
                     const char* arg1,
                     int32_t arg2) = 0;
   virtual void push(event_id::_enum id,
                     int32_t arg0,
                     int32_t arg1) = 0;
   virtual void push(event_id::_enum id,
                     const char* arg0,
                     const char* arg1,
                     int32_t arg2,
                     int32_t arg3) = 0;
   virtual void push(event_id::_enum id,
                     const char* arg0,
                     const char* arg1,
                     const char* arg2) = 0;
   //注册事件处理函数
   virtual void registerhandle(const STRING& name,
                               function_eventhandle handle,
                               uint32_t ownerdata = NULL) = 0;
   //处理
   virtual void processall() = 0;
   //取消注册事件处理函数
   virtual void unregisterhandle(const STRING& name,
                                 function_eventhandle handle,
                                 uint32_t ownerdata) = 0;

};

}; //namespace vengine_game

#endif //VENGINE_GAME_EVENTSYSTEM_H_
