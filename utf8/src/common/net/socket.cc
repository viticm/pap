#include "common/net/socket.h"
#include "common/lib/vnet/vnet.hpp"

namespace pap_common_net {

Socket::Socket() {
  __ENTER_FUNCTION
    socketid_ = SOCKET_INVALID;
    memset(host_, '\0', sizeof(host_));
    port_ = 0;
  __LEAVE_FUNCTION
}

Socket::Socket(const char* host, uint16_t port) {
  __ENTER_FUNCTION
    memset(host_, '\0', sizeof(host_));
    snprintf(host_, sizeof(host_) - 1, "%s", host);
    port_ = port;
    create();
  __LEAVE_FUNCTION
}

Socket::~Socket() {
  __ENTER_FUNCTION
    close()
  __LEAVE_FUNCTION
}

bool Socket::create() {
  __ENTER_FUNCTION
    bool result = true;
    socketid_ = vnet_socketbase_create();
    result = isvalid();
    return result;
  __LEAVE_FUNCTION
    return false;
}

void Socket::close() {
  __ENTER_FUNCTION
    if (isvalid() && !iserror())
      vnet_socketbase_close(socketid_);
    socketid_ = SOCKET_INVALID;
    memset(host_, '\0', sizeof(host_));
    port_ = 0;
  __LEAVE_FUNCTION
}

bool Socket::connect() {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_connect(socketid_, host_, port_);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Socket::connect(const char* host, uint16_t port) {
  __ENTER_FUNCTION
    bool result = true;
    snprintf(host_, sizeof(host_) - 1, "%s", host);
    port_ = port;
    result = connect();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Socket::reconnect(const char* host, uint16_t port) {
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

uint32_t Socket::send(const void* buffer, uint32_t length, uint32_t flag) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_send(socketid_, buffer, length, flag);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint32_t Socket::receive(void* buffer, uint32_t length, uint32_t flag) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_receive(socketid_, buffer, length, flag);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint32_t Socket::available() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_available(socketid_);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

int32_t Socket::accept(uint16_t port) {
  __ENTER_FUNCTION
    int32_t result = SOCKET_ERROR;
    result = vnet_socketbase_accept(socketid_, port);
    return result;
  __LEAVE_FUNCTION
    return SOCKET_ERROR;
}

int32_t Socket::fastaccept() {
  __ENTER_FUNCTION
    int32_t result = SOCKET_ERROR;
    result = vnet_socketbase_fastaccept(socketid_);
    return result;
  __LEAVE_FUNCTION
    return SOCKET_ERROR;
}

bool Socket::bind() {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_bind(socketid_, port_);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Socket::bind(uint16_t port) {
  __ENTER_FUNCTION
    bool result = true;
    port_ = port;
    result = vnet_socketbase_bind(socketid_, port_);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Socket::listen(uint32_t backlog) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_listen(socketid_, backlog);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Socket::getlinger() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_getlinger(socketid_);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool Socket::setlinger(uint32_t lingertime) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_setlinger(socketid_, lingertime);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Socket::is_reuseaddr() const {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_is_reuseaddr(socketid_);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Socket::set_reuseaddr(bool on) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_set_reuseaddr(socketid_, on);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Socket::getlast_errorcode() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_getlast_errorcode();
    return result;
  __LEAVE_FUNCTION
    return 0;
}

void Socket::getlast_errormessage(char* buffer, uint16_t length) const {
  __ENTER_FUNCTION
    vnet_socketbase_getlast_errormessage(buffer, length);
  __LEAVE_FUNCTION
}

bool Socket::iserror() const {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_iserror(socketid_);
    return result;
  __LEAVE_FUNCTION
    return true;
}

bool Socket::is_nonblocking() const {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_is_nonblocking(socketid_);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Socket::set_nonblocking(bool on) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_set_nonblocking(on);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Socket::getreceive_buffersize() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_getreceive_buffersize(socketid_);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool Socket::setreceive_buffersize(uint32_t size) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_setreceive_buffersize(socketid_, size);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Socket::getsend_buffersize() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = vnet_socketbase_getsend_buffersize(socketid_);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool Socket::setsend_buffersize(uint32_t size) {
  __ENTER_FUNCTION
    bool result = true;
    result = vnet_socketbase_setsend_buffersize(socketid_, size);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint16_t Socket::getport() const {
  __ENTER_FUNCTION
    uint16_t result = 0;
    result = port_;
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint64_t Socket::getu64host() const {
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

bool Socket::isvalid() const {
  __ENTER_FUNCTION
    bool result = true;
    result = socketid_ != SOCKET_INVALID;
    return result;
  __LEAVE_FUNCTION
    return false;
}

int32_t Socket::getid() const {
  __ENTER_FUNCTION
    int32_t result = SOCKET_INVALID;
    result = socketid_;
    return result;
  __LEAVE_FUNCTION
    return SOCKET_INVALID;
}

} //namespace pap_common_net
