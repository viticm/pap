#include "resource1.h"
#include "vengine/capability/profile.h"
#include "vengine/capability/ax/profile.h"
#include "vengine/capability/debuger.h"
#include "vengine/exception/base.h"
#include "vengine/time/system.h"
#include "vengine/ui/system.h"
#include "vengine/resource/provider.h"
#include "client/game/stdafx.h"
#include "client/game/global.h"
#include "client/game/net/manager.h"
#include "client/game/input/system.h"
#include "client/game/sound/system.h"
#include "client/game/database/system.h"
#include "client/game/variable/system.h"
#include "client/game/event/system.h"
#include "client/game/cursor/manager.h"
#include "client/game/script/system.h"
#include "client/game/timer/manager.h"
#include "client/game/resource/loadlistener.h"
#include "client/game/resource/provider.h"
#include "client/game/procedure/login.h"
#include "client/game/procedure/base.h"

namespace procedure {

const char kMainWindowClass[] = "pap windowclass";
const uint16_t kDefaultWindowHeight = 1024;
const uint16_t kDefaultWindowWidth = 768;

const uint16_t kMiniWindowHeight = 800;
const uint16_t kMiniWindowWidth = 600;

const uint32_t kDefaultWindowStyle = //默认的窗口样式
  WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

//class static variable init
Login* Base::login_ = NULL;
net::Manager* Base::netmanager_ = NULL;
vengine_input::System* Base::inputsystem_ = NULL;
vengine_game::WorldSystem* Base::worldsystem_ = NULL;
vengine_game::object::BaseSystem* Base::objectsystem_ = NULL;
vengine_game::Interface* Base::interface_ = NULL;
vengine_game::data_pool::Base* Base::datapool_ = NULL;
vengine_game::data_pool::Ui* Base::ui_datapool_ = NULL;
vengine_game::EventSystem* Base::eventsystem_ = NULL;
vengine_game::ItemTransferSystem* Base::itemtransfer_system_ = NULL;
vengine_capability::Debuger* Base::debuger_ = NULL;
vengine_render::System* Base::rendersystem_ = NULL;
vengine_ui::System* Base::uisystem_ = NULL;
vengine_time::System* Base::timesystem_ = NULL;
vengine_sound::System* Base::soundsystem_ = NULL;
vengine_db::System* Base::dbsystem_ = NULL;
vengine_cursor::System* Base::cursorsystem_ = NULL;
vengine_script::System* Base::scriptsystem_ = NULL;
vengine_resource::Provider* Base::resourceprovider_ = NULL;
vengine_variable::System* Base::variablesystem_ = NULL;

Base* Base::active_ = NULL;
Base* Base::previous_ = NULL;

bool Base::minimized_ = false;
bool Base::maxmized_ = false;
bool Base::fullscreen_ = false;

RECT Base::windowrect_;
float Base::windowproportion_ = static_cast<float>(
    kDefaultWindowHeight / kDefaultWindowWidth);
RECT Base::frameclient_rectoffset_;
bool Base::isactive_ = false;
bool Base::renderpaused_ = false;
bool Base::ui_handleinput_ = false;
MMRESULT Base::eventtimer_ = NULL;
HANDLE Base::tickevent_ = NULL;

void Base::init_staticmember() {
  srand((unsigned)timeGetTime());
  //注册本地类
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(vengine_kernel::Node));
  //网络管理器
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(net::Manager));
  //场景管理器
  //g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS());
  //图形系统
  //g_root_kernel.registerclass();
  //输入管理器
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(input::System));
  //时间管理器
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(vengine_time::System));
  //声音管理器
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(sound::System));
  //数据库管理器
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(database::System));
  //UI操作接口
  //g_root_kernel.registerclass();
  //UI数据池
  //g_root_kernel.registerclass();
  //g_root_kernel.registerclass();
  //UI鼠标操作类
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(cursor::Manager));
  //脚本系统
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(script::System));
  //事件系统
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(event::System));
  //操作管理
  //g_root_kernel.registerclass();
  //UI模型显示管理
  //g_root_kernel.registerclass();
  //外接帮助系统
  //g_root_kernel.registerclass();
  //资源
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(resource::Provider));
  //物品传输系统
  //g_root_kernel.registerclass();
  //定时器
  g_root_kernel.registerclass(VENGINE_KERNEL_GETCLASS(timer::Manager));

