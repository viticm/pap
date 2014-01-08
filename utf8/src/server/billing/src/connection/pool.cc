#include "server/billing/connection/pool.h"

connection::Pool* g_connectionpool;

namespace connection {

Pool::Pool() {
  connection_ = NULL;
  position_ = 0;
  count_ = 0;
}

Pool::~Pool() {
  SAFE_DELETE_ARRAY(connection_);
}

bool Pool::init() {
  __ENTER_FUNCTION
    using namespace pap_server_common_net;
    connection_ = new ServerConnection[kPoolSizeMax];
    Assert(connection_);
    uint16_t i;
    for(i = 0; i < kPoolSizeMax; ++i) {
      connection_[i].setid(i);
      connection_[i].setempty(true);
    }
    position_ = 0;
    count_ = kPoolSizeMax;
    return true;
  __LEAVE_FUNCTION
    return false;
}


} //namespace connection
