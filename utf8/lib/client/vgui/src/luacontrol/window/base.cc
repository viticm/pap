#include "vgui/luacontrol/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

LuaPlus::LuaObject* Base::metatable_ = NULL;

Base::Base(CEGUI::Window* window) {
  window_ = window;
}

Base* Base::create(CEGUI::Window* window) {

  CEGUI::String type = window->getWidgetType();

  if ("Falagard/ActionButton" == type) {
    return new ActionButton(window);
  }
  else if ("Falagard/ProgressBar" == type) {
    return new ProgressBar(window);
  }
  else if ("Falagard/SuperProgress" == type) {
    return new SuperProgressBar(window);
  }
  else if ("Falagard/PopupMenu" == type) {
    return new PopMenu(window);
  }
  else if ("Falagard/Radar" == type) {
    return new Minimap(window);
  }
  else if ("Falagard/ComplexWindow" == type) {
    return new ComplexWindow(window);
  }
  else if ("Falagard/Listbox" == type) {
    return new ListBox(window);
  }
  else if ("Falagard/ImageListbox" == type) {
    return new ImageListBox(window);
  }
  else if ("Falagard/ImageListboxEx" == type) {
    return new ImageListBoxEx(window);
  }
  else if ("Falagard/CheckBox" == type) {
    return new CheckButton(window);
  }
  else if ("Falagard/Combobox" == type) {
    return new ComboBox(window);
  }
  else if ("Falagard/StaticImage" == type) {
    return new StaticImage(window);
  }
  else if ("Falagard/Scrollbar" == type) {
    return new ScrollBar(window);
  }
  else if ("Falagard/SuperTooltip" == type) {
    return new SuperTooltip(window);
  }
  else if ("Falagard/MeshWindow" == type) {
    return new MeshWindow(window);
  }
  else if ("Falagard/ChatHistory" == type) {
    return new ChatHistory(window);
  }
  else if ("Falagard/ChatChannel" == type) {
    return new ChatChannel(window);
  }
  else if ("Falagard/SceneMap" == type) {
    return new SceneMap(window);
  }
  else if ("Falagard/WorldMap" == type) {
    return new WorldMap(window);
  }
  else if ("Falagard/InfoList" == type) {
    return new InfoList(window);
  }
  else if ("Falagard/MultiColumnList" == type) {
    return new CtrlList(window);
  }
  else if ("Falagard/SoftKeyWindow" == type) {
    return new SoftKeyWindow(window);
  }
  else if ("Falagard/Animate" == type) {
    return new AnimateWindow(window);
  }
  else if ("Falagard/IMEEditBox" == type) {
    return new EditBox(window);
  }
  else if ("Falagard/MultiIMEEditBox" == type) {
    return new MultiLineEditbox(window);
  }
  else if ("Falagard/ScrollInfo" == type) {
    return new ScrollInfo(window);
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
  Base::metatable_->RegisterObjectFunctor("SetProperty", &Base::setproperty);
  Base::metatable_->RegisterObjectFunctor("GetProperty", &Base::getproperty);
  Base::metatable_->RegisterObjectFunctor("GetType", &Base::gettype);
  Base::metatable_->RegisterObjectFunctor("GetText", &Base::gettext);
  Base::metatable_->RegisterObjectFunctor("SetText", &Base::settext);
  Base::metatable_->RegisterObjectFunctor("SetTextOriginal", 
                                          &Base::set_textoriginal);
  Base::metatable_->RegisterObjectFunctor("TransText", &Base::transtext);
  Base::metatable_->RegisterObjectFunctor("Show", &Base::show);
  Base::metatable_->RegisterObjectFunctor("Hide", &Base::hide);
  Base::metatable_->RegisterObjectFunctor("Disable", &Base::disable);
  Base::metatable_->RegisterObjectFunctor("Enable", &Base::enable);
  Base::metatable_->RegisterObjectFunctor("IsVisible", &Base::isvisiable);
  Base::metatable_->RegisterObjectFunctor("SetForce", &Base::setforce);
  Base::metatable_->RegisterObjectFunctor("SetToolTip", &Base::set_tooltip);
  Base::metatable_->RegisterObjectFunctor("CaptureInput", &Base::captureinput);
  Base::metatable_->RegisterObjectFunctor("CenterWindow", &Base::center);
  Base::metatable_->RegisterObjectFunctor("SetWindowCenter", &Base::setcenter);
  Base::metatable_->RegisterObjectFunctor("SetClippedByParent", 
                                          &Base::setclipped_byparent);
  Base::metatable_->RegisterObjectFunctor("AutoMousePosition", 
                                          &Base::auto_mouseposition);
  Base::metatable_->RegisterObjectFunctor("SetAlpha", &Base::setalpha);
  Base::metatable_->RegisterObjectFunctor("SetAreaAndTexCoord", 
                                          &Base::setarea_and_texturecoord);
  Base::metatable_->RegisterObjectFunctor("CreateChildWindow",
                                          &Base::createchild);
  Base::metatable_->RegisterObjectFunctor("RemoveChildWindow", 
                                          &Base::removechild);
  Base::metatable_->RegisterObjectFunctor("DebugWindowInfo", &Base::debuginfo);
  Base::metatable_->RegisterObjectFunctor("SetEvent", &Base::setevent);
  Base::metatable_->RegisterObjectFunctor("SetPosition", &Base::setposition);
  Base::metatable_->RegisterObjectFunctor("GetPosition", &Base::getposition);
  /* } base */

  /* progress { */
  ProgressBar::metatable_ = new LuaPlus::LuaObject;
  *ProgressBar::metatable_ = luastate->GetGlobals().CreateTable(
      "MetaTable_Control_ProgressBar");
  ProgressBar::metatable_->SetMetaTable(*Base::metatable_);
  ProgressBar::metatable_->SetObject("__index", *ProgressBar::metatable_);
  ProgressBar::metatable_->RegisterObjectFunctor("SetProgress", 
                                                 &ProgressBar::setprogress);
  /* } progress */
}

} //namespace window

} //namespace vgui_luacontrol
