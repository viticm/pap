#include "common/net/packets/client_toserver/heartbeat.h"
#include "server/common/net/connection/base.h"
namespace pap_common_net {

namespace packets {

namespace client_toserver {

HeartBeat::HeartBeat() {
  __ENTER_FUNCTION
  __LEAVE_FUNCTION
}

bool HeartBeat::read(socket::InputStream& inputstream) {
  __ENTER_FUNCTION
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool HeartBeat::write(socket::OutputStream& outputstream) const {
  __ENTER_FUNCTION
    return true;
  __LEAVE_FUNCTION
    return false;
}

uint32_t HeartBeat::execute(pap_server_common_net::connection::Base* connection) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = HeartBeatHandler::execute(this, connection);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint16_t HeartBeat::getid() const {
  using namespace pap_common_game::define;
  return id::packet::client_toserver::kHeartBeat;
}

uint32_t HeartBeat::getsize() const {
  uint32_t result = 0;
  return result;
}


packet::Base* HeartBeatFactory::createpacket() {
  __ENTER_FUNCTION
    return new HeartBeat();
  __LEAVE_FUNCTION
    return NULL;
}

uint16_t HeartBeatFactory::get_packetid() const {
  using namespace pap_common_game::define;
  return id::packet::client_toserver::kHeartBeat;
}

uint32_t HeartBeatFactory::get_packet_maxsize() const {
  uint32_t result = 0;
  return result;
}

} //namespace client_toserver

} //namespace packets

} //namespace pap_common_net