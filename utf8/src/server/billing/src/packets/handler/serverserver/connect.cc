#include "server/common/net/packets/serverserver/connect.h"
#include "server/billing/connection/server.h"
#include "server/common/base/log.h"

namespace pap_server_common_net {

namespace packets {

namespace serverserver { 

uint32_t ConnectHandler::execute(Connect* packet, 
                                 connection::Base* connection) {
  __ENTER_FUNCTION
    g_log->fast_save_log(kBillingLogFile, 
                         "ConnectHandler::execute(...) serverid: %d ...success", 
                         packet->get_serverid());
    return kPacketExecuteStatusContinue;
  __LEAVE_FUNCTION
    return kPacketExecuteStatusError;
}

} //namespace serverserver

} //namespace packets

} //namespace pap_server_common_net
