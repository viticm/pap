/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-26 11:40:04
 * @uses vgui script base module
 */
#ifndef VGUI_SCRIPT_BASE_H_
#define VGUI_SCRIPT_BASE_H_

#include <CEGUIScriptModule.h>
#include "vengine/config.h"
#include "vgui/config.h"

namespace vgui_script {

class Base : public CEGUI::ScriptModule {

 public:
   Base();
   virtual ~Base();

 public:
   virtual void executefile(const CEGUI::String& filename,
                            const CEGUI::String& resourcegroup = "");
   //执行某个全局脚本函数
   virtual int32_t execute_globalfunction(const CEGUI::String& functionname);
   //响应UI事件
   virtual bool execute_eventhandler(const CEGUI::String& handlername,
                                     const CEGUI::EventArgs& eventargs);
   virtual void executestring(const CEGUI::String& str);
   virtual void startbindings(); //开始脚本绑定
   virtual void stopbindings(); //停止脚本绑定

   // for abstract
   virtual void	executeScriptFile(const CEGUI::String& filename, 
                                  const CEGUI::String& resourceGroup = "");
   virtual int32_t executeScriptGlobal(const CEGUI::String& functionname);
   virtual bool	executeScriptedEventHandler(const CEGUI::String& handler_name, 
                                            const CEGUI::EventArgs& e);
   void executeString(const CEGUI::String& str);

};

}; //namespace vgui_script

#endif //VGUI_SCRIPT_BASE_H_
