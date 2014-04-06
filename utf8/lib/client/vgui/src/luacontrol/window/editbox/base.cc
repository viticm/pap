#include "FalIMEEditBox.h"
#include "vgui/string/system.h"
#include "vgui/luacontrol/window/editbox/base.h"

namespace vgui_luacontrol {

namespace window {

namespace editbox {

LuaPlus::LuaObject* Base::metatable_ = NULL;

LuaPlus::LuaObject* Base::get_metatable() {
  return metatable_;
}

int32_t Base::lua_set_item_elementstring(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  CEGUI::IFalagardIMEEditBox* window = 
    dynamic_cast<CEGUI::IFalagardIMEEditBox*>(
        dynamic_cast<CEGUI::FalagardIMEEditBox*>(window_));
  STRING mbcs = args[2].GetString();
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_elementonly_runtime(mbcs, str);
  window->setItemElementString(str);
  return 0;
}

int32_t Base::lua_setselected(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsInteger()) return 0;
  int32_t start = args[2].GetInteger();
  int32_t end = args[3].GetInteger();
  CEGUI::Editbox* window = dynamic_cast<CEGUI::Editbox*>(window_);
  if (-1 == end) end = static_cast<int32_t>(window->getText().length());
  window->setSelection(start, end);
  return 0;
}

int32_t Base::lua_set_blinktext(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (args[2].IsInteger()) {
    CEGUI::IFalagardIMEEditBox* window = 
      dynamic_cast<CEGUI::IFalagardIMEEditBox*>(
          dynamic_cast<CEGUI::FalagardIMEEditBox*>(window_));
    char value[128] = {0};
    snprintf(value, sizeof(value) - 1, "%d", args[2].GetInteger());
    CEGUI::String str;
    vgui_string::System::mbcs_to_utf8(value, str);
    window->setBlinkText(str);
  }
  return 0;
}

int32_t Base::lua_get_item_elementstring(LuaPlus::LuaState* luastate) {
  CEGUI::IFalagardIMEEditBox* window = 
    dynamic_cast<CEGUI::IFalagardIMEEditBox*>(
        dynamic_cast<CEGUI::FalagardIMEEditBox*>(window_));
  CEGUI::String32 str = window->getItemElementString();
  STRING mbcs;
  vgui_string::System::getself()->parsestring_reverseruntime(str, mbcs);
  luastate->PushString(mbcs.c_str());
  return 1;
}

} //namespace editbox

} //namespace window

} //namespace vgui_luacontrol
