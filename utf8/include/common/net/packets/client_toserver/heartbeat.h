/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id heartbeat.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-04-08 15:58:59
 * @uses packet HeartBeat class
 */
#ifndef PAP_COMMON_NET_PACKETS_CLIENT_TOSERVER_HEARTBEAT_H_
#define PAP_COMMON_NET_PACKETS_CLIENT_TOSERVER_HEARTBEAT_H_

#include "common/net/config.h"
#include "common/net/connection/base.h"
#include "common/net/packet/base.h"
#include "common/net/packet/factory.h"
#include "common/game/define/all.h"

namespace pap_server_common_net {

class Connection;

}; //namespace pap_server_common_net
namespace pap_common_net {

namespace packets {

namespace client_toserver {

class HeartBeat : public packet::Base {

 public:
   HeartBeat();
   virtual ~HeartBeat() {};

 public:  
   virtual bool read(socket::InputStream& inputstream);
   virtual bool write(socket::OutputStream& outputstream) const;
   virtual uint32_t execute(connection::Base* connection);
   virtual uint16_t getid() const;
   virtual uint32_t getsize() const;
   
 public: 

 private:

};

class HeartBeatFactory : public packet::Factory {

 public:
   packet::Base* createpacket();
   uint16_t get_packetid() const;
   uint32_t get_packet_maxsize() const;

};

class HeartBeatHandler {

 public:
   static uint32_t execute(HeartBeat* packet, 
                           pap_server_common_net::connection::Base* connection);

};

}; //namespace client_toserver

}; //namespace packets

}; //namespace pap_common_net

#endif //PAP_COMMON_NET_PACKETS_CLIENT_TOSERVER_HEARTBEAT_H_
