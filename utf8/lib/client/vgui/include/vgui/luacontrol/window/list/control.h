/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id control.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 15:37:47
 * @uses vgui luacontrol control info window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_LIST_INFO_H_
#define VGUI_LUACONTROL_WINDOW_LIST_INFO_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace list {

class Control : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_addcolumn(LuaPlus::LuaState* luastate);
   int32_t lua_insertcolumn(LuaPlus::LuaState* luastate);
   int32_t lua_add_newitem(LuaPlus::LuaState* luastate);
   int32_t lua_set_itemtext(LuaPlus::LuaState* luastate);
   int32_t lua_set_itemdata(LuaPlus::LuaState* luastate);
   int32_t lua_deleteitem(LuaPlus::LuaState* luastate);
   int32_t lua_remove_allitem(LuaPlus::LuaState* luastate);
   int32_t lua_removecolumn(LuaPlus::LuaState* luastate);
   int32_t lua_get_itemtext(LuaPlus::LuaState* luastate);
   int32_t lua_get_itemcount(LuaPlus::LuaState* luastate);
   int32_t lua_get_columncount(LuaPlus::LuaState* luastate);
   int32_t lua_get_selectitem(LuaPlus::LuaState* luastate);
   int32_t lua_set_selectitem(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   Control(CEGUI::Window* window) : Base(window) {}
   virtual ~Control() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace list

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_LIST_INFO_H_
