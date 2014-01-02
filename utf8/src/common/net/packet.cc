#include "common/net/packet.h"

namespace pap_common_net {

Packet::Packet() {
  //do nothing
}

Packet::~Packet() {
  //do nothing
}

int8_t Packet::getindex() const {
  return index_;
}

void Packet::setindex(int8_t index) {
  index_ = index;
}

uint8_t Packet::getstatus() const {
  return status_;
}

void Packet::setstatus(uint8_t status) {
  status_ = status;
}

} //namespace pap_common_net
