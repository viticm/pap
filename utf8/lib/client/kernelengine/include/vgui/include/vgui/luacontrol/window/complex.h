/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id complex.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 13:43:05
 * @uses vgui luacontrol complex window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_COMPLEX_H_
#define VGUI_LUACONTROL_WINDOW_COMPLEX_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

class Complex : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_add_chatboard_element(LuaPlus::LuaState* luastate);
   int32_t lua_add_textelement(LuaPlus::LuaState* luastate);
   int32_t lua_add_optionelement(LuaPlus::LuaState* luastate);
   int32_t lua_add_moneyelement(LuaPlus::LuaState* luastate);
   int32_t lua_add_impactelement(LuaPlus::LuaState* luastate);
   int32_t lua_add_actionelement(LuaPlus::LuaState* luastate);
   int32_t lua_clean_allelement(LuaPlus::LuaState* luastate);
   int32_t lua_set_textcolor(LuaPlus::LuaState* luastate); //设置字体颜色
   int32_t lua_pageend(LuaPlus::LuaState* luastate);
   int32_t lua_add_itemelement(LuaPlus::LuaState* luastate);
   int32_t lua_setcolor(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   Complex(CEGUI::Window* window) : Base(window) {}
   virtual ~Complex() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_COMPLEX_H_
