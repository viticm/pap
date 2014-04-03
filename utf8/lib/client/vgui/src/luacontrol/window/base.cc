#include "vgui/luacontrol/window/config.h"
/* controls { */
#include "vgui/luacontrol/window/animation.h"
#include "vgui/luacontrol/window/complex.h"
#include "vgui/luacontrol/window/mesh.h"
#include "vgui/luacontrol/window/softkey.h"
#include "vgui/luacontrol/window/tree.h"
#include "vgui/luacontrol/window/button/action.h"
#include "vgui/luacontrol/window/button/check.h"
#include "vgui/luacontrol/window/chat/channel.h"
#include "vgui/luacontrol/window/combobox/base.h"
#include "vgui/luacontrol/window/editbox/base.h"
#include "vgui/luacontrol/window/editbox/multiline.h"
#include "vgui/luacontrol/window/image/static.h"
#include "vgui/luacontrol/window/list/control.h"
#include "vgui/luacontrol/window/list/info.h"
#include "vgui/luacontrol/window/listbox/image/base.h"
#include "vgui/luacontrol/window/listbox/image/extend.h"
#include "vgui/luacontrol/window/listbox/base.h"
#include "vgui/luacontrol/window/map/scene/base.h"
#include "vgui/luacontrol/window/map/scene/mini.h"
#include "vgui/luacontrol/window/map/world.h"
#include "vgui/luacontrol/window/menu/pop.h"
#include "vgui/luacontrol/window/progressbar/base.h"
#include "vgui/luacontrol/window/progressbar/super.h"
#include "vgui/luacontrol/window/scroll/bar.h"
#include "vgui/luacontrol/window/scroll/info.h"
#include "vgui/luacontrol/window/tooltip/super.h"
/* } controls */

#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

LuaPlus::LuaObject* Base::metatable_ = NULL;

Base::Base(CEGUI::Window* window) {
  window_ = window;
}

LuaPlus::LuaObject* Base::get_metatable() {
  return metatable_;
}

Base* Base::create(CEGUI::Window* window) {

  CEGUI::String type = window->getWidgetType();

  if ("Falagard/ActionButton" == type) {
    return new button::Action(window);
  }
  else if ("Falagard/ProgressBar" == type) {
    return new progressbar::Base(window);
  }
  else if ("Falagard/SuperProgress" == type) {
    return new progressbar::Super(window);
  }
  else if ("Falagard/PopupMenu" == type) {
    return new menu::Pop(window);
  }
  else if ("Falagard/Radar" == type) {
    return new map::scene::Mini(window);
  }
  else if ("Falagard/ComplexWindow" == type) {
    return new Complex(window);
  }
  else if ("Falagard/Listbox" == type) {
    return new listbox::Base(window);
  }
  else if ("Falagard/ImageListbox" == type) {
    return new listbox::image::Base(window);
  }
  else if ("Falagard/ImageListboxEx" == type) {
    return new listbox::image::Extend(window);
  }
  else if ("Falagard/CheckBox" == type) {
    return new button::Check(window);
  }
  else if ("Falagard/Combobox" == type) {
    return new combox::Base(window);
  }
  else if ("Falagard/StaticImage" == type) {
    return new image::Static(window);
  }
  else if ("Falagard/Scrollbar" == type) {
    return new scroll::Bar(window);
  }
  else if ("Falagard/SuperTooltip" == type) {
    return new tooltip::Super(window);
  }
  else if ("Falagard/MeshWindow" == type) {
    return new Mesh(window);
  }
  else if ("Falagard/ChatHistory" == type) {
    return new chat::History(window);
  }
  else if ("Falagard/ChatChannel" == type) {
    return new chat::Channel(window);
  }
  else if ("Falagard/SceneMap" == type) {
    return new map::scene::Base(window);
  }
  else if ("Falagard/WorldMap" == type) {
    return new map::World(window);
  }
  else if ("Falagard/InfoList" == type) {
    return new list::Info(window);
  }
  else if ("Falagard/MultiColumnList" == type) {
    return new list::Control(window);
  }
  else if ("Falagard/SoftKeyWindow" == type) {
    return new SoftKey(window);
  }
  else if ("Falagard/Animate" == type) {
    return new Animation(window);
  }
  else if ("Falagard/IMEEditBox" == type) {
    return new editbox::Base(window);
  }
  else if ("Falagard/MultiIMEEditBox" == type) {
    return new editbox::MultiLine(window);
  }
  else if ("Falagard/ScrollInfo" == type) {
    return new scroll::Info(window);
  }
  else if ("Falagard/Tree" == type) {
    return new Tree(window);
  }
  else {
    return new Base(window);
  }
}

void Base::destroy(CEGUI::Window* window) {
  SAFE_DELETE(window);
}

