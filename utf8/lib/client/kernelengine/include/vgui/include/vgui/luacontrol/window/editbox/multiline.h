/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id multiline.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 16:10:29
 * @uses vgui luacontrol multiline editbox window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_EDITBOX_MULTILINE_H_
#define VGUI_LUACONTROL_WINDOW_EDITBOX_MULTILINE_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace editbox {

class MultiLine : public vgui_luacontrol::window::Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_set_item_elementstring(LuaPlus::LuaState* luastate);
   int32_t lua_get_item_elementstring(LuaPlus::LuaState* luastate);

 protected:
   friend class vgui_luacontrol::window::Base;
   MultiLine(CEGUI::Window* window) : vgui_luacontrol::window::Base(window) {}
   virtual ~MultiLine() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace editbox

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_EDITBOX_MULTILINE_H_
