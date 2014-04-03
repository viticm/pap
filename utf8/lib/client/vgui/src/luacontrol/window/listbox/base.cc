#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/listbox/base.h"

namespace vgui_luacontrol {

namespace window {

namespace listbox {

LuaPlus::LuaObject* Base::metatable_ = NULL;

LuaPlus::LuaObject* Base::get_metatable() {
  return metatable_;
}

int32_t Base::lua_additem(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsInteger()) return 0;
  STRING mbcs = args[2].GetString();
  STRING str;
  vgui_string::System::mbcs_to_utf8(mbcs, str);
  int32_t index = args[3].GetInteger();
  CEGUI::colour textcolor = CEGUI::colour(1.0f, 1.0f, 1.0f);
  if (args[4].IsString()) {
    textcolor = CEGUI::PropertyHelper::stringToColour(args[4].GetString());
  }
  
  CEGUI::String32 out;
  vgui_string::System::getself()->parsestring_runtime(mbcs, out);
  CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(out, index);
  CEGUI::colour selecttext_color = CEGUI::colour(1.0f, 1.0f, 1.0f);
  if (args[5].IsString()) {
    selecttext_color = 
      CEGUI::PropertyHelper::stringToColour(args[5].GetString());
  }
  if (args[ 6 ].IsInteger()) {
    item->->setHorzFomate(CEGUI::TextFormatting(args[6].GetInteger()));
  }
  if (args[7].IsString() && args[8].IsString()) {
    item->setSelectionBrushImage(args[7].GetString(), args[8].GetString());
  }
  else {
    item->setSelectionBrushImage("wxsj_questlog", "questlog_choice_back");
  }
  (dynamic_cast<CEGUI::Listbox*>(window_))->addItem(item);
  return 0;
}

int32_t Base::lua_set_tagtext(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsString()) return 0;
  CEGUI::ListboxItem* item = 
    (dynamic_cast<CEGUI::Listbox*>(window_))->getListboxItemFromIndex(
        args[2].GetInteger());
  item->setTagText(args[3].GetString());
  return 0;
}

int32_t Base::lua_set_refindex(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  (dynamic_cast<CEGUI::Listbox*>(window_))->setRefIndex(args[2].GetInteger());
  return 0;
}

int32_t Base::lua_set_tooltip(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsString()) return 0;
  (dynamic_cast<CEGUI::Listbox*>(window_))->setItemTooltipsEnabled(true);
  CEGUI::ListboxItem* item = 
    (dynamic_cast<CEGUI::Listbox*>(window_))->getListboxItemFromIndex(
        args[2].GetInteger());
  item->setTooltipText(args[3].GetString());
  return 0;
}

int32_t Base::lua_set_item_tooptip_state(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  bool set = 0 == args[2].GetInteger() ? false : true;
  (dynamic_cast<CEGUI::Listbox*>(window_))->setItemTooltipsEnabled(set);
  return 0;
}

int32_t Base::lua_set_itemtext(LuaPlus::LuaState* luastate) { 
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsString()) return 0;
  CEGUI::ListboxItem* item = 
    (dynamic_cast<CEGUI::Listbox*>(window_))->getListboxItemFromIndex(
        args[2].GetInteger());
  STRING mbcs = args[3].GetString();
  CEGUI::String32 str;
  vgui_string::System::mbcs_to_utf8(mbcs, str);
  item->setText(str);
  (dynamic_cast<CEGUI::Listbox*>(window_))->requestRedraw();
  return 0;
}

int32_t Base::lua_deleteitem(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  CEGUI::ListboxItem* item = 
    (dynamic_cast<CEGUI::Listbox*>(window_))->getListboxItemFromIndex(
        args[2].GetInteger());
  (dynamic_cast<CEGUI::Listbox*>(window_))->removeItem(item);
  return 0;
}

int32_t Base::lua_getitem(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  CEGUI::ListboxItem* item = 
    (dynamic_cast<CEGUI::Listbox*>(window_))->getListboxItemFromIndex(
        args[2].GetInteger());
  STRING mbcs;
  vgui_string::System::utf8_to_mbcs(item->getText().c_str(), mbcs);
  luastate->PushString(mbcs.c_str());
  luastate->PushInteger(item->getID());
  return 2;
}

int32_t Base::lua_get_mousemove_item(LuaPlus::LuaState* luastate) { 
  CEGUI::ListboxItem* item = 
    (dynamic_cast<CEGUI::Listbox*>(window_))->getMouseMoveSelectedItem();
  luastate->PushInteger(item ? item->getID() : -1);
  return 1;
}

int32_t Base::lua_clear(LuaPlus::LuaState* luastate) {
  (dynamic_cast<CEGUI::Listbox*>(window_))->resetList();
  return 0;
}

int32_t Base::lua_getfirst_selectitem(LuaPlus::LuaState* luastate) {
  CEGUI::ListboxTextItem* item = 
    dynamic_cast<CEGUI::ListboxTextItem*>(
        (dynamic_cast<CEGUI::Listbox*>(window_))->getFirstSelectedItem());
  luastate->PushInteger(item ? item->getID() : -1);
  return 1;
}

int32_t Base::lua_getfirst_selectitem_string(LuaPlus::LuaState* luastate) {
  CEGUI::ListboxTextItem* item = 
    dynamic_cast<CEGUI::ListboxTextItem*>(
        (dynamic_cast<CEGUI::Listbox*>(window_))->getFirstSelectedItem());
  if (item != NULL) {
    STRING str = item->getText().c_str();
    STRING mbcs;
    vgui_string::System::utf8_to_mbcs(str, mbcs);
    luastate->PushString(mbcs.c_str());
  }
  else {
    luastate->PushString("");
  }
  return 1;
}

int32_t Base::lua_setfirst_selectitem_string(LuaPlus::LuaState* luastate) { 
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  CEGUI::ListboxTextItem* item = 
    dynamic_cast<CEGUI::ListboxTextItem*>(
        (dynamic_cast<CEGUI::Listbox*>(window_))->getFirstSelectedItem());
  if (item != NULL) {
    STRING mbcs = args[2].GetString();
    CEGUI::String32 str;
    vgui_string::System::mbcs_to_utf8(mbcs, str);
    item->setText(str);
    (dynamic_cast<CEGUI::Listbox*>(window_))->requestRedraw();
  }
  return 0;
}

int32_t Base::lua_clear_allselections(LuaPlus::LuaState* luastate) {
  (dynamic_cast<CEGUI::Listbox*>(window_))->clearAllSelections();
  return 0;
}

int32_t Base::lua_set_itemselect(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  int32_t itemindex = args[2].GetInteger();
  (dynamic_cast<CEGUI::Listbox*>(window_))->setItemSelectState(itemidex, true);
  return 0;
}

int32_t Base::lua_set_itemselect_byid(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  int32_t itemid = args[2].GetInteger();
  (dynamic_cast<CEGUI::Listbox*>(window_))->setItemSelectStateByItemID(itemid, 
                                                                       true);
  return 0;
}

} //namespace listbox

} //namespace window

} //namespace vgui_luacontrol
