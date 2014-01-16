#include "server/common/net/packets/billing_tologin/resultauth.h"

namespace pap_server_common_net {

namespace packets {

namespace billing_tologin {

ResultAuth::ResultAuth() {
  __ENTER_FUNCTION
    memset(account_, 0, sizeof(account_));
    memset(servername_, 0, sizeof(servername_));
  __LEAVE_FUNCTION
}

bool ResultAuth::read(pap_common_net::socket::InputStream& inputstream) {
  __ENTER_FUNCTION
    inputstream.read(account_, sizeof(account_) - 1);
    inputstream.read((char*)(&result_), sizeof(result_));
    inputstream.read((char*)(&playerid_), sizeof(playerid_));
    inputstream.read((char*)(&playerguid_), sizeof(playerguid_));
    inputstream.read(servername_, sizeof(servername_) - 1);
    inputstream.read((char*)&isfatigue_, sizeof(isfatigue_) - 1);
    inputstream.read((char*)(&total_onlinetime_), sizeof(total_onlinetime_));
    inputstream.read((char*)&isphone_bind_, sizeof(isphone_bind_) - 1);
    inputstream.read((char*)&isip_bind_, sizeof(isip_bind_) - 1);
    inputstream.read((char*)&ismibao_bind_, sizeof(ismibao_bind_) - 1);
    inputstream.read((char*)&ismac_bind_, sizeof(ismac_bind_) - 1);
    inputstream.read((char*)&is_realname_bind_, sizeof(is_realname_bind_) - 1);
    inputstream.read((char*)&is_inputname_bind_, sizeof(is_inputname_bind_) - 1);
  __LEAVE_FUNCTION
    return false;
}

bool ResultAuth::write(pap_common_net::socket::OutputStream& outputstream) const {
  __ENTER_FUNCTION
    outputstream.write(account_, sizeof(account_) - 1);
    outputstream.write((char*)(&result_), sizeof(result_));
    outputstream.write((char*)(&playerid_), sizeof(playerid_));
    outputstream.write((char*)(&playerguid_), sizeof(playerguid_));
    outputstream.write(servername_, sizeof(servername_) - 1);
    outputstream.write((char*)&isfatigue_, sizeof(isfatigue_) - 1);
    outputstream.write((char*)(&total_onlinetime_), sizeof(total_onlinetime_));
    outputstream.write((char*)&isphone_bind_, sizeof(isphone_bind_) - 1);
    outputstream.write((char*)&isip_bind_, sizeof(isip_bind_) - 1);
    outputstream.write((char*)&ismibao_bind_, sizeof(ismibao_bind_) - 1);
    outputstream.write((char*)&ismac_bind_, sizeof(ismac_bind_) - 1);
    outputstream.write((char*)&is_realname_bind_, sizeof(is_realname_bind_) - 1);
    outputstream.write((char*)&is_inputname_bind_, sizeof(is_inputname_bind_) - 1);
  __LEAVE_FUNCTION
    return false;
}

uint32_t ResultAuth::execute(connection::Base* connection) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = ResultAuthHandler::execute(this, connection);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint16_t ResultAuth::getid() const {
  using namespace pap_server_common_game::define;
  return id::packet::billing_tologin::kResultAuth;
}

uint32_t ResultAuth::getsize() const {
  uint32_t result = sizeof(account_) - 1 +
                    sizeof(result_) +
                    sizeof(playerid_) +
                    sizeof(playerguid_) +
                    sizeof(servername_) - 1 +
                    sizeof(isfatigue_) +
                    sizeof(total_onlinetime_) +
                    sizeof(isphone_bind_) +
                    sizeof(isip_bind_) +
                    sizeof(ismibao_bind_) +
                    sizeof(ismac_bind_) +
                    sizeof(is_realname_bind_) +
                    sizeof(is_inputname_bind_);
  return result;
}

void ResultAuth::get_account(char* buffer, uint16_t length) {
  __ENTER_FUNCTION
    snprintf(buffer, length, account_);
  __LEAVE_FUNCTION
}
void ResultAuth::set_account(const char* account) {
  __ENTER_FUNCTION
    strncpy(account_, account, sizeof(account_) - 1);
    account_[sizeof(account_)] = 0;
  __LEAVE_FUNCTION
}
pap_common_game::define::result::login::_enum ResultAuth::get_result() {
  return result_;
}
void ResultAuth::set_result(pap_common_game::define::result::login::_enum result) {
  result_ = result;
}
uint16_t ResultAuth::get_playerid() {
  return playerid_;
}
void ResultAuth::set_playerid(uint16_t playerid) {
  playerid_ = playerid;
}
uint32_t ResultAuth::get_playerguid() {
  return playerguid_;
}
void ResultAuth::set_playerguid(uint32_t playerguid) {
  playerguid_ = playerguid;
}
void ResultAuth::get_servername(char* buffer, uint16_t length) {
  __ENTER_FUNCTION
    snprintf(buffer, length, servername_);
  __LEAVE_FUNCTION
}
void ResultAuth::set_servername(const char* servername) {
  __ENTER_FUNCTION
    strncpy(servername_, servername, sizeof(servername_) - 1);
    servername_[sizeof(servername_)] = 0;
  __LEAVE_FUNCTION
}
char ResultAuth::get_isfatigue() {
  return isfatigue_;
}
void ResultAuth::set_isfatigue(char isfatigue) {
  isfatigue_ = isfatigue;
}
uint32_t ResultAuth::get_total_onlinetime() {
  return total_onlinetime_;
}
void ResultAuth::set_total_onlinetime(uint32_t total_onlinetime) {
  total_onlinetime_ = total_onlinetime;
}
char ResultAuth::get_isphone_bind() {
  return isphone_bind_;
}
void ResultAuth::set_isphone_bind(char isphone_bind) {
  isphone_bind_ = isphone_bind;
}
char ResultAuth::get_isip_bind() {
  return isip_bind_;
}
void ResultAuth::set_isip_bind(char isip_bind) {
  isip_bind_ = isip_bind;
}
char ResultAuth::get_ismibao_bind() {
  return ismibao_bind_;
}
void ResultAuth::set_ismibao_bind(char ismibao_bind) {
  ismibao_bind_ = ismibao_bind;
}
char ResultAuth::get_ismac_bind() {
  return ismac_bind_;
}
void ResultAuth::set_ismac_bind(char ismac_bind) {
  ismac_bind_ = ismac_bind;
}
char ResultAuth::get_is_realname_bind() {
  return is_realname_bind_;
}
void ResultAuth::set_is_realname_bind(char is_realname_bind) {
  is_realname_bind_ = is_realname_bind;
}
char ResultAuth::get_is_inputname_bind() {
  return is_inputname_bind_;
}
void ResultAuth::set_is_inputname_bind(char is_inputname_bind) {
  is_inputname_bind_ = is_inputname_bind;
}

pap_common_net::packet::Base* ResultAuthFactory::createpacket() {
  __ENTER_FUNCTION
    return new ResultAuth();
  __LEAVE_FUNCTION
    return NULL;
}

uint16_t ResultAuthFactory::get_packetid() const {
  using namespace pap_server_common_game::define;
  return id::packet::billing_tologin::kResultAuth;
}

uint32_t ResultAuthFactory::get_packet_maxsize() const {
  uint32_t result = sizeof(char) * ACCOUNTLENGTH_MAX +
                    sizeof(pap_common_game::define::result::login::_enum) +
                    sizeof(uint16_t) +
                    sizeof(uint32_t) +
                    sizeof(char) * SERVRENAME_MAX +
                    sizeof(char) +
                    sizeof(uint32_t) +
                    sizeof(char) +
                    sizeof(char) +
                    sizeof(char) +
                    sizeof(char) +
                    sizeof(char) +
                    sizeof(char);
  return result;
}

} //namespace billing_tologin

} //namespace packets

} //namespace pap_server_common_net