/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-21 16:11:04
 * @uses vengine render system class
 *       cn: 渲染系统接口
 */
#ifndef VENGINE_RENDER_SYSTEM_H_
#define VENGINE_RENDER_SYSTEM_H_

#include "vengine/config.h"

namespace vengine_render {

class VENGINE_API System : public vengine_kernel::Node {

 public:
   virtual void init(void*) = 0;
   virtual void release() = 0;
   //场景渲染
   virtual void renderframe() = 0;
   //渲染Loading画面
   virtual void render_loadingframe(const char* loading) = 0;
   //响应WM_PAINT消息
   virtual void onpaint() = 0;
   //窗口大小改变事件
   virtual void on_windowsize_change(uint32_t message, 
                                     WPARAM wparam, 
                                     LPARAM lparam) = 0;
   //取得渲染窗口
   virtual HWND getwindow() = 0;
   //当前屏幕截图到文件中
   virtual void printscreen(const char* buffer, int32_t size) = 0;
 
 //debugs
 public:
   //加入debug信息
   virtual void debug_pushstring(const char* format, ...) = 0;
   //设置debug状态信息
   virtual void debug_setstring(const char* name, const char* value) = 0;
   //设置选中物体信息
   virtual void set_hitobjet_string(const char* str);

};

}; //namespace vengine_render

#endif //VENGINE_RENDER_SYSTEM_H_