#ifdef USEOGRELIB
  extern void install_uisystem(vengine_kernel::Base* kernel);
#else
  g_root_kernel.loadplugin("vgui.dll", &g_root_kernel);
#endif

  //初始化所有的循环实例
  login_ = new procedure::Login(); //登陆循环
  //初始化数据核心
  //0.输入管理器
  inputsystem_ = dynamic_cast<vengine_input::System*>(
      g_root_kernel.newnode("input::System", "bin", "input"));
  //1.时间管理器
  timesystem_ = dynamic_cast<vengine_time::System*>(
      g_root_kernel.newnode("vengine_time::System", "bin", "time"));
  //2.网络管理器
  netmanager_ = dynamic_cast<net::Manager*>(
      g_root_kernel.newnode("net::Manager", "bin", "net"));
  //3.声音管理器
  soundsystem_ = dynamic_cast<vengine_sound::System*>(
      g_root_kernel.newnode("sound::System", "bin", "sound"));
  //4.渲染器节点

  //5.调试器节点
  debuger_ = dynamic_cast<vengine_capability::Debuger*>(
      g_root_kernel.newnode("vengine_capability::Debuger", "bin", "debuger"));
  //6.物体管理器
  
  //7.UI管理器
  uisystem_ = dynamic_cast<vengine_ui::System*>(
      g_root_kernel.newnode("vengine_ui::System", "bin", "ui"));

  //8.数据库管理器
  dbsystem_ = dynamic_cast<vengine_db::System*>(
      g_root_kernel.newnode("database::System", "bin", "db"));
  //9.世界管理器
  
  //10.变量管理器
  variablesystem_ = dynamic_cast<vengine_variable::System*>(
      g_root_kernel.newnode("variable::System", "bin", "var"));

  //11.接口管理器
  
  //12.UI数据池
  
  //13.鼠标管理器
  cursorsystem_ = dynamic_cast<vengine_cursor::System*>(
      g_root_kernel.newnode("cursor::System", "bin", "cursor"));

  //14.脚本系统
  scriptsystem_ = dynamic_cast<vengine_script::System*>(
      g_root_kernel.newnode("script::System", "bin", "script"));
  //15.事件系统
  eventsystem_ = dynamic_cast<vengine_game::EventSystem*>(
      g_root_kernel.newnode("event::System", "bin", "event"));
  //16.操作管理

  //17.UI模型显示管理

  //18.外接帮助系统

  //19.资源
  resourceprovider_ = dynamic_cast<vengine_resource::Provider*>(
      g_root_kernel.newnode("resource::Provider", "bin", "resource_provider"));
  //20.时间管理器
  timesystem_ = dynamic_cast<vengine_time::System*>(
      g_root_kernel.newnode("TimeSystem", "bin", "time"));
  //21.物品传输系统

  //创建主窗口前初始化变量系统
  variablesystem_->init(NULL);
  create_mainwindow();

  //初始化工作节点
  eventsystem_->init(NULL);
  //rendersystem_
  scriptsystem_->init(NULL);
  dbsystem_->init(NULL);
  timesystem_->init(NULL);
  netmanager_->init(NULL);
  //worldsystem_
  //objectsystem_
  //if (debuger_) debuger_->init(NULL);
  if (uisystem_) uisystem_->init(NULL);
  inputsystem_->init(NULL);
  soundsystem_->init(&g_mainwindow_handle);
  //ui_datapool_
  //datapool_
  cursorsystem_->init(NULL);
  //actionsystem_
  //interface_
  //fake_objectsystem_
  //helpersystem_
  resourceprovider_->init(NULL);
  //itemtransfer_system_->init(NULL);

  //创建Tick驱动
  int32_t FPSMax = variablesystem_->getint32("System_MaxFPS");
  if (FPSMax < 5 || FPSMax > 150) FPSMax = 30;
  tickevent_ = ::CreateEvent(NULL, false, false, NULL);
  ::ResetEvent(tickevent_);
  eventtimer_ = ::timeSetEvent(
      static_cast<int32_t>(1000.0f/FPSMax), 
      static_cast<int32_t>(1000.0f/FPSMax), 
      eventtimer, 
      0, 
      TIME_PERIODIC | TIME_CALLBACK_FUNCTION);
  //通过关闭窗口事件，来实现初始化所有窗口。
  //解决了在游戏中初始化窗口时卡的问题
  /**
  std::vector<STRING> param;
  char temp[MAX_PATH] = {0};
  snprintf(temp, sizeof(temp) - 1, "%d", 0);
  param.push_back(temp);
  param.push_back("distance");
  **/
}

