#include "common/net/socket/inputstream.h"
#include "common/base/util.h"

namespace pap_common_net {

namespace socket {

InputStream::InputStream(Base* socket, 
                         uint32_t bufferlength,
                         uint32_t bufferlength_max) {
  __ENTER_FUNCTION
    socket_ = socket;
    //struct packet_t and endecode_param_t in c, so need init memory to it
    packet_ = (struct packet_t*)malloc(sizeof(struct packet_t));
    endecode_param_ = NULL;
    /**
    endecode_param_ = 
      (struct endecode_param_t*)malloc(sizeof(struct endecode_param_t));
    **/
    packet_->bufferlength = bufferlength;
    packet_->bufferlength_max = bufferlength_max;
    packet_->headlength = 0;
    packet_->taillength = 0;
    packet_->buffer = (char*)malloc(sizeof(char) * bufferlength);
  __LEAVE_FUNCTION
}

InputStream::~InputStream() {
  __ENTER_FUNCTION
    SAFE_FREE(packet_->buffer);
    SAFE_FREE(packet_);
    SAFE_FREE(endecode_param_);
  __LEAVE_FUNCTION
}

uint32_t InputStream::read(char* buffer, uint32_t length) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    if (endecode_param_ != NULL && (*endecode_param_).keysize > 0) {
      result = vnet_socket_inputstream_encoderead(packet_, 
                                                  buffer, 
                                                  length, 
                                                  endecode_param_);
    }
    else {
      result = vnet_socket_inputstream_read(packet_, buffer, length);
    }
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool InputStream::readpacket(packet::Base* packet) {
  __ENTER_FUNCTION
    bool result = false;
    result = skip(PACKET_HEADERSIZE);
    if (!result) return result;
    result = packet->read(*this);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool InputStream::peek(char* buffer, uint32_t length) {
  __ENTER_FUNCTION
    bool result = false;
    result = 1 == vnet_socket_inputstream_peek(*packet_, buffer, length);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool InputStream::skip(uint32_t length) {
  __ENTER_FUNCTION
    bool result = false;
    if (endecode_param_ != NULL && (*endecode_param_).keysize > 0) {
      result = 1 == vnet_socket_inputstream_encodeskip(packet_,
                                                  length,
                                                  endecode_param_);
    }
    else {
      result = 1 == vnet_socket_inputstream_skip(packet_, length);
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t InputStream::fill() {
  __ENTER_FUNCTION
    uint32_t result = 0;
    if (!socket_->isvalid()) return result;
    int32_t socketid = socket_->getid();
    result = vnet_socket_inputstream_fill(socketid, packet_);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

void InputStream::init() {
  __ENTER_FUNCTION
    vnet_socket_inputstream_packetinit(packet_);
  __LEAVE_FUNCTION
}

bool InputStream::resize(int32_t size) {
  __ENTER_FUNCTION
    bool result = false;
    result = 1 == vnet_socket_inputstream_resize(packet_, size);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t InputStream::reallength() {
  __ENTER_FUNCTION
    uint32_t length = 0;
    length = vnet_socket_inputstream_reallength(*packet_);
    return length;
  __LEAVE_FUNCTION
    return 0;
}

bool InputStream::isempty() {
  return (*packet_).headlength == (*packet_).taillength;
}

void InputStream::cleanup() {
  __ENTER_FUNCTION
    vnet_socket_inputstream_packetinit(packet_);
    endecode_param_ = NULL;
  __LEAVE_FUNCTION
}

void InputStream::setkey(unsigned char const* key) {
  __ENTER_FUNCTION
    SAFE_FREE(endecode_param_); //free last
    endecode_param_ = //malloc for it, construct not get memory 
      (struct endecode_param_t*)malloc(sizeof(struct endecode_param_t));
    endecode_param_->key = key;
    endecode_param_->keysize = strlen(reinterpret_cast<const char*>(key));
  __LEAVE_FUNCTION
}

int32_t InputStream::get_keylength() {
  int32_t result = (*endecode_param_).keysize;
  return result;
}

Base* InputStream::getsocket() {
  return socket_;
}

} //namespace socket

} //namespace pap_common_net
