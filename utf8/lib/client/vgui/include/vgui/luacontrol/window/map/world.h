/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id world.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 15:30:20
 * @uses vgui luacontrol world map window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_MAP_WORLD_H_
#define VGUI_LUACONTROL_WINDOW_MAP_WORLD_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace map {

class World : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_init(LuaPlus::LuaState* luastate);
   int32_t lua_update(LuaPlus::LuaState* luastate);
   int32_t lua_getcurrent_selectscene(LuaPlus::LuaState* luastate);
   int32_t lua_set_cityhover(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   World(CEGUI::Window* window) : Base(window) {}
   virtual ~World() {}

 protected:
   void updateplayer();
   CEGUI::String get_scenename(int32_t id);

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace map

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_MAP_WORLD_H_
