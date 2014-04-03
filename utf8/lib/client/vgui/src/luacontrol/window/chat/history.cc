#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/chat/history.h"

namespace vgui_luacontrol {

namespace window {

namespace chat {

LuaPlus::LuaObject* History::metatable_ = NULL;

LuaPlus::LuaObject* History::get_metatable() {
  return metatable_;
}

int32_t History::lua_insertstring(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  STRING mbcs = args[2].GetString();
  STRING::size_type start = mbcs.find("#aB");
  STRING::size_type end = mbcs.find("#aE");
  int32_t talkerlength = end - start - 3;
  talkerlength = (talkerlength - 2) / 2 + 2;
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  (dynamic_cast<CEGUI::IFalagardChatHistory*>(
    dynamic_cast<CEGUI::FalagardChatHistory*>(window_)))
    ->insertChatString(-1, str, talkerlength);
  return 0;
}

int32_t History::lua_remove_allstring(LuaPlus::LuaState* luastate) {
  (dynamic_cast<CEGUI::IFalagardChatHistory*>(
    dynamic_cast<CEGUI::FalagardChatHistory*>(window_)))
    ->removeAllChatStrings();
  return 0;
}

int32_t History::lua_scroll_toend(LuaPlus::LuaState* luastate) {
  (dynamic_cast<CEGUI::IFalagardChatHistory*>(
    dynamic_cast<CEGUI::FalagardChatHistory*>(window_)))
    ->scrollToEnd();
  return 0;
}

int32_t History::lua_extend_clearregion(LuaPlus::LuaState* luastate) {
  (dynamic_cast<CEGUI::IFalagardChatHistory*>(
    dynamic_cast<CEGUI::FalagardChatHistory*>(window_)))
    ->extendClearRegion();
  return 0;
}

} //namespace chat

} //namespace window

} //namespace vgui_luacontrol
