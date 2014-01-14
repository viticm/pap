/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id server.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-31 17:34:43
 * @uses billing net server connection class
 */
#ifndef PAP_SERVER_BILLING_CONNECTION_SERVER_H_
#define PAP_SERVER_BILLING_CONNECTION_SERVER_H_

#include "server/billing/connection/billing.h"
#include "server/common/base/config.h"

namespace billingconnection {

class Server : public Billing {

 public:
   Server(bool isserver = true);
   ~Server();

 public:
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
   pap_server_common_base::server_data_t* get_serverdata();
   void set_serverdata(pap_server_common_base::server_data_t* data);
   void freeown();

 private:
   uint32_t status_;
   pap_server_common_base::server_data_t* serverdata_;
};

}; //namespace connection

#endif //PAP_SERVER_BILLING_CONNECTION_SERVER_H_
