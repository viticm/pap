#include "common/net/packets/client_toserver/heartbeat.h"

namespace pap_common_net {

namespace packets {

namespace client_toserver { 

uint32_t HeartBeatHandler::execute(HeartBeat* packet, 
                                 pap_server_common_net::connection::Base* connection) {
  __ENTER_FUNCTION
    return kPacketExecuteStatusContinue;
  __LEAVE_FUNCTION
    return kPacketExecuteStatusError;
}

} //namespace client_toserver

} //namespace packets

} //namespace pap_server_common_net
