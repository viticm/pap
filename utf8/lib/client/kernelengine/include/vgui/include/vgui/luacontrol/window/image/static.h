/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id static.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 14:25:14
 * @uses vgui luacontrol static image window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_IMAGE_STATIC_H_
#define VGUI_LUACONTROL_WINDOW_IMAGE_STATIC_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace image {

class Static : public vgui_luacontrol::window::Base {
 
 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_set(LuaPlus::LuaState* luastate);
   int32_t lua_setcolor(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   Static(CEGUI::Window* window) : Base(window) {}
   virtual ~Static() {}

 protected:   
   static LuaPlus::LuaObject* metatable_;


};

}; //namespace image

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_IMAGE_STATIC_H_
