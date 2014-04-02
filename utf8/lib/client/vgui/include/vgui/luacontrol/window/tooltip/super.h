/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id super.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 14:52:32
 * @uses vgui luacontrol super tooltip window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_TOOLTIP_SUPER_H_
#define VGUI_LUACONTROL_WINDOW_TOOLTIP_SUPER_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace tooltip {

class Super : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_positionself(LuaPlus::LuaState* luastate);
   int32_t lua_modifywidth(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   Super(CEGUI::Window* window) : Base(window) {}
   virtual ~Super() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace tooltip

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_TOOLTIP_SUPER_H_
