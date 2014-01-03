#ifndef PAP_COMMON_NET_PACKETS_BILLING_TOLOGIN_RESULTAUTH_H_
#define PAP_COMMON_NET_PACKETS_BILLING_TOLOGIN_RESULTAUTH_H_

#include "server/common/net/config.h"
#include "server/common/net/connection.h"
#include "common/net/packet.h"
#include "common/net/packetfactory.h"
#include "common/game/define.h"

namespace pap_server_common_net {

namespace packets {

namespace billing_tologin {

class ResultAuth : public pap_common_net::Packet {

 public:
   ResultAuth();
   virtual ~ResultAuth() {};

 public:
   

};

}; //namespace billing_tologin

}; //namespace packets

}; //namespace pap_server_common_net

#endif //PAP_COMMON_NET_PACKETS_BILLING_TOLOGIN_RESULTAUTH_H_
