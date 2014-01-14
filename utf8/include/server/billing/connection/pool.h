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
#include "server/billing/connection/server.h"

namespace billingconnection {

const uint16_t kPoolSizeMax = 1280;

class Pool {

 public:
   Pool();
   ~Pool();

 public:
   bool init();
   Server* get(int16_t id);
   Server* create(); //new
   void remove(int16_t id); //delete
   void lock();
   void unlock();

 private:
   Server* connection_;
   uint32_t position_;
   pap_common_sys::ThreadLock lock_;
   uint32_t count_;

};

}; //namespace connection

extern billingconnection::Pool* g_connectionpool;

#endif //PAP_SERVER_BILLING_CONNECTION_POOL_H_
