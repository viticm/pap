/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id billing.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-2 11:17:20
 * @uses billing connection class
 */
#ifndef PAP_SERVER_COMMON_NET_CONNECTION_H_
#define PAP_SERVER_COMMON_NET_CONNECTION_H_

#include "server/common/net/connection.h"

namespace connection {

class Billing : public pap_server_common_net::Connection {

 public:
   Billing(bool isserver = true);
   ~Billing();

 public:
   virtual bool processinput();
   virtual bool processoutput();
   virtual bool processcommand(bool option = true);
   virtual void cleanup();
   virtual bool heartbeat(uint32_t time = 0);
 
 public:
   virtual bool isserver();
   virtual bool isplayer();
   virtual bool isbilling();
   virtual bool islogin();
   void setstatus(uint32_t status);
   uint32_t getstatus();
   void clear_keeplive_sendnumber();
   virtual bool isvalid();
   virtual bool sendpacket(pap_common_net::Packet* packet);

 private:
   uint32_t status_;
   uint32_t last_keeplive_time_; //上一次保持连接的时间
   int32_t keeplive_sendnumber_; //保持连接总共发送的包数量

};

}; //namespace connection
