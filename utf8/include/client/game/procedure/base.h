/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-8 09:58:08
 * @uses client game procedure base class
 *       cn: 流程控制基类
 */
#ifndef PAP_CLIENT_GAME_PROCEDURE_BASE_H_
#define PAP_CLIENT_GAME_PROCEDURE_BASE_H_

#include "vengine/classes.h"
#include "vengine/ui/system.h"

//all use classes
namespace procedure {
class Login;
}; //namespace procedure

namespace net {
class Manager;
}; //namespace net

#define NEW_DEBUG_MESSAGE(str) \
  if (procedure::Base::eventsystem_) \
    procedure::Base::eventsystem_->push( \
        vengine_game::event_id::kNewDebugMessage, (str)##.c_str());

//parsestring functions macros
#define NOCOLOR_MESSAGE \
  procedure::Base::uisystem_->parsestring_nocolor_varparam

#define COLOR_MESSAGE \
  procedure::Base::uisystem_->parsestring_varparam

#define NOPARAM_MESSAGE(str) \
  procedure::Base::uisystem_ ? \
    procedure::Base::uisystem_->parsestring_no_varparam(STRING(str).c_str()) \
      : ""

namespace procedure {

typedef std::vector<STRING> unuse_string_vector;

class Base {

 public:
   static Login* login_; //登陆流程（目前只做这个）
   static net::Manager* netmanager_; //网络管理器
   static vengine_input::System* inputsystem_; //输入系统
   static vengine_game::WorldSystem* worldsystem_; //世界管理器（场景）
   static vengine_game::object::BaseSystem* objectsystem_; //对象管理器
   static vengine_game::Interface* interface_; //逻辑接口
   static vengine_game::data_pool::Base* datapool_; //数据池
   static vengine_game::data_pool::Ui* ui_datapool_; //UI数据池
   static vengine_game::EventSystem* eventsystem_; //事件管理器
   //物品传输系统
   static vengine_game::ItemTransferSystem* itemtransfer_system_;
   static vengine_capability::Debuger* debuger_; //调试指针
   static vengine_render::System* rendersystem_; //渲染系统
   static vengine_ui::System* uisystem_; //UI系统
   static vengine_time::System* timesystem_; //时间管理器
   static vengine_sound::System* soundsystem_; //声音管理器
   static vengine_db::System* dbsystem_; //数据管理器
   static vengine_cursor::System* cursorsystem_; //鼠标管理器
   static vengine_script::System* scriptsystem_; //脚本管理器
   static vengine_resource::Provider* resourceprovider_; //资源提供

 public:
   static void init_staticmember(); //静态成员初始化
   static void setactive();
   static void tickactive();
   static void processevent(); //事件处理
   static void process_activeinput(); //键盘事件和鼠标事件的处理
   static void process_closerequest(); //玩家请求退出程序事件
   static void renderactive(); //进入当前游戏循环的渲染函数
   static void release_staticmemeber(); //释放静态成员
   static void mainloop(); //消息主循环
   static void handle_windowsize_change(uint32_t message, 
                                        WPARAM wparam, 
                                        LPARAM lparam); //处理窗口改变
   static Base* getactive(); //获得当前激活的流程
   static bool is_windowactive(); //主窗口是否激活
   static void _tick();
   static Base* getprevious(); //得到前一个流程

 public:
   static bool needfresh_minimap_;
   static bool wait_needfresh_minimap_;

 protected:
   static Base* active_; //当前游戏流程
   static Base* previous_; //前一个游戏流程


 protected:
   static bool minimized_; //是否为最小化窗口
   static bool maxmized_; //是否为最大化窗口
   static bool fullscreen_; //是否为全屏
   static RECT windowrect_; //窗口位置
   static float windowproportion_; //窗口比例
   static RECT frameclient_rectoffset_; //Frame<->Client的差值
   static bool isactive_; //窗口是否处于焦点状态
   static bool renderpaused_; //渲染暂停
   static bool ui_handleinput_; //ui获得输入状态
   static float FPS_; //帧率
   static MMRESULT eventtimer_; //系统驱动事件（windows)
   static HANDLE tickevent_; //tick通知事件
   static void CALLBACK eventtimer(uint32_t timeid, 
                                   uint32_t message,
                                   uint64_t user,
                                   uint64_t param1,
                                   uint64_t param2); //系统Tick驱动函数
   static HANDLE renderevent_; //渲染事件
   
 private:
   static void create_mainwindow();
   static void destroy_mainwindow();
   static LRESULT CALLBACK mainwindow_process(HWND, UINT, WPARAM, LPARAM);
   static void keep_windowproportion(RECT* rect, 
                                     uint32_t changing, 
                                     uint32_t anchor);

};

}; //namespace procedure

#endif //PAP_CLIENT_GAME_PROCEDURE_BASE_H_
