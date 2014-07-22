/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id action.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 11:31:03
 * @uses vgui lua control action button window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_BUTTON_ACTION_H_
#define VGUI_LUACONTROL_WINDOW_BUTTON_ACTION_H_

//for bugs
#ifdef VENGINE_API
#undef VENGINE_API
#define VENGINE_API
#endif

#include "vengine/game/action/reference.h"
#include "vgui/config.h"
#include "vgui/luacontrol/window/base.h"

namespace vgui_luacontrol {

namespace window {

namespace button {

class Action : public Base, public vengine_game::action::Reference {

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 public:
   int32_t lua_setitem(LuaPlus::LuaState* luastate);
   int32_t lua_do(LuaPlus::LuaState* luastate);
   int32_t lua_dosub(LuaPlus::LuaState* luastate);
   int32_t lua_setpushed(LuaPlus::LuaState* luastate);
   int32_t lua_setflash(LuaPlus::LuaState* luastate);
   int32_t lua_gloom(LuaPlus::LuaState* luastate); //置灰
   int32_t lua_bright(LuaPlus::LuaState* luastate); //置亮
   int32_t lua_set_keystate(LuaPlus::LuaState* luastate);
   int32_t lua_set_logicitem_data(LuaPlus::LuaState* luastate);
   int32_t lua_set_normalimage(LuaPlus::LuaState* luastate);
   int32_t lua_set_item_iconname(LuaPlus::LuaState* luastate);
   int32_t lua_get_itemid(LuaPlus::LuaState* luastate);
   int32_t lua_get_item_defineid(LuaPlus::LuaState* luastate);

 public:
   virtual void bedestroyed(); //逻辑Action已经被销毁
   virtual void setcheck(bool check); //按钮按下
   virtual void enterflash(bool flash); //进入闪烁
   virtual void setdefault(bool flag); //将按钮设置为默认状态
   virtual void enter_cooldown(int32_t time, float percent); //进入冷却
   virtual void set_cornerchar(cornernumber_position_enum position, 
                               const char* _char);
   virtual void update(int32_t itemid);
   virtual void disable();
   virtual void enable();
   virtual void gloom();
   virtual void bright();
   virtual void locked();
   virtual void unlock();

 protected:
   friend class Base;
   Action(CEGUI::Window* window) : Base(window), item_(NULL) {}
   virtual ~Action() {};

 protected:
   static LuaPlus::LuaObject* metatable_;
   vengine_game::action::Item* item_;
  
};

}; //namespace button

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_BUTTON_ACTION_H_
