#include <CEGUIPropertyHelper.h>
#include "LuaPlus.h"
#include "vgui/script/base.h"

namespace vgui_script {

class EventArgs { //CEGUI 事件参数查询接口

 public:
   EventArgs() : metetable_(NULL), eventargs_(NULL){};
   virtual ~EventArgs(){}
   LuaPlus::LuaObject* metatable_; //lua元表
   CEGUI::EventArgs* eventargs_; //参数保存

 public:
   //属性值查询
   int32_t lua_getvalue(LuaPlus::LuaState* luastate) {
     LuaState args(luastate);
     if (NULL == eventargs_ || !(args[2].IsString())) {
       luastate->PushString("");
       return 1;
     }
     STRING argname = args[2].GetString();
     if ("WindowName" == argname && eventargs_->isKindOf("Window")) {
       if ((dynamic_cast<CEGUI::WindowEventArgs*>(eventargs_))->window) {
         luastate->PushString(
             (dynamic_cast<CEGUI::WindowEventArgs*>(eventargs_))
             ->window->getName().c_str());
       }
       else {
         luastate->PushString("");
       }
     }
     else if ("HyperLinkName" == argname && 
              eventargs_->isKindOf("HyperLink")) {
       luastate->PushString(
           (dynamic_cast<CEGUI::HyperLinkEventArgs*>(eventargs_))
           ->hyperLinkName.c_str());
     }
     else if ("MousePosition" == argname && 
              eventargs_->isKindOf("Mouse")) {
       luastate->PushString(
           (dynamic_cast<CEGUI::MouseEventArgs*>(eventargs_))
           ->position.c_str());
     }
     else if ("MouseButtion" == argname &&
              eventargs_->isKindOf("Mouse")) {
       switch ((dynamic_cast<CEGUI::MouseEventArgs*>(eventargs_))->button) {
         case CEGUI::LeftButton : {
           luastate->PushString("LeftButton");
           break;
         }
         case CEGUI::RightButton : {
           luastate->PushString("RightButton");
           break;
         }
         case CEGUIE::MiddleButton : {
           luastate->PushString("MiddleButton");
           break;
         }
         case CEGUI::X1Button : {
           luastate->PushString("X1Button");
           break;
         }
         case CEGUI::X2Button : {
           luastate->PushString("X2Button");
           break;
         }
         case CEGUI::NoButton : {
           luastate->PushString("NoButton");
           break;
         }
         default: {
           luastate->PushString("");
           break;
         }
       }
     }
     else if ("MouseClickCount" == argname) {
       luastate->PushString(CEGUI::PropertyHelper::intToString(
             (dynamic_cast<CEGUI::MouseEventArgs*>(eventargs_))
             ->clickCount).c_str());
     }
     return 1;
   }
}

static EventArgs g_eventargs;

Base::Base() {
  //do nothing
}

Base::~Base() {
  //do nothing
}

void Base::executefile(const CEGUI::String& filename,
                       const CEGUI::String& resourcegroup = "") {
  CEGUI::executeScriptFile(filename, resourcegroup);
}

int32_t Base::execute_globalfunction(const CEGUI::String& functionname) {
  int32_t result = CEGUI::executeScriptGlobal(functionname);
  return result;
}

bool Base::execute_eventhandler(const CEGUI::String& handlername,
                                const CEGUI::EventArgs& eventargs) {
  const CEGUI::WindowEventArgs& eventwindow = 
    dynamic_cast<const CEGUI::WindowEventArgs&>(eventargs);
  CEGUI::Window window = eventwindow.window;
  do {
    if (!window) break;
    void* userdata = window->getUserData();
    if (userdata) {
      ((CEGUI::CUIWindowItem*)userdata)->FireUIEvent(handlername.c_str(), 
                                                     eventwindow.window);
      break;
    }
    window = window->getParent();
  } while (window);
  g_eventargs.eventargs_ = 0;
  return true;
}

void Base::startbindings() {
  LuaPlus::LuaState* luastate = g_scriptsystem->get_luastate();
  VENGINE_ASSERT(luastate);
  //全局函数
  luastate->GetGlobals().Register("GetIconFullName", 
                                  vgui_icon::System::lua_get_icon_fullname);
  g_eventargs.metatable_ = new LuaPlus::LuaObject;
  *(g_eventargs.metatable_) = luastate->CreateTable("CEGUIEventMetaTable");
  g_eventargs.metatable_->SetObject("__index", *(g_eventargs.metatable_));
  g_eventargs.metatable_->RegisterObjectFunctor("GetValue", 
                                                &EventArgs::lua_getvalue);
  LuaObject event = luastate->BoxPointer(&(g_eventargs));
  event.SetMetaTable(*(g_eventargs.metatable_));
  luastate->GetGlobals().SetObject("CEArg", event);

  //注册引用对象
  LuaObject metatable_ui_windowitem = 
    luastate->GetGlobals().CreateTable("MetaTable_UIWindowItem");
  metatable_ui_windowitem.SetObject("__index", metatable_ui_windowitem);
  metatable_ui_windowitem.RegisterObjectFunctor(
      "RegisterEvent", 
      &CEGUI::CUIWindowItem::LUA_RegisterEvent);
  metatable_ui_windowitem.RegisterObjectFunctor(
      "Show",
      &CEGUI::CUIWindowItem::LUA_Show);
  metatable_ui_windowitem.RegisterObjectFunctor(
      "Hide",
      &CEGUI::CUIWindowItem::LUA_Hide);
  metatable_ui_windowitem.RegisterObjectFunctor(
      "TogleShow",
      &CEGUI::CUIWindowItem::LUA_TigleShow);
  metatable_ui_windowitem.RegisterObjectFunctor(
      "IsVisible",
      &CEGUI::CUIWindowItem::LUA_IsVisible);
  metatable_ui_windowitem.RegisterObjectFunctor(
      "TransAllWindowText",
      &CEGUI::CUIWindowItem::LUA_TransAllWindowText);
  metatable_ui_windowitem.RegisterObjectFunctor(
      "CareObject",
      &CEGUI::CUIWindowItem::LUA_CareObject);

  //控件
  vgui_luacontrol::window::Base::register_metatable();
}

void Base::stopbindings() {
  delete g_eventargs.eventargs_;
  g_eventargs.metatable_ = NULL;
  //释放控件注册
  vgui_luacontrol::window::Base::destroy_metatable();
}

void Base::executeScriptFile(const CEGUI::String& filename, 
                             const CEGUI::String& resourceGroup = "") {
  executefile(filename, resourceGroup);
}

int32_t Base::executeScriptGlobal(const CEGUI::String& functionname) {
  execute_globalfunction(functionname);
}

bool Base::executeScriptedEventHandler(const CEGUI::String& handler_name, 
                                       const CEGUI::EventArgs& e) {
  bool result = execute_eventhandler(handler_name, e);
  return result;
}

void Base::executeString(const CEGUI::String& str) {
  executestring(str);
}

} //namespace vgui_script