void Base::release_staticmemeber() {
  if (eventtimer_) ::timeKillEvent(eventtimer_);
  eventtimer_ = NULL;
  ::CloseHandle(tickevent_);
  SAFE_DELETE(login_);
  previous_ = active_ = NULL; //流程指针置空

  //21.物品传输系统

  //20.时间管理器
  SAFE_RELEASE(timesystem_);
  //19.资源
  SAFE_RELEASE(resourceprovider_);
  //18.外接帮助系统

  //17.UI模型显示管理

  //16.操作管理

  //15.事件系统
  SAFE_RELEASE(eventsystem_);
  //14.脚本系统
  SAFE_RELEASE(scriptsystem_);
  //13.鼠标管理器
  SAFE_RELEASE(cursorsystem_);
  //12.UI数据池

  //11.接口管理器

  //10.变量管理器
  SAFE_RELEASE(variablesystem_);
  //9.世界管理器

  //8.数据库管理器
  SAFE_RELEASE(dbsystem_);
  //7.UI管理器
  SAFE_RELEASE(uisystem_);
  //6.物体管理器

  //5.调试器节点

  //4.渲染器节点

  //3.声音管理器
  SAFE_RELEASE(soundsystem_);
  //2.网络管理器
  SAFE_RELEASE(netmanager_);
  //1.时间管理器
  SAFE_RELEASE(timesystem_);
  //0.输入管理器
  SAFE_RELEASE(inputsystem_);

  //关闭核心
  g_root_kernel.shutdown();
  //销毁主窗口
  destroy_mainwindow();
}

VOID CALLBACK Base::eventtimer(UINT timeid, 
                               UINT message,
                               DWORD user,
                               DWORD param1,
                               DWORD param2) {
  ::SetEvent(tickevent_);
}

void Base::setactive(Base* active) {
  if (NULL == active || active_ == active) return;
  previous_ = active_;
  active_ = active;
  //...
}

void Base::mainloop() {
  MSG msg;
  ::ZeroMemory(&msg, sizeof(MSG));
  for (;;) {
    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (WM_QUIT == msg.message) return; //退出消息
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
    }
    //等待有新的消息进入消息队列或者到达渲染时间
    uint32_t result = ::MsgWaitForMultipleObjects(1, 
                                                  &tickevent_, 
                                                  false, 
                                                  INFINITE, 
                                                  QS_ALLINPUT);
    if (WAIT_OBJECT_0 == result) {
      tickactive();
      renderactive();
      processevent();
    }
    else {
      continue;
    }
  } //for loop
}

void Base::tickactive() {
  //如果要转入新的游戏循环
  if (previous_ != active_) {
    //调用旧循环的释放函数
    previous_->release();
    //调用新循环的初始化函数
    active_->init();
    //开始新的循环
    previous_ = active_;
  }
  _tick();
}

