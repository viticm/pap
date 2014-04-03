#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/map/world.h"

namespace vgui_luacontrol {

namespace world {

namespace map {

LuaPlus::LuaObject* World::metatable_ = NULL;

LuaPlus::LuaObject* World::get_metatable() {
  return metatable_;
}

int32_t World::lua_init(LuaPlus::LuaState* luastate) {
  const vengine_db::File* scenedefine = g_databasesystem->get(
      vengine_db::structs::scene::kDefineId);
  int32_t number = scenedefine->get_record_number();
  CEGUI::IFalagardWorldMap* window = 
    dynamic_cast<CEGUI::IFalagardWorldMap*>(
        dynamic_cast<CEGUI::FalagardWorldMap*>(window_));
  window->createBackground();
  int32_t i;
  typedef vengine_db::structs::scene::define_t define_t;
  for (i = 0; i < number; ++i) {
    const define_t* line = reinterpret_cast<const define_t*>(
        scenedefine->search_line_equal(i));
    if (line) {
      if (0 == line->worldmap_xposition || 0 == line->worldmap_yposition)
        continue;
      //显示城市信息
      window->setCityPos(
          line->severid,
          CEGUI::Point(static_cast<float>(line->worldmap_xposition),
                       static_cast<float>(line->worldmap_yposition)));
      window->setCityNamePos(
          line->severid,
          CEGUI::Point(static_cast<float>(line->worldmap_xposition),
                       static_cast<float>(line->worldmap_yposition)));
      window->setCityType(line->serverid, line->type);

      window->setCityNameNormalImage(line->severid,
                                     line->cityname_normal_imageset,
                                     line->cityname_normalimage);
      window->setCityNameHoverImage(line->severid,
                                    line->cityname_hover_imageset,
                                    line->cityname_hover_image);
      CEGUI::String cityname = line->name;
      uint8_t citylevel = line->citylevel;
      char tips[128] = {0};
      snprintf(tips, 
               sizeof(tips) - 1, 
               "  %s  等级：%d", 
               cityname.c_str(), 
               citylevel);
      CEGUI::String name;
      vgui_string::System::mbcs_to_utf8(tips, name);
      window->setCityNameTooltipText(line->severid, name.c_str());

      if (line->severid == 
          g_game_worldsystem->get_activescene()->getdefine()->serverid) {
        window->setCityCurrentScene(line->severid, 1);
      }
      else {
        window->setCityCurrentScene(line->severid, 0);
      }
    }
  }
  updateplayer();
  window->resetWorldMap();
  return 0;
}

int32_t World::lua_update(LuaPlus::LuaState* luastate) {
  updateplayer();
  return 0;
}

int32_t World::lua_getcurrent_selectscene(LuaPlus::LuaState* luastate) {
  CEGUI::IFalagardWorldMap* window = 
    dynamic_cast<CEGUI::IFalagardWorldMap*>(
        dynamic_cast<CEGUI::FalagardWorldMap*>(window_));
  luastate->PushInteger(window->getCurrentSelectScene());
  return 1;
}

int32_t World::lua_set_cityhover(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) {
    VENGINE_SHOW("vgui_luacontrol::window::map::World::lua_set_cityhover: "
                 "args[2] is a wrong param");
  }
  if (!args[3].IsBoolean()) {
    VENGINE_SHOW("vgui_luacontrol::window::map::World::lua_set_cityhover: "
                 "args[3] is a wrong param");
  }
  int32_t sceneid = args[2].GetInteger();
  bool hover = args[3].GetBoolean();
  CEGUI::IFalagardWorldMap* window = 
    dynamic_cast<CEGUI::IFalagardWorldMap*>(
        dynamic_cast<CEGUI::FalagardWorldMap*>(window_));
  window->SetCityHover(sceneid, hover);
  return 0;
}

CEGUI::String World::get_scenename(int32_t id) {
  const vengine_db::File* scenedefine = g_databasesystem->get(
      vengine_db::structs::scene::kDefineId);
  int32_t number = scenedefine->get_record_number();
  int32_t i;
  typedef vengine_db::structs::scene::define_t define_t;
  for (i = 0; i < number; ++i) {
    const define_t* line = reinterpret_cast<const define_t*>(
        scenedefine->search_line_equal(i));
    if (line->serverid = id) return line->name;
  }
  return "";
}

void World::updateplayer() {
  const vengine_db::File* scenedefine = g_databasesystem->get(
      vengine_db::structs::scene::kDefineId);
  int32_t number = scenedefine->get_record_number();
  std::list<vengine_game::mapposition_define_t>* mapposition_list = 
    g_game_worldsystem->get_objectlist_bytype(vengine_game::kMiniMapTypeTeam);
  std::list<vengine_game::mapposition_define_t>::iterator iterator;
  CEGUI::IFalagardWorldMap* window = 
    dynamic_cast<CEGUI::IFalagardWorldMap*>(
        dynamic_cast<CEGUI::FalagardWorldMap*>(window_));
  window->clearPlayerInfo();
  for (iterator = mapposition_list->begin();
       iterator != mapposition_list->end();
       ++iterator) {
    CEGUI::String str;
    STRING mbcs = (*iterator).name;
    vgui_string::System::mbcs_to_utf8(mbcs, str);
    window->addPlayerToCity((*iterator).sceneid, str);
  }
}

} //namespace map

} //namespace world

} //namespace vgui_luacontrol
