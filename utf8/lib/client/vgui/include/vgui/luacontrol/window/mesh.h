/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id mesh.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 14:58:33
 * @uses vgui luacontrol mesh window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_MESH_H_
#define VGUI_LUACONTROL_WINDOW_MESH_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

class Mesh : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_set_fakeobject(LuaPlus::LuaState* luastate);
   int32_t lua_rotatestart(LuaPlus::LuaState* luastate);
   int32_t lua_rotateend(LuaPlus::LuaState* luastate);
   int32_t lua_get_objectname(LuaPlus::LuaState* luastate);
   int32_t lua_set_unfake_object(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   Mesh(CEGUI::Window* window) : Base(window) {}
   virtual ~Mesh() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_MESH_H_
