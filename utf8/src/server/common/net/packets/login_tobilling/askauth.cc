#include "server/common/net/packets/login_tobilling/askauth.h"
#include "server/common/game/define/all.h"

namespace pap_server_common_net {

namespace packets {

namespace login_tobilling {


AskAuth::AskAuth() {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::size;
    memset(account_, '\0', sizeof(account_));
    memset(password_, '\0', sizeof(password_));
    memset(ip_, '\0', sizeof(ip_));
    uint32_t i;
    for (i = 0; i < mibao::kUnitNumber; ++i) {
      memset(all_mibao_key[i], '\0', sizeof(all_mibao_key[i]));
      memset(all_mibao_value[i], '\0', sizeof(all_mibao_value[i]));
    }
    memset(macaddress_, '\0', sizeof(macaddress_));
  __LEAVE_FUNCTION
}

bool AskAuth::read(pap_common_net::socket::InputStream& inputstream) {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::size;
    inputstream.read(account_, sizeof(account_) - 1);
    inputstream.read(password_, sizeof(password_) - 1);
    inputstream.read(reinterpret_cast<char*>(&playerid_), sizeof(playerid_));
    inputstream.read(ip_, sizeof(ip_) - 1);
    uint8_t i;
    for (i = 0; i < mibao::kUnitNumber; ++i) {
      inputstream.read(all_mibao_key[i], sizeof(all_mibao_key[i]) - 1);
    }
    for (i = 0; i < mibao::kUnitNumber; ++i) {
      inputstream.read(all_mibao_value[i], sizeof(all_mibao_value[i]) - 1);
    }
    inputstream.read(macaddress_, sizeof(macaddress_) - 1);
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool AskAuth::write(pap_common_net::socket::OutputStream& outputstream) const {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::size;
    outputstream.write(account_, sizeof(account_) - 1);
    outputstream.write(password_, sizeof(password_) - 1);
    outputstream.write((char*)&playerid_, sizeof(playerid_));
    outputstream.write(ip_, sizeof(ip_) - 1);
    uint8_t i;
    for (i = 0; i < mibao::kUnitNumber; ++i) {
      outputstream.write(all_mibao_key[i], sizeof(all_mibao_key[i]) - 1);
    }
    for (i = 0; i < mibao::kUnitNumber; ++i) {
      outputstream.write(all_mibao_value[i], sizeof(all_mibao_value[i]) - 1);
    }
    outputstream.write(macaddress_, sizeof(macaddress_) - 1);
    return true;
  __LEAVE_FUNCTION
    return false;
}

uint32_t AskAuth::execute(connection::Base* connection) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = AskAuthHandler::execute(this, connection);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint16_t AskAuth::getid() const {
  using namespace pap_server_common_game::define;
  return id::packet::login_tobilling::kAskAuth;
}

uint32_t AskAuth::getsize() const {
  using namespace pap_common_game::define::size;
  uint32_t result = sizeof(account_) - 1 +
                    sizeof(password_) - 1 +
                    sizeof(ip_) - 1 +
                    sizeof(all_mibao_key) - mibao::kUnitNumber * 1 +
                    sizeof(all_mibao_value) - mibao::kUnitNumber * 1 +
                    sizeof(macaddress_) - 1;
  return result;
}

void AskAuth::getaccount(char* buffer, uint8_t length) const {
  __ENTER_FUNCTION
    snprintf(buffer, length, "%s", account_);
  __LEAVE_FUNCTION
}

void AskAuth::setaccount(const char* account) {
  __ENTER_FUNCTION
    Assert(account); //string copy if need format then use snprinf
    //snprintf(account_, sizeof(account_) - 1, "%s", account);
    strncpy(account_, account, sizeof(account_) - 1);
    account_[sizeof(account_)] = '\0';
  __LEAVE_FUNCTION
}

void AskAuth::getpassword(char* buffer, uint8_t length) const {
  __ENTER_FUNCTION
    snprintf(buffer, length, "%s", password_);
  __LEAVE_FUNCTION
}

void AskAuth::setpassword(const char* password) {
  __ENTER_FUNCTION
    Assert(password);
    //snprintf(password_, sizeof(password_) -  1, "%s", password);
    strncpy(password_, password, sizeof(password) - 1);
    password_[sizeof(password_)] = '\0';
  __LEAVE_FUNCTION
}

uint16_t AskAuth::get_playerid() const {
  return playerid_;
}

void AskAuth::set_playerid(uint16_t id) {
  playerid_ = id;
}

void AskAuth::getip(char* buffer, uint8_t length) const {
  __ENTER_FUNCTION  
    snprintf(buffer, length, "%s", ip_);
  __LEAVE_FUNCTION
}

void AskAuth::setip(const char* ip) {
  __ENTER_FUNCTION
    Assert(ip);
    //snprintf(ip_, sizeof(ip_) - 1, "%s", ip);
    strncpy(ip_, ip, sizeof(ip_));
    ip_[sizeof(ip_)] = '\0';
  __LEAVE_FUNCTION
}

void AskAuth::get_macaddress(char* buffer, uint8_t length) const {
  __ENTER_FUNCTION
    snprintf(buffer, length, "%s", macaddress_);
  __LEAVE_FUNCTION
}

void AskAuth::set_macaddress(const char* address) {
  __ENTER_FUNCTION
    Assert(address);
    //snprintf(macaddress_, sizeof(macaddress_) - 1, "%s", address);
    strncpy(macaddress_, address, sizeof(macaddress_) - 1);
    macaddress_[sizeof(macaddress_)] = '\0';
  __LEAVE_FUNCTION
}

void AskAuth::get_mibao_key(int32_t index, 
                            char* buffer, 
                            uint8_t length) const {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::size;
    if (index < 0 || index >= mibao::kUnitNumber) {
      return;
    }
    snprintf(buffer, length, "%s", all_mibao_key[index]);
  __LEAVE_FUNCTION
}

void AskAuth::set_mibao_key(int32_t index, int32_t row, int32_t column) {
  __ENTER_FUNCTION
    USE_PARAM(row);
    USE_PARAM(column);
    using namespace pap_common_game::define::size;
    if (index < 0 || index >= mibao::kUnitNumber) return;
    //key为"00"，通知Billing玩家没有选择“使用密保卡”的选项
    snprintf(all_mibao_key[index], 
             sizeof(all_mibao_key[index]) - 1, 
             "%d%d", 
             0, 
             0);
  __LEAVE_FUNCTION
}

void AskAuth::get_mibao_value(int32_t index, 
                              char* buffer, 
                              uint8_t length) const {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::size;
    if (index < 0 || index >= mibao::kUnitNumber) return;
    snprintf(buffer, length, "%s", all_mibao_value_[index]);
  __LEAVE_FUNCTION
}

void AskAuth::set_mibao_value(int32_t index, const char* value) {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::size;
    if (index < 0 || index >= mibao::kUnitNumber) return;
    strncpy(all_mibao_value_[index], 
            value, 
            sizeof(all_mibao_value_[index]) - 1);
    all_mibao_value_[index][sizeof(all_mibao_value_[index])] = '\0';
  __LEAVE_FUNCTION
}

pap_common_net::packet::Base* AskAuthFactory::createpacket() {
  __ENTER_FUNCTION
    return new AskAuth();
  __LEAVE_FUNCTION
    return NULL;
}

uint16_t AskAuthFactory::get_packetid() const {
  using namespace pap_server_common_game::define;
  return id::packet::login_tobilling::kAskAuth;
}

uint32_t AskAuthFactory::get_packet_maxsize() const {
  using namespace pap_common_game::define::size;
  uint32_t result = sizeof(char) * ACCOUNTLENGTH_MAX +
                    sizeof(char) * MD5SIZE_MAX +
                    sizeof(char) * IP_SIZE +
                    sizeof(char) * mibao::kUnitNumber * mibao::kUnitNameLength +
                    sizeof(char) * mibao::kUnitNumber * mibao::kUnitValueLength +
                    sizeof(char) * MD5SIZE_MAX;
  return result;
}

} //namespace login_tobilling

} //namespace packets

} //namespace pap_server_common_net
