#ifndef PAP_COMMON_NET_PACKETS_LOGIN_TOBILLING_ASKAUTH_H_
#define PAP_COMMON_NET_PACKETS_LOGIN_TOBILLING_ASKAUTH_H_

#include "server/common/net/config.h"
#include "server/common/net/connection.h"
#include "common/net/packet.h"
#include "common/net/packetfactory.h"
#include "common/game/define/all.h"

namespace pap_server_common_net {

namespace packets {

namespace login_tobilling {

class AskAuth : public pap_common_net::Packet {
 
 public:
   AskAuth();
   virtual ~AskAuth(){};

 public:
   virtual bool read(pap_common_net::SocketInputStream& inputstream);
   virtual bool write(pap_common_net::SocketOutputStream& outputstream) const;
   virtual uint32_t execute(Connection* connection);
   virtual uint16_t get_packetid() const;
   virtual uint32_t get_packetsize() const;

 public:
   void getaccount(char* buffer, uint8_t length) const;
   void setaccount(const char* account);
   void getpassword(char* buffer, uint8_t length) const;
   void setpassword(const char* password);
   uint16_t get_playerid() const;
   void set_playerid(uint16_t id);
   void getip(char* buffer, uint8_t length) const;
   void setip(const char* ip);
   void get_mibao_key(int32_t index, char* buffer, uint8_t length) const;
   void set_mibao_key(int32_t index, int32_t row, int32_t column);
   void clear_mibao_key(int32_t index);
   void set_mibao_value(int32_t index, const char* value);
   void get_mibao_value(int32_t index, char* buffer, uint8_t length) const;
   void get_macaddress(char* buffer, uint8_t length) const;
   void set_macaddress(const char* address);

 private:
   char account_[ACCOUNTLENGTH_MAX + 1];
   char password_[MD5SIZE_MAX + 1];
   char ip_[IP_SIZE + 1];
   uint16_t playerid_;
   //为了不混乱的代价似乎有点大
   char all_mibao_key[pap_common_game::define::size::mibao::kUnitNumber]
     [pap_common_game::define::size::mibao::kUnitNameLength + 1];
   char all_mibao_value[pap_common_game::define::size::mibao::kUnitNumber]
     [pap_common_game::define::size::mibao::kUnitValueLength + 1];
   char macaddress_[MD5SIZE_MAX + 1];

};

class AskAuthFactory : public pap_common_net::PacketFactory {

 public:
   pap_common_net::Packet* createpacket();
   uint16_t get_packetid() const;
   uint32_t get_packet_maxsize() const;

};

class AskAuthHandler {

 public:
   static uint32_t execute(AskAuth* packet, Connection* connection);

};

}; //namespace login_tobilling

}; //namespace packets

}; //namespace pap_server_common_net

#endif //PAP_COMMON_NET_PACKETS_LOGIN_TOBILLING_ASKAUTH_H_
