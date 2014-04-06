#include "CEGUIPropertyHelper.h"
#include "FalTree.h"
#include "vgui/string/system.h"
#include "vgui/luacontrol/window/tree.h"

namespace vgui_luacontrol {

namespace window {

LuaPlus::LuaObject* Tree::metatable_ = NULL;

LuaPlus::LuaObject* Tree::get_metatable() {
  return metatable_;
}

int32_t Tree::lua_clear(LuaPlus::LuaState* luastate) {
  CEGUI::FalagardTree* window = dynamic_cast<CEGUI::FalagardTree*>(window_);
  window->resetList();
  return 0;
}

int32_t Tree::lua_additem(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsInteger()) return 0;
  STRING mbcs = args[2].GetString();
  int32_t index = args[3].GetInteger();
  CEGUI::colour textcolor = CEGUI::colour(1.0f, 1.0f, 1.0f);
  if (args[4].IsString()) {
    textcolor = CEGUI::PropertyHelper::stringToColour(args[4].GetString());
  }
  CEGUI::FalagardTree* window = dynamic_cast<CEGUI::FalagardTree*>(window_);
  if (!window) return 0;
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  CEGUI::TreeItem* item = new CEGUI::TreeItem(str, index);
  item->setSelectionBrushImage("wxsj_questlog", "questlog_choice_back");
  item->setTextColours(textcolor);
  
  if (args[5].IsString()) { //场景名
    STRING mbcs_scenename = args[5].GetString();
    CEGUI::String32 str_scenename;
    vgui_string::System::getself()->parsestring_runtime(mbcs_scenename, 
                                                        str_scenename);
    CEGUI::TreeItem* sceneitem = window->findFirstItemWithText(str_scenename);
    if (NULL == sceneitem) {
      sceneitem =  new CEGUI::TreeItem(str_scenename);
      window->addItem(sceneitem);
    }
    sceneitem->setSelectionBrushImage("wxsj_questlog", 
                                      "questlog_choice_back");
    sceneitem->addItem(item);
  }
  else {
    window->addItem(item);
  }
  return 0;
}

int32_t Tree::lua_getfirst_selectitem(LuaPlus::LuaState* luastate) {
  CEGUI::FalagardTree* window = dynamic_cast<CEGUI::FalagardTree*>(window_);
  CEGUI::TreeItem* item = window->getFirstSelectedItem();
  if (!item || item->getItemCount() > 0) {
    luastate->PushInteger(-1);
  }
  else {
    luastate->PushInteger(item->getID());
  }
  return 1;
}

int32_t Tree::lua_getfirst_selectitem_string(LuaPlus::LuaState* luastate) {
  CEGUI::FalagardTree* window = dynamic_cast<CEGUI::FalagardTree*>(window_);
  CEGUI::TreeItem* item = window->getFirstSelectedItem();
  if (!item) {
    luastate->PushString("");
    return 1;
  }
  STRING str = item->getText().c_str();
  STRING mbcs;
  vgui_string::System::utf8_to_mbcs(str, mbcs);
  luastate->PushString(mbcs.c_str());
  return 1;
}

int32_t Tree::lua_setfirst_selectitem_string(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  CEGUI::FalagardTree* window = dynamic_cast<CEGUI::FalagardTree*>(window_);
  CEGUI::TreeItem* item = window->getFirstSelectedItem();
  if (!item) {
    STRING mbcs = args[2].GetString();
    CEGUI::String32 str;
    vgui_string::System::getself()->parsestring_runtime(mbcs, str);
    item->setText(str);
    window->requestRedraw();
  }
  return 0;
}

int32_t Tree::lua_set_itemselect_byid(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  int32_t id = args[2].GetInteger();
  CEGUI::FalagardTree* window = dynamic_cast<CEGUI::FalagardTree*>(window_);
  window->setItemSelectState(id, true); 
  return 0;
}

int32_t Tree::lua_setitem_toggle(LuaPlus::LuaState* luastate) {
  CEGUI::FalagardTree* window = dynamic_cast<CEGUI::FalagardTree*>(window_);
  CEGUI::TreeItem* item = window->getFirstSelectedItem();
  if (!item) return 0;
  if (0 == item->getItemCount()) return 0;
  item->toggleIsOpen();
  window->requestRedraw();
  return 0;
}

} //namespace window

} //namespace vgui_luacontrol
