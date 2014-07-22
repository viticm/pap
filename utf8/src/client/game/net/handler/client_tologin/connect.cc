#include "common/net/packets/client_tologin/connect.h"

namespace pap_common_net {

namespace packets {

namespace client_tologin { 

  uint32_t ConnectHandler::execute(Connect* packet, 
    pap_server_common_net::connection::Base* connection) {
      __ENTER_FUNCTION
        return kPacketExecuteStatusContinue;
      __LEAVE_FUNCTION
        return kPacketExecuteStatusError;
  }

} //namespace client_tologin

} //namespace packets

} //namespace pap_server_common_net