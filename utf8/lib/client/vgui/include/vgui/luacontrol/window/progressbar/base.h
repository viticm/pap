/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 10:55:19
 * @uses vgui lua control progress bar base window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_PROGRESSBAR_BASE_H_
#define VGUI_LUACONTROL_WINDOW_PROGRESSBAR_BASE_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace progressbar {

class Base : public vgui_luacontrol::window::Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t setprogress(LuaPlus::LuaState* luastate);

 protected:
   friend class vgui_luacontrol::window::Base;
   Base(CEGUI::Window* window) : vgui_luacontrol::window::Base(window) {}
   virtual ~Base() {};

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace progressbar

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_PROGRESSBAR_BASE_H_
