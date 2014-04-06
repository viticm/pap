#include "FalagardScrollInfo.h"
#include "vgui/string/system.h"
#include "vgui/luacontrol/window/scroll/info.h"

namespace vgui_luacontrol {

namespace window {

namespace scroll {

LuaPlus::LuaObject* Info::metatable_ = NULL;

LuaPlus::LuaObject* Info::get_metatable() {
  return metatable_;
}

int32_t Info::lua_set(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  CEGUI::IFalagardScrollInfo* window = 
    dynamic_cast<CEGUI::IFalagardScrollInfo*>(
        dynamic_cast<CEGUI::FalagardScrollInfo*>(window_));
  STRING mbcs = args[2].GetString();
  STRING use_defaultcolor;
  if (args[3].IsString()) {
    use_defaultcolor = args[3].GetString();
  }
  else {
    use_defaultcolor = "0";
  }

  CEGUI::String32 str;
  if ("0" == use_defaultcolor) {
    str += 0xFBFFFFFF;
  }
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  window->setWaitingInfo(str);
  return 0;
}

} //namespace scroll

} //namespace window

} //namespace vgui_luacontrol
