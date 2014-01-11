/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-10 23:41:31
 * @uses server net connect manager
 */
#ifndef PAP_SERVER_COMMON_NET_CONNECTION_MANAGER_H_
#define PAP_SERVER_COMMON_NET_CONNECTION_MANAGER_H_

#include "common/net/packet/base.h"
#include "common/net/socket/base.h"
#include "server/common/net/connection/base.h"

namespace pap_server_common_net {

namespace connection {

class Manager {

 public:
   Manager();
   ~Manager();

 public:
   void cleanup();
   virtual bool heartbeat(uint32_t time = 0);
   bool add(Base* connection);
   bool add(int32_t id);
   virtual void remove(int32_t id);
   int32_t* get_allid();
   uint32_t getcount();
   bool hash();

 protected:
   int16_t connectionids_[CONNECTION_MAX];
   uint32_t count_;

};

}; //namespace connection

}; //namespace pap_server_common_net

#endif //PAP_SERVER_COMMON_NET_CONNECTION_MANAGER_H_
