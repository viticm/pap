/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id info.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 15:37:47
 * @uses vgui luacontrol list info window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_LIST_INFO_H_
#define VGUI_LUACONTROL_WINDOW_LIST_INFO_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace list {

class Info : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_add(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   Info(CEGUI::Window* window) : Base(window) {}
   virtual ~Info() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace list

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_LIST_INFO_H_
