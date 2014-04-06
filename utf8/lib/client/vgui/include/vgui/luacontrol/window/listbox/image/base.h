/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 14:07:43
 * @uses vgui luacontrol image listbox base class
 */
#ifndef VGUI_LUACONTROL_WINDOW_LISTBOX_IMAGE_BASE_H_
#define VGUI_LUACONTROL_WINDOW_LISTBOX_IMAGE_BASE_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"
#include "vgui/luacontrol/window/listbox/base.h"


namespace vgui_luacontrol {

namespace window {

namespace listbox {

namespace image {

class Base : public vgui_luacontrol::window::listbox::Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 protected:
   virtual int32_t lua_additem(LuaPlus::LuaState* luastate);

 protected:
   friend class vgui_luacontrol::window::Base;
   Base(CEGUI::Window* window) : 
     vgui_luacontrol::window::listbox::Base(window) {}
   virtual ~Base() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace image

}; //namespace listbox

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_LISTBOX_IMAGE_BASE_H_
