#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/map/scene/mini.h"

namespace vgui_luacontrol {

namespace window {

namespace map {

namespace scene {

LuaPlus::LuaObject* Mini::metatable_ = NULL;

LuaPlus::LuaObject* Mini::get_metatable() {
  return metatable_;
}

int32_t Mini::lua_updateflag(LuaPlus::LuaState* luastate) {
  CEGUI::IFalagardSceneMapWindow* window = 
    dynamic_cast<CEGUI::IFalagardSceneMapWindow*>(
        dynamic_cast<CEGUI::FalagardRadar*>(window_));
  if (window->isVisible()) {
    //更新所有的标志位置
    window->Clear();
    uint8_t i;
    for (i = 0; i < vengine_game::kMiniMapTypeNumber; ++i) {
      std::list<mapposition_define_t>* mapposition_list = 
        g_game_worldsystem->get_objectlist_bytype(i);
      if (NULL == mapposition_list) continue;
      std::list<mapposition_define_t>::iterator iterator;
      for (iterator = mapposition_list->begin();
           iterator != mapposition_list->end();
           ++iterator) {
        //如果是队友，需要单独处理
        if (kMiniMapTypeTeam == i) {
          //在同一场景才会添加
          if ((*iterator).sceneid != g_game_worldsystem->get_active_sceneid())
            continue;
        }
        window->setMinimapData(i, 
                               (*iterator).position.x,
                               (*iterator).position.z,
                               (*iterator).name);
      } //for loop
    } //for loop
  }
  vengine_math::base::threefloat_vector_t selfposition;
  selfposition = g_game_worldsystem->get_selfposition();
  int32_t dir = g_game_worldsystem->get_selfdirect();
  window->setMyselfPos(CEGUI::Point(selfposition.x, selfposition.z));
  window->setMyselfDir(dirc);
  return 0;
}

} //namespace scene

} //namespace map

} //namespace window

} //namespace vgui_luacontrol