void Base::register_metatable() {
  LuaPlus::LuaState* luastate = g_scriptsystem->get_luastate();
  VENGINE_ASSERT(luastate);
  /* base { */
  Base::metatable_ = new LuaPlus::LuaObject;
  *Base::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_Window");
  Base::metatable_->SetObject("__index", *Base::metatable_);
  Base::metatable_->RegisterObjectFunctor("SetProperty", 
                                          &Base::Base::lua_setproperty);
  Base::metatable_->RegisterObjectFunctor("GetProperty", 
                                          &Base::Base::lua_getproperty);
  Base::metatable_->RegisterObjectFunctor("GetType", &Base::Base::lua_gettype);
  Base::metatable_->RegisterObjectFunctor("GetText", &Base::Base::lua_gettext);
  Base::metatable_->RegisterObjectFunctor("SetText", &Base::Base::lua_settext);
  Base::metatable_->RegisterObjectFunctor("SetTextOriginal", 
                                          &Base::Base::lua_set_textoriginal);
  Base::metatable_->RegisterObjectFunctor("TransText", 
                                          &Base::Base::lua_transtext);
  Base::metatable_->RegisterObjectFunctor("Show", &Base::Base::lua_show);
  Base::metatable_->RegisterObjectFunctor("Hide", &Base::Base::lua_hide);
  Base::metatable_->RegisterObjectFunctor("Disable", &Base::Base::lua_disable);
  Base::metatable_->RegisterObjectFunctor("Enable", &Base::Base::lua_enable);
  Base::metatable_->RegisterObjectFunctor("IsVisible", 
                                          &Base::Base::lua_isvisiable);
  Base::metatable_->RegisterObjectFunctor("SetForce", 
                                          &Base::Base::lua_setforce);
  Base::metatable_->RegisterObjectFunctor("SetToolTip", 
                                          &Base::Base::lua_set_tooltip);
  Base::metatable_->RegisterObjectFunctor("CaptureInput", 
                                          &Base::Base::lua_captureinput);
  Base::metatable_->RegisterObjectFunctor("CenterWindow", 
                                          &Base::Base::lua_center);
  Base::metatable_->RegisterObjectFunctor("SetWindowCenter", 
                                          &Base::Base::lua_setcenter);
  Base::metatable_->RegisterObjectFunctor("SetClippedByParent", 
                                          &Base::Base::lua_setclipped_byparent);
  Base::metatable_->RegisterObjectFunctor("AutoMousePosition", 
                                          &Base::Base::lua_auto_mouseposition);
  Base::metatable_->RegisterObjectFunctor("SetAlpha", 
                                          &Base::Base::lua_setalpha);
  Base::metatable_->RegisterObjectFunctor(
      "SetAreaAndTexCoord", 
      &Base::Base::lua_setarea_and_texturecoord);
  Base::metatable_->RegisterObjectFunctor("CreateChildWindow",
                                          &Base::Base::lua_createchild);
  Base::metatable_->RegisterObjectFunctor("RemoveChildWindow", 
                                          &Base::Base::lua_removechild);
  Base::metatable_->RegisterObjectFunctor("DebugWindowInfo", 
                                          &Base::Base::lua_debuginfo);
  Base::metatable_->RegisterObjectFunctor("SetEvent", 
                                          &Base::Base::lua_setevent);
  Base::metatable_->RegisterObjectFunctor("SetPosition", 
                                          &Base::Base::lua_setposition);
  Base::metatable_->RegisterObjectFunctor("GetPosition", 
                                          &Base::Base::lua_getposition);
  /* } base */

  /* progress { */
  progressbar::Base::metatable_ = new LuaPlus::LuaObject;
  *progressbar::Base::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ProgressBar");
  progressbar::Base::metatable_->SetMetaTable(*Base::metatable_);
  progressbar::Base::metatable_->SetObject("__index", 
                                           *progressbar::Base::metatable_);
  progressbar::Base::metatable_->RegisterObjectFunctor(
      "SetProgress", 
      &progressbar::Base::lua_setprogress);
  progressbar::Super::metatable_ = new LuaPlus::LuaObject;
  *progressbar::Super::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_SuperProgressBar");
  progressbar::Super::metatable_->SetMetaTable(*progressbar::Base::metatable_);
  progressbar::Super::metatable_->SetObject("__index", 
                                           *progressbar::Base::metatable_);
  /* } progress */

  /* button { */
  button::Action::metatable_ = new LuaPlus::LuaObject;
  *button::Action::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ActionButton");
  button::Action::metatable_->SetMetaTable(*Base::metatable_);
  button::Action::metatable_->SetObject("__index", *button::Action::metatable_);
  button::Action::metatable_->RegisterObjectFunctor(
      "SetActionItem",
      button::Action::lua_setitem);
  button::Action::metatable_->RegisterObjectFunctor(
      "DoAction",
      button::Action::lua_do);
  button::Action::metatable_->RegisterObjectFunctor(
      "DoSubAction",
      button::Action::lua_dosub);
  button::Action::metatable_->RegisterObjectFunctor(
      "SetPushed",
      button::Action::lua_setpushed);
  button::Action::metatable_->RegisterObjectFunctor(
      "SetFlash",
      button::Action::lua_setflash);
  button::Action::metatable_->RegisterObjectFunctor(
      "Gloom",
      button::Action::lua_gloom);
  button::Action::metatable_->RegisterObjectFunctor(
      "Bright",
      button::Action::lua_bright);
  button::Action::metatable_->RegisterObjectFunctor(
      "SetActionSystemKeyState",
      button::Action::lua_keystate);
  button::Action::metatable_->RegisterObjectFunctor(
      "GetActionItemId",
      button::Action::lua_get_itemid);
  button::Action::metatable_->RegisterObjectFunctor(
      "GetActionItemDefineId",
      button::Action::lua_get_item_defineid);
  button::Action::metatable_->RegisterObjectFunctor(
      "SetLogicItemData",
      button::Action::lua_set_logicitem_data);
  button::Action::metatable_->RegisterObjectFunctor(
      "SetActionItemIconName",
      button::Action::lua_set_item_iconname);
  button::Action::metatable_->RegisterObjectFunctor(
      "SetNormalImage",
      button::Action::lua_set_normalimage);

  //check button as check box use
  button::Check::metatable_ = new LuaPlus::LuaObject;
  *button::Check::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ImageCheckbox");
  button::Check::metatable_->SetMetaTable(*Base::metatable_);
  button::Check::metatable_->SetObject("__index", *button::Check::metatable_);
  button::Check::metatable_->RegisterObjectFunctor("SetCheck", 
                                                   button::Check::lua_set);
  button::Check::metatable_->RegisterObjectFunctor("GetCheck",
                                                   button::Check::lua_get);
  /* } button */

  /* menu { */
  menu::Pop::metatable_ = new LuaPlus::LuaObject;
  *menu::Pop::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_PopMenu");
  menu::Pop::metatable_->SetMetaTable(*Base::metatable_);
  menu::Pop::metatable_->SetObject("__index", *menu::Pop::metatable_);
  menu::Pop::metatable_->RegisterObjectFunctor("OpenPopMenu", 
                                               menu::Pop::lua_openit);
  menu::Pop::metatable_->RegisterObjectFunctor("ClosePopMenu",
                                               menu::Pop::lua_closeit);
  menu::Pop::metatable_->RegisterObjectFunctor("SetPopMenuPos",
                                               menu::Pop::lua_setposition);
  /* } menu */

  /* complex { */
  Complex::metatable_ = new LuaPlus::LuaObject;
  *Complex::metatable_->GetGlobals().CreateTable(
      "MetaTable_Control_ComplexWindow");
  Complex::metatable_->SetMetaTable(*Base::metatable_);
  Complex::metatable_->SetObject("__index", *Complex::metatable_);
  Complex::metatable_->RegisterObjectFunctor("AddTextElement",
                                             Complex::lua_add_textelement);
  Complex::metatable_->RegisterObjectFunctor("AddOptionElement",
                                             Complex::lua_add_optionelement);
  Complex::metatable_->RegisterObjectFunctor("AddItemElement",
                                             Complex::lua_add_itemelement);
  Complex::metatable_->RegisterObjectFunctor("AddActionElement",
                                             Complex::lua_add_actionelement);
  Complex::metatable_->RegisterObjectFunctor("AddMoneyElement",
                                             Complex::lua_add_moneyelement);
  Complex::metatable_->RegisterObjectFunctor("AddImpactElement",
                                             Complex::lua_add_impactelement);
  Complex::metatable_->RegisterObjectFunctor("ClearAllElement",
                                             Complex::lua_clean_allelement);
  Complex::metatable_->RegisterObjectFunctor("SetTextColour",
                                             Complex::lua_set_textcolor);
  Complex::metatable_->RegisterObjectFunctor("PageEnd",
                                             Complex::lua_pageend);
  Complex::metatable_->RegisterObjectFunctor(
      "AddChatBoardElement",
      Complex::lua_add_chatboard_element);
  /* } complex */

  /* map { */
  map::scene::Base::metatable_ = new LuaPlus::LuaObject;
  *map::scene::Base::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_SceneMapWindow");
  map::scene::Base::metatable_->SetMetaTable(*Base::metatable_);
  map::scene::Base::metatable_->SetObject("__index", 
                                          *map::scene::Base::metatable_);
  map::scene::Base::metatable_->RegisterObjectFunctor(
      "SetSceneFileName",
      map::scene::Base::lua_set_filename);
  map::scene::Base::metatable_->RegisterObjectFunctor(
      "CloseSceneMap",
      map::scene::Base::lua_closeit);
  map::scene::Base::metatable_->RegisterObjectFunctor(
      "GetMouseScenePos",
      map::scene::Base::lua_get_mouseposition);
  map::scene::Base::metatable_->RegisterObjectFunctor(
      "UpdateSceneMap",
      map::scene::Base::lua_update);
  map::scene::Base::metatable_->RegisterObjectFunctor(
      "SetSceneZoomMode",
      map::scene::Base::lua_set_zoommode);
  map::scene::Base::metatable_->RegisterObjectFunctor(
      "UpdateViewRect",
      map::scene::Base::lua_update_viewrect);
  map::scene::Base::metatable_->RegisterObjectFunctor(
      "moveMapByDirection",
      map::scene::Base::lua_move_bydirection);
  map::scene::Base::metatable_->RegisterObjectFunctor(
      "AddTeamPlayerPos",
      map::scene::Base::lua_add_teamplayer_position);

  map::scene::Mini::metatable_ = new LuaPlus::LuaObject;
  *map::scene::Mini::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_Minimap");
  map::scene::Mini::metatable_->SetMetaTable(*map::scene::Base::metatable_);
  map::scene::Mini::metatable_->SetObject("__index", 
                                          *map::scene::Mini::metatable_);
  map::scene::Mini::metatable_->RegisterObjectFunctor(
      "UpdateFlag",
      map::scene::Mini::lua_updateflag);

  map::World::metatable_ = new LuaPlus::LuaObject;
  *map::World::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_WorldMapWindow");
  map::World::metatable_->SetMetaTable(*Base::metatable_);
  map::World::metatable_->SetObject("__index", *map::World::metatable_);
  map::World::metatable_->RegisterObjectFunctor(
      "InitWorldMap",
      &map::World::lua_init);
  map::World::metatable_->RegisterObjectFunctor(
      "GetCurrentSelectScene",
      &map::World::lua_getcurrent_selectscene);
  map::World::metatable_->RegisterObjectFunctor(
      "UpdateWorldMap",
      &map::World::lua_update);
  map::World::metatable_->RegisterObjectFunctor(
      "SetCityHover",
      &map::World::lua_set_cityhover);
  /* } map */

  /* listbox { */
  listbox::Base::metatable_ = new LuaPlus::LuaObject;
  *listbox::Base::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_Listbox");
  listbox::Base::metatable_->SetMetaTable(*Base::metatable_);
  listbox::Base::metatable_->SetObject("__index", *listbox::Base::metatable_);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "SetItemTooltip",
      listbox::Base::lua_set_item_tooptip);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "SetItemTooltipState",
      listbox::Base::lua_set_item_tooptip_state);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "AddItem",
      listbox::Base::lua_additem);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "SetTagText",
      listbox::Base::lua_set_tagtext);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "SetRefIndex",
      listbox::Base::lua_set_refindex);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "SetListItemText",
      listbox::Base::lua_set_itemtext);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "GetItem",
      listbox::Base::lua_getitem);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "DelItem",
      listbox::Base::lua_deleteitem);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "ClearListBox",
      listbox::Base::lua_clear);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "GetFirstSelectItem",
      listbox::Base::lua_getfirst_selectitem);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "GetFirstSelectItemString",
      listbox::Base::lua_getfirst_selectitem_string);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "SetFirstSelectItemString",
      listbox::Base::lua_setfirst_selectitem_string);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "SetItemSelect",
      listbox::Base::lua_set_itemselect);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "SetItemSelectByItemID",
      listbox::Base::lua_set_itemselect_byid);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "ClearAllSelections",
      listbox::Base::lua_clear_allselections);
  listbox::Base::metatable_->RegisterObjectFunctor(
      "GetMouseMoveItem",
      listbox::Base::lua_get_mousemove_item);

  listbox::image::Base::metatable_ = new LuaPlus::LuaObject;
  *listbox::image::Base::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ImageListbox");
  listbox::image::Base::metatable_->SetMetaTable(*listbox::Base::metatable_);
  listbox::image::Base::metatable_->SetObject(
      "__index", 
      *listbox::image::Base::metatable_);
  listbox::image::Base::metatable_->RegisterObjectFunctor(
      "AddItem", 
      &listbox::image::Base::lua_additem);

  listbox::image::Extend::metatable_ = new LuaPlus::LuaObject;
  *listbox::image::Extend::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ImageListboxEx");
  listbox::image::Extend::metatable_->SetMetaTable(*listbox::Base::metatable_);
  listbox::image::Extend::metatable_->SetObject(
      "__index", 
      *listbox::image::Extend::metatable_);
  listbox::image::Extend::metatable_->RegisterObjectFunctor(
      "AddItem", 
      &listbox::image::Extend::lua_additem);
  /* } listbox */

  /* combobox { */
  combobox::Base::metatable_ = new LuaPlus::LuaObject;
  *combobox::Base::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ComboBox");
  combobox::Base::metatable_->SetMetaTable(*Base::metatable_);
  combobox::Base::metatable_->SetObject("__index", 
                                        *combobox::Base::metatable_);
  combobox::Base::metatable_->RegisterObjectFunctor(
      "ComboBoxAddItem",
      &combobox::Base::lua_additem);
  combobox::Base::metatable_->RegisterObjectFunctor(
      "ResetList",
      &combobox::Base::lua_resetlist);
  combobox::Base::metatable_->RegisterObjectFunctor(
      "GetCurrentSelect",
      &combobox::Base::lua_get_currentselect);
  combobox::Base::metatable_->RegisterObjectFunctor(
      "SetCurrentSelect",
      &combobox::Base::lua_set_currentselect);
  combobox::Base::metatable_->RegisterObjectFunctor(
      "SetItemText",
      &combobox::Base::lua_set_itemtext);
  /* } combobox */

  /* image { */
  image::Static::metatable_ = new LuaPlus::LuaObject;
  *image::Static::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_StaticImage");
  image::Static::metatable_->SetMetaTable(*Base::metatable_);
  image::Static::metatable_->SetObject("__index", *image::Static::metatable_);
  image::Static::metatable_->RegisterObjectFunctor(
      "SetImage",
      &image::Static::lua_set);
  image::Static::metatable_->RegisterObjectFunctor(
      "SetImageColor",
      &image::Static::lua_setcolor);
  /* { image */

  /* scroll { */
  scroll::Bar::metatable_ = new LuaPlus::LuaObject;
  *scroll::Bar::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ScrollBar");
  scroll::Bar::metatable_->SetMetaTable(*Base::metatable_);
  scroll::Bar::metatable_->SetObject("__index", *scroll::Bar::metatable_);
  scroll::Bar::metatable_->RegisterObjectFunctor(
      "SetPosition",
      &scroll::Bar::lua_setposition);
  scroll::Bar::metatable_->RegisterObjectFunctor(
      "GetPosition",
      &scroll::Bar::lua_getposition);

  scroll::Info::metatable_ = new LuaPlus::LuaObject;
  *scroll::Info::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ScrollInfo");
  scroll::Info::metatable_->SetMetaTable(&Base::metatable_);
  scroll::Info::metatable_->SetObject("__index", *scroll::Info::metatable_);
  scroll::Info::metatable_->RegisterObjectFunctor(
      "SetScrollInfo",
      &scroll::Info::lua_set);
  /* } scroll */

  /* tooltip { */
  tooltip::Super::metatable_ = new LuaPlus::LuaObject;
  *tooltip::Super::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_SuperTooltip");
  tooltip::Super::metatable_->SetMetaTable(*Base::metatable_);
  tooltip::Super::metatable_->SetObject("__index", *tooltip::Super::metatable_);
  tooltip::Super::metatable_->RegisterObjectFunctor(
      "PositionSelf",
      &tooltip::Super::lua_positionself);
  tooltip::Super::metatable_->RegisterObjectFunctor(
      "modifyWidth",
      &tooltip::Super::lua_modifywidth);
  /* } tooltip */

  /* mesh { */
  Mesh::metatable_ = new LuaPlus::LuaObject;
  *Mesh::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_MeshWindow");
  Mesh::metatable_->SetMetaTable(*Base::metatable_);
  Mesh::metatable_->SetObject("__index", *Mesh::metatable_);
  Mesh::metatable_->RegisterObjectFunctor("SetFakeObject",
                                          &Mesh::lua_set_fakeobject);
  Mesh::metatable_->RegisterObjectFunctor("RotateBegin",
                                          &Mesh::lua_rotatestart);
  Mesh::metatable_->RegisterObjectFunctor("RotateEnd",
                                          &Mesh::lua_rotateend);
  Mesh::metatable_->RegisterObjectFunctor("GetObjName",
                                          &Mesh::lua_get_objectname);
  Mesh::metatable_->RegisterObjectFunctor("SetUnFakeObject",
                                          &Mesh::lua_set_unfake_object);
  /* } mesh */

  /* chat { */
  chat::Channel::metatable_ = new LuaPlus::LuaObject;
  *chat::Channel::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ChatChannel");
  chat::Channel::metatable_->SetMetaTable(*Base::metatable_);
  chat::Channel::metatable_->SetObject("__index", *chat::Channel::metatable_);
  chat::Channel::metatable_->RegisterObjectFunctor(
      "ClearAllChannel",
      &chat::Channel::lua_clearall);
  chat::Channel::metatable_->RegisterObjectFunctor(
      "AddChannel",
      &chat::Channel::lua_add);

  chat::History::metatable_ = new LuaPlus::LuaObject;
  *chat::History::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ChatHistory");
  chat::History::metatable_->SetMetaTable(*Base::metatable_);
  chat::History::metatable_->SetObject("__index", *chat::History::metatable_);
  chat::History::metatable_->RegisterObjectFunctor(
      "InsertChatString",
      &chat::History::lua_insertstring);
  chat::History::metatable_->RegisterObjectFunctor(
      "RemoveAllChatString",
      &chat::History::lua_remove_allstring);
  chat::History::metatable_->RegisterObjectFunctor(
      "ScrollToEnd",
      &chat::History::lua_scroll_toend);
  chat::History::metatable_->RegisterObjectFunctor(
      "ExtendClearRegion",
      &chat::History::lua_extend_clearregion);
  /* } chat */

  /* list { */
  list::Control::metatable_ = new LuaPlus::LuaObject;
  *list::Control::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_CtrlListWindow");
  list::Control::metatable_->SetMetaTable(*Base::metatable_);
  list::Control::metatable_->SetObject("__index", *list::Control::metatable_);
  list::Control::metatable_->RegisterObjectFunctor(
      "AddColumn",
      &list::Control::lua_addcolumn);
  list::Control::metatable_->RegisterObjectFunctor(
      "InsertColumn",
      &list::Control::lua_insertcolumn);
  list::Control::metatable_->RegisterObjectFunctor(
      "AddNewItem",
      &list::Control::lua_add_newitem);
  list::Control::metatable_->RegisterObjectFunctor(
      "SetItemText",
      &list::Control::lua_set_itemtext);
  list::Control::metatable_->RegisterObjectFunctor(
      "SetItemData",
      &list::Control::lua_set_itemdata);
  list::Control::metatable_->RegisterObjectFunctor(
      "DeleteItem",
      &list::Control::lua_deleteitem);
  list::Control::metatable_->RegisterObjectFunctor(
      "RemoveAllItem",
      &list::Control::lua_remove_allitem);
  list::Control::metatable_->RegisterObjectFunctor(
      "GetItemText",
      &list::Control::lua_get_itemtext);
  list::Control::metatable_->RegisterObjectFunctor(
      "GetItemCount",
      &list::Control::lua_get_itemcount);
  list::Control::metatable_->RegisterObjectFunctor(
      "GetColumnCount",
      &list::Control::lua_get_columncount);
  list::Control::metatable_->RegisterObjectFunctor(
      "GetSelectItem",
      &list::Control::lua_get_selectitem);
  list::Control::metatable_->RegisterObjectFunctor(
      "RemoveColumn",
      &list::Control::lua_removecolumn);
  list::Control::metatable_->RegisterObjectFunctor(
      "SetSelectItem",
      &list::Control::lua_set_selectitem);

  list::Info::metatable_ = new LuaPlus::LuaObject;
  *list::Info::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_InfoListWindow");
  list::Info::metatable_->SetMetaTable(*Base::metatable_);
  list::Info::metatable_->SetObject("__index", *list::Info::metatable_);
  list::Info::metatable_->RegisterObjectFunctor("AddInfo", 
                                                &list::Info::lua_add);
  /* } list */

  /* animation { */
  Animation::metatable_ = new LuaPlus::LuaObject;
  *Animation::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_AnimateWindow");
  Animation::metatable_->SetMetaTable(*Base::metatable_);
  Animation::metatable_->SetObject("__index", *Animation::metatable_);
  Animation::metatable_->RegisterObjectFunctor("Play", &Animation::lua_play);
  /* } animation */

  /* softkey { */
  SoftKey::metatable_ = new LuaPlus::LuaObject;
  *SoftKey::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_SoftKeyWindow");
  SoftKey::metatable_->SetMetaTable(*Base::metatable_);
  SoftKey::metatable_->SetObject("__index", *SoftKey::metatable_);
  SoftKey::metatable_->RegisterObjectFunctor("SetAimEditBox",
                                             SoftKey::lua_setaim_editbox);
  /* } softkey */

  /* editbox { */
  editbox::Base::metatable_ = new LuaPlus::LuaObject;
  *editbox::Base::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_EditBox");
  editbox::Base::metatable_->SetMetaTable(*Base::metatable_);
  editbox::Base::metatable_->SetObject("__index", *editbox::Base::metatable_);
  editbox::Base::metatable_->RegisterObjectFunctor(
      "SetItemElementsString",
      &editbox::Base::lua_set_item_elementstring);
  editbox::Base::metatable_->RegisterObjectFunctor(
      "GetItemElementsString",
      &editbox::Base::lua_get_item_elementstring);
  editbox::Base::metatable_->RegisterObjectFunctor(
      "SetBlinkText",
      &editbox::Base::lua_set_blinktext);
  editbox::Base::metatable_->RegisterObjectFunctor(
      "SetSelected",
      &editbox::Base::lua_setselected);

  editbox::MultiLine::metatable_ = new LuaPlus::LuaObject;
  *editbox::MultiLine::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_MultiLineEditBox");
  editbox::MultiLine::metatable_->SetMetaTable(*Base::metatable_);
  editbox::MultiLine::metatable_->SetObject("__index", 
                                            *editbox::MultiLine::metatable_);
  editbox::MultiLine::metatable_->RegisterObjectFunctor(
      "SetItemElementsString",
      &editbox::MultiLine::lua_set_item_elementstring);
  editbox::MultiLine::metatable_->RegisterObjectFunctor(
      "GetItemElementsString",
      &editbox::MultiLine::lua_get_item_elementstring);
  /* } editbox */

  /* tree { */
  Tree::metatable_ = new LuaPlus::LuaObject;
  *Tree::metatable_ = luastate->GetGlobals().CreateTable( 
      "MetaTable_Control_Tree");
  Tree::metatable_->SetMetaTable(*Base::metatable_);
  Tree::metatable_->SetObject("__index", *Tree::metatable_);
  Tree::metatable_->RegisterObjectFunctor("AddItem", &Tree::lua_additem);
  Tree::metatable_->RegisterObjectFunctor("ClearTree", &Tree::lua_clear);
  Tree::metatable_->RegisterObjectFunctor("GetFirstSelectItem", 
                                          &Tree::lua_getfirst_selectitem);
  Tree::metatable_->RegisterObjectFunctor(
      "GetFirstSelectItemString",
      &Tree::lua_getfirst_selectitem_string);
  Tree::metatable_->RegisterObjectFunctor(
      "SetFirstSelectItemString",
      &Tree::lua_setfirst_selectitem_string);
  Tree::metatable_->RegisterObjectFunctor(
      "SetItemSelectByItemID",
      &Tree::lua_setitem_select_byid);
  Tree::metatable_->RegisterObjectFunctor(
      "SetItemToggle",
      &Tree::lua_setitem_toggle);
  /* } tree */
}

