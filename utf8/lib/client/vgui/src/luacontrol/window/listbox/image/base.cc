#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/listbox/image/base.h"

namespace vgui_luacontrol {

namespace window {

namespace listbox {

namespace image {

LuaPlus::LuaObject* Base::metatable_ = NULL;

LuaPlus::LuaObject* Base::get_metatable() {
  return metatable_;
}

int32_t Base::lua_additem(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsInteger()) return 0;
  CEGUI::String text;
  char value[128] = {0};
  snprintf(value, 
           sizeof(value) - 1, 
           "id=%d text=%s", 
           args[3].GetInteger(), 
           args[2].GetString());
  window->setProperty("AddItem", value);
  return 0;
}

} //namespace image

} //namespace listbox

} //namespace window

} //namespace vgui_luacontrol
