/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 15:16:00
 * @uses vgui luacontrol scene map window base class
 */
#ifndef VGUI_LUACONTROL_WINDOW_MAP_SCENE_BASE_H_
#define VGUI_LUACONTROL_WINDOW_MAP_SCENE_BASE_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace map {

namespace scene {

class Base : public vgui_luacontrol::window::Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_update_viewrect(LuaPlus::LuaState* luastate);
   int32_t lua_set_filename(LuaPlus::LuaState* luastate);
   int32_t lua_closeit(LuaPlus::LuaState* luastate);
   int32_t lua_get_mouseposition(LuaPlus::LuaState* luastate);
   int32_t lua_update(LuaPlus::LuaState* luastate);
   int32_t lua_set_zoommode(LuaPlus::LuaState* luastate); 
   int32_t lua_move_bydirection(LuaPlus::LuaState* luastate);
   int32_t lua_add_teamplayer_position(LuaPlus::LuaState* luastate);

 public:
   const char* get_filepostfix(const char* filename);

 protected:
   friend class vgui_luacontrol::window::Base;
   Base(CEGUI::Window* window) : vgui_luacontrol::window::Base(window) {}
   virtual ~Base() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

};

}; //namespace map

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_MAP_SCENE_BASE_H_
