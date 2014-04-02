/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 14:31:02
 * @uses vgui luacontrol scroll bar window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_SCROLL_BAR_H_
#define VGUI_LUACONTROL_WINDOW_SCROLL_BAR_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace scroll {

class Bar : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_getposition(LuaPlus::LuaState* luastate);
   int32_t lua_setposition(LuaPlus::LuaState* luastate);

 protected:
   friend class vgui_luacontrol::window::Base;
   Bar(CEGUI::Window* window) : Base(window) {}
   virtual Bar() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace scroll

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_SCROLL_BAR_H_
