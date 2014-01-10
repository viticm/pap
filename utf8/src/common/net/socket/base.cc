#include "common/net/socket/base.h"
#include "common/lib/vnet/vnet.hpp"

namespace pap_common_net {

namespace socket {

Base::Base() {
  __ENTER_FUNCTION
    socketid_ = SOCKET_INVALID;
    memset(host_, '\0', sizeof(host_));
    port_ = 0;
  __LEAVE_FUNCTION
}

Base::Base(const char* host, uint16_t port) {
  __ENTER_FUNCTION
    memset(host_, '\0', sizeof(host_));
    snprintf(host_, sizeof(host_) - 1, "%s", host);
    port_ = port;
    create();
  __LEAVE_FUNCTION
}

Base::~Base() {
  __ENTER_FUNCTION
    close()
  __LEAVE_FUNCTION
}

bool Base::create() {
  __ENTER_FUNCTION
    bool result = true;
    socketid_ = vnet_socketbase_create();
    result = isvalid();
    return result;
  __LEAVE_FUNCTION
    return false;
}

void Base::close() {
  __ENTER_FUNCTION
    if (isvalid() && !iserror())
      vnet_socketbase_close(socketid_);
    socketid_ = SOCKET_INVALID;
    memset(host_, '\0', sizeof(host_));
    port_ = 0;
  __LEAVE_FUNCTION
}

bool Base::connect() {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_connect(socketid_, host_, port_);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Base::connect(const char* host, uint16_t port) {
  __ENTER_FUNCTION
    bool result = true;
    snprintf(host_, sizeof(host_) - 1, "%s", host);
    port_ = port;
    result = connect();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Base::reconnect(const char* host, uint16_t port) {
  __ENTER_FUNCTION
    bool result = true;
    close();
    snprintf(host_, sizeof(host_) - 1, "%s", host);
    port_ = port;
    create();
    result = connect();
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Base::send(const void* buffer, uint32_t length, uint32_t flag) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_send(socketid_, buffer, length, flag);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint32_t Base::receive(void* buffer, uint32_t length, uint32_t flag) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_receive(socketid_, buffer, length, flag);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint32_t Base::available() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_available(socketid_);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

int32_t Base::accept(uint16_t port) {
  __ENTER_FUNCTION
    int32_t result = SOCKET_ERROR;
    result = vnet_socketbase_accept(socketid_, port);
    return result;
  __LEAVE_FUNCTION
    return SOCKET_ERROR;
}

int32_t Base::fastaccept() {
  __ENTER_FUNCTION
    int32_t result = SOCKET_ERROR;
    result = vnet_socketbase_fastaccept(socketid_);
    return result;
  __LEAVE_FUNCTION
    return SOCKET_ERROR;
}

bool Base::bind() {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_bind(socketid_, port_);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Base::bind(uint16_t port) {
  __ENTER_FUNCTION
    bool result = true;
    port_ = port;
    result = vnet_socketbase_bind(socketid_, port_);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Base::listen(uint32_t backlog) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_listen(socketid_, backlog);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Base::getlinger() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_getlinger(socketid_);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool Base::setlinger(uint32_t lingertime) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_setlinger(socketid_, lingertime);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Base::is_reuseaddr() const {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_is_reuseaddr(socketid_);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Base::set_reuseaddr(bool on) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_set_reuseaddr(socketid_, on);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Base::getlast_errorcode() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_getlast_errorcode();
    return result;
  __LEAVE_FUNCTION
    return 0;
}

void Base::getlast_errormessage(char* buffer, uint16_t length) const {
  __ENTER_FUNCTION
    vnet_socketbase_getlast_errormessage(buffer, length);
  __LEAVE_FUNCTION
}

bool Base::iserror() const {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_iserror(socketid_);
    return result;
  __LEAVE_FUNCTION
    return true;
}

bool Base::is_nonblocking() const {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_is_nonblocking(socketid_);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Base::set_nonblocking(bool on) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_set_nonblocking(on);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Base::getreceive_buffersize() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_getreceive_buffersize(socketid_);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool Base::setreceive_buffersize(uint32_t size) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_setreceive_buffersize(socketid_, size);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Base::getsend_buffersize() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_getsend_buffersize(socketid_);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool Base::setsend_buffersize(uint32_t size) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_setsend_buffersize(socketid_, size);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint16_t Base::getport() const {
  __ENTER_FUNCTION
    uint16_t result = 0;
    result = port_;
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint64_t Base::getu64host() const {
  __ENTER_FUNCTION
    uint64_t result = 0;
    if (0 == strlen(host_)) {
      result = vnet_sokectbase_getu64host(NULL);
    }
    else {
      result = vnet_socketbase_getu64host(static_cast<const char*>(host_));
    }
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool Base::isvalid() const {
  __ENTER_FUNCTION
    bool result = true;
    result = socketid_ != SOCKET_INVALID;
    return result;
  __LEAVE_FUNCTION
    return false;
}

int32_t Base::getid() const {
  __ENTER_FUNCTION
    int32_t result = SOCKET_INVALID;
    result = socketid_;
    return result;
  __LEAVE_FUNCTION
    return SOCKET_INVALID;
}

} //namespace socket

} //namespace pap_common_net
