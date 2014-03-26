/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-26 16:52:39
 * @uses vgui icon manager
 */
#ifndef VGUI_ICON_MANAGER_H_
#define VGUI_ICON_MANAGER_H_

#include "vengine/config.h"
#include "vgui/config.h"

namespace LuaPlus {
class LuaState;
}; //namespace LuaPlus

namespace CEGUI {
class Imageset;
class Image;
}; //namespace CEGUI

namespace vgui_icon {

class Base {

 public:
   Base();
   virtual ~Base();
   static Base* getself();

 public:
   STRING get_icon_fullname(const char* iconname);
   const CEGUI::Image* geticon(const char* iconname);
   HCURSOR create_as_windowscursor(const char* iconname);

 public:
   //for lua
   static int32_t lua_get_icon_fullname(LuaPlus::LuaState* luastate);

 public:
   typedef std::map<STRING, const CEGUI::Imageset*> iconmap;
   void init();

 protected:
   iconmap iconmap_;
   static Base* self_;

};

}; //namespace vgui_icon

#endif //VGUI_ICON_MANAGER_H_
