#include "elements/CEGUIScrollbar.h"
#include "vgui/luacontrol/window/scroll/bar.h"

namespace vgui_luacontrol {

namespace window {

namespace scroll {

LuaPlus::LuaObject* Bar::metatable_ = NULL;

LuaPlus::LuaObject* Bar::get_metatable() {
  return metatable_;
}

int32_t Bar::lua_getposition(LuaPlus::LuaState* luastate) {
  luastate->PushNumber(
      (dynamic_cast<CEGUI::Scrollbar*>(window_))->getScrollPosition());
  return 0;
}

int32_t Bar::lua_setposition(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsNumber()) return 0;
  (dynamic_cast<CEGUI::Scrollbar*>(window_))
    ->setScrollPosition(args[2].GetFloat());
  return 0;
}

} //namespace scroll

} //namespace window

} //namespace vgui_luacontrol
