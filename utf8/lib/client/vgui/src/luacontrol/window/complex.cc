#include "vgui/luacontrol/window/complex.h"

namespace vgui_luacontrol {

namespace window {

LuaPlus::LuaObject* Complex::metatable_ = NULL;

LuaPlus::LuaObject* Complex::get_metatable() {
  return metatable_;
}

int32_t Complex::lua_add_textelement(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  STRING mbcs = args[2].GetString();
  CEGUI::String32 str;
  CEGUI::FontBase* font = NULL;
  CEGUI::IFalagardComplexWindow* complexwindow = 
    dynamic_cast<CEGUI::IFalagardComplexWindow*>(
        dynamic_cast<CEGUI::FalagardComplexWindow*>(window_));
  if (args[3].IsString()) {
    STRING mbcs_font = args[3].GetString();
    CEGUI::String32 fontstr;
    vgui_string::System::getself()->parsestring_runtime(mbcs_font, fontstr);
    CEGUI::FontManager* fontmanager = CEGUI::FontManager::getSingletonPtr();
    font = fontmanager->getFont(fontstr);
  }
  uint8_t typeset = 4;
  STRING mbcs_extral;
  const char* temp = args[2].GetString();
  const char* delimiter = strchr(temp, '@');
  if (delimiter) {
    mbcs.assign(delimiter + 2);
    mbcs_extralassign(delimiter + 1, delimiter + 2);
    typeset = atoi(&mbcs_extral.at(0));
  }
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  complexwindow->AddChildElement_Text(str, 
                                      font, 
                                      (CEGUI::TextFormatting)typeset);
  return 0;
}

int32_t Complex::lua_add_chatboard_element(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  STRING mbcs = args[2].GetString();
  CEGUI::String32 str;
  CEGUI::FontBase* font = NULL;
  CEGUI::IFalagardComplexWindow* complexwindow = 
    dynamic_cast<CEGUI::IFalagardComplexWindow*>(
        dynamic_cast<CEGUI::FalagardComplexWindow*>(window_));
  if (args[3].IsString()) {
    STRING mbcs_font = args[3].GetString();
    CEGUI::String32 fontstr;
    vgui_string::System::getself()->parsestring_runtime(mbcs_font, fontstr);
    CEGUI::FontManager* fontmanager = CEGUI::FontManager::getSingletonPtr();
    font = fontmanager->getFont(fontstr);
  }
  uint8_t typeset = 4;
  STRING mbcs_extral;
  const char* temp = args[2].GetString();
  const char* delimiter = strchr(temp, '@');
  if (delimiter) {
    mbcs.assign(delimiter + 2);
    mbcs_extralassign(delimiter + 1, delimiter + 2);
    typeset = atoi(&mbcs_extral.at(0));
  }
  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  complexwindow->AddChildElement_ChatBoard(str, NULL);
  return 0;
}

int32_t Complex::lua_add_optionelement(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  STRING mbcs;
  STRING mbcs_extral;
  STRING mbcs_extra2;
  STRING mbcs_extra3;
  //南海冰妖#21101,-1$-1
  const char* temp = args[2].GetString();
  const char* delimiter1 = strchr(temp, '#');
  const char* delimiter2 = strchr(temp, ' ');
  const char* delimiter3 = strchr(temp, '$');
  if ((delimiter1 && (!delimiter2 || !delimiter3)) ||
      (delimiter2 && (!delimiter1 || !delimiter3)) || 
      (delimiter3 && (!delimiter1 || !delimiter2))) {
    VENGINE_ASSERT(delimiter1 && delimiter2 &&delimiter3);
  }
  if (delimiter1 && delimiter2 && delimiter3) {
    mbcs.assign(temp, delimiter1 - temp);
    mbcs_extral.assign(delimiter1 + 1, delimiter2 - 1 - delimiter1);
    mbcs_extra2.assign(delimiter2 + 1, delimiter3 - 1 - delimiter2);
    mbcs_extra3.assign(delimiter3 + 1);
  }
  else {
    mbcs.assign(temp);
    mbcs_extral.assign("-1");
    mbcs_extra2.assign("-1");
    mbcs_extra3.assign("-1");
  }
  CEGUI::String32 str;
  CEGUI::String32 extra1;
  CEGUI::String32 extra2;
  CEGUI::String32 extra3;

  vgui_string::System::getself()->parsestring_runtime(mbcs, str);
  vgui_string::System::getself()->parsestring_runtime(mbcs_extral, extra1);
  vgui_string::System::getself()->parsestring_runtime(mbcs_extra2, extra2);
  vgui_string::System::getself()->parsestring_runtime(mbcs_extra3, extra3);
  //创建新的选项
  CEGUI::IFalagardComplexWindow* complexwindow = 
   dynamic_cast<CEGUI::IFalagardComplexWindow*>(
        dynamic_cast<CEGUI::FalagardComplexWindow*>(window_));
  complexwindow->AddChildElement_Option(str, extra1, extra2, extra3);
  return 0;
}

int32_t Complex::lua_add_itemelement(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsInteger() || !args[4].IsInteger())
    return 0;
  int32_t itemid = args[2].GetInteger();
  int32_t itemnumber = args[3].GetInteger();
  bool radio = 1 == args[4].GetInteger();
  bool rearrange = false;
  if (args[5].IsInteger()) rearrange = 1 == args[5].GetInteger();
  vengine_game::object::Item* item = g_game_objectsystem->finditem(itemid);
  if (NULL == item) return 0;
  STRING icon_fullname = vgui_icon::Manager::getself()->get_icon_fullname(
      item->geticon());
  STRING iconname_str;
  vgui_string::System::mbcs_to_utf8(icon_fullname.c_str(), iconname_str);
  CEGUI::String32 description;
  vgui_string::System::getself()->parsestring_runtime(item->getname(), 
                                                      description);
  CEGUI::IFalagardComplexWindow* complexwindow = 
   dynamic_cast<CEGUI::IFalagardComplexWindow*>(
        dynamic_cast<CEGUI::FalagardComplexWindow*>(window_));
  complexwindow->AddChildElement_Item(iconname_str, 
                                      description, 
                                      radio, 
                                      rearrange);
  return 0;
}

int32_t Complex::lua_add_actionelement(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsInteger() || !args[3].IsInteger() || !args[4].IsInteger())
    return 0;
  int32_t itemid = args[2].GetInteger();
  int32_t itemnumber = args[3].GetInteger();
  bool radio = 1 == args[4].GetInteger();
  bool rearrange = false;
  if (args[5].IsInteger()) rearrange = 1 == args[5].GetInteger();
  vengine_game::object::Item* item = g_game_objectsystem->finditem(itemid);
  if (NULL == item) return 0;
  STRING icon_fullname = vgui_icon::Manager::getself()->get_icon_fullname(
      item->geticon());
  STRING iconname_str;
  vgui_string::System::mbcs_to_utf8(icon_fullname.c_str(), iconname_str);
  CEGUI::String32 description;
  vgui_string::System::getself()->parsestring_runtime(item->getname(), 
                                                      description);
  CEGUI::IFalagardComplexWindow* complexwindow = 
   dynamic_cast<CEGUI::IFalagardComplexWindow*>(
        dynamic_cast<CEGUI::FalagardComplexWindow*>(window_));
  CEGUI::IFalagardActionButton* actionbutton =
    dynamic_cast<CEGUI::IFalagardActionButton*>
      (dynamic_cast<CEGUI::FalagardActionButton*>(
          complexwindow->AddChildElement_Action(
            iconname_str, itemid, radio, rearrange)));
  if (item->get_defineid() != 20005020) {
    //保留在这里，以前的随机物品不显示提示信息  
  }
  actionbutton->subscribeMouseEnterEvent(
      CEGUI::Event::Subscriber(
        &vgui_base::System::handle_actionbutton_mouseenter, 
        vgui_base::System::getself()));
  actionbutton->subscribeMouseLeaveEvent(
      CEGUI::Event::Subscriber(
        &vgui_base::System::handle_actionbutton_mouseleave, 
        vgui_base::System::getself()));
  CEGUI::Window* window = dynamic_cast<CEGUI::Window*>(
      dynamic_cast<CEGUI::FalagardActionButton*>(actionbutton));
  window->subscribeEvent(
      "ParentHidden", 
      CEGUI::Event::Subscriber(
        &vgui_base::System::handle_actionbutton_parenthidden, 
        vgui_base::System::getself());
  return 0;
}

int32_t Complex::lua_add_impactelement(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  STRING icon_fullname = 
    vgui_icon::Manager::getself()->get_icon_fullname(args[2].GetString());
  CEGUI::String iconname_str;
  vgui_string::System::mbcs_to_utf8(icon_fullname, iconname_str);
  CEGUI::String32 description;
  vgui_string::System::mbcs_to_utf8("", description);
  CEGUI::IFalagardComplexWindow* complexwindow = 
    dynamic_cast<CEGUI::IFalagardComplexWindow*>(
      dynamic_cast<CEGUI::FalagardComplexWindow*>(window_));
  complexwindow->AddChildElement_Item(iconname_str, description, 0, 0);
  return 0;
}

int32_t Complex::lua_add_moneyelement(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[2].IsString()) return 0;
  CEGUI::IFalagardComplexWindow* complexwindow = 
    dynamic_cast<CEGUI::IFalagardComplexWindow*>(
      dynamic_cast<CEGUI::FalagardComplexWindow*>(window_));
  complexwindow->AddChildElement_Money(atoi(args[2].GetString()));
  return 0;
}

int32_t Complex::lua_clean_allelement(LuaPlus::LuaState* luastate) {
  CEGUI::IFalagardComplexWindow* complexwindow = 
    dynamic_cast<CEGUI::IFalagardComplexWindow*>(
      dynamic_cast<CEGUI::FalagardComplexWindow*>(window_));
  complexwindow->ClearAllElement();
  return 0;
}

int32_t Complex::lua_setcolor(LuaPlus::LuaState* luastate) {
  return 0;
}

int32_t Complex::lua_pageend(LuaPlus::LuaState* luastate) {
   CEGUI::IFalagardComplexWindow* complexwindow = 
    dynamic_cast<CEGUI::IFalagardComplexWindow*>(
      dynamic_cast<CEGUI::FalagardComplexWindow*>(window_));
  complexwindow->PageEnd();
  return 0;
}

} //namespace window

} //namespace vgui_luacontrol
