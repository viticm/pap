#include "elements/CEGUIPopupMenu.h"
#include "FalSuperTooltip.h"
#include "vgui/window/manager.h"
#include "vgui/luacontrol/window/tooltip/super.h"

namespace vgui_luacontrol {

namespace window {

namespace tooltip {

LuaPlus::LuaObject* Super::metatable_ = NULL;

LuaPlus::LuaObject* Super::get_metatable() {
  return metatable_;
}

int32_t Super::lua_positionself(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsString()) return 0;
  //强制重新计算大小
  (dynamic_cast<CEGUI::IFalagardSuperTooltip*>(
      dynamic_cast<CEGUI::FalagardSuperTooltip*>(window_)))->resizeSelf();
  float button_left = args[2].GetFloat();
  float button_top = args[3].GetFloat();
  float button_right = args[4].GetFloat();
  float button_bottom = args[5].GetFloat();
  //重新计算
  float width = window_->getAbsoluteWidth();
  float height = window_->getAbsoluteHeight();
  float screenwidth = 
    vgui_window::Manager::get_clientscreen()->getAbsoluteWidth();
  float screenheight = 
    vgui_window::Manager::get_clientscreen()->getAbsoluteHeight();
  float x, y;
  if (button_right + width + 5.0f > screenwidth) {
    x = button_left - width;
  }
  else {
    x = button_right + 5.0f;
  }

  if (button_bottom + height + 5.0f > screenheight) {
    y = button_top - height;
  }
  else {
    y = button_bottom + 5.0f;
  }

  if (x < 0.0f) x = 0.0f;
  if (y < 0.0f) y = 0.0f;
  (dynamic_cast<CEGUI::PopupMenu*>(window_))->setXPosition(CEGUI::Absolute, x);
  (dynamic_cast<CEGUI::PopupMenu*>(window_))->setYPosition(CEGUI::Absolute, y);
  luastate->PushNumber(x);
  luastate->PushNumber(y);
  return 2;
}

int32_t Super::lua_modifywidth(LuaPlus::LuaState* luastate) {
  return 0;
}

} //namespace tooltip

} //namespace window

} //namespace vgui_luacontrol
