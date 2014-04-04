#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/list/info.h"

namespace vgui_luacontrol {

namespace window {

namespace list {

LuaPlus::LuaObject* Info::metatable_ = NULL;

LuaPlus::LuaObject* Info::get_metatable() {
  return metatable_;
}

int32_t Info::lua_add(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  STRING mbcs = args[2].GetString();
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  (dynamic_cast<CEGUI::IFalagardInfoList*>(
    dynamic_cast<CEGUI::FalagardInfoList*>(window_)))->AddInfo(str);
  return 0;
}

} //namespace list

} //namespace window

} //namespace vgui_luacontrol
