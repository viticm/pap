#include "CEGUIPropertyHelper.h"
#include "vgui/icon/manager.h"
#include "vgui/luacontrol/window/image/static.h"

namespace vgui_luacontrol {

namespace window {

namespace image {

LuaPlus::LuaObject* Static::metatable_ = NULL;

LuaPlus::LuaObject* Static::get_metatable() {
  return metatable_;
}

int32_t Static::lua_set(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  if (args[3].IsString()) { //图片全路径
    char imagename[128] = {0};
    snprintf("set:%s image:%s",
             sizeof(imagename) - 1, 
             args[2].GetString(), 
             args[3].GetString());
    window_->setProperty("Image", imagename);
  }
  else { //icon
    STRING iconname;
    try {
      iconname = 
        vgui_icon::Manager::getself()->get_icon_fullname(args[2].GetString());
      window_->setProperty("Image", iconname.c_str());
    }
    catch(...) {
      //catch functions
    }
  }
  return 0;
}

int32_t Static::lua_setcolor(LuaPlus::LuaState* luastate) { 
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  CEGUI::colour color = CEGUI::PropertyHelper::stringToColour(
      args[2].GetString());
  CEGUI::ColourRect colorrect(color);
  window_->setProperty("ImageColours",
                       CEGUI::PropertyHelper::colourRectToString(colorrect));
  return 0;
}

} //namespace image

} //namespace window

} //namespace vgui_luacontrol
