#include "vgui/luacontrol/window/menu/pop.h"

namespace vgui_luacontrol {

namespace window {

namespace menu {

LuaPlus::LuaObject* Pop::metatable_ = NULL;

LuaPlus::LuaObject* Pop::get_metatable() {
  return metatable_;
}

int32_t Pop::lua_openit(LuaPlus::LuaState* luastate) {
  (dynamic_cast<CEGUI::PopupMenu*>(window_))->openPopupMenu();
  return 0;
}

int32_t Pop::lua_closeit(LuaPlus::LuaState* luastate) {
  (dynamic_cast<CEGUI::PopupMenu*>(window_))->closePopupMenu();
  return 0;
}

int32_t Pop::lua_setposition(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsString()) return 0;
  float x = args[2].GetFloat();
  float y = args[3].GetFloat();
  //重新计算
  float width = window_->getAbsoluteWidth();
  float height = window_->getAbsoluteHeight();
  float screenwidth = 
    vgui_window::Manager::get_clientscreen()->getAbsoluteWidth();
  float screenheight =
    vgui_window::Manager::get_clientscreen()->getAbsoluteHeight();
  if (x + width > screenwidth) x -= width;
  if (y + height > screenheight) y -= height;
  (dynamic_cast<CEGUI::PopupMenu*>(window_))->setXPosition(CEGUI::Relative,
                                                           x / screenwidth);
  (dynamic_cast<CEGUI::PopupMenu*>(window_))->setYPosition(CEGUI::Relative,
                                                           y / screenheight);
  window_->requestRedraw();
  return 0;
}

} //namespace menu

} //namespace window

} //namespace vgui_luacontrol
