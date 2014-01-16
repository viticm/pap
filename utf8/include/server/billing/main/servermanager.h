/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id servermanager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-11 23:38:58
 * @uses billing server manager
 */
#ifndef PAP_SERVER_BILLING_MAIN_SERVERMANAGER_H_
#define PAP_SERVER_BILLING_MAIN_SERVERMANAGER_H_

/*system include {*/
#if defined(__LINUX__)
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#elif defined(__WINDOWS__)
#include <winsock.h>
#endif
/*system include }*/

#include "server/billing/connection/manager.h"
#include "server/billing/connection/server.h"
#include "server/common/net/socket.h"
#include "server/common/base/define.h"
#include "common/sys/thread.h"


class ServerManager : public billingconnection::Manager {

 public:
   ServerManager();
   ~ServerManager();

 public:
   bool init(); //初始化
   bool select(); //网络侦测
   bool processinput(); //数据接受接口
   bool processoutput(); //数据发送接口
   bool processexception(); //异常连接处理
   bool processcommand(); //消息执行
   bool accept_newconnection(); //新连接接收处理
   virtual bool heartbeat();
   void loop();
   bool isactive();
   void setactive(bool active);

 public:
   //将connection数据加入系统中
   bool addconnection(pap_server_common_net::connection::Base* connection);
   //将拥有fd句柄的玩家(服务器)数据从当前系统中清除
   bool deleteconnection(pap_server_common_net::connection::Base* connection);
   //出现异常后将connection信息清除，并将系统中的信息也清除 断开玩家(服务器)的连接
   bool removeconnection(pap_server_common_net::connection::Base* connection);
   void remove_allconnection();
   //获得服务器连接指针
   billingconnection::Server* get_serverconnection(uint16_t id);
   //服务器广播
   void broadcast(pap_common_net::packet::Base* packet);
   bool connectserver(); //just test

 public:
   uint64_t threadid_;
   int16_t serverhash_[OVER_SERVER_MAX];

 private:
   //用于侦听的服务器Socket
   pap_server_common_net::Socket* serversocket_;
   //用于侦听的服务器SOCKET句柄值（此数据即serversocket_内拥有的SOCKET句柄值）
   int32_t socketid_;
   //网络相关数据
   enum {
     kSelectFull = 0, //当前系统中拥有的完整句柄数据
     kSelectUse, //用于select调用的句柄数据
     kSelectMax,
   };
   fd_set readfds_[kSelectMax];
   fd_set writefds_[kSelectMax];
   fd_set exceptfds_[kSelectMax];
   timeval timeout_[kSelectMax];
   int32_t maxfd_;
   int32_t minfd_;
   int32_t fdsize_;
   bool active_;
   billingconnection::Server billing_serverconnection_;

};

extern ServerManager* g_servermanager;

#endif //PAP_SERVER_BILLING_MAIN_SERVERMANAGER_H_
