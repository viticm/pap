/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-11 10:12:52
 * @uses vgui base config and global set
 */
#ifndef VGUI_LUACONTROL_WINDOW_TREE_H_
#define VGUI_LUACONTROL_WINDOW_TREE_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

class Tree : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_clear(LuaPlus::LuaState* luastate);
   int32_t lua_additem(LuaPlus::LuaState* luastate);
   int32_t lua_getfirst_selectitem(LuaPlus::LuaState* luastate);
   int32_t lua_getfirst_selectitem_string(LuaPlus::LuaState* luastate);
   int32_t lua_setfirst_selectitem_string(LuaPlus::LuaState* luastate);
   int32_t lua_setitem_select_byid(LuaPlus::LuaState* luastate);
   int32_t lua_setitem_toggle(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   Tree(CEGUI::Window* window) : Base(window) {}
   virtual ~Tree() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_TREE_H_
