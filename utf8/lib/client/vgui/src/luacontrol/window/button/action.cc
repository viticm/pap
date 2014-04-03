#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/button/action.h"

namespace vgui_luacontrol {

namespace window {

namespace button {

LuaPlus::LuaObject* Action::metatable_ = NULL;

LuaPlus::LuaObject* Action::get_metatable() {
  return metatable_;
}

int32_t Action::lua_setitem(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  int32_t itemid = args[2].GetInteger();
  update(itemid);
  return 0;
}

int32_t Action::lua_set_keystate(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsInteger()) return 0;
  int32_t keystate = args[2].GetInteger();
  bool isfirst = args[3].GetInteger() > 0;
  g_game_actionsystem->set_systemkey_state(keystate, isfirst);
  return 0;
}

int32_t Action::lua_get_itemid(LuaPlus::LuaState* luastate) {
  if (!item_ || NULL == item_) {
    luastate->->PushInteger(-1);
    return 1;
  }
  int32_t id = item_->getid();
  luastate->PushInteger(id);
  return 1;
}

int32_t Action::lua_get_item_defineid(LuaPlus::LuaState* luastate) {
  if (!item_ || NULL == item_) {
    luastate->->PushInteger(-1);
    return 1;
  }
  int32_t defineid = item_->get_defineid();
  luastate->PushInteger(defineid);
  return 1;
}

int32_t Action::lua_do(LuaPlus::LuaState* luastate) {
  if (item_) item_->doaction();
  return 0;
}

int32_t Action::lua_dosub(LuaPlus::LuaState* luastate) {
  if (item_) {
    item_->do_subaction();
    luastate->PushInteger(1);
  }
  luastate->PushInteger(0);
  return 1;
}

int32_t Action::lua_setpushed(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  bool check = 1 == args[2].GetInteger();
  setcheck(check);
  return 0;
}

int32_t Action::lua_setflash(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  bool flash = 1 == args[2].IsInteger();
  enterflash(flash);
  return 0;
}

int32_t Action::lua_set_item_iconname(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  STRING iconname(args[2].GetString());
  if (item_) item_->seticon(iconname);
  return 0;
}

int32_t Action::lua_set_logicitem_data(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  int32_t id = args[2].GetInteger();
  (dynamic_cast<CEGUI::IFalagardActionButton*>(
    dynamic_cast<CEGUI::FalagardActionButton*>(window_)))
    ->setLogicItemData((void*)(int32_t*)id);
  return 0;
}

int32_t Action::lua_set_normalimage(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  window_->show();
  window_->setProperty("Empty", "False");
  STRING iconname = 
    vgui_base::System::getself()->get_iconmanager()->get_icon_fullname(
        args[2].GetString());
  if (!iconname.empty())
    window_->setProperty("NormalImage", iconname.c_str());
  return 0;
}

void Action::locked() {
  window_->setProperty("Locked", "False");
  window_->requestRedraw();
}

void Action::unlock() {
  window_->setProperty("Locked", "False");
  window_->requestRedraw();
}

void Action::bedestoryed() {
  window_->setProperty("Empty", "True");
  (dynamic_cast<CEGUI::IFalagardActionButton*>(
    dynamic_cast<CEGUI::FalagardActionButton*>(window_)))
    ->setLogicItemData((void*)(int32_t*)-1);
  (dynamic_cast<CEGUI::IFalagardActionButton*>(
    dynamic_cast<CEGUI::FalagardActionButton*>(window_)))
    ->cleanAnimate();
  if (g_game_actionsystem->get_tooltips_focus() &&
      item_ == g_game_actionsystem->get_tooltips_focus()) {
    vengine_capability::ax::trace(0, 0, "***CleanSupertooltips");
    g_game_eventsystem->push(vengine_game::event_id::kSuperToolTip, "0");
  }
  window_->requestRedraw();
  item_ = NULL;
}

void Action::update(uint32_t itemid) {
  vengine_game::action::Item* item = g_game_actionsystem()->get(itemid);
  //断开和原来的Action的联系
  if (item && item != item_) {
    item->removereference(this);
  }
  if (NULL == item) {
    //如果逻辑项为空, 清空显示
    bedestoryed();
    window_->setProperty("ShowTooltip", "True");
    return;
  }
  //不显示默认tooltip
  window_setProperty("ShowTooltip", "False");
  //设置有效无效标记
  if (item->isenable()) {
    bright();
  }
  else {
    gloom();
  }
  //设置新的Action
  (dynamic_cast<CEGUI::IFalagardActionButton*>(
    dynamic_cast<CEGUI::FalagardActionButton*>(window_)))
    ->setLogicItemData((void*)(int32_t*)item->getid());
  item_ = item;
  const char* dragname = 
    (dynamic_cast<CEGUI::FalagardActionButton*>(window_))->getDragAcceptName();
  if ('M' == dragname[0] || 'F' == dragname[0]) {
    item->addreference(this, true);
  }
  else {
    item->addreference(this, false);
  }
  const STRING iconname = 
    vgui_base::System::getself()
    ->get_iconmanager()
    ->get_icon_fullname(item->geticon());
  window_->show();
  window_->setProperty("Empty", "False");
  if (!iconname.empty()) window_->setProperty("NormalImage", iconname);
}

void Action::disable() {
  window_->setProperty("Disabled", "True");
  window_->requestRedraw();
}

void Action::enable() {
  window_->setProperty("Disabled", "False");
  window_->requestRedraw();
}

void Action::gloom() {
  window_->setProperty("Gloom", "True");
  window_->requestRedraw();
}

void Action::bright() {
  window_->setProperty("Gloom", "False");
  window_->requestRedraw();
}

int32_t Action::lua_gloom(LuaPlus::LuaState* luastate) {
  gloom();
  return 0;
}

int32_t Action::lua_bright(LuaPlus::LuaState* luastate) {
  bright();
  return 0;
}

void Action::setcheck(bool check) {
  window_->setProperty("Checked", check ? "True" : "False");
  window_->requestRedraw();
}

void Action::setdefault(bool flag) {
  window_->setProperty("Default", flag ? "True" : "False");
  window_->requestRedraw();
}

void Action::set_cornerchar(cornernumber_position_enum position, 
                            const char* _char) {
  char temp[MAX_PATH] = {0};
  switch (position) {
    case kCornerNumberPositionTopLeft: {
      snprintf(temp, sizeof(temp) - 1, "TopLeft %s", _char);
      break;
    }
    case kCornerNumberPositionTopRight: {
      snprintf(temp, sizeof(temp) - 1, "TopRight %s", _char);
      break;
    }
    case kCornerNumberPositionFootLeft: {
      snprintf(temp, sizeof(temp) - 1, "BotLeft %s", _char);
      break;
    }
    case kCornerNumberPositionFootRight: {
      snprintf(temp, sizeof(temp) - 1, "BotRight %s", _char);
      break;
    }
    default:
      break;
  }
  window_->setProperty("CornerChar", temp);
}

void Action::enter_cooldown(int32_t time, float percent) {
  if (time < 0) {
    (dynamic_cast<CEGUI::IFalagardActionButton*>(
      dynamic_cast<CEGUI::FalagardActionButton*>(window_)))
      ->cleanAnimate();
  }
  else {
    (dynamic_cast<CEGUI::IFalagardActionButton*>(
      dynamic_cast<CEGUI::FalagardActionButton*>(window_)))
      ->setAnimate("CoolDown", time, percent);
  }
}

void Action::enterflash(bool flash) {
  if (flash) {
    (dynamic_cast<CEGUI::IFalagardActionButton*>(
      dynamic_cast<CEGUI::FalagardActionButton*>(window_)))
      ->setAnimate("Flash", 1000, 0.0);
  }
  else {
    (dynamic_cast<CEGUI::IFalagardActionButton*>(
      dynamic_cast<CEGUI::FalagardActionButton*>(window_)))
      ->cleanAnimate();
  }
}

} //namespace button

} //namespace window

} //namespace vgui_luacontrol
