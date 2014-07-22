/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id animation.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 15:58:58
 * @uses vgui luacontrol animation window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_ANIMATION_H_
#define VGUI_LUACONTROL_WINDOW_ANIMATION_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

class Animation : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_play(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   Animation(CEGUI::Window* window) : Base(window) {}
   virtual ~Animation() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

}; 

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_ANIMATION_H_
