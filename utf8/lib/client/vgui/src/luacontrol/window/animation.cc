#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/animation.h"

namespace vgui_luacontrol {

namespace window {

LuaPlus::LuaObject* Animation::metatable_ = NULL;

LuaPlus::LuaObject* Animation::get_metatable() {
  return metatable_;
}

int32_t Animation::lua_play(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsBoolean()) return 0;
  CEGUI::IFalagardAnimate* window = dynamic_cast<CEGUI::IFalagardAnimate*>(
      dynamic_cast<CEGUI::FalagardAnimate*>(window_));
  window->Play(args[2].GetBoolean());
  return 0;
}

} //namespace window

} //namespace vgui_luacontrol
