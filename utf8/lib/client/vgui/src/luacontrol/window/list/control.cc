#include "vgui/luacontrol/window/config.h"
#include "vgui/luacontrol/window/list/control.h"

namespace vgui_luacontrol {

namespace window {

namespace list {

LuaPlus::LuaObject* Control::metatable_ = NULL;

LuaPlus::LuaObject* Control::get_metatable() {
  return metatable_;
}

int32_t Control::lua_addcolumn(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsInteger() || !args[4].IsNumber()) 
    return 0;
  STRING mbcs = args[2].GetString();
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  (dynamic_cast<CEGUI::MultiColumnList*>(window_))->addColumn(
      str,
      args[3].GetInteger(),
      args[4].GetFloat());
  return 0;
}

int32_t Control::lua_insertcolumn(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || 
      !args[3].IsInteger() || 
      !args[4].IsNumber() ||
      !args[5].IsInteger()) 
    return 0;
  STRING mbcs = args[2].GetString();
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  (dynamic_cast<CEGUI::MultiColumnList*>(window_))->addColumn(
      str,
      args[3].GetInteger(),
      args[4].GetFloat(),
      args[5].GetInteger());
  return 0;
}

int32_t Control::lua_removecolumn(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  (dynamic_cast<CEGUI::MultiColumnList*>(window_))->removeColumn(
      args[2].GetInteger());
  return 0;
}

int32_t Control::lua_add_newitem(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsInteger() || !args[4].IsInteger())
    return 0;
  STRING mbcs = args[2].GetString();
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  CEGUI::ListboxTextItem* item = 
    new CEGUI::ListboxTextItem(str, args[3].GetInteger());
  CEGUI::colour textcolor = CEGUI::colour(1.0f, 1.0f, 1.0f);
  item->setTextColours(textcolor);
  item->setSelectionColours(CEGUI::colour(1.0f, 0.0f, 0.0f));
  if (args[5].IsString()) {
    item->setTextColours(CEGUI::PropertyHelper::stringToColour(
          args[5].GetString()));
  }
  if (args[6].IsString()) {
    item->setSelectionColours(CEGUI::PropertyHelper::stringToColour(
          args[6].GetString());
  }

  if (args[7].IsString()) {
    STRING tooltips = args[7].GetString();
    CEGUI::String32 str;
    vgui_string::System::getself()->parsestring_runtime(tooltips, str);
    item->setTooltipText(str);
  }

  if (args[8].IsString() && args[9].IsString()) {
    item->setSelectionBrushImage(args[8].GetString(), args[9].GetString());
  }
  else {
    item->setSelectionBrushImage("wxsj_questlog", "questlog_choice_back");
  }

  CEGUI::MCLGridRef grid_ref(args[4].GetInteger(), 0);
  CEGUI::ListboxItem* existitem = NULL;
  uint32_t rowcount = 
    (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getRowCount();
  uint32_t cloumncount = 
    (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getColumnCount();
  if (grid_ref.row < rowcount && grid_ref.column < cloumncount) {
    existitem = (dynamic_cast<CEGUI::MultiColumnList*>(window_))
                  ->getItemAtGridReference(grid_ref);
  }
  
  if (existitem) {
    (dynamic_cast<CEGUI::MultiColumnList*>(window_))->setItem(
        item,
        args[3].GetInteger(),
        args[4].GetInteger());
  }
  else {
    item->setID(args[4].GetInteger());
    (dynamic_cast<CEGUI::MultiColumnList*>(window_))->addRow(
        item,
        args[3].GetInteger(),
        args[4].GetInteger());
  }
  return 0;
}

int32_t Control::lua_set_itemtext(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsInteger()) return 0;
  CEGUI::MCLGridRef grid_ref(args[2].GetInteger(), args[3].GetInteger());
  CEGUI::ListboxItem* item = NULL;
  uint32_t rowcount = 
    (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getRowCount();
  uint32_t cloumncount = 
    (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getColumnCount();
  if (grid_ref.row < rowcount && grid_ref.column < cloumncount) {
    item = (dynamic_cast<CEGUI::MultiColumnList*>(window_))
           ->getItemAtGridReference(grid_ref);
  }
  if (item) {
    STRING mbcs = args[4].GetString();
    CEGUI::String32 str;
    vgui_string::System::getself()->parsestring_runtime(mbcs, str);
    item->setText(str);
  }
  return 0;
}

int32_t Control::lua_set_itemdata(LuaPlus::LuaState* luastate) {
  //old do nothing, last I will delete it -- viticm
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsInteger()) return 0;
  CEGUI::MCLGridRef grid_ref(args[2].GetInteger(), args[3].GetInteger());
  CEGUI::ListboxItem* item = NULL;
  uint32_t rowcount = 
    (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getRowCount();
  uint32_t cloumncount = 
    (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getColumnCount();
  if (grid_ref.row < rowcount && grid_ref.column < cloumncount) {
    item = (dynamic_cast<CEGUI::MultiColumnList*>(window_))
           ->getItemAtGridReference(grid_ref);
  }
  if (item) {
    STRING mbcs = args[4].GetString();
    CEGUI::String32 str;
    vgui_string::System::getself()->parsestring_runtime(mbcs, str);
    item->setText(str);
  }
  return 0;
}

int32_t Control::lua_deleteitem(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  (dynamic_cast<CEGUI::MultiColumnList*>(window_))->removeRow(
      args[2].GetInteger());
  return 0;
}

int32_t Control::lua_remove_allitem(LuaPlus::LuaState* luastate) {
  (dynamic_cast<CEGUI::MultiColumnList*>(window_))->resetList();
  return 0;
}

int32_t Control::lua_get_itemtext(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsInteger()) return 0;
  CEGUI::MCLGridRef grid_ref(args[2].GetInteger(), args[3].GetInteger());
  CEGUI::ListboxItem* item = NULL;
  uint32_t rowcount = 
    (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getRowCount();
  uint32_t cloumncount = 
    (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getColumnCount();
  if (grid_ref.row < rowcount && grid_ref.column < cloumncount) {
    item = (dynamic_cast<CEGUI::MultiColumnList*>(window_))
           ->getItemAtGridReference(grid_ref);
  }
  if (item) {
    STRING str = item->getText().c_str();
    STRING out;
    vgui_string::System::utf8_to_mbcs(str, out);
    luastate->PushString(out);
  }
  else {
    luastate->PushString("");
  }
  return 1;
}

int32_t Control::lua_get_itemcount(LuaPlus::LuaState* luastate) {
  luastate->PushInteger(
      (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getRowCount());
  return 1;
}

int32_t Control::lua_get_columncount(LuaPlus::LuaState* luastate) {
  luastate->PushInteger(
      (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getColumnCount());
  return 1;
}

int32_t Control::lua_get_selectitem(LuaPlus::LuaState* luastate) {
  CEGUI::ListboxItem* item = NULL;
  item = dynamic_cast<CEGUI::ListboxItem*>(
      (dynamic_cast<CEGUI::MultiColumnList*>(window_))->getFirstSelectedItem());
  if (item) {
    luastate->PushInteger(item->getID());
  }
  else {
    luastate->PushInteger(-1);
  }
  return 1;
}

int32_t Control::lua_set_selectitem(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  CEGUI::MultiColumnList* multilist = 
    dynamic_cast<CEGUI::MultiColumnList*>(window_);
  int32_t rowindex = args[2].GetInteger();
  if (rowindex < 0 || 
      rowindex >= static_cast<int32_t>(multilist->getRowCount())) {
    return 0;
  }

  CEGUI::MCLGridRef grid_ref(rowindex, 0);
  CEGUI::ListboxItem* item = item->getItemAtGridReference(grid_ref);
  if (item) item->setItemSelectState(grid_ref, true);
  return 0;
}

} //namespace list

} //namespace window

} //namespace vgui_luacontrol
