/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id softkey.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 15:52:07
 * @uses vgui luacontrol softkey window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_SOFTKEY_H_
#define VGUI_LUACONTROL_WINDOW_SOFTKEY_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

class SoftKey : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_setaim_editbox(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   SoftKey(CEGUI::Window* window) : Base(window) {}
   virtual ~SoftKey() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_SOFTKEY_H_
