/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id asklogin.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-04-14 14:53:21
 * @uses packet AskLogin class
 */
#ifndef PAP_COMMON_NET_PACKETS_CLIENT_TOLOGIN_ASKLOGIN_H_
#define PAP_COMMON_NET_PACKETS_CLIENT_TOLOGIN_ASKLOGIN_H_

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

namespace client_tologin {

class AskLogin : public packet::Base {

 public:
   AskLogin();
   virtual ~AskLogin() {};

 public:  
   virtual bool read(socket::InputStream& inputstream);
   virtual bool write(socket::OutputStream& outputstream) const;
   virtual uint32_t execute(connection::Base* connection);
   virtual uint16_t getid() const;
   virtual uint32_t getsize() const;
   
 public: 
   void get_account(char* buffer, uint16_t length);
   void set_account(const char* account);
   void get_password(char* buffer, uint16_t length);
   void set_password(const char* password);
   uint32_t get_version();
   void set_version(uint32_t version);
   void get_all_mibao_value(int32_t index, char* buffer, uint16_t length);
   void set_all_mibao_value(int32_t index, const char* value);
   void get_mac_address(char* buffer, uint16_t length);
   void set_mac_address(const char* mac_address);

 private:
   char account_[ACCOUNTLENGTH_MAX + 1]; //账号名
   char password_[MD5SIZE_MAX + 1]; //密码
   uint32_t version_; //客户端版本
   char all_mibao_value_[pap_common_game::define::size::mibao::kUnitNumber]
     [pap_common_game::define::size::mibao::kUnitValueLength + 1]; //密保值
   char mac_address_[MD5SIZE_MAX + 1]; //MAC地址

};

class AskLoginFactory : public packet::Factory {

 public:
   packet::Base* createpacket();
   uint16_t get_packetid() const;
   uint32_t get_packet_maxsize() const;

};

class AskLoginHandler {

 public:
   static uint32_t execute(AskLogin* packet, 
                           pap_server_common_net::connection::Base* connection);

};

}; //namespace client_tologin

}; //namespace packets

}; //namespace pap_common_net

#endif //PAP_COMMON_NET_PACKETS_CLIENT_TOLOGIN_ASKLOGIN_H_
