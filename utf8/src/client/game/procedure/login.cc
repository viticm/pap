#include "common/net/packets/client_tologin/connect.h"
#include "common/net/packets/client_tologin/asklogin.h"
#include "vengine/variable/system.h"
#include "vengine/input/system.h"
#include "vengine/render/system.h"
#include "vengine/ui/system.h"
#include "vengine/capability/ax/profile.h"
#include "client/game/event/system.h"
#include "client/game/stdafx.h"
#include "client/game/global.h"
#include "client/game/net/manager.h"
#include "client/game/procedure/logindata.h"
#include "client/game/procedure/login.h"

namespace procedure {

Login::Login() {
  status_ = kStatusSelectServer;
  relogin_ = false;
  soundsource_ = NULL;
  load_serverinfo(); //加载登陆服务器信息
  build_autoselect_table();
  username_ = "";
  password_ = "";
  uint8_t i;
  for (i = 0; i < kProvideCount; ++i) {
    autoarea_index_[i] = -1;
    autoserver_index_[i] = -1;
  }
  //前一次找到网络状态空闲的索引
  pre_findidle_ = -1;
  //前一次找到网络状态正常的索引
  pre_findnormal_ = -1;
  //前一次找到网络状态拥挤的索引
  pre_findbusy_ = -1;
  prevserver_ = -1;
  prevarea_ = -1;
}

Login::~Login() {
  //SAFE_DELETE_ARRAY(areainfo_);
}

void Login::firstlogin() {
  Base::variablesystem_->setint32("Login_Mode", kStatusFirstLogin);
}

void Login::render() {
  if (rendersystem_) rendersystem_->renderframe();
}

void Login::changescene() {
  Base::variablesystem_->setint32("Login_Mode", kStatusChangeScene);
}

void Login::init() {
  //禁止改变窗口大小
  int64_t style = ::GetWindowLong(g_mainwindow_handle, GWL_STYLE);
  style &= ~WS_THICKFRAME;
  style &= ~WS_MAXIMIZEBOX;
  ::SetWindowLong(g_mainwindow_handle, GWL_STYLE, (LONG)style);
  ::PostMessage(g_mainwindow_handle, WM_NCACTIVATE, true, 0);
  Base::variablesystem_->set_twofloat_vector("View_Resoution", 
                                             1024, 
                                             768, 
                                             false);
  if (1 == Base::variablesystem_->getint32("GameServer_ConnectDirect")) {
    return;
  }
  //直接连接服务器
  if (1 == Base::variablesystem_->getint32("Game_EnterDirect")) {
    selectserver(0, 0);
    return;
  }
  if (kStatusSelectServer == status_) {
    eventsystem_->push(vengine_game::event_id::kLoginOpenSelectServer);
  }
  //选择旧服务器
  select_oldserver();
}

void Login::select_oldserver() {
  int32_t pre_current_selectarea = variablesystem_->getint32("Login_Area");
  int32_t pre_current_selectserver = variablesystem_->getint32("Login_Server");
  if (pre_current_selectarea >= 0 && pre_current_selectarea < areacount_) {
    int32_t servercount = get_area_servercount(pre_current_selectarea);
    if (pre_current_selectserver >= 0 && 
        pre_current_selectserver < servercount) {
      eventsystem_->push(vengine_game::event_id::kLoginSelectArea,
                         pre_current_selectarea);
      eventsystem_->push(vengine_game::event_id::kLoginSelectLoginServer,
                         pre_current_selectserver);
      return;
    }
  }
}

void Login::tick() {
  Base::tick();
  switch (status_) {
    case kStatusDebug: {
      if (!uisystem_) {
        setstatus(kStatusDisconnect);
      }
      else {
        //wait ui status
      }
      break;
    }
    case kStatusSelectServer: {
      if (1 == variablesystem_->getint32("GameServer_ConnectDirect")) {
        //setactive(); --直接切换场景
        return;
      }
      break;
    }
    case kStatusDisconnect: {
      rendersystem_->debug_pushstring("connect to login server %s:%d...",
                                      serverip_,
                                      serverport_);
      setstatus(kStatusConnecting); //开始连接
      net::Manager::getself()->connect(serverip_, serverport_);
      break;
    }
    case kStatusConnecting:
      break;
    case kStatusConnectSuccess:
      break;
    case kStatusConnectFailed: {
      net::Manager::getself()->close();
      break;
    }
    case kStatusBeginRequesting:
      break;
    case kStatusRequesting:
      break;
    case kStatusSuccess: { //账号验证成功
      //save login server
      variablesystem_->setint32("Login_Area", currentselect_areaid_, false);
      variablesystem_->setint32("Login_Server", currentselect_serverid_, false);
      if (relogin_) { //重连，直接进入场景

      }
      else {
        firstlogin(); //首次登陆
        //转入选择人物循环 --后续再做
      }
      break;
    }
    default:
      break;
   } //switch
}

} //namespace procedure
