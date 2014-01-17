#include "server/common/net/socket.h"
#include "common/lib/vnet/vnet.hpp"

namespace pap_server_common_net {

Socket::Socket(uint16_t port, uint32_t backlog) {
  __ENTER_FUNCTION
    bool result = false;
    socket_ = new pap_common_net::socket::Base();
    if (NULL == socket_) { //memory not enough
      ERRORPRINTF("pap_server_common_net::Socket::Socket"
                  "new pap_common_net::socket::Base() failed");
      throw 1;
    }
    result = socket_->create();
    if (false == result) {
      ERRORPRINTF("pap_server_common_net::Socket::Socket"
                  " socket_->create() failed"); 
      throw 1;
    }
    result = socket_->set_reuseaddr();
    if (false == result) {
      ERRORPRINTF("pap_server_common_net::Socket::Socket"
                  " socket_->set_reuseaddr() failed");
      throw 1;
    }
    result = socket_->bind(port);
    if (false == result) {
      ERRORPRINTF("pap_server_common_net::Socket::Socket"
                  " socket_->bind(%d) failed", 
                  port);
      throw 1;
    }
    result = socket_->listen(backlog);
    if (false == result) {
      ERRORPRINTF("pap_server_common_net::Socket::Socket"
                  " socket_->listen(%d) failed",
                  backlog);
      throw 1;
    }
  __LEAVE_FUNCTION
}

Socket::~Socket() {
  __ENTER_FUNCTION
    if (socket_ != NULL) {
      socket_->close();
      SAFE_DELETE(socket_);
    }
  __LEAVE_FUNCTION
}

void Socket::close() {
  if (socket_ != NULL) socket_->close();
}

bool Socket::accept(pap_common_net::socket::Base* socket) {
  __ENTER_FUNCTION
    if (NULL == socket) return false;
    socket->close();
    if (0 == socket->port_) {
      socket->socketid_ = socket_->fastaccept();
    }
    else {
      socket->socketid_ = socket_->accept(socket->port_);
    }
    if (SOCKET_INVALID == socket->socketid_) return false;
    return true;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Socket::getlinger() const {
  __ENTER_FUNCTION
    uint32_t linger;
    linger = socket_->getlinger();
    return linger;
  __LEAVE_FUNCTION
    return 0;
}

bool Socket::setlinger(uint32_t lingertime) {
  __ENTER_FUNCTION
    bool result = false;
    result = socket_->setlinger(lingertime);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Socket::is_nonblocking() const {
  __ENTER_FUNCTION
    bool result = false;
    result = socket_->is_nonblocking();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Socket::set_nonblocking(bool on) {
  __ENTER_FUNCTION
    return socket_->set_nonblocking(on);
  __LEAVE_FUNCTION
    return false;
}

uint32_t Socket::getreceive_buffersize() const {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = socket_->getreceive_buffersize();
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool Socket::setreceive_buffersize(uint32_t size) {
  __ENTER_FUNCTION
    bool result = false;
    result = socket_->setreceive_buffersize(size);
    return result;
  __LEAVE_FUNCTION
    return false;
}

int32_t Socket::getid() const {
  __ENTER_FUNCTION
    int32_t result = SOCKET_INVALID;
    result = socket_->getid();
    return result;
  __LEAVE_FUNCTION
    return SOCKET_INVALID;
}

} //namespace pap_server_common_net
