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
 *           所以挪到此处，消费服务器与世界服务器需重写
 */
#ifndef PAP_SERVER_COMMON_NET_CONNECTION_SERVER_H_
#define PAP_SERVER_COMMON_NET_CONNECTION_SERVER_H_

#include "server/common/net/config.h"
#include "server/common/net/connection/base.h"

namespace pap_server_common_net {

namespace connection {

class Server : public Base {

 public:
   Server(bool isserver = true);
   ~Server();

 public:
   bool init();
   virtual bool processinput();
   virtual bool processoutput();
   virtual bool processcommand(bool option = true);
   virtual void cleanup();
   virtual bool heartbeat(uint32_t time = 0);

 public:
   virtual bool isserver();
   virtual bool isplayer();
   virtual bool islogin();
   virtual bool isbilling();
   void setstatus(uint32_t status);
   virtual bool isvalid();
   virtual bool sendpacket(pap_common_net::packet::Base* packet);

 private:
   uint32_t status_;

};

}; //namespace connection

}; //namespace pap_server_common_net

#endif //PAP_SERVER_COMMON_NET_CONNECTION_SERVER_H_
