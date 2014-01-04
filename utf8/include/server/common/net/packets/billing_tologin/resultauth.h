#ifndef PAP_COMMON_NET_PACKETS_BILLING_TOLOGIN_RESULTAUTH_H_
#define PAP_COMMON_NET_PACKETS_BILLING_TOLOGIN_RESULTAUTH_H_

#include "server/common/net/config.h"
#include "server/common/net/connection.h"
#include "common/net/packet.h"
#include "common/net/packetfactory.h"
#include "common/game/define/all.h"

namespace pap_server_common_net {

namespace packets {

namespace billing_tologin {

class ResultAuth : public pap_common_net::Packet {

 public:
   ResultAuth();
   virtual ~ResultAuth() {};

 public:  
   virtual bool read(pap_common_net::SocketInputStream& inputstream);
   virtual bool write(pap_common_net::SocketOutputStream& outputstream) const;
   virtual uint32_t execute(Connection* connection);
   virtual uint16_t get_packetid() const;
   virtual uint32_t get_packetsize() const;

 public:
   void getaccount(char* buffer, uint8_t length);
   void setaccount(const char* account);
   pap_common_game::define::result::login::_enum getresult() const;
   void set_result(pap_common_game::define::result::login::_enum result);
   uint16_t get_playerid() const;
   void set_playerid(uint16_t id);
   uint32_t getguid() const;
   void setguid(uint32_t id);
   void get_servername(char* buffer, uint16_t length) const;
   void set_servername(const char* servername);
   void get_serverip(char* buffer, uint16_t length) const;
   void set_serverip(const char* serverip);
   char get_fatiguesign() const;
   void set_fatiguesign(char sign);
   uint32_t get_total_onlinetime() const;
   void set_total_onlinetime(uint32_t time);
   char get_phonebind() const;
   void set_phonebind(char sign);
   char get_mibaobind() const;
   void set_mibaobind(char sign);
   char get_ipbind() const;
   void set_ipbind(char sign);
   char get_realname_bind() const;
   void set_realname_bind(char sign);
   char get_macbind() const;
   void set_macbind(char sign);
   char get_inputname_bind() const;
   void set_inputname_bind(char sign);
 
 private:
   char account_[ACCOUNTLENGTH_MAX + 1];
   pap_common_game::define::result::login::_enum result_;
   uint16_t playerid_;
   uint32_t playerguid_;
   char servername_[SERVRENAME_MAX + 1]; //服务器名称
   char serverip_[IP_SIZE + 1]; //服务器IP
   char isfatigue_; //是否加入防沉迷
   uint32_t total_onlinetime_; //用户累计在线时间
   char isphone_bind_; //是否手机绑定
   char isip_bind_; //是否IP绑定
   char ismibao_bind_; //是否密保绑定
   char ismac_bind_; //是否密保绑定
   char is_realname_bind_; //是否实名绑定
   char is_inputname_bind_; //是否输入实名

};

class ResultAuthFactory : public pap_common_net::PacketFactory {

 public:
   pap_common_net::Packet* createpacket();
   uint16_t get_packetid();
   uint32_t get_packet_maxsize();

};

class ResultAuthHandler {

 public:
   static uint32_t execute(ResultAuth* packet, Connection* connection);

}

}; //namespace billing_tologin

}; //namespace packets

}; //namespace pap_server_common_net

#endif //PAP_COMMON_NET_PACKETS_BILLING_TOLOGIN_RESULTAUTH_H_
