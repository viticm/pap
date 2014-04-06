#include "elements/CEGUIListbox.h"
#include "elements/CEGUIListboxTextItem.h"
#include "elements/CEGUICombobox.h"
#include "vgui/string/system.h"
#include "vgui/luacontrol/window/combobox/base.h"

namespace vgui_luacontrol {

namespace window {

namespace combobox {

LuaPlus::LuaObject* Base::metatable_ = NULL;

LuaPlus::LuaObject* Base::get_metatable() {
  return metatable_;
}

int32_t Base::lua_additem(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  STRING mbcs = args[2].GetString();
  STRING str;
  vgui_string::System::mbcs_to_utf8(mbcs, str);
  CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(
      str,
      args[3].GetInteger());
  item->setSelectionColours(CEGUI::colour(1.0f, 0.0f, 0.0f));
  if (args[3].IsString() && args[4].IsString()) {
    item->setSelectionBrushImage(args[3].GetString(), args[4].GetString());
  }
  else {
    //更名 viticm
    item->setSelectionBrushImage("wxsj_questlog", "questlog_choice_back");
  }
  (dynamic_cast<CEGUI::Combobox*>(window_))->addItem(item);
  return 0;
}

int32_t Base::lua_resetlist(LuaPlus::LuaState* luastate) {
  (dynamic_cast<CEGUI::Combobox*>(window_))->resetList();
  return 0;
}

int32_t Base::lua_get_currentselect(LuaPlus::LuaState* luastate) { 
  if ((dynamic_cast<CEGUI::Combobox*>(window_))->getSelectedItem()) {
    luastate->PushString(
        (dynamic_cast<CEGUI::Combobox*>(window_))
        ->getSelectedItem()
        ->getText().c_str());
    luastate->PushInteger(
        (dynamic_cast<CEGUI::Combobox*>(window_))
        ->getSelectedItem()
        ->getID());
  }
  else {
    luastate->PushString("-1");
    luastate->PushInteger(-1);
  }
  return 2;
}

int32_t Base::lua_set_currentselect(LuaPlus::LuaState* luastate) { 
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  int32_t itemindex = args[2].GetInteger();
  CEGUI::ListboxItem* item = 
    (dynamic_cast<CEGUI::Combobox*>(window_))
    ->getListboxItemFromIndex(itemindex);
  (dynamic_cast<CEGUI::Combobox*>(window_))->setItemSelectState(itemindex, true);
  (dynamic_cast<CEGUI::Combobox*>(window_))->setText(item->getText());
  return 0;
}

int32_t Base::lua_set_itemtext(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate); 
  if (!args[2].IsInteger() || !args[3].IsString()) return 0;
  int32_t itemindex = args[2].GetInteger();
  CEGUI::ListboxItem* item = 
    (dynamic_cast<CEGUI::Combobox*>(window_))
    ->getListboxItemFromIndex(itemindex);
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(args[3].GetString(), str);
  item->setText(str);
  return 0;
}

} //namespace combobox

} //namespace window

} //namespace vgui_luacontrol
