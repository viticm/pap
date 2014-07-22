/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id connect.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-04-14 14:38:10
 * @uses packet Connect class
 */
#ifndef PAP_COMMON_NET_PACKETS_CLIENT_TOLOGIN_CONNECT_H_
#define PAP_COMMON_NET_PACKETS_CLIENT_TOLOGIN_CONNECT_H_

#include "common/net/config.h"
#include "server/common//net/connection/base.h"
#include "common/net/packet/base.h"
#include "common/net/packet/factory.h"
#include "common/game/define/all.h"

namespace pap_server_common_net {

class Connection;

}; //namespace pap_server_common_net
namespace pap_common_net {

namespace packets {

namespace client_tologin {

class Connect : public packet::Base {

 public:
   Connect();
   virtual ~Connect() {};

 public:  
   virtual bool read(socket::InputStream& inputstream);
   virtual bool write(socket::OutputStream& outputstream) const;
   virtual uint32_t execute(pap_server_common_net::connection::Base* connection);
   virtual uint16_t getid() const;
   virtual uint32_t getsize() const;
   
 public: 
   uint8_t get_mibao();
   void set_mibao(uint8_t mibao);
   netprovider_enum get_netprovider();
   void set_netprovider(netprovider_enum netprovider);

 private:
   uint8_t mibao_; //密保
   netprovider_enum netprovider_; //供应商ID

};

class ConnectFactory : public packet::Factory {

 public:
   packet::Base* createpacket();
   uint16_t get_packetid() const;
   uint32_t get_packet_maxsize() const;

};

class ConnectHandler {

 public:
   static uint32_t execute(Connect* packet, 
                           pap_server_common_net::connection::Base* connection);

};

}; //namespace client_tologin

}; //namespace packets

}; //namespace pap_common_net

#endif //PAP_COMMON_NET_PACKETS_CLIENT_TOLOGIN_CONNECT_H_