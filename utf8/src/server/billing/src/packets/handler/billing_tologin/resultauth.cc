#include "server/common/net/packets/billing_tologin/resultauth.h"

namespace pap_server_common_net {

namespace packets {

namespace billing_tologin { 

uint32_t ResultAuthHandler::execute(ResultAuth* packet, 
                                    connection::Base* connection) {
  __ENTER_FUNCTION
    return kPacketExecuteStatusContinue;
  __LEAVE_FUNCTION
    return kPacketExecuteStatusError;
}

} //namespace billing_tologin

} //namespace packets

} //namespace pap_server_common_net