void Base::processevent() {
  if (eventsystem_) eventsystem_->processall();
}

void Base::renderactive() {
  //执行激活循环的渲染函数
  if (previous_ == active_ && active_ && !minimized_ && !renderpaused_) {
    //激活中，直接渲染
    if (isactive_) {
      active_->render();
    }
    else {
      //使用窗口非法方式重绘
      ::InvalidateRect(g_mainwindow_handle, 0, false);
      ::PostMessage(g_mainwindow_handle, WM_NCPAINT, true, 0);
    }
  }
}

void Base::_tick() {
  //extend ticks
}

void Base::tick() {
  //逻辑轮询所有节点
  timesystem_->tick();
  inputsystem_->tick();
  if (uisystem_) uisystem_->tick();
  netmanager_->tick();
  //worldsystem_->tick();
  //objectsystem_->tick();
  soundsystem_->tick();
  //rendersystem_->tick();
  //ui_datapool_->tick();
  //datapool_->tick();
  //actionsystem_->tick();
  //fake_objectsystem_->tick();
  scriptsystem_->tick();
}

void Base::process_activeinput() {
  //执行激活循环的键盘函数
  if (active_ == previous_ && active_)
    active_->processinput();
}

void Base::process_closerequest() {
  if (active_ == previous_ && active_)
    active_->closerequest();
}

void Base::processinput() {

}

void Base::closerequest() {

}

void Base::create_mainwindow() {
  int32_t windowwidth = kDefaultWindowWidth;
  int32_t windowheigth = kDefaultWindowHeight;
  if (variablesystem_) {
    bool have = false;
    vengine_math::base::twofloat_vector_t resoution =
      variablesystem_->get_twofloat_vector("View_Resoution", &have);
    if (have) {
      windowwidth = static_cast<int32_t>(resoution.x);
      windowheigth = static_cast<int32_t>(resoution.y);
    }
  }
  //compute window size
  minimized_ = false;
  fullscreen_ = false;
  ::SetRect(&windowrect_, 0, 0, windowwidth, windowheigth);
  ::AdjustWindowRect(&windowrect_, kDefaultWindowStyle, false);
  ::SetRect(&frameclient_rectoffset_,
            windowrect_.left,
            windowrect_.top,
            windowrect_.right - windowwidth,
            windowrect_.bottom -windowheigth);
  uint32_t x = (::GetSystemMetrics(SM_CXFULLSCREEN) - 
      (windowrect_.right - windowrect_.left)) / 2;
  uint32_t y = (::GetSystemMetrics(SM_CYFULLSCREEN) - 
      (windowrect_.bottom - windowrect_.top)) / 2;
  ::OffsetRect(&windowrect_, 
               -frameclient_rectoffset_.left, 
               -frameclient_rectoffset_.top);
  ::OffsetRect(&windowrect_, x, y);
  isactive_ = true;
  renderpaused_ = false;
  //for windows, just use windows type
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wcex.lpfnWndProc = (WNDPROC)_mainwindow_process;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = g_instance_handle;
  wcex.hIcon = ::LoadIcon(g_instance_handle, (LPCTSTR)IDD_GAME_DIALOG);
  wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)NULL;
  wcex.lpszMenuName = (LPCTSTR)NULL;
  wcex.lpszClassName = kMainWindowClass;
  wcex.hIconSm = ::LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
  ::RegisterClassEx(&wcex);
  
  //create window
  char title[MAX_PATH] = {0};
  snprintf(title, 
           sizeof(title) - 1, 
           "%s %s (%s %s)", 
           kGameTitle, 
           kVersionInfo, 
           __DATE__, 
           __TIME__);
  HWND window_handle = ::CreateWindowEx(NULL,
                                        kMainWindowClass,
                                        title,
                                        kDefaultWindowStyle,
                                        windowrect_.left,
                                        windowrect_.top,
                                        windowrect_.right - windowrect_.left,
                                        windowrect_.bottom - windowrect_.top,
                                        NULL,
                                        NULL,
                                        g_instance_handle,
                                        NULL);
  if (!window_handle) {
    VENGINE_ASSERT("procedure::Base::create_mainwindow:" 
                   " can't create main window!");
  }

  ::ShowWindow(window_handle, SW_SHOW);
  g_mainwindow_handle = window_handle;
}

