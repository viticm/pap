/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-10 23:41:31
 * @uses billing server net connect manager
 */
#ifndef PAP_SERVER_BILLING_CONNECTION_MANAGER_H_
#define PAP_SERVER_BILLING_CONNECTION_MANAGER_H_

#include "common/net/packet/base.h"
#include "common/net/socket/base.h"
#include "server/common/net/connection/base.h"
#include "server/common/net/connection/manager.h"

namespace billingconnection {

class Manager : public pap_server_common_net::connection::Manager {

 public:
   Manager();
   ~Manager();

 public:
   void cleanup();
   virtual bool heartbeat(uint32_t time = 0);
   bool add(pap_server_common_net::connection::Base* connection);
   bool add(int16_t id);
   void remove(int16_t id);
   int16_t* get_allid();
   uint16_t getcount();
   bool hash();

};

}; //namespace connection

#endif //PAP_SERVER_BILLING_CONNECTION_MANAGER_H_
