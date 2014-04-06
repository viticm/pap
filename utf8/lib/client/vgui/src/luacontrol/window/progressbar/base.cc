#include "elements/CEGUIProgressBar.h"
#include "vgui/luacontrol/window/progressbar/base.h"

namespace vgui_luacontrol {

namespace window {

namespace progressbar {

LuaPlus::LuaObject* Base::metatable_ = NULL;


LuaPlus::LuaObject* Base::get_metatable() {
  return metatable_;
}

int32_t Base::lua_setprogress(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsNumber()) return 0;
  float now = args[2].GetFloat();
  float max = args[3].GetFloat();
  if (-1.0f == max)
    (dynamic_cast<CEGUI::ProgressBar*>(window_))->setProgress(now);
  else 
    (dynamic_cast<CEGUI::ProgressBar*>(window_))->setProgress(now/max);
  return 0;
}


} //namespace progressbar

} //namespace window

} //namespace vgui_luacontrol
