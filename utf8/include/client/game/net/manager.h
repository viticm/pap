/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-7 16:24:14
 * @uses pap client game net manager
 */
#ifndef PAP_CLIENT_GAME_NET_MANAGER_H_
#define PAP_CLIENT_GAME_NET_MANAGER_H_

//#include <winsock2.h>

#include "vengine/kernel/node.h"

#include "common/net/socket/base.h"
#include "common/net/socket/inputstream.h"
#include "common/net/socket/outputstream.h"
#include "common/net/packet/base.h"
#include "common/net/packet/factorymanager.h"

// -- 在exe的外面不会有大的命名空间

namespace net {

class Manager : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(net_Manager);

 public:
   Manager();
   virtual ~Manager();
   static Manager* getself();

 public:
   void connect(const char* ip, uint16_t port);
   void sendpacket(pap_common_net::packet::Base* packet);
   void close();
   void processinput(pap_common_net::socket::InputStream& inputstream);
   pap_common_net::packet::FactoryManager get_packet_factorymanager();

 public:
   virtual void init(void*);
   virtual void tick(); //逻辑轮询
   virtual void release();

 public:
   enum status_enum {
     kStatusConnectSuccess = 0,
     kStatusCreateSocketError,
     kStatusConnectError,
     kStatusConnectFailed,
     kStatusConnectTimeOut,
   };
   //流程 ~
   void tick_loginprocedure();
   void tick_mainprocedure();
   void tick_selectcharacter_procedure();
   void tick_changeserver_procedure();
   void tick_createcharacter_procedure();
   void tick_enterprocedure();
   //网络状态设置
   void setstatus(status_enum status);
   void set_loginstatus(status_enum status);
   void set_mainstatus(status_enum status);

 protected:
   //连接服务器专用线程
   static uint32_t CALLBACK connectthread_forserver(LPVOID param);
   int32_t connectthread();
   //连接线程句柄
   HANDLE connectthread_handle_;
   uint32_t beginconnect_time_; //开始连接时间
   static Manager* self_;
   STRING serverip_;
   uint16_t serverport_;
   status_enum status_;

 private:
   fd_set readfd_;
   fd_set writefd_;
   fd_set exceptfd_;
   pap_common_net::socket::Base socket_;
   pap_common_net::socket::InputStream socket_inputstream_;
   pap_common_net::socket::OutputStream socket_outputstream_;
   pap_common_net::packet::FactoryManager packet_factorymanager_;

 private:
   void waitconnecting();
   void waitpacket();
   void send_heartbeat();
   bool select();
   bool processinput();
   bool processoutput();
   bool processexcept();
   void processcommand();

   uint32_t executepacket_cppexception(pap_common_net::packet::Base* packet);
   uint32_t executepacket_genexception(pap_common_net::packet::Base* packet);

};

}; //namespace net

#endif //PAP_CLIENT_GAME_NET_MANAGER_H_
