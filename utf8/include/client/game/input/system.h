/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-10 17:19:55
 * @uses pap client game input system
 *       cn: 客户端输入系统
 */
#ifndef PAP_CLIENT_GAME_INPUT_SYSTEM_H_
#define PAP_CLIENT_GAME_INPUT_SYSTEM_H_

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <queue>
#include "vengine/input/system.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace input {

class System : public vengine_input::System {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   System();
   virtual ~System();

 public:
   static System* getself();

 public: //implement for abstract
   //获得传输的队列
   virtual vengine_input::eventqueue& get_eventqueue();
   //查询队列中是否有某事件存在
   virtual bool is_eventexist(vengine_input::eventid_enum id);
   //捕获状态
   virtual vengine_input::capturestatus_enum getcapture() const;
   virtual void setcapture(vengine_input::capturestatus_enum type);
   //处理windows消息
   virtual bool messageprocess(HWND hwnd, 
                               uint32_t message, 
                               WPARAM wparam, 
                               LPARAM lparam);

 public: //implement for abstract 
   //某个键是否被按下
   virtual bool is_keydown(vengine_input::keycode_enum key);
   //某个键是否刚被按下
   virtual bool is_keypress(vengine_input::keycode_enum key);
   //某个键是否刚被抬起
   virtual bool is_keypressed(vengine_input::keycode_enum key);
   //判断某个系统键是否按下
   virtual bool is_ctrldown();
   virtual bool is_shiftdown();
   virtual bool is_altdown();

 public: //implement for abstract 
   //设置鼠标
   virtual void set_mouseposition(int32_t x, int32_t y);
   virtual POINT get_mousepostion();
   virtual POINT get_mouse_oldpostion();
   virtual RECT get_mouse_LB_dragrect();
   virtual RECT get_mouse_MB_dragrect();
   virtual RECT get_mouse_RB_dragrect();
   virtual uint32_t get_mouseflag();
   virtual uint32_t get_mouse_oldflag();
   virtual uint32_t get_L_putdown_time();

 public:
   virtual void init(void*);
   virtual void tick();
   virtual void release();

 public:
   void on_windowactive(bool active); //窗口激活时
   bool is_mouse_inclient() const;

 protected:
   static System* self_;
   HWND windowhandle_;
   vengine_input::capturestatus_enum capturestatus_;
   bool firstactive_; //本桢是否是激活后的第一桢
   LPDIRECTINPUT8 directinput_;
   LPDIRECTINPUTDEVICE8 directinput_device_;
   const static int32_t kKeysNumber = 256;
   uint8_t currentkeys_[kKeysNumber]; //当前的键盘状态
   uint8_t oldkeys_[kKeysNumber]; //上一桢键盘状态
   bool keypresses_[kKeysNumber]; //某键是否刚被按下
   bool keypresseds_[kKeysNumber]; //某键是否刚被释放
   //WM_KEYDOWN保存区，用来处理键盘自动Repeat
   bool catch_keydown_;
   std::pair<WPARAM, LPARAM> buffer_wm_keydown_;
   vengine_input::eventqueue eventqueue_;
   POINT mouseposition_;
   POINT mouse_oldposition_;
   uint32_t mouseflag_;
   uint32_t mouse_oldflag_;
   uint32_t LB_putdown_time_; //左键按下的时间
   RECT LB_dragrect_; //拖动盒
   RECT MB_dragrect_;
   RECT RB_dragrect_;
   bool mouse_inclient_;

 protected:
   void acquire_keyboard(); //开始使用dinput键盘
   void unacquire_keyboard(); //释放dinput键盘
   void keyboard_flushdata(); //清空键盘数据
   void keyboard_tick(); //键盘逻辑
   void mousetick(); //鼠标逻辑
   void addevent(vengine_input::eventid_enum id, int32_t index = 0x00);

 private:
   POINT mouse_nowposition_;
   POINT mouse_L_downposition_;
   POINT mouse_M_downposition_;
   POINT mouse_R_downposition_;

};

}; //namespace input

#endif //PAP_CLIENT_GAME_INPUT_SYSTEM_H_
