#include "common/net/packets/client_tologin/asklogin.h"
#include "server/common/net/connection.h"
namespace pap_common_net {

namespace packets {

namespace client_tologin {

AskLogin::AskLogin() {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::size;
    memset(account_, 0, sizeof(account_));
    memset(password_, 0, sizeof(password_));
    uint8_t i;
    for (i = 0; i < mibao::kUnitNumber; ++i) {
      memset(all_mibao_value_[i], 0, sizeof(all_mibao_value_[i]));
    }
    memset(mac_address_, 0, sizeof(mac_address_));
  __LEAVE_FUNCTION
}

bool AskLogin::read(socket::InputStream& inputstream) {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::size;
    inputstream.read(account_, sizeof(account_) - 1);
    inputstream.read(password_, sizeof(password_) - 1);
    inputstream.read((char*)(&version_), sizeof(version_));
    uint8_t i;
    for (i = 0; i < mibao::kUnitNumber; ++i) { 
      inputstream.read(all_mibao_value_[i], sizeof(all_mibao_value_[i]) - 1);
    }
    inputstream.read(mac_address_, sizeof(mac_address_) - 1);
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool AskLogin::write(socket::OutputStream& outputstream) const {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::size;
    outputstream.write(account_, sizeof(account_) - 1);
    outputstream.write(password_, sizeof(password_) - 1);
    outputstream.write((char*)(&version_), sizeof(version_));
    uint8_t i;
    for (i = 0; i < mibao::kUnitNumber; ++i) {
      outputstream.write(all_mibao_value_[i], sizeof(all_mibao_value_[i]) - 1);
    }
    outputstream.write(mac_address_, sizeof(mac_address_) - 1);
    return true;
  __LEAVE_FUNCTION
    return false;
}

uint32_t AskLogin::execute(connection::Base* connection) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = AskLoginHandler::execute(this, connection);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint16_t AskLogin::getid() const {
  using namespace pap_common_game::define;
  return id::packet::client_tologin::kAskLogin;
}

uint32_t AskLogin::getsize() const {
  uint32_t result = sizeof(account_) - 1 +
                    sizeof(password_) - 1 +
                    sizeof(version_) +
                    sizeof(all_mibao_value_) - 1 +
                    sizeof(mac_address_) - 1;
  return result;
}

void AskLogin::get_account(char* buffer, uint16_t length) {
  __ENTER_FUNCTION
    snprintf(buffer, length, account_);
  __LEAVE_FUNCTION
}
void AskLogin::set_account(const char* account) {
  __ENTER_FUNCTION
    strncpy(account_, account, sizeof(account_) - 1);
    account_[sizeof(account_)] = 0;
  __LEAVE_FUNCTION
}
void AskLogin::get_password(char* buffer, uint16_t length) {
  __ENTER_FUNCTION
    snprintf(buffer, length, password_);
  __LEAVE_FUNCTION
}
void AskLogin::set_password(const char* password) {
  __ENTER_FUNCTION
    strncpy(password_, password, sizeof(password_) - 1);
    password_[sizeof(password_)] = 0;
  __LEAVE_FUNCTION
}
uint32_t AskLogin::get_version() {
  return version_;
}
void AskLogin::set_version(uint32_t version) {
  version_ = version;
}
void AskLogin::get_all_mibao_value(int32_t index, 
                                   char* buffer, 
                                   uint16_t length) {
  __ENTER_FUNCTION
    using namespace pap_common_game::define::size;
    if (index < 0 || index >= mibao::kUnitNumber) return;
    snprintf(buffer, length, all_mibao_value_[index]);
  __LEAVE_FUNCTION
}
void AskLogin::set_all_mibao_value(int32_t index, const char* value) {
  __ENTER_FUNCTION
    strncpy(all_mibao_value_[index], value, sizeof(all_mibao_value_[i]) - 1);
    all_mibao_value_[index][sizeof(all_mibao_value_[index])] = 0;
  __LEAVE_FUNCTION
}
void AskLogin::get_mac_address(char* buffer, uint16_t length) {
  __ENTER_FUNCTION
    snprintf(buffer, length, mac_address_);
  __LEAVE_FUNCTION
}
void AskLogin::set_mac_address(const char* mac_address) {
  __ENTER_FUNCTION
    strncpy(mac_address_, mac_address, sizeof(mac_address_) - 1);
    mac_address_[sizeof(mac_address_)] = 0;
  __LEAVE_FUNCTION
}

packet::Base* AskLoginFactory::createpacket() {
  __ENTER_FUNCTION
    return new AskLogin();
  __LEAVE_FUNCTION
    return NULL;
}

uint16_t AskLoginFactory::get_packetid() const {
  using namespace pap_common_game::define;
  return id::packet::client_tologin::kAskLogin;
}

uint32_t AskLoginFactory::get_packet_maxsize() const {
  uint32_t result = sizeof(char) * ACCOUNTLENGTH_MAX +
                    sizeof(char) * MD5SIZE_MAX +
                    sizeof(uint32_t) +
                    sizeof(char) * pap_common_game::define::size::mibao::kUnitNumber][pap_common_game::define::size::mibao::kUnitValueLength +
                    sizeof(char) * MD5SIZE_MAX;
  return result;
}

} //namespace client_tologin

} //namespace packets

} //namespace pap_common_net
