/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id channel.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 15:05:08
 * @uses vgui luacontrol chat channel window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_CHAT_CHANNEL_H_
#define VGUI_LUACONTROL_WINDOW_CHAT_CHANNEL_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace chat {

class Channel : public Base {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_add(LuaPlus::LuaState* luastate);
   int32_t lua_clearall(LuaPlus::LuaState* luastate); 

 protected:
   friend class Base;
   Channel(CEGUI::Window* window) : Base(window) {}
   virtual ~Channel() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace chat

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_CHAT_CHANNEL_H_