void Base::destroy_metatable() {
  //delete from the last to first
  SAFE_DELETE(Tree::metatable_); //tree
  //editbox
  SAFE_DELETE(editbox::Base::metatable_);
  SAFE_DELETE(editbox::MultiLine::metatable_);
  //softkey
  SAFE_DELETE(SoftKey::metatable_);
  //animation
  SAFE_DELETE(Animation::metatable_);
  //list
  SAFE_DELETE(list::Info::metatable_);
  SAFE_DELETE(list::Control::metatable_);
  //chat
  SAFE_DELETE(chat::History::metatable_);
  SAFE_DELETE(chat::Channel::metatable_);
  //mesh
  SAFE_DELETE(Mesh::metatable_);
  //tooltip
  SAFE_DELETE(tooltip::Super::metatable_);
  //scroll
  SAFE_DELETE(scroll::Info::metatable_);
  SAFE_DELETE(scroll::Bar::metatable_);
  //image
  SAFE_DELETE(image::Static);
  //combobox
  SAFE_DELETE(combobox::Base::metatable_);
  //listbox
  SAFE_DELETE(listbox::image::Extend::metatable_);
  SAFE_DELETE(listbox::image::Base::metatable_);
  SAFE_DELETE(listbox::Base::metatable_);
  //map
  SAFE_DELETE(map::World::metatable_);
  SAFE_DELETE(map::scene::Mini::metatable_);
  SAFE_DELETE(map::scene::Base::metatable_);
  //complex
  SAFE_DELETE(Complex::metatable_);
  //menu
  SAFE_DELETE(menu::Pop::metatable_);
  //button
  SAFE_DELETE(button::Check::metatable_);
  SAFE_DELETE(button::Action::metatable_);
  //progress
  SAFE_DELETE(progressbar::Super::metatable_);
  SAFE_DELETE(progressbar::Base::metatable_);
  //base
  SAFE_DELETE(Base::metatable_);
}

