#include "common/net/packets/client_tologin/connect.h"
#include "server/common/net/connection/base.h"
namespace pap_common_net {

namespace packets {

namespace client_tologin {

Connect::Connect() {
  __ENTER_FUNCTION
  __LEAVE_FUNCTION
}

bool Connect::read(socket::InputStream& inputstream) {
  __ENTER_FUNCTION
    inputstream.read((char*)(&mibao_), sizeof(mibao_));
    inputstream.read((char*)(&netprovider_), sizeof(netprovider_));
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool Connect::write(socket::OutputStream& outputstream) const {
  __ENTER_FUNCTION
    outputstream.write((char*)(&mibao_), sizeof(mibao_));
    outputstream.write((char*)(&netprovider_), sizeof(netprovider_));
    return true;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Connect::execute(pap_server_common_net::connection::Base* connection) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = ConnectHandler::execute(this, connection);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint16_t Connect::getid() const {
  using namespace pap_common_game::define;
  return id::packet::client_tologin::kConnect;
}

uint32_t Connect::getsize() const {
  uint32_t result = sizeof(mibao_) +
                    sizeof(netprovider_);
  return result;
}

uint8_t Connect::get_mibao() {
  return mibao_;
}
void Connect::set_mibao(uint8_t mibao) {
  mibao_ = mibao;
}
netprovider_enum Connect::get_netprovider() {
  return netprovider_;
}
void Connect::set_netprovider(netprovider_enum netprovider) {
  netprovider_ = netprovider;
}

packet::Base* ConnectFactory::createpacket() {
  __ENTER_FUNCTION
    return new Connect();
  __LEAVE_FUNCTION
    return NULL;
}

uint16_t ConnectFactory::get_packetid() const {
  using namespace pap_common_game::define;
  return id::packet::client_tologin::kConnect;
}

uint32_t ConnectFactory::get_packet_maxsize() const {
  uint32_t result = sizeof(uint8_t) +
                    sizeof(netprovider_enum);
  return result;
}

} //namespace client_tologin

} //namespace packets

} //namespace pap_common_net