#include "common/net/packets/client_toserver/heartbeat.h"

#include "vengine/exception/base.h"
#include "vengine/time/system.h"
#include "vengine/base/util.h"

#include "client/game/global.h"
#include "client/game/event/system.h"
#include "client/game/script/system.h"
#include "client/game/procedure/base.h"
#include "client/game/procedure/login.h"
#include "client/game/net/manager.h"

namespace net {

const uint32_t kConnectTimeMax = 10 * 100000; //最大连接时间 10s

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(Manager);

Manager* Manager::self_ = NULL;

extern char error[128];

Manager::Manager() {
  socket_inputstream_ = socket_outputstream_ = &socket_;
  self_ = this;
  connectthread_handle_ = NULL;
}

Manager::~Manager() {
  //do nothing
}

Manager* Manager::getself() {
 return self_;
}

void Manager::init(void*) {
  //window socket init
  WSADATA wsa_data;
  if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0 || 
      (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE( wsa_data.wVersion ) != 2)) {
    WSACleanup();
    VENGINE_SHOW("net::Manager::init failed! not find a usable winsock dll!");
    return;
  }
  connectthread_handle_ = NULL;
  packet_factorymanager_.init();
}

//游戏登陆流程
void Manager::tick_loginprocedure() {
  switch (procedure::Base::login_->getstatus()) {
    case procedure::Login::kStatusDebug: {
      break;
    }
    case procedure::Login::kStatusSelectServer: {
      break;
    }
    case procedure::Login::kStatusDisconnect: {
      break;
    }
    case procedure::Login::kStatusConnecting: {
      waitpacket();
      break;
    }
    case procedure::Login::kStatusConnectFailed: {
      break;
    }
    case procedure::Login::kStatusBeginRequesting: {
      break;
    }
    case procedure::Login::kStatusConnectSuccess: {
      waitpacket();
      break;
    }
    case procedure::Login::kStatusRequesting: {
      waitpacket();
      break;
    }
    default: {
      waitpacket();
      break;
    }
  }
}

void Manager::tick_selectcharacter_procedure() {
  waitpacket();
}

void Manager::tick_createcharacter_procedure() {
  waitpacket();
}

void Manager::tick_mainprocedure() { //进入游戏后的流程
  waitpacket();
  send_heartbeat(); //保持连接
}

void Manager::tick_changeserver_procedure() {
  //以后待做
}

void Manager::tick_enterprocedure() {
  //以后待做
}

void Manager::tick() {
  if (procedure::Base::getactive() == 
      dynamic_cast<procedure::Base*>(procedure::Base::login_)) {
    tick_loginprocedure();
  }
}

void Manager::waitconnecting() {
  int32_t exitcode = 0;
  if (::GetExitCodeThread(connectthread_handle_, (DWORD*)&exitcode)) {

  }
  //登录线程未结束
  if (STILL_ACTIVE == exitcode) {
    uint32_t nowtime = procedure::Base::timesystem_->get_nowtime();
    uint32_t used = procedure::Base::timesystem_->get_difftime(
        beginconnect_time_, 
        nowtime);
    if (used > kConnectTimeMax) { //超时
      TerminateThread(connectthread_handle_, 0);
      exitcode = -3;
    }
    else {
      return; //继续等待
    }
  }
  //登录线程已经结束 关闭句柄
  if (CloseHandle(connectthread_handle_)) {
    connectthread_handle_ = NULL;
  }

  if (exitcode < 0) { //发生错误
    switch (exitcode) {
      case -1: {
        setstatus(kStatusCreateSocketError);
        STRING temp = "";
        temp = NOCOLOR_MESSAGE("net::Manager-> socket create error");
        procedure::Base::eventsystem_->push(vengine_game::event_id::kNetClose,
                                            temp.c_str());
        break;
      }
      case -2: {
        setstatus(kStatusConnectFailed);
        STRING temp = "";
        temp = NOCOLOR_MESSAGE("net::Manager-> socket connect failed");
        procedure::Base::eventsystem_->push(vengine_game::event_id::kNetClose,
                                            temp.c_str());
        break;
      }
      case -3: {
        setstatus(kStatusConnectTimeOut);
        STRING temp = "";
        temp = NOCOLOR_MESSAGE("net::Manager-> connect is time out");
        procedure::Base::eventsystem_->push(vengine_game::event_id::kNetClose,
                                            temp.c_str());
        break;
      }
      default: {
        setstatus(kStatusConnectFailed);
        STRING temp = "";
        temp = NOCOLOR_MESSAGE("net::Manager-> unkown error");
        procedure::Base::eventsystem_->push(vengine_game::event_id::kNetClose,
                                            temp.c_str());
        break;
      }
    }
    this->close();
    return;
  }
  //连接成功后设置为非阻塞模式和设置Linger参数
  if (!socket_->set_nonblocking() || socket_->setlinger(0)) {
    setstatus(kStatusConnectFailed);
    VENGINE_SHOW("net::Manager::tick socket have error in setting");
    return;
  }
  
  //通知登陆流程连接成功
  if (procedure::Base::getactive() == 
      dynamic_cast<procedure::Base*>(procedure::Base::login_)) {
    procedure::Base::login_->send_connectmessage();
    setstatus(kStatusSuccess);
  }
}