void Base::destroy_mainwindow() {
  ::DestroyWindow(g_mainwindow_handle);
  ::UnregisterClass(kMainWindowClass, NULL);
  g_mainwindow_handle = NULL;
}

LRESULT CALLBACK Base::_mainwindow_process(HWND hwnd, 
                                           UINT message, 
                                           WPARAM wparam, 
                                           LPARAM lparam) {
  //首先让输入管理器处理消息
  if (inputsystem_ && 
      inputsystem_->messageprocess(hwnd, message, wparam, lparam))
    return 0;
  //UI处理文字输入
  if (uisystem_ && 
      uisystem_->messageprocess(hwnd, message, wparam, lparam))
    return 0;
  //执行激活循环的消息响应函数
  LRESULT result;
  if (active_) {
    result = active_->mainwindow_process(hwnd, message, wparam, lparam);
  }
  else {
    result = ::DefWindowProc(hwnd, message, wparam, lparam);
  }
  return result;
}

LRESULT Base::mainwindow_process(HWND hwnd, 
                                 UINT message, 
                                 WPARAM wparam, 
                                 LPARAM lparam) {
  switch (message) {
    case WM_SIZE: { //window size changed
      if (SIZE_MINIMIZED == wparam) {
        renderpaused_ = true;
        minimized_ = true;
        maxmized_ = false;
      }
      else if (SIZE_MAXIMIZED == wparam) {
        renderpaused_ = false;
        minimized_ = false;
        maxmized_ = true;
        handle_windowsize_change(message, wparam, lparam);
      }
      else if (SIZE_RESTORED == wparam) {
        if (maxmized_) {
          maxmized_ = false;
          handle_windowsize_change(message, wparam, lparam);
        }
        else if (minimized_) {
          renderpaused_ = false;
          minimized_ = false;
          handle_windowsize_change(message, wparam, lparam);
        }
        else {
          //do something in here
        }
      }
      break;
    }
    case WM_ENTERSIZEMOVE: {
      renderpaused_ = true;
      break;
    }
    case WM_SIZING: { //拖动中
      RECT* rect = (RECT*)lparam;
      switch (wparam) {
        case WMSZ_RIGHT:
          break;
        case WMSZ_BOTTOMRIGHT: {
          keep_windowproportion(rect, WMSZ_RIGHT, WMSZ_TOPLEFT);
          break;
        }
        case WMSZ_LEFT:
          break;
        case WMSZ_BOTTOMLEFT: {
          keep_windowproportion(rect, WMSZ_LEFT, WMSZ_TOPRIGHT);
          break;
        }
        case WMSZ_TOP:
          break;
        case WMSZ_TOPRIGHT: {
          keep_windowproportion(rect, WMSZ_TOP, WMSZ_BOTTOMLEFT);
          break;
        }
        case WMSZ_BOTTOM: {
          keep_windowproportion(rect, WMSZ_BOTTOM, WMSZ_TOPLEFT);
          break;
        }
        case WMSZ_TOPLEFT: {
          keep_windowproportion(rect, WMSZ_TOP, WMSZ_BOTTOMRIGHT);
          break;
        }
      } //switch
      return 1;
    }
    case WM_WINDOWPOSCHANGING: {
      WINDOWPOS* position = (WINDOWPOS*)lparam;
      //不是大小改变
      if (position->flags & SWP_NOSIZE || position->flags & SWP_DRAWFRAME)
        break;
      //是"全屏"状态
      if (variablesystem_ && variablesystem_->getint32("View_FullScreen"))
        break;
      RECT framerect;
      ::SetRect(&framerect, 0, 0, position->cx, position->cy);
      ::OffsetRect(&framerect, position->x, position->y);
      RECT newframe_rect;
      ::CopyRect(&newframe_rect, &framerect);
      keep_windowproportion(&newframe_rect, (uint32_t)-1, WMSZ_TOPLEFT);
      if (::EqualRect(&framerect, &newframe_rect)) //相同则不处理
        break;
      position->x = newframe_rect.left;
      position->y = newframe_rect.right;
      position->cx = newframe_rect.right - newframe_rect.left;
      position->cy = newframe_rect.bottom - newframe_rect.top;
      return 0;
    }
    case WM_DISPLAYCHANGE: { //桌面分辨率改变
      if (eventsystem_ && 
          variablesystem_ &&
          variablesystem_->getint32("View_FullScreen")) {
        eventsystem_->push(vengine_game::event_id::kVariableChanged, 
                           "View_FullScreen", 
                           "1");
      }
      if (maxmized_) {
        ::ShowWindow(g_mainwindow_handle, SW_RESTORE);
        ::ShowWindow(g_mainwindow_handle, SW_MAXIMIZE);
      }
      else {
        eventsystem_->push(
            vengine_game::event_id::kVariableChanged,
            "View_Resoution",
            variablesystem_->getstring("View_Resoution").c_str());
      }
      break;
    }
    case WM_EXITSIZEMOVE: { //用户拖动窗口边缘结束
      renderpaused_ = false;
      handle_windowsize_change(message, wparam, lparam);
      //设置分辨率变量
      if (variablesystem_) {
        RECT rect;
        ::GetClientRect(hwnd, &rect);
        char temp[MAX_PATH] = {0};
        snprintf(temp, 
                 sizeof(temp) - 1, 
                 "%d,%d", 
                 rect.right - rect.left, 
                 rect.bottom - rect.top);
        variablesystem_->setvariable("View_Resoution", temp, false, false);
      }
      break;
    }
    case WM_GETMINMAXINFO: { //决定窗口最大最小尺寸
      MINMAXINFO* minmaxinfo = (MINMAXINFO*)lparam;
      minmaxinfo->ptMinTrackSize.x = kMiniWindowWidth;
      minmaxinfo->ptMinTrackSize.y = kMiniWindowHeight;
      //最大尺寸为"窗口最大化"时的大小
      RECT rect;
      ::SetRect(&rect, 
                0, 
                0, 
                ::GetSystemMetrics(SM_CXSCREEN), 
                ::GetSystemMetrics(SM_CYSCREEN));
      ::AdjustWindowRect(&rect, GetWindowStyle(g_mainwindow_handle), false);
      minmaxinfo->ptMaxSize.x = rect.right - rect.left;
      minmaxinfo->ptMaxSize.y = rect.bottom - rect.top;
      minmaxinfo->ptMaxTrackSize.x = rect.right - rect.left;
      minmaxinfo->ptMaxTrackSize.y = rect.bottom - rect.top;
      break;
    }
    case WM_SETCURSOR: { //鼠标改变
      switch (LOWORD(lparam)) {
        case HTCLIENT: {
          if (cursorsystem_) {
            cursorsystem_->onset();
            return 1;
          }
        }
        default:
          break;
      } //switch
    }
    case WM_ACTIVATEAPP: {
      isactive_ = 1 == wparam ? true : false;
      //通知输入器
      if (inputsystem_)
        (dynamic_cast<input::System*>(inputsystem_))
          ->on_windowactive(isactive_);
      break;
    }
    case WM_ENTERMENULOOP: { //消息主循环移到菜单中
      renderpaused_ = true;
      break;
    }
    case WM_EXITMENULOOP: { //消息主循环移出菜单
      renderpaused_ = false;
      break;
    }
    case WM_SYSCOMMAND: { //系统按键
      switch (wparam) {
        case SC_KEYMENU: //屏蔽F10
          return true;
        default:
          break;
      }
      break;
    }
    case WM_PAINT: {
      PAINTSTRUCT paint_struct;
      ::BeginPaint(hwnd, &paint_struct);
      ::EndPaint(hwnd, &paint_struct);
      //rendersystem_->onpaint();
      break;
    }
    case WM_ERASEBKGND: { //窗口背景刷新
      return 1;
    }
    case WM_CLOSE: { //窗口关闭，处理玩家退出
      //主流程中,弹出设置菜单
      /**
      if (getactive() == main_) {

      }
      **/
      break;
    }
    case WM_DESTROY: {
      ::PostQuitMessage(0);
      break;
    }
    case WM_INPUTLANGCHANGE: { //输入法改变
      //if (eventsystem_)
        //eventsystem_->push();
      break;
    }
    case WM_IME_NOTIFY: {
      if (IMN_SETOPENSTATUS == wparam || IMN_SETCONVERSIONMODE == wparam) {
        if (eventsystem_) {
          //输入法改变
          //eventsystem_->push(); 
        }
      }
    }
    default:
      break;
  } //switch
  LRESULT result = ::DefWindowProc(hwnd, message, wparam, lparam);
  return result;
}
 
