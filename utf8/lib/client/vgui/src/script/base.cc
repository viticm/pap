#include <CEGUIPropertyHelper.h>
#include "LuaPlus.h"
#include "vgui/script/base.h"

namespace vgui_script {

class EventArgs { //CEGUI 事件参数查询接口

 public:
   EventArgs() : metetable_(NULL), eventargs_(NULL){};
   virtual ~EventArgs(){}
   LuaPlus::LuaObject* metetable_; //lua元表
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
 
} //namespace vgui_script