int32_t Base::lua_setproperty(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsString()) return 0;
  CEGUI::Window* window = window_;
  if (!args[4].IsNil()) {
    if (args[4].IsString()) {
      const char* windowname = args[4].GetString();
      if (0 == strcmp("Parent", windowname)) {
        window = window_->getParent();
      }
      else {
        window = CEGUI::WindowManager::getSingleton().getWindow(windowname);
      }
    }
  }
  const char* name = args[2].GetString();
  const char* value = args[3].GetString();
  STRING full_iconname, iconname;
  if (0 == strcmp("ShortImage", name)) {
    STRING mbcs = args[3].GetString();
    CEGUI::String32 str;
    vgui_string::System::getself()->parsestring_runtime(mbcs, str);
    window->setText(str);
    return 0;
  }
  if (0 == strcmp("Tooltip", name)) {
    STRING mbcs = args[3].GetString();
    CEGUI::String32 str;
    vgui_string::System::getself()->parsestring_runtime(mbcs, str);
    window->setProperty(name, str.c_str());
    return 0;
  }
  try {
    window->setProperty(name, value);
  }
  catch(...) {

  }
  return 0;
}

int32_t Base::lua_setevent(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsString()) return 0;
  CEGUI::Window* window = window_;
  if (!args[4].IsNil()) {
    if (args[4].IsString()) {
      const char* windowname = args[4].GetString();
      if (0 == strcmp("Parent", windowname)) {
        window = window_->getParent();
      }
      else {
        window = CEGUI::WindowManager::getSingleton().getWindow(windowname);
      }
    }
  }
  CEGUI::String eventname(args[2].GetString());
  CEGUI::String functionname(args[3].GetString());
  if (window) {
    window->subscribeEvent(eventname, CEGUI::ScriptFunctor(functionname));
  }
  return 1;
}

