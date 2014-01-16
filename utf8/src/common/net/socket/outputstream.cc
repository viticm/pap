#include "common/net/socket/outputstream.h"

namespace pap_common_net {

namespace socket {

OutputStream::OutputStream(Base* socket, 
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

OutputStream::~OutputStream() {
  __ENTER_FUNCTION
    SAFE_FREE(packet_->buffer);
    SAFE_FREE(packet_);
    SAFE_FREE(endecode_param_);
  __LEAVE_FUNCTION
}

uint32_t OutputStream::write(const char* buffer, uint32_t length) {
  __ENTER_FUNCTION
    uint32_t result = 0; 
    if (endecode_param_ != NULL && (*endecode_param_).keysize > 0) {
      result = vnet_socket_outputstream_encodewrite(packet_,
                                                    buffer,
                                                    length,
                                                    endecode_param_);
    }
    else {
      result = vnet_socket_outputstream_write(packet_, buffer, length);
    }
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool OutputStream::writepacket(const packet::Base* packet) {
  __ENTER_FUNCTION
    bool result = false;
    uint16_t packetid = packet->getid();
    uint32_t writecount = 0;
    uint32_t packetcheck; //index and size(if diffrent then have error)
    //write packetid
    writecount = write(reinterpret_cast<const char*>(&packetid), sizeof(packetid));
    uint32_t packetsize = packet->getsize();
    uint32_t packetindex = packet->getindex();
    SET_PACKETINDEX(packetcheck, packetindex);
    SET_PACKETLENGTH(packetcheck, packetsize);
    writecount = write(reinterpret_cast<const char*>(&packetcheck), 
                       sizeof(packetcheck));
    result = packet->write(*this);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t OutputStream::flush() {
  __ENTER_FUNCTION
    uint32_t result = 0;
    if (!socket_->isvalid()) return result;
    int32_t socketid = socket_->getid();
    result = vnet_socket_outputstream_flush(socketid, packet_);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

void OutputStream::init() {
  __ENTER_FUNCTION
    vnet_socket_outputstream_packetinit(packet_);
  __LEAVE_FUNCTION
}

bool OutputStream::resize(int32_t size) {
  __ENTER_FUNCTION
    bool result = false;
    result = 1 == vnet_socket_outputstream_resize(packet_, size);
    return result;
  __LEAVE_FUNCTION
    return false;
}

uint32_t OutputStream::reallength() {
  __ENTER_FUNCTION
    uint32_t length = 0;
    length = 1 == vnet_socket_outputstream_reallength(*packet_);
    return length;
  __LEAVE_FUNCTION
    return 0;
}

bool OutputStream::isempty() {
  return (*packet_).headlength == (*packet_).taillength;
}

void OutputStream::cleanup() {
  __ENTER_FUNCTION
    vnet_socket_outputstream_packetinit(packet_);
    endecode_param_ = NULL;
  __LEAVE_FUNCTION
}

void OutputStream::setkey(unsigned char const* key) {
  __ENTER_FUNCTION
    //when key use, the endecode_param_ just available
    SAFE_FREE(endecode_param_); //free last
    endecode_param_ = 
      (struct endecode_param_t*)malloc(sizeof(struct endecode_param_t));
    endecode_param_->key = key;
    endecode_param_->keysize = strlen(reinterpret_cast<const char*>(key));
  __LEAVE_FUNCTION
}

int32_t OutputStream::get_keylength() {
  int32_t result = (*endecode_param_).keysize;
  return result;
}

Base* OutputStream::getsocket() {
  return socket_;
}

} //namespace socket

} //namespace pap_common_net
