#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/editbox/multiline.h"

namespace vgui_luacontrol {

namespace window {

namespace editbox {

LuaPlus::LuaObject* MultiLine::metatable_ = NULL;

LuaPlus::LuaObject* MultiLine::get_metatable() {
  return metatable_;
}

int32_t MultiLine::lua_set_item_elementstring(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  CEGUI::FalagardMultiIMEEditBox* window = 
    dynamic_cast<CEGUI::FalagardMultiIMEEditBox>(window_);
  STRING mbcs = args[2].GetString();
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_elementonly_runtime(mbcs, str);
  window->setItemElementString(str);
  return 0;
}

int32_t MultiLine::lua_get_item_elementstring(LuaPlus::LuaState* luastate) {
  CEGUI::FalagardMultiIMEEditBox* window = 
    dynamic_cast<CEGUI::FalagardMultiIMEEditBox>(window_);
  CEGUI::String32 str = window->getItemElementString();
  STRING mbcs;
  vgui_string::System::getself()->parsestring_reverseruntime(str, mbcs);
  luastate->PushString(mbcs);
  return 1;
}

} //namespace editbox

} //namespace window

} //namespace vgui_luacontrol
