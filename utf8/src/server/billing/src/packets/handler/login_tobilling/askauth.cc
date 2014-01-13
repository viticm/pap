#include "server/common/net/packets/login_tobilling/askauth.h"
#include "server/common/net/packets/billing_tologin/resultauth.h"
#include "server/billing/connection/server.h"

namespace pap_server_common_net {

namespace packets {

namespace login_tobilling { 

uint32_t AskAuthHandler::execute(AskAuth* packet, 
                                 connection::Base* connection) {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::result;
    Assert(packet);
    Assert(connection);
    //return success
    billing_tologin::ResultAuth message;
    message.set_account(packet->get_account);
    message.set_result(login::kSuccess);
    message.set_playerid(packet->get_playerid());
    message.set_isfatigue(0);
    message.set_total_onlinetime(0);
    message.set_isphone_bind(0);
    message.set_isip_bind(0);
    message.set_ismibao_bind(0);
    message.set_ismac_bind(0);
    message.set_is_realname_bind(0);
    message.set_is_inputname_bind(0);
    connection::Server* serverconnection = NULL;
    serverconnection = dynamic_cast<connection::Server*>(connection);
    Assert(serverconnection);
    serverconnection->sendpacket(&message);
    return kPacketExecuteStatusContinue;
  __LEAVE_FUNCTION
    return kPacketExecuteStatusError;
}

} //namespace billing_tologin

} //namespace packets

} //namespace pap_server_common_net