void Base::keep_windowproportion(RECT* rect, 
                                 uint32_t changing, 
                                 uint32_t anchor) {
  RECT temprect;
  ::CopyRect(&temprect, rect);
  temprect.left -= frameclient_rectoffset_.left;
  temprect.top -= frameclient_rectoffset_.top;
  temprect.right -= frameclient_rectoffset_.right;
  temprect.bottom -= frameclient_rectoffset_.bottom;
  if (WMSZ_LEFT == changing || WMSZ_RIGHT == changing) {
    //宽不变
    temprect.bottom = temprect.top + 
      static_cast<int32_t>(
          (temprect.right - temprect.left) * windowproportion_);
  }
  else if (WMSZ_TOP == changing || WMSZ_BOTTOM == changing) {
    //高不变
    temprect.right = temprect.left + 
      static_cast<int32_t>(
          (temprect.bottom - temprect.top) * windowproportion_);
  }
  else { //自动调节尺寸
    float proportion = static_cast<float>(
        (temprect.bottom - temprect.top) / (temprect.right - temprect.left));
    if (proportion > windowproportion_) {
      temprect.bottom = temprect.top + 
        static_cast<int32_t>(
            ((temprect.right - temprect.left) * windowproportion_));
    }
    else {
      temprect.right = temprect.left +
        static_cast<int32_t>(
            ((temprect.bottom - temprect.top) * windowproportion_));
    }
  }
  ::AdjustWindowRect(&temprect, kDefaultWindowStyle, false);
  switch (anchor) {
    case WMSZ_TOPLEFT: {
      rect->right = rect->left + (temprect.right - temprect.left);
      rect->bottom = rect->top + (temprect.bottom - temprect.top);
      break;
    }
    case WMSZ_TOPRIGHT: {
      rect->left = rect->right - (temprect.right - temprect.left);
      rect->bottom = rect->top + (temprect.bottom - temprect.top);
      break;
    }
    case WMSZ_BOTTOMLEFT: {
      rect->right = rect->left + (temprect.right - temprect.left);
      rect->bottom = rect->top + (temprect.bottom - temprect.top);
      break;
    }
    case WMSZ_BOTTOMRIGHT: {
      rect->left = rect->right - (temprect.right - temprect.left);
      rect->bottom = rect->top + (temprect.bottom - temprect.top);
      break;
    }
    default:
      break;
  } //switch
}

void Base::handle_windowsize_change(uint32_t message, 
                                    WPARAM wparam, 
                                    LPARAM lparam) {
  if (!g_mainwindow_handle || !rendersystem_) return;
  //... --last complete
}

Base* Base::getactive() {
  return active_;
}

Base* Base::getprevious() {
  return previous_;
}

bool Base::is_windowactive() {
  return isactive_;
}

} //namespace procedure
