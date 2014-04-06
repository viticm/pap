#include "FalagardRadar.h"
#include "FalagardScenemap.h"
#include "vengine/db/system.h"
#include "vengine/db/struct/all.h"
#include "vengine/game/worldsystem.h"
#include "vgui/string/system.h"
#include "vgui/luacontrol/window/map/scene/base.h"

namespace vgui_luacontrol {

namespace window {

namespace map {

namespace scene {

LuaPlus::LuaObject* Base::metatable_ = NULL;

LuaPlus::LuaObject* Base::get_metatable() {
  return metatable_;
}

int32_t Base::lua_set_zoommode(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsNumber()) return 0;
  CEGUI::IFalagardSceneMapWindow* window = 
    dynamic_cast<CEGUI::IFalagardSceneMapWindow*>(
        dynamic_cast<CEGUI::FalagardRadar*>(window_));
  window->SetZoomMode(static_cast<int32_t>(args[2].GetFloat()));
  return 0;
}

int32_t Base::lua_update_viewrect(LuaPlus::LuaState* luastate) {
  CEGUI::IFalagardSceneMapWindow* window = 
    dynamic_cast<CEGUI::IFalagardSceneMapWindow*>(
        dynamic_cast<CEGUI::FalagardRadar*>(window_));
  vengine_math::base::threefloat_vector_t selfposition;
  selfposition = g_game_worldsystem->get_selfposition();
  CEGUI::Point position;
  position.d_x = selfposition.x;
  position.d_y = selfposition.z;
  window->setMyselfPos(position);
  window->setSceneMapCenter();
  return 0;
}

//获取场景文件名后缀
const char* Base::get_filepostfix(const char* filename) {
  const vengine_db::File* scenedefine = g_databasesystem->get(
      vengine_db::structs::scene::kDefineId); 
  int32_t number = scenedefine->get_record_number();
  int32_t i;
  typedef vengine_db::structs::scene::define_t define_t;
  for (i = 0; i < number; ++i) {
    const define_t* line = reinterpret_cast<const define_t*>(
        scenedefine->search_first_column_equal(
          define_t::kSceneServerIdColumn, i));
    if (0 == strcmp(line->map, filename)) { //case sensitive
      if (strstr(line->minimap, "jpg")) return "jpg";
      if (strstr(line->minimap, "png")) return "png";
    }
  }
  return "jpg";
}

int32_t Base::lua_set_filename(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsNumber() || !args[3].IsNumber() || !args[4].IsString())
    return 0;
  CEGUI::IFalagardSceneMapWindow* window = 
    dynamic_cast<CEGUI::IFalagardSceneMapWindow*>(
        dynamic_cast<CEGUI::FalagardRadar*>(window_));
  window->SetSceneSize(CEGUI::Size(args[2].GetFloat(), args[3].GetFloat()));
  const char* filename = args[4].GetString();
  const char* postfix = get_filepostfix(filename);
  window->SetSceneFileName(args[4].GetString(), postfix);
  return 0;
}

int32_t Base::lua_closeit(LuaPlus::LuaState* luastate) {
  CEGUI::IFalagardSceneMapWindow* window = 
    dynamic_cast<CEGUI::IFalagardSceneMapWindow*>(
        dynamic_cast<CEGUI::FalagardRadar*>(window_));
  window->Clear();
  return 0;
}

int32_t Base::lua_get_mouseposition(LuaPlus::LuaState* luastate) {
  CEGUI::IFalagardSceneMapWindow* window = 
    dynamic_cast<CEGUI::IFalagardSceneMapWindow*>(
        dynamic_cast<CEGUI::FalagardRadar*>(window_));
  const CEGUI::Point position = window->GetMouseScenePos();
  luastate->PushInteger(static_cast<int32_t>(position.d_x));
  luastate->PushInteger(static_cast<int32_t>(position.d_y));
  return 2;
}

int32_t Base::lua_update(LuaPlus::LuaState* luastate) { 
  CEGUI::IFalagardSceneMapWindow* window = 
    dynamic_cast<CEGUI::IFalagardSceneMapWindow*>(
        dynamic_cast<CEGUI::FalagardRadar*>(window_));
  if (window_->isVisible()) {
    //更新所有的标志位置
    window->Clear();
    uint8_t i;
    for (i = 0; i < vengine_game::kMiniMapTypeNumber; ++i) {
      std::list<vengine_game::mapposition_define_t>* mapposition_list = 
        g_game_worldsystem->get_objectlist_bytype(i);
      if (NULL == mapposition_list) continue;
      std::list<vengine_game::mapposition_define_t>::iterator iterator;
      for (iterator = mapposition_list->begin();
           iterator != mapposition_list->end();
           ++iterator) {
        //如果是队友，需要单独处理
        if (vengine_game::kMiniMapTypeTeam == i) {
          //在同一场景才会添加
          if ((*iterator).sceneid != g_game_worldsystem->get_active_sceneid())
            continue;
        }
        window->setMinimapData(i, 
                               (*iterator).position.x,
                               (*iterator).position.z,
                               CEGUI::String32((*iterator).name));
      } //for loop
    } //for loop
  }
  vengine_math::base::threefloat_vector_t selfposition;
  selfposition = g_game_worldsystem->get_selfposition();
  int32_t dir = g_game_worldsystem->get_selfdirect();
  window->setMyselfPos(CEGUI::Point(selfposition.x, selfposition.z));
  window->setMyselfDir(dir);
  return 0;
}


int32_t Base::lua_move_bydirection(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsNumber() || !args[3].IsNumber()) return 0;
  CEGUI::IFalagardSceneMapWindow* window = 
    dynamic_cast<CEGUI::IFalagardSceneMapWindow*>(
        dynamic_cast<CEGUI::FalagardRadar*>(window_));
  window->moveMapByDirection(args[2].GetInteger(), args[3].GetInteger());
  return 0;
}

int32_t Base::lua_add_teamplayer_position(LuaPlus::LuaState* luastate) { 
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsInteger() || !args[4].IsInteger())
    return 0;
  if (!window_->isVisible()) return 0;
  CEGUI::IFalagardSceneMapWindow* window = 
    dynamic_cast<CEGUI::IFalagardSceneMapWindow*>(
        dynamic_cast<CEGUI::FalagardRadar*>(window_));
  CEGUI::Point point = 
    CEGUI::Point(CEGUI::Vector2(
    static_cast<float>(args[2].GetInteger()), 
    static_cast<float>(args[3].GetInteger())));
  CEGUI::String name = args[4].GetString();
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(name, str);
  window->addTeammatePos(point, str);
  return 0;
}

} //namespace scene

} //namespace map

} //namespace window

} //namespace vgui_luacontrol
