/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id check.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 12:01:38
 * @uses vgui luacontrol check button window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_BUTTON_CHECK_H_
#define VGUI_LUACONTROL_WINDOW_BUTTON_CHECK_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace button {

class Check : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_set(LuaPlus::LuaState* luastate);
   int32_t lua_get(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   Check(CEGUI::Window* window) : Base(window) {}
   virtual ~Check() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace button

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_BUTTON_CHECK_H_