void Manager::waitpacket() {
  if (!socket_.isvalid()) return;
  //网络数据流操作
  if (!select() || !processexcept() || !processinput() || !processoutput()) {
    procedure::Base::eventsystem_->push(vengine_game::event_id::kNetClose);
    return;
  }
  processcommand();
}

void Manager::release() {
  //尚有登录线程在运行,强制终止
  if (connectthread_handle_) {
    TerminateThread(connectthread_handle_, 0);
    CloseHandle(connectthread_handle_);
    connectthread_handle_ = NULL;
  }
  socket_.close();
  WSACleanup();
}

void Manager::connect(const char* ip, uint16_t port) {
  //已经有登录线程在运行中
  if (connectthread_handle_) return;
  serverip_ = ip;
  port_ = port;
  uint32_t threadid;
  connectthread_handle_ = (HANDLE)::_beginthreadex(
      NULL, 
      0, 
      connectthread_forserver, 
      this, 
      CREATE_SUSPENDED | THREAD_QUERY_INFORMATION, 
      &threadid);
  if (NULL == connectthread_handle_) {
    VENGINE_SHOW("net::Manager::connect: can't create connect thread");
  }
  beginconnect_time_ = procedure::Base::timesystem_->get_nowtime();
  ResumeThread(connectthread_handle_);
}

void Manager::sendpacket(pap_common_net::packet::Base* packet) {
  //如果是处于等待切换场景流程中，则返回 --暂时不做
  if (socket_.isvalid()) {
    uint32_t beforesize = socket_outputstream_.length();
    socket_outputstream_.writepacket(packet);
    uint32_t aftersize = socket_outputstream_.length();
    if (packet->getsize() != aftersize - beforesize - 6) {
      VENGINE_SHOW("net::Manager::sendpacket: size error "
                   "[id = %d, stream = %d, size = %d]",
                   packet->getid(),
                   aftersize - beforesize - 6,
                   packet->getsize());
    }
  }
}

uint32_t Manager::connectthread_forserver(LPVOID param) {
  VENGINE_ASSERT(param);
  Manager* manager = (Manager*)param;
  return manager->connectthread();
}

int32_t Manager::connectthread() {
  socket_.close();
  if (!socket_.create()) return -1; //无法创建socket
  if (!socket_.connect(serverip_, serverport_)) {
    socket_.close();
    return -2; //无法连接到服务器
  }
  return 1;
}

bool Manager::select() {
  FD_ZERO(&exceptfd_);
  FD_ZERO(&readfd_);
  FD_ZERO(&writefd_);

  FD_SET(socket_.getid(), &exceptfd_);
  FD_SET(socket_.getid(), &readfd_);
  FD_SET(socket_.getid(), &writefd_);

  timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
 
  if (SOCKET_ERROR == pap_common_net::socket::Base::select(
        0,
        &readfd_,
        &writefd_,
        &exceptfd_,
        &timeout)) {
    return false;
  }
  else {
    return true;
  }
}

bool Manager::processinput() {
  if (FD_ISSET(socket_.getid(), &readfd_)) {
    uint32_t result = socket_inputstream_.fill();
    if (static_cast<int32_t>(result) <= SOCKET_ERROR) {
      socket_.close();
      return false;
    }
  }
  return true;
}

bool Manager::processoutput() {
  //如果是处于等待切换场景流程中则不处理 --暂时不做
  if (FD_ISSET(socket_.getid(), &writefd_)) {
    uint32_t result = socket_outputstream_.flush();
    if (static_cast<int32_t>(result) <= SOCKET_ERROR) {
      socket_.close();
      return false;
    }
  }
  return true;
}

