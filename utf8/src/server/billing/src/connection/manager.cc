#include "server/billing/connection/manager.h"
#include "server/billing/connection/pool.h"

namespace billingconnection {

Manager::Manager() : pap_server_common_net::connection::Manager() {
  //do nothing
}

Manager::~Manager() {
  //do nothing
}

void Manager::cleanup() {
  pap_server_common_net::connection::Manager::cleanup();
}

bool Manager::heartbeat(uint32_t time) {
  __ENTER_FUNCTION
    bool result = false;
    result = pap_server_common_net::connection::Manager::heartbeat(time);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Manager::add(pap_server_common_net::connection::Base* connection) {
  __ENTER_FUNCTION
    bool result = false;
    result = pap_server_common_net::connection::Manager::add(connection);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Manager::add(int16_t id) {
  __ENTER_FUNCTION
    bool result = false;
    result = pap_server_common_net::connection::Manager::add(id);
    return result;
  __LEAVE_FUNCTION
    return false;
}

void Manager::remove(int16_t id) {
  __ENTER_FUNCTION
    Assert(count_ > 0);
    pap_server_common_net::connection::Base* connection = NULL;
    connection = g_connectionpool->get(id);
    if (NULL == connection) {
      Assert(false);
      return;
    }
    int16_t managerid = connection->get_managerid();
    if (managerid >= static_cast<int16_t>(sizeof(connectionids_))) {
      Assert(false);
      return;
    }
    connection = g_connectionpool->get(connectionids_[count_ - 1]);
    if (NULL == connection) {
      Assert(false);
      return;
    }
    connectionids_[managerid] = connectionids_[count_ - 1];
    connectionids_[count_ - 1] = ID_INVALID;
    connection->set_managerid(managerid);
    --count_;
    Assert(count_ >= 0);
  __LEAVE_FUNCTION
}

int16_t* Manager::get_allid() {
  return connectionids_;
}

uint16_t Manager::getcount() {
  return count_;
}

bool Manager::hash() {
  bool result = count_ > 0;
  return result;
}

} //namespace connection
