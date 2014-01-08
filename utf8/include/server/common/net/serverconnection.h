/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id server.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-31 17:34:43
 * @uses server net server connection class
 *       cn: 服务器连接模块，用于服务器之间的连接，因为各个服务器都会用到，
 *           所以挪到此处
 */
#ifndef PAP_SERVER_COMMON_NET_SERVERCONNECTION_H_
#define PAP_SERVER_COMMON_NET_SERVERCONNECTION_H_

#include "server/common/net/config.h"
#include "server/common/net/connection.h"

namespace pap_server_common_net {

class ServerConnection : public Connection {

 public:
   ServerConnection(bool isserver = true);
   ~ServerConnection();

 public:
   virtual bool processinput();
   virtual bool processoutput();
   virtual bool processcommand(bool option = true);
   virtual void cleanup();
   virtual bool heartbeat(uint32_t time = 0);

 public:
   virtual isserver();
   virtual isplayer();
   virtual islogin();
   virtual isbilling();
   void setstatus(uint32_t status);
   virtual bool isvalid();
   virtual bool sendpacket(pap_common_net::Packet* packet);

 private:
   uint32_t status_;

};

}; //namespace pap_server_common_net

#endif //PAP_SERVER_COMMON_NET_SERVERCONNECTION_H_
