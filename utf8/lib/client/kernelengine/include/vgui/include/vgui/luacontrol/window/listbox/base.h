/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 13:53:12
 * @uses vgui luacontrol listbox window base class
 */
#ifndef VGUI_LUACONTROL_WINDOW_LISTBOX_BASE_H_
#define VGUI_LUACONTROL_WINDOW_LISTBOX_BASE_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace listbox {

class Base : public vgui_luacontrol::window::Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   virtual int32_t lua_additem(LuaPlus::LuaState* luastate);
   virtual int32_t lua_set_tagtext(LuaPlus::LuaState* luastate);
   virtual int32_t lua_set_item_tooptip(LuaPlus::LuaState* luastate);
   virtual int32_t lua_set_item_tooptip_state(LuaPlus::LuaState* luastate);
   virtual int32_t lua_set_itemtext(LuaPlus::LuaState* luastate);
   virtual int32_t lua_set_refindex(LuaPlus::LuaState* luastate);

   int32_t lua_deleteitem(LuaPlus::LuaState* luastate);
   int32_t lua_getitem(LuaPlus::LuaState* luastate);
   int32_t lua_clear(LuaPlus::LuaState* luastate);
   int32_t lua_getfirst_selectitem(LuaPlus::LuaState* luastate);
   int32_t lua_getfirst_selectitem_string(LuaPlus::LuaState* luastate);
   int32_t lua_setfirst_selectitem_string(LuaPlus::LuaState* luastate);
   int32_t lua_set_itemselect(LuaPlus::LuaState* luastate);
   int32_t lua_set_itemselect_byid(LuaPlus::LuaState* luastate);
   int32_t lua_clear_allselections(LuaPlus::LuaState* luastate);
   int32_t lua_get_mousemove_item(LuaPlus::LuaState* luastate);

 protected:
   friend class vgui_luacontrol::window::Base;
   Base(CEGUI::Window* window) : vgui_luacontrol::window::Base(window) {}
   virtual ~Base() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace listbox

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_LISTBOX_BASE_H_
