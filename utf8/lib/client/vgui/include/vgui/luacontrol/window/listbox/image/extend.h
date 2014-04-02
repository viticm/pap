/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id extend.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 14:13:59
 * @uses vgui luacontrol image listbox extend class
 */
#ifndef VGUI_LUACONTROL_WINDOW_LISTBOX_IMAGE_EXTEND_H_
#define VGUI_LUACONTROL_WINDOW_LISTBOX_IMAGE_EXTEND_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"


namespace vgui_luacontrol {

namespace window {

namespace listbox {

namespace image {

class Extend : public vgui_luacontrol::window::listbox::Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 protected:
   virtual lua_additem(LuaPlus::LuaState* luastate);

 protected:
   friend class vgui_luacontrol::window::Base;
   Extend(CEGUI::Window* window) : 
     vgui_luacontrol::window::listbox::Base(window) {}
   virtual ~Extend() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace image

}; //namespace listbox

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_LISTBOX_IMAGE_EXTEND_H_
