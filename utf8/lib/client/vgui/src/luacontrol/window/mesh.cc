#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/mesh.h"

namespace vgui_luacontrol {

namespace window {

LuaPlus::LuaObject* Mesh::metatable_ = NULL;

LuaPlus::LuaObject* Mesh::get_metatable() {
  return metatable_;
}

int32_t Mesh::lua_set_fakeobject(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  int32_t windowwidth = window_->getAbsoluteWidth();
  int32_t windowheight = window_->getAbsoluteHeight();
  int32_t temp = 1;
  while (std::pow(2.f, temp) < windowwidth) ++temp;
  windowwidth = std::pow(2.f, temp);
  temp = 1;
  while (std::pow(2.f, temp) < windowheight) ++temp;
  windowheight = std::pow(2.f, temp);
  //通知FakeObject系统
  g_game_fake_objectsystem->on_ui_hook(
      window_->getName().c_str(),
      args[2].GetString(),
      windowwidth,
      windowheight,
      window_->->getProperty("BackgroundName").c_str());
  //通知UI
  window_->setProperty("FakeObject", args[2].GetString());
  return 0;
}

int32_t Mesh::lua_rotatestart(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsNumber()) return 0;
  float angle = args[2].GetFloat();
  //通知FakeObject系统
  g_game_fake_objectsystem->rotatestart(
      window_->getProperty("FakeObject").c_str(),
      angle);
  return 0;
}

int32_t Mesh::lua_rotateend(LuaPlus::LuaState* luastate) {
  g_game_fake_objectsystem->rotateend(
      window_->getProperty("FakeObject").c_str());
  return 0;
}

int32_t Mesh::lua_get_objectname(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  luastate->PushString("CreateRole_Man");
  return 1;
}

int32_t Mesh::lua_set_unfake_object(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  g_game_fake_objectsystem->on_ui_unhook(args[2].GetString());
  return 0;
}

} //namespace window

} //namespace vgui_luacontrol
