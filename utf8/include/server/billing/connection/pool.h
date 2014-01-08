/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id pool.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-31 17:34:43
 * @uses billing connection pool class
 */
#ifndef PAP_SERVER_BILLING_CONNECTION_POOL_H_
#define PAP_SERVER_BILLING_CONNECTION_POOL_H_

#include "common/sys/thread.h"
#include "common/net/serverconnection.h"

namespace connection {

const uint16_t kPoolSizeMax = 1280;

class Pool {

 public:
   Pool();
   ~Pool();

 public:
   bool init();
   pap_server_common_net::ServerConnection* getconnection(uint16_t connectionid);
   pap_server_common_net::ServerConnection* newconnection();
   void deleteconnection();
   void lock();
   void unlock();

 private:
   pap_server_common_net::ServerConnection* connection_;
   uint32_t position_;
   pap_common_sys::ThreadLock lock_;
   uint32_t count_;

};

}; //namespace connection

extern connection::Pool* g_connectionpool;

#endif //PAP_SERVER_BILLING_CONNECTION_POOL_H_
