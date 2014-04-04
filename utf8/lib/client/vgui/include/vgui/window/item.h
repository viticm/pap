/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id item.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-30 17:02:02
 * @uses vgui window item class
 */
#ifndef VGUI_WINDOW_ITEM_H_
#define VGUI_WINDOW_ITEM_H_

#include "CEGUIVector.h"
#include "vengine/config.h"
#include "vengine/game/eventsystem.h"
#include "vgui/config.h"

namespace CEGUI {
class Window;
}; //namespace CEGUI

namespace vengine_script {
class Environment;
}; //namespace vengine_script

namespace vengine_db {

namespace structs {

namespace ui {

struct layoutdefine_t;

}; //namespace ui

}; //namespace structs

}; //namespace vengine_db

namespace LuaPlus {
class LuaState;
}; //namespace LuaPlus

namespace vgui_luacontrol {

namespace window {
class Base;
}; //namespace window

}; //namespace vgui_luacontrol

namespace vgui_window {

class Item {

 public:
   Item(const vengine_db::structs::ui::layoutdefine_t layoutdefine);
   virtual ~Item();

 public:
   typedef std::vector<STRING> registered_eventname_list;
   registered_eventname_list eventname_list_;

 public:
   void pre_loadwindow(); //预加载
   void loadwindow(); //窗口加载
   void show(bool flag); //显示/隐藏窗口
   bool is_windowshow(); //窗口是否正在显示
   bool is_child_windowshow() const; //子窗口是否正在显示
   const char* get_windowname(); //得到窗口名
   void moveto(CEGUI::Point& position); //将窗口移动到某一位置
   void positionself(); //窗口位置自适应
   static bool callback_property(CEGUI::Window* window, 
                                 CEGUI::String& propname, 
                                 CEGUI::String& propvalue, 
                                 void* userdata); //加载窗口属性回调
   void set_openclose_sound(uint16_t open, uint16_t close); //设置打开关闭声音
   void on_sizechange(); //窗口大小改变,调整窗口到合适的位置
   void reloadscript(); //重新加载脚本
 //for script
 public:
   int32_t lua_registerevent(LuaPlus::LuaState* luastate);
   int32_t lua_show(LuaPlus::LuaState* luastate);
   int32_t lua_hide(LuaPlus::LuaState* luastate);
   int32_t lua_toggle(LuaPlus::LuaState* luastate);
   int32_t lua_isvisible(LuaPlus::LuaState* luastate);
   int32_t lua_trans_alltext(LuaPlus::LuaState* luastate);
   int32_t lua_careobject(LuaPlus::LuaState* luastate);

 public:
   void handle_uievent(const char* eventhandle, CEGUI::Window* window);
   bool is_candemise();
   uint8_t get_demisetype();

 protected:
   int64_t id_;
   STRING windowname_;
   STRING layout_filename_;
   STRING script_filename_;
   uint8_t is_candemise_; //是否可以自动滚动显示,屏幕最多可以显示两个可禅让窗口
   STRING defaultposition_; //默认显示位置
   CEGUI::Window* window_; //窗口指针
   bool show_; //是否显示
   vengine_script::Environment* scriptenvironment_; //脚本环境指针
   bool layoutloaded_; //窗口是否已经加载
   int32_t openwindow_soundid_;
   int32_t closewindow_soundid_;
   std::vector<vgui_luacontrol::window::Base*> controls_;

 protected:
   void on_windowhide();
   static void WINAPI on_gameevent(const vengine_game::event_t* event, 
                                   uint32_t userdata);
   void registercontrol_toscript(CEGUI::Window* window); //控件注册
   void transtext(CEGUI::Window* window);

};
   
}; //namespace vgui_window

#endif //VGUI_WINDOW_ITEM_H_
