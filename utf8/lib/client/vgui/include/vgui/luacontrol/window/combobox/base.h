/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 14:18:21
 * @uses vgui luacontrol combobox window base class
 */
#ifndef VGUI_LUACONTROL_WINDOW_COMBOBOX_BASE_H_
#define VGUI_LUACONTROL_WINDOW_COMBOBOX_BASE_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace combobox {

class Base : public vgui_luacontrol::window::Base {
  
 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_additem(LuaPlus::LuaState* luastate);
   int32_t lua_resetlist(LuaPlus::LuaState* luastate);
   int32_t lua_get_currentselect(LuaPlus::LuaState* luastate);
   int32_t lua_set_currentselect(LuaPlus::LuaState* luastate);

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace combobox

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_COMBOBOX_BASE_H_
