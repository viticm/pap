/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id mini.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 15:25:34
 * @uses vgui luacontrol mini scene map window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_MAP_SCENE_MINI_H_
#define VGUI_LUACONTROL_WINDOW_MAP_SCENE_MINI_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace map {

namespace scene {

class Mini : public vgui_luacontrol::window::Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_updateflag(LuaPlus::LuaState* luastate);

 public:
   const char* get_filepostfix(const char* filename);

 protected:
   friend class vgui_luacontrol::window::Base;
   Mini(CEGUI::Window* window) : vgui_luacontrol::window::Base(window) {}
   virtual ~Mini() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace scene

}; //namespace map

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_MAP_SCENE_MINI_H_
