/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id connect.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-04-08 15:58:59
 * @uses packet Connect class
 */
#ifndef PAP_SERVER_COMMON_NET_PACKETS_SERVERSERVER_CONNECT_H_
#define PAP_SERVER_COMMON_NET_PACKETS_SERVERSERVER_CONNECT_H_

#include "server/common/net/config.h"
#include "server/common/net/connection/base.h"
#include "common/net/packet/base.h"
#include "common/net/packet/factory.h"
#include "server/common/game/define/all.h"


namespace pap_server_common_net {

namespace packets {

namespace serverserver {

class Connect : public pap_common_net::packet::Base {

 public:
   Connect();
   virtual ~Connect() {};

 public:  
   virtual bool read(pap_common_net::socket::InputStream& inputstream);
   virtual bool write(pap_common_net::socket::OutputStream& outputstream) const;
   virtual uint32_t execute(connection::Base* connection);
   virtual uint16_t getid() const;
   virtual uint32_t getsize() const;
   
 public: 
   int16_t get_serverid();
   void set_serverid(int16_t serverid);
   int16_t get_worldid();
   void set_worldid(int16_t worldid);
   int16_t get_zoneid();
   void set_zoneid(int16_t zoneid);

 private:
   int16_t serverid_; //服务器ID
   int16_t worldid_; //世界ID
   int16_t zoneid_; //区域ID

};

class ConnectFactory : public pap_common_net::packet::Factory {

 public:
   pap_common_net::packet::Base* createpacket();
   uint16_t get_packetid() const;
   uint32_t get_packet_maxsize() const;

};

class ConnectHandler {

 public:
   static uint32_t execute(Connect* packet, 
                           connection::Base* connection);

};

}; //namespace serverserver

}; //namespace packets

}; //namespace pap_server_common_net

#endif //PAP_SERVER_COMMON_NET_PACKETS_SERVERSERVER_CONNECT_H_