#include "CEGUIPropertyHelper.h"
#include "vgui/luacontrol/window/button/check.h"

namespace vgui_luacontrol {

namespace window {

namespace button {

LuaPlus::LuaObject* Check::metatable_ = NULL; 

LuaPlus::LuaObject* Check::get_metatable() {
  return metatable_;
}

int32_t Check::lua_set(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  if (1 == args[2].GetInteger()) {
    window_->setProperty("Selected", "True");
  }
  else {
    window_->setProperty("Selected", "False");
  }
  return 0;
}

int32_t Check::lua_get(LuaPlus::LuaState* luastate) {
  if (CEGUI::PropertyHelper::stringToBool(window_->getProperty("Selected"))) {
    luastate->PushInteger(1);
  }
  else {
    luastate->PushInteger(0);
  }
  return 1;
}


int32_t lua_get(LuaPlus::LuaState* luastate);

} //namepsace button

} //namespace window

} //namespace vgui_luacontrol