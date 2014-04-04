#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/softkey.h"

namespace vgui_luacontrol {

namespace window {

LuaPlus::LuaObject* SoftKey::metatable_ = NULL;

LuaPlus::LuaObject* SoftKey::get_metatable() {
  return metatable_;
}

int32_t SoftKey::lua_setaim_editbox(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  CEGUI::IFalagardSoftKeyBoard* window = 
    dynamic_cast<CEGUI::IFalagardSoftKeyBoard*>(
      dynamic_cast<CEGUI::FalagardSoftKeyBoard*>(window_));
  window->SetActiveEditBox(args[2].GetString());
  return 0;
}

} //namespace window

} //namespace vgui_luacontrol
