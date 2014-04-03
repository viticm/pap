#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/listbox/image/extend.h"

namespace vgui_luacontrol {

namespace window {

namespace listbox {

namespace image {

LuaPlus::LuaObject* Extend::metatable_ = NULL;

LuaPlus::LuaObject* Extend::get_metatable() {
  return metatable_;
}

int32_t Base::lua_additem(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsInteger() || !args[4].IsInteger()) 
    return 0;
  CEGUI::String text;
  char value[128] = {0};
  snprintf(value, 
           sizeof(value) - 1, 
           "id=%d state=%d text=%s", 
           args[3].GetInteger(),
           args[4].GetInteger(),
           args[2].GetString());
  STRING mbcs = value;
  CEGUI::String str;
  vgui_string::System::mbcs_to_utf8(mbcs, str);
  window->setProperty("AddItem", str);
  return 0;
}

} //namespace image

} //namespace listbox

} //namespace window

} //namespace vgui_luacontrol
