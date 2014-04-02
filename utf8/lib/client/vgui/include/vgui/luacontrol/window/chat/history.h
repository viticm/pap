/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id history.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 15:05:08
 * @uses vgui luacontrol chat history window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_CHAT_HISTORY_H_
#define VGUI_LUACONTROL_WINDOW_CHAT_HISTORY_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace chat {

class History : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_insertstring(LuaPlus::LuaState* luastate);
   int32_t lua_romve_allstring(LuaPlus::LuaState* luastate); 
   int32_t lua_scroll_toend(LuaPlus::LuaState* luastate); 
   int32_t lua_extend_clearregion(LuaPlus::LuaState* luastate);

 protected:
   friend class Base;
   History(CEGUI::Window* window) : Base(window) {}
   virtual ~History() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace chat

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_CHAT_HISTORY_H_