int32_t Base::lua_center(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  CEGUI::Window* parent = window->getParent();
  if (parent) {
    CEGUI::Point position;
    CEGUI::Rect rect = parent->getAbsoluteRect();
    position.d_x = (rect.d_left + rect.d_right) / 2 - 
                   window_->getAbsoluteRect().getWidth() / 2;
    position.d_y = (rect.d_top + rect.d_bottom ) / 2 - 
                   window_->getAbsoluteRect().getHeight() / 2;
    window_->setPosition(CEGUI::Absolute, position);
  }
  return 0;
}

int32_t Base::lua_setcenter(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsInteger()) return 0;
  CEGUI::Point position;
  position.d_x = 
    args[2].GetInteger() - window_->getAbsoluteRect().getWidth() / 2;
  position.d_y =
    args[3].GetInteger() - window_->getAbsoluteRect().getHeight() / 2;
  window_->setPosition(CEGUI::Absolute, position);
  return 0;
}

int32_t Base::lua_setclipped_byparent(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger()) return 0;
  uint8_t flag = args[2].GetInteger();
  if (0 == flag) {
    window_->setClippedByParent(false);
    window_->setAlwaysOnTop(true);
  }
  else {
    window_->setClippedByParent(true);
  }
  return 0;
}

int32_t Base::lua_auto_mouseposition(LuaPlus::LuaState* luastate) { 
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsString()) return 0;
  float x = args[2].GetFloat();
  float y = args[3].GetFloat();
  //重新计算
  float width = window_->getAbsoluteWidth();
  float height = window_->getAbsoluteHeight();
  float screenwidth = 
    vgui_window::Manager::get_clientscreen()->getAbsoluteWidth();
  float screenheight =
    vgui_window::Manager::get_clientscreen()->getAbsoluteHeight();
  if (x + width + 5.0f > screenwidth) {
    x -= width + 5.0f;
  }
  else {
    x += 5.0f;
  }
  if (y + height + 5.0f > screenheight) {
    y -= height + 5.0f;
  }
  else {
    y += 5.0f;
  }
  CEGUI::Point position;
  position.d_x = x;
  position.d_y = y;
  window_->setPosition(CEGUI::Absolute, position);
  return 0;
}

