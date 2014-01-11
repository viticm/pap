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
    connection_ = new pap_server_common_net::connection::Server[kPoolSizeMax];
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

pap_server_common_net::ServerConnection* Pool::get(uint16_t id) {
  __ENTER_FUNCTION
    pap_server_common_net::connection::Server* connection = NULL;
    if (connectionid > kPoolSizeMax) return NULL;
    connection = &(connection_[id]);
    return connection;
  __LEAVE_FUNCTION
    return NULL;
}

pap_server_common_net::ServerConnection* Pool::create() {
  __ENTER_FUNCTION
    pap_server_common_net::connection::Server* connection = NULL;
    lock();
    uint16_t result = 0, i;
    for (i = 0; i < kPoolSizeMax; ++i) {
      if (connection_[position_].isempty()) { //找出空闲位置
        result = position_;
        connection_[position_].setempty(false);
        ++position_;
        position_ >= kPoolSizeMax && position_ = 0;
        --count_;
        connection = &(connection_[result]);
        break;
      }
      ++position_;
      position_ >= kPoolSizeMax && position_ = 0;
    }
    unlock();
    return connection;
  __LEAVE_FUNCTION
    unlock();
    return NULL;
}

void Pool::remove(uint16_t id) {
  __ENTER_FUNCTION
    lock();
    if (id > kPoolSizeMax) {
      Assert(false);
      unlock();
      return;
    }
    connection_[id].setempty(true);
    ++count_;
    unlock();
  __LEAVE_FUNCTION
    unlock();
}

void Pool::lock() {
  lock_.lock();
}

void Pool::unlock() {
  lock_.unlock();
}

} //namespace connection
