#include "vengine/game/eventsystem.h"
#include "vengine/game/eventdefine.h"
#include "vengine/render/system.h"
#include "vengine/exception/base.h"
#include "vengine/time/system.h"
#include "vengine/ui/system.h"
#include "vengine/capability/ax/profile.h"
#include "client/game/stdafx.h"
#include "client/game/global.h"
#include "client/game/procedure/base.h"
#include "client/game/input/system.h"

#define _IsKeyDown(exp) (GetAsyncKeyState(exp) & 0xff00)
#define _IsKeyDowned(exp) (GetAsyncKeyState(exp) & 0x00ff)

namespace input {

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(
    System,
    VENGINE_KERNEL_GETCLASS(vengine_input::System));

System* System::self_ = NULL;

System::System() {
  self_ = this;
  directinput_ = NULL;
  directinput_device_ = NULL;
  windowhandle_ = NULL;
  capturestatus_ = kCaptureStatusNone;
  catch_keydown_ = false;
  mouseflag_ = 0;
  mouse_oldflag_ = 0;
  LB_putdown_time_ = 0;
  mouse_inclient_ = true;
  firstactive_ = true;
  ZeroMemory(currentkeys_, sizeof(currentkeys_));
  ZeroMemory(oldkeys_, sizeof(oldkeys_));
  ZeroMemory(keypresses_, sizeof(keypresses_));
  ZeroMemory(keypresseds_, sizeof(keypresseds_));
}

System::~System() {
  release();
}

void System::init(void*) {
  HRESULT result_handle;
  windowhandle_ = g_mainwindow_handle;
  if (FAILED(result_handle = DirectInput8Create(
          GetModuleHandle(NULL), 
          DIRECTINPUT_VERSION,
          IID_IDirectInput8,
          (void**)&directinput_,
          NULL))) {
    VENGINE_SHOW("input::System::init: DirectInput8Create failed!");
    return;
  }
  result_handle = directinput_->CreateDevice(GUID_SysKeyboard, 
                                             &directinput_device_, 
                                             NULL);
  if (DI_OK == result_handle) {
    directinput_device_->SetDataFormat(&c_dfDIKeyboard);
    directinput_device_->SetCooperativeLevel(
        g_mainwindow_handle, 
        DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    acquire_keyboard(); //开始接受输入    
  }
}

void System::acquire_keyboard() {
  if (directinput_device_) {
    HRESULT result_handle = directinput_device_->Acquire();
    if (DI_OK == result_handle || S_FALSE == result_handle) {
      keyboard_flushdata();
    }
  }
}

void System::keyboard_flushdata() {
  ::ZeroMemory(currentkeys_, sizeof(currentkeys_));
  ::ZeroMemory(oldkeys_, sizeof(oldkeys_));
}

void System::unacquire_keyboard() {
  keyboard_flushdata();
  if (directinput_device_) directinput_device_->Unacquire();
}

void System::set_mouseposition(int32_t x, int32_t y) {
  POINT clientposition;
  clientposition.x = x;
  clientposition.y = y;
  ::ClientToScreen(g_mainwindow_handle, &clientposition);
  ::SetCursorPos(clientposition.x, clientposition.y);
  mouseposition_.x = mouse_nowposition_.x = x;
  mouseposition_.y = mouse_nowposition_.y = y;
}

bool System::messageprocess(HWND hwnd, 
                            uint32_t message, 
                            WPARAM wparam, 
                            LPARAM lparam) {
  switch (message) {
    case WM_MOUSEWHEEL: { //鼠标滚轮
      if (GET_WHEEL_DELTA_WPARAM(wparam) > 0) {
        mouseflag_ |= vengine_input::kMouse_WHEELUP;
      }
      else {
        mouseflag_ |= vengine_input::kMouse_WHEELDOWN;
      }
      return true;
      //break;
    }
    case WM_KEYDOWN: { //键盘按下
      buffer_wm_keydown_ = std::make_pair(wparam, lparam);
      catch_keydown_ = true;
      return false;
      //break;
    }
    case WM_KEYUP: { //键盘放开
      if (VK_SNAPSHOT == wparam) { //截屏处理
        if (procedure::Base::rendersytem_) {
          char filename[MAX_PATH] = {0};
          if (procedure::Base::rendersytem_->printscreen(
                filename, 
                sizeof(filename) - 1)) {
            procedure::Base::eventsystem_->push(
                vengine_game::event_id::kNewDebugMessage,
                filename);
          }
        }
        return false;
      }
      break;
    }
    //鼠标
    case WM_LBUTTONDBLCLK:
      break;
    case WM_LBUTTONDOWN:
      break;
    case WM_LBUTTONUP:
      break;
    case WM_RBUTTONDOWN:
      break;
    case WM_RBUTTONUP:
      break;
    case WM_MOUSEMOVE: {
      mouse_nowposition_.x = GET_X_LPARAM(lparam);
      mouse_nowposition_.y = GET_Y_LPARAM(lparam);
      return false;
    }
  } //switch
  return false;
}

void System::tick() {
  //如果主窗口没有激活,返回
  HWND activewindow_handle = ::GetActiveWindow();
  if (g_mainwindow_handle != activewindow_handle) return;
  //清空事件队列,正常情况应该到这里时已经是空的
  if (!eventqueue_.empty()) eventqueue_.clear();
  keyboard_tick(); //键盘
  mousetick(); //鼠标
  //激活后的第一桢不处理输入
  if (firstactive_) {
    firstactive_ = false;
    return;
  }
  vengine_input::capturestatus_enum capturestatus = getcapture();
  switch (capturestatus) {
    case kCaptureStatusNone: {
      if (procedure::Base::uisystem_)
        procedure::Base::uisystem_->injectinput();
      capturestatus = getcapture(); //重新获取一次
      if (capturestatus != kCaptureStatusUI) 
        procedure::Base::process_activeinput();
      break;
    }
    case kCaptureStatusUI: {
      procedure::Base::uisystem_->injectinput();
      break;
    }
    case kCaptureStatusGame: {
      procedure::Base::process_activeinput();
      break;
    }
    default:
      break;
  } //switch
}

System::keyboard_tick() {
  using namespace vengine_input;
  if (!directinput_device_) return;
  //保留旧状态
  memcpy(currentkeys_, oldkeys_, kKeysNumber);
  HRESULT result_handle = directinput_device_->GetDeviceState(kKeysNumber,
                                                              currentkeys_);
  if (result_handle != DI_OK) {
    acquire_keyboard();
  }
  else {
    int32_t i;
    for (i = 0; i < kKeysNumber; ++i) {
      //该键刚刚被按下
      keypresses_[i]  = (!(oldkeys_[i] & 0x80) && (currentkeys_[i] & 0x80)); 
      //该键刚刚被释放
      keypresseds_[i] = ((oldkeys_[i] & 0x80) && !(currentkeys_[i] & 0x80))
      //保存键盘输入事件
      if (keypresses_[i]) addevent(kEventId_KEY_DOWN, i);
      if (keypresseds_[i]) addevent(kEventId_KEY_UP, i);
    }
 }
  //检查是否有自动发送的RepeatKeyDown
  if (catch_keydown_ && !is_eventexist(kEventId_KEY_DOWN)) {
    switch (buffer_wm_keydown_.first) {
      case VK_LEFT: {
        addevent(kEventId_KEY_DOWN, kKeyCode_LEFT);
        break;   
      }
      case VK_UP: {
        addevent(kEventId_KEY_DOWN, kKeyCode_UP);
        break;   
      }
      case VK_RIGHT: {
        addevent(kEventId_KEY_DOWN, kKeyCode_RIGHT);
        break;   
      }
      case VK_DOWN: {
        addevent(kEventId_KEY_DOWN, kKeyCode_DOWN);
        break;   
      }
      case VK_BACK: {
        addevent(kEventId_KEY_DOWN, kKeyCode_BACK);
        break;   
      }
      default:
        break;
    } //switch
  }
  catch_keydown_ = false; 
}

void System::on_windowactive(bool active) {
  firstactive_ = true;
}

void System::mousetick() {
  using namespace vengine_input;
  //判断是否是click的数据标准  
  const uint32_t kDragTimeMax = 500; //ms
  const uint32_t kMouseRepeatDown = 1000; //ms, 开始自动行走
  RECT clientrect;
  GetClientRect(g_mainwindow_handle, &clientrect);
  POINT temppositon;
  ::GetCursorPos(&temppositon);
  ::ScreenToClient(g_mainwindow_handle, &temppositon);
  if (!::PtInRect(&clientrect, temppositon) && 
      ::GetCapture() != g_mainwindow_handle) {
    mouse_inclient_ = false;
    return;
  }
  mouse_inclient_ = true;
  mouse_oldposition_ = mouseposition_; //保存原来的鼠标位置
  mouseposition_ = mouse_nowposition_;
  mouse_oldflag_ = mouseflag_; //保存原来的鼠标状态
  mouseflag_ = 0;
  uint32_t nowtime = procedure::Base::timesystem_->get_nowtime();
  bool mousemove = false;
  if (mouse_oldposition_.x != mouse_nowposition_.x || 
      mouse_oldposition_.y != mouse_nowposition_.y) {
    mousemove = true;
    //保存鼠标移动事件
    addevent(kEventId_MOUSE_MOVE);
  }
  //察看按键
  if (_IsKeyDown(VK_LBUTTON)) mouseflag_ |= kMouse_LBDOWN;
  if (_IsKeyDown(VK_MBUTTON)) mouseflag_ |= kMouse_MBDOWN;
  if (_IsKeyDown(VK_RBUTTON)) mouseflag_ |= kMouse_RBDOWN;
  static uint32_t mouse_L_downtime_begin = 0;
  static uint32_t mouse_M_downtime_begin = 0;
  static uint32_t mouse_R_downtime_begin = 0;
  static bool L_repeatdown_mode = false; //双击
  if ((false == (mouse_oldflag_ & kMouse_LBDOWN) && 
       (mouseflag_ & kMouse_LBDOWN))) { //左键单击
    //保存鼠标DOWN事件
    addevent(kEventId_MOUSE_LBDOWN);
    mouseflag_ |= kMouse_LBCLICK;
    mouse_L_downposition_ = mouse_nowposition_;
    //记录时间
    mouse_L_downtime_begin = nowtime;
    L_repeatdown_mode = false;
  }

  if (false == (mouse_oldflag_ & kMouse_MBDOWN) && 
      (mouseflag_ & kMouse_MBDOWN)) { //中键单击
    addevent(kEventId_MOUSE_MBDOWN);
    mouseflag_ |= kMouse_MBCLICK;
    mouse_M_downposition_ = mouse_nowposition_;
    mouse_M_downtime_begin = nowtime;
  }
  
  if (false == (mouse_oldflag_ & kMouse_RBDOWN) &&
      (mouseflag_ & kMouse_RBDOWN)) { //右键单击
    addevent(kEventId_MOUSE_RBDOWN);
    mouseflag_ |= kMouse_RBCLICK;
    mouse_R_downposition_ = mouse_nowposition_;
    mouse_R_downtime_begin = nowtime;
  }

  if (false == (mouseflag_ & kMouse_LBDOWN) &&
      (mouse_oldflag_ & kMouse_LBDOWN)) {
    //计算时间
    uint32_t difftime = procedure::Base::timesystem_->get_difftime(
        mouse_L_downtime_begin, 
        nowtime);
    if (difftime < kDragTimeMax &&
        abs(mouse_L_downposition_.x - mouse_nowposition_.x) <= 4 &&
        abs(mouse_L_downposition_.y - mouse_nowposition_.y) <= 4) {
      mouseflag_ |= kMouse_LBCLICKED;
      addevent(kEventId_MOUSE_LBCLICK);
    }
    addevent(kEventId_MOUSE_LBUP);
    L_repeatdown_mode = false;
  }

  if ((mouse_oldflag_ & kMouse_MBDOWN) && 
      false == (mouseflag_ & kMouse_MBDOWN)) {
    uint32_t difftime = procedure::Base::timesystem_->get_difftime(
        mouse_M_downtime_begin,
        nowtime);
    if (difftime < kDragTimeMax) {
      mouseflag_ |= kMouse_MBCLICKED;
      addevent(kEventId_MOUSE_MBCLICK);
    }
    addevent(kEventId_MOUSE_MBUP);
  }

  if ((mouse_oldflag_ & kMouse_RBDOWN) && 
      false == (mouseflag_ & kMouse_RBDOWN)) {
    uint32_t difftime = procedure::Base::timesystem_->get_difftime(
        mouse_R_downtime_begin,
        nowtime);
    if (difftime < kDragTimeMax &&
        abs(mouse_R_downposition_.x - mouse_nowposition_.x) <= 4 &&
        abs(mouse_R_downposition_.y - mouse_nowposition_.y) <= 4) {
      mouseflag_ |= kMouse_RBCLICKED;
      addevent(kEventId_MOUSE_RBCLICK);
    }
    addevent(kEventId_MOUSE_RBUP);
  }

  //处理拖动
  LB_putdown_time_ = 0;
  if ((mouseflag_ & kMouse_LBDOWN) && (mouse_oldflag_ & kMouse_LBDOWN)) {
    LB_putdown_time_ = procedure::Base::timesystem_->get_difftime();
  }
  //左键拖动状态
  if ((mouseflag_ & kMouse_LBDOWN) && (mouse_oldflag_ & kMouse_LBDOWN)) {
    if (mousemove) addevent(kEventId_MOUSE_LDRAG_MOVE);
    //左键长按
    if (LB_putdown_time_ > kMouseRepeatDown) {
      addevent(kEventId_MOUSE_LBDOWNREPEAT);
      L_repeatdown_mode = true;
    }
  }
  
  //右键拖动事件
  if ((mouseflag_ & kMouse_RBDOWN) && (mouse_oldflag_ & kMouse_RBDOWN)) {
    if (mousemove) addevent(kEventId_MOUSE_RDRAG_MOVE);
  }

  //检测是否为双击
  static uint32_t doubleclick_time = ::GetDoubleClickTime();
  if (mouseflag_ & kMouse_LBCLICKED) { //左键
    static uint32_t clicked = 0;
    if (nowtime < clicked + doubleclick_time) {
      //保存"双击"事件
      addevent(kEventId_MOUSE_LDBCLICK);
      mouseflag_ |= kMouse_LBDBLCLK;
    }
    clicked = nowtime;
    LB_putdown_time_ = 0;
  }
  
  if (mouseflag_ & kMouse_MBCLICKED)  { //中键
    static uint32_t clicked = 0;
    if (nowtime < clicked + doubleclick_time) {
      addevent(kEventId_MOUSE_MDBCLICK);
      mouseflag_ |= kMouse_MBDBLCLK;
    }
    clicked = nowtime;
  }

  if (mouseflag_ & kMouse_RBCLICKED) { //右键
    static uint32_t clicked = 0;
    if (nowtime < clicked + doubleclick_time) {
      addevent(kEventId_MOUSE_RDBCLICK);
      mouseflag_ |= kMouse_RDBCLICK;
    }
    clicked = nowtime;
  }

  //计算拖拽盒
  if (mouseflag_ & kMouse_RBCLICK) {
    //右键被按下 拖拽框左上
    RB_dragrect_.left = mouseposition_.x;
    RB_dragrect_.top = mouseposition_.y;
  }

  if (mouse_oldflag_ & kMouse_RBCLICKED) {
    //右键抬起
    RB_dragrect_.right = mouseposition_.x;
    RB_dragrect_.bottom = mouseposition_.y;
  }

  //滚轮
  if (mouse_oldflag_ & kMouse_WHEELUP) {
    addevent(kEventId_MOUSE_WHEEL_UP);
  }

  if (mouse_oldflag_ & kMouse_WHEELDOWN) {
    addevent(kEventId_MOUSE_WHEEL_DOWN);
  }
}

bool System::is_eventexist(vengine_input::eventid_enum id) {
  vengine_input::eventqueue::iterator iterator;
  if (iterator = eventqueue_.begin();
      iterator != eventqueue_.end();
      ++iterator) {
    if (iterator->id == id) return true;
  }
  return false;
}

void System::release() {
  if (directinput_device_) {
    directinput_device_->Unacquire();
    directinput_device_->Release();
    directinput_device_ = NULL;
  }
  if (directinput_) directinput_->Release();
  directinput_ = NULL;
}

void System::setcapture(vengine_input::capturestatus_enum status) {
  capturestatus_ = status;  
}

void System::addevent(vengine_input::eventid_enum id, int32_t index) {
  vengine_input::event_t event;
  event.id = id;
  event.keyindex = static_cast<vengine_input::keycode_enum>(index);
  event.processed = false;
  eventqueue_.push_back(event);
}

vengine_input::capturestatus_enum System::getcapture() const {
  return capturestatus_;
}

bool System::is_keydown(vengine_input::keycode_enum index) {
  bool result = (currentkeys_[index] & 0x80) != 0;
  return result;
}

bool System::is_keypress(vengine_input::keycode_enum index) {
  bool result = keypresses_[index];
  return result;
}

bool System::is_keypressed(vengine_input::keycode_enum index) {
  bool result = keypresseds_[index];
  return result;
}

bool System::is_ctrldown() {
  bool result = is_keydown(vengine_input::kKeyCode_LCONTROL) || 
    is_keydown(vengine_input::kKeyCode_RCONTROL);
  return result;
}

bool System::is_shiftdown() {
  bool result = is_keydown(vengine_input::kKeyCode_LSHIFT) || 
    is_keydown(vengine_input::kKeyCode_RSHIFT);
  return result;
}

bool System::is_altdown() {
  bool result = is_keydown(vengine_input::kKeyCode_LMENU) || 
    is_keydown(vengine_input::kKeyCode_RMENU);
  return result;
}

POINT System::get_mousepostion() {
  return mouseposition_;
}

POINT System::get_mouse_oldpostion() {
  return mouse_oldposition_;
}

RECT System::get_mouse_LB_dragrect() {
  return LB_dragrect_;
}

RECT System::get_mouse_MB_dragrect() {
  return MB_dragrect_;
}

RECT System::get_mouse_RB_dragrect() {
  return RB_dragrect_;
}

uint32_t System::get_mouseflag() {
  return mouseflag_;
}

uint32_t System::get_mouse_oldflag() {
  return mouse_oldflag_;
}

bool System::is_mouse_inclient() const {
  return mouse_inclient_;
}

uint32_t System::get_L_putdown_time() {
  return LB_putdown_time_;
}

}; //namespace input
