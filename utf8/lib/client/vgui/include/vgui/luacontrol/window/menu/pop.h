/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-11 10:12:52
 * @uses luacontrol pop menu window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_MENU_POP_H_
#define VGUI_LUACONTROL_WINDOW_MENU_POP_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace menu {

class Pop : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public: //for export
   int32_t lua_openit(LuaPlus::LuaState* luastate);
   int32_t lua_closeit(LuaPlus::LuaState* luastate);
   int32_t lua_setposition(LuaPlus::LuaState* luastate);

 protected:
   Pop(CEGUI::Window* window) : Base(window) {}
   virtual ~Pop() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace menu

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_MENU_POP_H_
