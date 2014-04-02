/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-1 20:16:52
 * @uses vgui luacontrol for window base module
 */
#ifndef VGUI_LUACONTROL_WINDOW_BASE_H_
#define VGUI_LUACONTROL_WINDOW_BASE_H_

#include "vgui/config.h"
#include "CEGUIWindow.h"
#include "LuaPlus.h"
#include "vengine/game/action/system.h"

namespace vgui_luacontrol {

namespace window { //特别说明大的命名空间中建议嵌套的子命名空间数 <= 3

class Base {

 public:
   Base(CEGUI::Window* window);
   virtual ~Base() {}

 public:
   static Base* create(CEGUI::Window* window);
   static void destroy(CEGUI::Window* window);

 public:
   static void register_metatable();
   static void destroy_metatable();
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_setproperty(LuaPlus::LuaState* luastate);
   int32_t lua_getproperty(LuaPlus::LuaState* luastate);
   int32_t lua_setevent(LuaPlus::LuaState* luastate);
   int32_t lua_gettype(LuaPlus::LuaState* luastate);
   int32_t lua_getname(LuaPlus::LuaState* luastate);
   int32_t lua_gettext(LuaPlus::LuaState* luastate);
   int32_t lua_settext(LuaPlus::LuaState* luastate);
   int32_t lua_set_textoriginal(LuaPlus::LuaState* luastate);
   int32_t lua_transtext(LuaPlus::LuaState* luastate);
   int32_t lua_setforce(LuaPlus::LuaState* luastate);
   //设置显示区域并设置材质坐标
   int32_t lua_setarea_and_texturecoord(LuaPlus::LuaState* luastate);
   int32_t lua_show(LuaPlus::LuaState* luastate);
   int32_t lua_hide(LuaPlus::LuaState* luastate);
   int32_t lua_disable(LuaPlus::LuaState* luastate);
   int32_t lua_enable(LuaPlus::LuaState* luastate);
   int32_t lua_setalpha(LuaPlus::LuaState* luastate);
   int32_t lua_isvisiable(LuaPlus::LuaState* luastate);
   int32_t lua_set_tooltip(LuaPlus::LuaState* luastate);
   int32_t lua_captureinput(LuaPlus::LuaState* luastate);
   int32_t lua_center(LuaPlus::LuaState* luastate);
   int32_t lua_setcenter(LuaPlus::LuaState* luastate);
   int32_t lua_setclipped_byparent(LuaPlus::LuaState* luastate);
   int32_t lua_auto_mouseposition(LuaPlus::LuaState* luastate);
   int32_t lua_createchild(LuaPlus::LuaState* luastate);
   int32_t lua_removechild(LuaPlus::LuaState* luastate);
   int32_t lua_debuginfo(LuaPlus::LuaState* luastate);
   int32_t lua_getposition(LuaPlus::LuaState* luastate);
   int32_t lua_setposition(LuaPlus::LuaState* luastate);

 protected:
   CEGUI::Window* window_;
   static LuaPlus::LuaObject* metatable_; //元表

};

}

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_BASE_H_
