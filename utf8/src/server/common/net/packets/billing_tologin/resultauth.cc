#include "server/common/net/packets/billing_tologin/resultauth.h"
#include "server/common/game/define/all.h"

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
    inputstream.read(static_cast<char*>(&result_), sizeof(result_));
    inputstream.read(static_cast<char*>(&playerid_), sizeof(playerid_));
    inputstream.read(static_cast<char*>(&playerguid_), sizeof(playerguid_));
    inputstream.read(servername_, sizeof(servername_) - 1);
    inputstream.read(isfatigue_, sizeof(isfatigue_) - 1);
    inputstream.read(static_cast<char*>(&total_onlinetime_), sizeof(total_onlinetime_));
    inputstream.read(isphone_bind_, sizeof(isphone_bind_) - 1);
    inputstream.read(isip_bind_, sizeof(isip_bind_) - 1);
    inputstream.read(ismibao_bind_, sizeof(ismibao_bind_) - 1);
    inputstream.read(ismac_bind_, sizeof(ismac_bind_) - 1);
    inputstream.read(is_realname_bind_, sizeof(is_realname_bind_) - 1);
    inputstream.read(is_inputname_bind_, sizeof(is_inputname_bind_) - 1);
  __LEAVE_FUNCTION
}

bool ResultAuth::write(pap_common_net::socket::OutputStream& outputstream) {
  __ENTER_FUNCTION
    outputstream.write(account_, sizeof(account_) - 1);
    outputstream.write(static_cast<char*>(&result_), sizeof(result_));
    outputstream.write(static_cast<char*>(&playerid_), sizeof(playerid_));
    outputstream.write(static_cast<char*>(&playerguid_), sizeof(playerguid_));
    outputstream.write(servername_, sizeof(servername_) - 1);
    outputstream.write(isfatigue_, sizeof(isfatigue_) - 1);
    outputstream.write(static_cast<char*>(&total_onlinetime_), sizeof(total_onlinetime_));
    outputstream.write(isphone_bind_, sizeof(isphone_bind_) - 1);
    outputstream.write(isip_bind_, sizeof(isip_bind_) - 1);
    outputstream.write(ismibao_bind_, sizeof(ismibao_bind_) - 1);
    outputstream.write(ismac_bind_, sizeof(ismac_bind_) - 1);
    outputstream.write(is_realname_bind_, sizeof(is_realname_bind_) - 1);
    outputstream.write(is_inputname_bind_, sizeof(is_inputname_bind_) - 1);
  __LEAVE_FUNCTION
}

uint32_t ResultAuth::execute(connection::Base* connection) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result = ResultAuthHandler::execute(this, connection);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint16_t ResultAuth::get_packetid() const {
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
  result_ = result
}
uint16_t ResultAuth::get_playerid() {
  return playerid_;
}
void ResultAuth::set_playerid(uint16_t playerid) {
  playerid_ = playerid
}
uint32_t ResultAuth::get_playerguid() {
  return playerguid_;
}
void ResultAuth::set_playerguid(uint32_t playerguid) {
  playerguid_ = playerguid
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
  isfatigue_ = isfatigue
}
uint32_t ResultAuth::get_total_onlinetime() {
  return total_onlinetime_;
}
void ResultAuth::set_total_onlinetime(uint32_t total_onlinetime) {
  total_onlinetime_ = total_onlinetime
}
char ResultAuth::get_isphone_bind() {
  return isphone_bind_;
}
void ResultAuth::set_isphone_bind(char isphone_bind) {
  isphone_bind_ = isphone_bind
}
char ResultAuth::get_isip_bind() {
  return isip_bind_;
}
void ResultAuth::set_isip_bind(char isip_bind) {
  isip_bind_ = isip_bind
}
char ResultAuth::get_ismibao_bind() {
  return ismibao_bind_;
}
void ResultAuth::set_ismibao_bind(char ismibao_bind) {
  ismibao_bind_ = ismibao_bind
}
char ResultAuth::get_ismac_bind() {
  return ismac_bind_;
}
void ResultAuth::set_ismac_bind(char ismac_bind) {
  ismac_bind_ = ismac_bind
}
char ResultAuth::get_is_realname_bind() {
  return is_realname_bind_;
}
void ResultAuth::set_is_realname_bind(char is_realname_bind) {
  is_realname_bind_ = is_realname_bind
}
char ResultAuth::get_is_inputname_bind() {
  return is_inputname_bind_;
}
void ResultAuth::set_is_inputname_bind(char is_inputname_bind) {
  is_inputname_bind_ = is_inputname_bind
}

pap_common_net::Packet* AskAuthFactory::createpacket() {
  __ENTER_FUNCTION
    return new ResultAuth();
  __LEAVE_FUNCTION
    return NULL;
}

uint16_t ResultAuthFactory::get_packetid() const {
  using namespace pap_server_common_game::define::id::packet;
  return billing_tologin::kResultAuth;
}

uint32_t ResultAuthFactory::get_packet_maxsize() const {
  uint32_t result = sizeof(account_) +
                    sizeof(result_) +
                    sizeof(playerid_) +
                    sizeof(playerguid_) +
                    sizeof(servername_) +
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

} //namespace billing_tologin

} //namespace packets

} //namespace pap_server_common_net
