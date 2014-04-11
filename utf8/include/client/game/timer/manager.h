/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-11 17:49:31
 * @uses pap client game timer manager
 *       cn: 定时器管理器
 */
#ifndef PAP_CLIENT_GAME_TIMER_MANAGER_H_
#define PAP_CLIENT_GAME_TIMER_MANAGER_H_

#include "client/game/timer/system.h"

namespace timer {

struct param1_t {
  timer_function function;
  uint32_t id;
};

struct param2_t {
  STRING function;
  STRING environment;
  uint32_t id;
};

class Manager : public System {

VENGINE_KERNEL_DECLARE_DYNAMIC(Manager);

 public:
   Manager();
   ~Manager();

 public: //implement from abstract
   virtual int32_t add(timer_function, uint32_t elapse);
   virtual int32_t add(const STRING& environment, 
                       const STRING& function, 
                       uint32_t elapse); 
   virtual void remove(uint32_t id);
   virtual void remove(timer_function function);
   virtual void remove(const STRING& function);
   virtual void clear(); //清除所有

 public:
   void init(void*);
   static Manager* getself();
   void get_scriptenvironment(uint32_t id, STRING& environment, STRING& script);

 public:
   int32_t lua_set(LuaPlus::LuaState* luastate);
   int32_t lua_kill(LuaPlus::LuaState* luastate);

 protected:
   typedef std::map<uint32_t, param1_t>::iterator param1_iterator;
   typedef std::map<uint32_t, param2_t>::iterator param2_iterator;

 private:
   std::map<uint32_t, param1_t> map1_;
   std::map<uint32_t, param2_t> map2_;
   static Manager* self_;
   //默认的事件处理函数
   static void __stdcall default_eventfunction(
       HWND, uint32_t, uint32_t, uint64_t);

};

}; //namespace timer

#endif //PAP_CLIENT_GAME_TIMER_MANAGER_H_
