/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id resultauth.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-01-07 23:56:12
 * @uses packet ResultAuth class
 */
#ifndef PAP_SERVER_COMMON_NET_PACKETS_BILLING_TOLOGIN_RESULTAUTH_H_
#define PAP_SERVER_COMMON_NET_PACKETS_BILLING_TOLOGIN_RESULTAUTH_H_

#include "server/common/net/config.h"
#include "server/common/net/connection/base.h"
#include "common/net/packet/base.h"
#include "common/net/packet/factory.h"
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
   virtual uint32_t execute(connection::Base* connection);
   virtual uint16_t get_packetid() const;
   virtual uint32_t get_packetsize() const;
   
 public: 
   void get_account(char* buffer, uint16_t length);
   void set_account(const char* account);
   pap_common_game::define::result::login::_enum get_result();
   void set_result(pap_common_game::define::result::login::_enum result);
   uint16_t get_playerid();
   void set_playerid(uint16_t playerid);
   uint32_t get_playerguid();
   void set_playerguid(uint32_t playerguid);
   void get_servername(char* buffer, uint16_t length);
   void set_servername(const char* servername);
   char get_isfatigue();
   void set_isfatigue(char isfatigue);
   uint32_t get_total_onlinetime();
   void set_total_onlinetime(uint32_t total_onlinetime);
   char get_isphone_bind();
   void set_isphone_bind(char isphone_bind);
   char get_isip_bind();
   void set_isip_bind(char isip_bind);
   char get_ismibao_bind();
   void set_ismibao_bind(char ismibao_bind);
   char get_ismac_bind();
   void set_ismac_bind(char ismac_bind);
   char get_is_realname_bind();
   void set_is_realname_bind(char is_realname_bind);
   char get_is_inputname_bind();
   void set_is_inputname_bind(char is_inputname_bind);

 private:
   char account_[ACCOUNTLENGTH_MAX + 1]; //账号名
   pap_common_game::define::result::login::_enum result_; //验证结果
   uint16_t playerid_; //玩家ID
   uint32_t playerguid_; //玩家GUID
   char servername_[SERVRENAME_MAX + 1]; //服务器名称
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
   uint16_t get_packetid() const;
   uint32_t get_packet_maxsize() const;

};

class ResultAuthHandler {

 public:
   static uint32_t execute(ResultAuth* packet, connection::Base* connection);

};

}; //namespace billing_tologin

}; //namespace packets

}; //namespace pap_server_common_net

#endif //PAP_SERVER_COMMON_NET_PACKETS_BILLING_TOLOGIN_RESULTAUTH_H_