int32_t Base::lua_getproperty(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  CEGUI::Window* window = window_;
  if (!args[3].IsNil()) {
    if (args[3].IsString()) {
      const char* windowname = args[3].GetString();
      if (0 == strcmp("Parent", windowname)) {
        window = window_->getParent();
      }
      else {
        window = CEGUI::WindowManager::getSingleton().getWindow(windowname);
      }
    }
  }
  try {
    CEGUI::String str = window->getProperty(args[2].GetString());
    STRING out;
    vgui_string::System::getself()->parsestring_runtime(str, out);
    luastate->PushString(out);
  }
  catch(...) {
    luastate->PushString("");
  }
  return 1;
}

int32_t Base::lua_settext(LuaPlus::LuaState* luastate) { 
  LuaStack args(luastate);
  if (args[2].IsInteger()) {
    char value[128] = {0};
    sprintf(value, "%d", args[2].GetInteger());
    STRING str;
    vgui_string::System::getself()->parsestring_runtime(value, str);
    window_->setText((CEGUI::String32)(CEGUI::utf8*)(str.c_str()));
  }
  else if (args[2].IsString()) {
    STRING mbcs = args[2].GetString();
    CEGUI::String32 str;
    vgui_string::System::getself()->parsestring_runtime(mbcs, str);
    window_->setText(str);
  }
  return 0;
}

