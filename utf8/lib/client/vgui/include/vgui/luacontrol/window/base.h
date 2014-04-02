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
   int32_t setproperty(LuaPlus::LuaState* luastate);
   int32_t getproperty(LuaPlus::LuaState* luastate);
   int32_t setevent(LuaPlus::LuaState* luastate);
   int32_t gettype(LuaPlus::LuaState* luastate);
   int32_t getname(LuaPlus::LuaState* luastate);
   int32_t gettext(LuaPlus::LuaState* luastate);
   int32_t settext(LuaPlus::LuaState* luastate);
   int32_t set_textoriginal(LuaPlus::LuaState* luastate);
   int32_t transtext(LuaPlus::LuaState* luastate);
   int32_t setforce(LuaPlus::LuaState* luastate);
   //设置显示区域并设置材质坐标
   int32_t setarea_and_texturecoord(LuaPlus::LuaState* luastate);
   int32_t show(LuaPlus::LuaState* luastate);
   int32_t hide(LuaPlus::LuaState* luastate);
   int32_t disable(LuaPlus::LuaState* luastate);
   int32_t enable(LuaPlus::LuaState* luastate);
   int32_t setalpha(LuaPlus::LuaState* luastate);
   int32_t isvisiable(LuaPlus::LuaState* luastate);
   int32_t set_tooltip(LuaPlus::LuaState* luastate);
   int32_t captureinput(LuaPlus::LuaState* luastate);
   int32_t center(LuaPlus::LuaState* luastate);
   int32_t setcenter(LuaPlus::LuaState* luastate);
   int32_t setclipped_byparent(LuaPlus::LuaState* luastate);
   int32_t auto_mouseposition(LuaPlus::LuaState* luastate);
   int32_t createchild(LuaPlus::LuaState* luastate);
   int32_t removechild(LuaPlus::LuaState* luastate);
   int32_t debuginfo(LuaPlus::LuaState* luastate);
   int32_t getposition(LuaPlus::LuaState* luastate);
   int32_t setposition(LuaPlus::LuaState* luastate);

 protected:
   CEGUI::Window* window_;
   static LuaPlus::LuaObject* metatable_; //元表

};

}

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_BASE_H_
