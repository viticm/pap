/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-11 17:49:31
 * @uses pap client game timer system
 */
#ifndef PAP_CLIENT_GAME_TIMER_SYSTEM_H_
#define PAP_CLIENT_GAME_TIMER_SYSTEM_H_

#include "vengine/kernel/node.h"

namespace LuaPlus {
class LuaState;
class LuaObject;
}; //namespace LuaPlus

namespace timer {

typedef void (__stdcall* timer_function)(HWND, UINT, UINT, DWORD);

class System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(timer_System);

 public:
   virtual int32_t add(timer_function, uint32_t elapse) = 0;
   virtual int32_t add(const STRING& environment, 
                       const STRING& function, 
                       uint32_t elapse) = 0; 
   virtual void remove(uint32_t id) = 0;
   virtual void remove(timer_function function) = 0;
   virtual void remove(const STRING& function) = 0;
   virtual void clear() = 0; //清除所有

};

}; //namespace timer

#endif //PAP_CLIENT_GAME_TIMER_SYSTEM_H_
