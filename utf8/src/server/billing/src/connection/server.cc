#include "server/billing/connection/server.h"

namespace billingconnection {

Server::Server(bool isserver) : Billing(isserver) {
  status_ = 0;
}

Server::~Server() {
  //do nothing
}

bool Server::processinput() {
  __ENTER_FUNCTION
    bool result = false;
    result = Billing::processinput();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Server::processoutput() {
  __ENTER_FUNCTION
    bool result = false;
    result = Billing::processoutput();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Server::processcommand(bool option) {
  __ENTER_FUNCTION
    bool result = false;
    result = Billing::processcommand(option);
    return result;
  __LEAVE_FUNCTION
    return false;
}

void Server::cleanup() {
  __ENTER_FUNCTION
    Billing::cleanup();
  __LEAVE_FUNCTION
}

bool Server::heartbeat(uint32_t time) {
  __ENTER_FUNCTION
    bool reslut = false;
    reslut = Billing::heartbeat(time);
    return reslut;
  __LEAVE_FUNCTION
    return false;
}

bool Server::isserver() {
  return true;
}

bool Server::isplayer() {
  return false;
}

bool Server::isbilling() {
  return false;
}

bool Server::islogin() {
  return false;
}

void Server::setstatus(uint32_t status) {
  status_ = status;
}

bool Server::isvalid() {
  __ENTER_FUNCTION
    bool result = false;
    result = Billing::isvalid();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Server::sendpacket(pap_common_net::packet::Base* packet) {
  __ENTER_FUNCTION
    bool result = false;
    result = Billing::sendpacket(packet);
    return result;
  __LEAVE_FUNCTION
    return false;
}

pap_server_common_base::server_data_t* Server::get_serverdata() {
  return serverdata_;
}

void Server::set_serverdata(pap_server_common_base::server_data_t* data) {
  serverdata_ = data;
}

void Server::freeown() {
  //nothing
}

} //namespace connection
