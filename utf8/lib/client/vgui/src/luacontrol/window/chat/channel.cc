#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/chat/channel.h"

namespace vgui_luacontrol {

namespace window {

namespace chat {

LuaPlus::LuaObject* Channel::metatable_ = NULL;

LuaPlus::LuaObject* Channel::get_metatable() {
  return metatable_;
}

int32_t Channel::lua_clearall(LuaPlus::LuaState* luastate) {
  (dynamic_cast<CEGUI::IFalagardChatChannel*>(
    dynamic_cast<CEGUI::FalagardChatChannel*>(window_)))->clearAllChannel();
  return 0;
}

int32_t Channel::lua_add(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsString() || !args[4].IsString())
    return 0;
  STRING mbcs_type = args[2].GetString();
  CEGUI::String32 type;
  vgui_string::System::getself()->parsestring_runtime(mbcs_type, type);

  STRING mbcs_iconname = args[3].GetString();
  CEGUI::String32 iconname;
  vgui_string::System::getself()->parsestring_runtime(mbcs_iconname, iconname);

  STRING mbcs_name = args[4].GetString();
  CEGUI::String32 name;
  vgui_string::System::getself()->parsestring_runtime(mbcs_name, name);
  (dynamic_cast<CEGUI::IFalagardChatChannel*>(
    dynamic_cast<CEGUI::FalagardChatChannel*>(window_)))->addChannel(
      type.c_str(),
      iconname.c_str(),
      name.c_str());
  return 0;
}

} //namespace chat

} //namespace window

} //namespace vgui_luacontrol
