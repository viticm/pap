#include "server/common/net/serverconnection.h"

namespace pap_server_common_net {

ServerConnection::ServerConnection(bool isserver) : Connection(isserver) {
  status_ = 0;
}

ServerConnection::~ServerConnection() {
  //do nothing
}

bool ServerConnection::processinput() {
  __ENTER_FUNCTION
    bool result = false;
    result = Connection::processinput();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool ServerConnection::processoutput() {
  __ENTER_FUNCTION
    bool result = false;
    result = Connection::processoutput();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool ServerConnection::processcommand(bool option) {
  __ENTER_FUNCTION
    bool result = false;
    result = Connection::processcommand(option);
    return result;
  __LEAVE_FUNCTION
    return false;
}

void ServerConnection::cleanup() {
  __ENTER_FUNCTION
    Connection::cleanup();
  __LEAVE_FUNCTION
}

bool ServerConnection::heartbeat(uint32_t time) {
  __ENTER_FUNCTION
    bool reslut = false;
    reslut = Connection::heartbeat(time);
    return reslut;
  __LEAVE_FUNCTION
    return false;
}

bool ServerConnection::isserver() {
  return true;
}

bool ServerConnection::isplayer() {
  return false;
}

bool ServerConnection::isbilling() {
  return false;
}

bool ServerConnection::islogin() {
  return false;
}

void ServerConnection::setstatus(uint32_t status) {
  status_ = status;
}

bool ServerConnection::isvalid() {
  __ENTER_FUNCTION
    bool result = false;
    result = Connection::isvalid();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool ServerConnection::sendpacket(pap_common_net::Packet* packet) {
  __ENTER_FUNCTION
    bool result = false;
    result = Connection::sendpacket(packet);
    return result;
  __LEAVE_FUNCTION
    return false;
}

} //namespace pap_server_common_net
