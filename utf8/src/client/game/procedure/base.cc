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
#include "client/game/cursor/system.h"
#include "client/game/script/system.h"
#include "client/game/timer/manager.h"
#include "client/resource/loadlistener.h"
#include "client/resource/provider.h"
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
vengine_sound::System* Base::timesystem_ = NULL;
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
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(vengine_kernel::Node));
  //网络管理器
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(net::Manager));
  //场景管理器
  //g_kernel->registerclass(VENGINE_KERNEL_GETCLASS());
  //图形系统
  //g_kernel->registerclass();
  //输入管理器
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(input::System));
  //时间管理器
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(vengine_time::System));
  //声音管理器
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(sound::System));
  //数据库管理器
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(database::System));
  //UI操作接口
  //g_kernel->registerclass();
  //UI数据池
  //g_kernel->registerclass();
  //g_kernel->registerclass();
  //UI鼠标操作类
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(cursor::System));
  //脚本系统
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(script::System));
  //事件系统
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(event::System));
  //操作管理
  //g_kernel->registerclass();
  //UI模型显示管理
  //g_kernel->registerclass();
  //外接帮助系统
  //g_kernel->registerclass();
  //资源
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(resoure::Provider));
  //物品传输系统
  //g_kernel->registerclass();
  //定时器
  g_kernel->registerclass(VENGINE_KERNEL_GETCLASS(timer::Manager));

#ifdef USEOGRELIB
  extern void install_uisystem(vengine_kernel::Base* kernel);
#else
  g_kernel->loadplugin("vgui.dll", g_kernel);
#endif

  //初始化所有的循环实例
  login_ = new Login(); //登陆循环
  //初始化数据核心
  //0.输入管理器
  inputsystem_ = dynamic_cast<vengine_input::System*>(
      g_kernel->newnode("input::System", "bin", "input"));
  //1.时间管理器
  timesystem_ = dynamic_cast<vengine_time::System*>(
      g_kernel->newnode("vengine_time::System", "bin", "time"));
  //2.网络管理器
  netmanager_ = dynamic_cast<net::Manager*>(
      g_kernel->newnode("net::Manager", "bin", "net"));
  //3.声音管理器
  soundsystem_ = dynamic_cast<vengine_sound::System*>(
      g_kernel->newnode("sound::System", "bin", "sound"));
  //4.渲染器节点

  //5.调试器节点
  debuger_ = dynamic_cast<vengine_capability::Debuger*>(
      g_kernel->newnode("vengine_capability::Debuger", "bin", "debuger"));
  //6.物体管理器
  
  //7.UI管理器
  uisystem_ = dynamic_cast<vengine_ui::System*>(
      g_kernel->newnode("vengine_ui::System", "bin", "ui"));

  //8.数据库管理器
  dbsystem_ = dynamic_cast<vengine_db::System*>(
      g_kernel->newnode("database::System", "bin", "db"));
  //9.世界管理器
  
  //10.变量管理器
  variablesystem_ = dynamic_cast<vengine_variable::System*>(
      g_kernel->newnode("variable::System", "bin", "var"));

  //11.接口管理器
  
  //12.UI数据池
  
  //13.鼠标管理器
  cursorsystem_ = dynamic_cast<vengine_cursor::System*>(
      g_kernel->newnode("cursor::System", "bin", "cursor"));

  //14.脚本系统
  scriptsystem_ = dynamic_cast<vengine_script::System*>(
      g_kernel->newnode("script::System", "bin", "script"));
  //15.事件系统
  eventsystem_ = dynamic_cast<vengine_game::EventSystem*>(
      g_kernel->newnode("event::System", "bin", "event"));
  //16.操作管理

  //17.UI模型显示管理

  //18.外接帮助系统

  //19.资源
  resourceprovider_ = dynamic_cast<vengine_resource::Provider*>(
      g_kernel->newnode("resource::Provider", "bin", "resource_provider"));
  //20.时间管理器
  timesystem_ = dynamic_cast<vengine_time::System*>(
      g_kernel->newnode("TimeSystem", "bin", "time"));
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
  g_kernel->shutdown();
  //销毁主窗口
  destroy_mainwindow();
}

void CALLBACK Base::eventtimer(uint32_t timeid, 
                               uint32_t message,
                               uint64_t user,
                               uint64_t param1,
                               uint64_t param2) {
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
  int32_t windowwidth = 0;
  int32_t windowheigth = 0;
  if (variablesystem_) {
    bool have = false;
    vengine_math::base::twofloat
  }
}

} //namespace procedure