void Manager::processinput(pap_common_net::socket::InputStream& inputstream) {
  bool result = false;
  char header[PACKET_HEADERSIZE] = {0};
  uint16_t packetid;
  uint32_t packetcheck, packetsize, packetindex;
  pap_common_net::packet::Base* packet = NULL;
  //same as the server, see the connections
  for (;;) {
    if (!socket_inputstream_.peek(&header[0], PACKET_HEADERSIZE)) {
      break;
    }
    memcpy(&packetid, &packetheader[0], sizeof(uint16_t));
    memcpy(&packetcheck, &packetheader[sizeof(uint16_t)], sizeof(uint32_t));
    packetsize = GET_PACKETLENGTH(packetcheck);
    packetindex = GET_PACKETINDEX(packetcheck);
    if (!pap_common_net::packet::FactoryManager::isvalid_packetid(packetid)) {
      VENGINE_SHOW("net::Manager::processinput: invalid packet id: %d", 
                   packetid);
      return;
    }
    
    if (socket_inputstream_.reallength() < PACKET_HEADERSIZE + packetsize) {
      break;
    }
    
    if (packetsize > packet_factorymanager_.getpacket_maxsize(packetid)) {
      VENGINE_SHOW("net::Manager::processinput:: packet size error!"
                   "packet id: %d, receive size: %d, max size: %d",
                   packetid,
                   packetsize,
                   packet_factorymanager_.getpacket_maxsize(packetid));
      break;
    }
    packet = g_packetfactory_manager.createpacket(packetid);
    Assert(packet);
    if (NULL == packet) {
      VENGINE_SHOW("net::Manager::processinput:: packet create error, id: %d",
                   packetid);
      return;
    }

    packet->setindex(static_cast<int8_t>(packetindex));
    
    reslut = socket_inputstream_.readpacket(packet);

    if (false == result) {
      VENGINE_SHOW("net::Manager::processinput:: packet read error, id: %d",
                   packetid);
      continue;
    }

    //执行
    result = executepacket_genexception(packet);
    if (result != pap_common_net::kPacketExecuteStatusNotRemove) {
      packet_factorymanager_.removepacket(packet);
    }

  } //for loop

}

uint32_t Manager::executepacket_genexception(
    pap_common_net::packet::Base* packet) {
  char title[MAX_PATH] = {0};
  snprintf(title, sizeof(title) - 1, "packet id: %d", packet->getid());
  __try {
    return executepacket_cppexception(packet);
  }
  __except(vengine_exception::base::processinner(
        GetExceptionInformation(), 
        g_mainwindow_handle, 
        title), 
      EXCEPTION_EXECUTE_HANDLER) {

  }
  return pap_common_net::kPacketExecuteStatusContinue;
}

uint32_t Manager::executepacket_cppexception(
    pap_common_net::packet::Base* packet) {
  try {
    return packet->execute(
        dynamic_cast<pap_server_common_net::connection::Base*>(this));
  }
  catch(const std::exception& exception) {
    static STRIN cppexception;
    cppexception = exception.what();
    LPVOID exceptionpointer = &cppexception;
    ::RaiseException(
        0XE000C0DE,
        EXCEPTION_NONCONTINUABLE,
        1,
        (const ULONG_PTR*)&exceptionpointer);
  }
  catch(...) {
    throw;
  }
  return pap_common_net::kPacketExecuteStatusContinue;
}

void Manager::processcommand() {
  processinput(socket_inputstream_);
}

bool Manager::processexcept() {
  if (FD_ISSET(socket_.getid(), &exceptfd_)) {
    socket_.close();
    return false;
  }
  return true;
}

void Manager::send_heartbeat() {
  static last_sendtime = 0;
  const uint32_t kSendInterval = 60 * 1000; //1 Minutes
  uint32_t nowtime = procedure::Base::timesystem_->get_nowtime();
  if (nowtime - last_sendtime > kSendInterval) {
    pap_common_net::packets::client_toserver::HeartBeat message;
    this->sendpacket(message);
    last_sendtime = nowtime;
  }
}

void Manager::close() {
  socket_.close();
}

void Manager::setstatus(status_enum status) {
  if (procedure::Base::getactive() == 
      dynamic_cast<procedure::Base*>(procedure::Base::login_)) {
    set_loginstatus(status);
  }
}

void Manager::set_loginstatus(status_enum status) {
  switch (status) {
    case kStatusSuccess: {
      procedure::Base::login_->setstatus(
          procedure::Login::kStatusConnectSuccess);
      break;
    }
    case kStatusCreateSocketError: {
      procedure::Base::login_->setstatus(
          procedure::Login::kStatusConnectFailed);
      break;
    }
    case kStatusConnectFailed: {
      procedure::Base::login_->setstatus(
          procedure::Login::kStatusConnectFailed);
      break;
    }
    case kStatusConnectTimeOut: {
      procedure::Base::login_->setstatus(
          procedure::Login::kStatusConnectFailed);
      break;
    }
    default:
      break;
  }
}

void Manager::set_mainstatus(status_enum status) {
  //do nothing
}

pap_common_net::packet::FactoryManager Manager::get_packet_factorymanager() {
  return packet_factorymanager_;
}

} //namespace net