int32_t Base::lua_hide(LuaPlus::LuaState* luastate) {
  window_->setVisible(false);
  if (window_->testClassName("Editbox")) {
    window_->releaseInput();
  }
  return 0;
}

int32_t Base::lua_gettext(LuaPlus::LuaState* luastate) {
  STRING mbcs = window_->getText().c_str();
  STRING str;
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  luastate->PushString(str.c_str());
  return 1;
}

int32_t Base::lua_set_textoriginal(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  STRING mbcs = args[2].GetString();
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  window_->setTextOriginal(str);
  return 0;
}

int32_t Base::lua_setalpha(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsNumber()) return 0;
  float value = args[2].GetFloat();
  window_->setAlpha(value);
  return 1;
}

int32_t Base::lua_setforce(LuaPlus::LuaState* luastate) {
  window_->activate();
  return 0;
}

int32_t Base::lua_setarea_and_texturecoord(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[4].IsInteger()) return 0;
  if (!args[3].IsNumber() || !args[5].IsNumber()) return 0;
  window_->setAreaAndTexCoord(args[2].GetInteger(),
                              args[3].GetFloat(),
                              args[4].GetInteger(),
                              args[5].GetFloat());
  return 0;
}

int32_t Base::lua_createchild(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsString()) return 0;
  STRING windowtype = args[2].GetString();
  STRING windowname = args[3].GetString();
  CEGUI::Window* window = CEGUI::WindowManager::getSingleton().createWindow(
      windowtype,
      windowname);
  window_->addChildWindow(window);
  return 0;
}

