/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id super.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-2 11:12:04
 * @uses vgui lua control super progressbar window class
 */
#ifndef VGUI_LUACONTROL_WINDOW_PROGRESSBAR_SUPER_H_
#define VGUI_LUACONTROL_WINDOW_PROGRESSBAR_SUPER_H_

#include "vgui/config.h"
#include "vgui/luacontrol/window/progressbar/base.h"

namespace vgui_luacontrol {

namespace window {

namespace progressbar {

//当命名空间有相同的元素存在于不同层级之时，
//没有加前缀的首先选择当前命名空间的元素
//如果想要使用其他层级相同的元素，请加上命名空间
class Super : public Base { //继承当前层级的Base类

 public:
   virtual LuaPlus::LuaObject* get_metatable();

 protected:
   friend class vgui_luacontrol::window::Base; //其他层级的Base类
   Super(CEGUI::Window* window) : Base(window) {}
   virtual ~Super() {}

 protected:
   static LuaPlus::LuaObject* metatable_;

};

}; //namespace progressbar

}; //namespace window

}; //namespace vgui_luacontrol

#endif //VGUI_LUACONTROL_WINDOW_PROGRESSBAR_SUPER_H_
