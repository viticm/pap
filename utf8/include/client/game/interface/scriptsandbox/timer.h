/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id timer.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-11 17:49:31
 * @uses pap client game timer manager lua exports
 */
#ifndef PAP_CLIENT_GAME_INTERFACE_SCRIPTSANDBOX_TIMER_H_
#define PAP_CLIENT_GAME_INTERFACE_SCRIPTSANDBOX_TIMER_H_

#include "LuaPlus.h"

namespace interface {

namespace timer {

int32_t lua_set(LuaPlus::LuaState* luastate);
int32_t lua_kill(LuaPlus::LuaState* luastate);
int32_t lua_clear(LuaPlus::LuaState* luastate);

}; //namespace timer

}; //namespace interface

#endif //PAP_CLIENT_GAME_INTERFACE_SCRIPTSANDBOX_TIMER_H_