int32_t Base::lua_removechild(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  STRING windowname = args[2].GetString();
  CEGUI::Window* window =  
    CEGUI::WindowManager::getSingleton().getWindow(windowname);
  if (window) window_->removeChildWindow(window);
  return 0;
}

int32_t Base::lua_debuginfo(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  //do something in here
  return 0;
}

int32_t Base::lua_getposition(LuaPlus::LuaState* luastate) {
  luastate->PushNumber(window_->getPosition(CEGUI::Absolute).d_x);
  luastate->PushNumber(window_->getPosition(CEGUI::Absolute).d_y);
  return 2;
}

int32_t Base::lua_setposition(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsInteger() || !args[4].IsInteger())
    return 0;
  CEGUI::Point position;
  position.d_x = args[3].GetInteger();
  position.d_y = args[4].GetInteger();
  CEGUI::MetricsMode metricsmode;
  if (0 == args[2].GetInteger()) {
    metricsmode = CEGUI::Relative;
  }
  else if (1 == args[2].GetInteger()) {
    metricsmode = CEGUI::Absolute;
  }
  else {
    metricsmode = CEGUI::Inherited;
  }
  window_->setPosition(metricsmode, position);
  return 0;
}

int32_t Base::lua_set_tooltip(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (args[2].IsString()) return 0;
  STRING mbcs = args[2].GetString();
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  window_->setProperty("Tooltip", str.c_str());
  return 0;
}

int32_t Base::lua_transtext(LuaPlus::LuaState* luastate) {
  CEGUI::String32 str = window_->getTextOriginal();
  if (!str.empty()) {
    STRING mbsc;
    vgui_string::System::utf8_to_mbcs(str.c_st(), mbcs);
    CEGUI::String32 out;
    vgui_string::System::getself()->parsestring_runtime(mbcs, out);
    window_->setText(out);
  }
  return 0;
}

int32_t Base::lua_captureinput(LuaPlus::LuaState* luastate) { 
  window_->activate();
  window_->captureInput();
  return 0;
}

int32_t Base::lua_gettype(LuaPlus::LuaState* luastate) {
  luastate->PushString(window_->getWidgetType().c_str());
  return 1;
}

int32_t Base::lua_getname(LuaPlus::LuaState* luastate) { 
  luastate->PushString(window_->getName().c_str());
  return 1;
}

int32_t Base::lua_show(LuaPlus::LuaState* luastate) {
  window_->setVisible(true);
  return 0;
}

int32_t Base::lua_disable(LuaPlus::LuaState* luastate) {
  window_->setEnabled(false);
  return 0;
}

int32_t Base::lua_enable(LuaPlus::LuaState* luastate) {
  window_->setEnabled(true);
  return 0;
}

int32_t Base::lua_isvisible(LuaPlus::LuaState* luastate) {
  luastate->PushBoolean(window_->isVisible());
  return 1;
}

} //namespace window

} //namespace vgui_luacontrol
