#include "server/billing/connection/billing.h"
#include "server/common/game/define/all.h"
#include "server/common/base/log.h"
#include "common/net/packet/factorymanager.h"

namespace billingconnection {

Billing::Billing(bool isserver) : 
  pap_server_common_net::connection::Base(isserver) {
  using namespace pap_server_common_game::define;
  status_ = status::connection::kBillingEmpty;
  last_keeplive_time_ = 0;
  keeplive_sendnumber_ = 0;
}

Billing::~Billing() {
  //do nothing
}

bool Billing::processinput() {
  __ENTER_FUNCTION
    bool result = false;
    result = pap_server_common_net::connection::Base::processinput();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Billing::processoutput() {
  __ENTER_FUNCTION
    bool result = false;
    result = pap_server_common_net::connection::Base::processoutput();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Billing::processcommand(bool option) {
  __ENTER_FUNCTION
    using namespace pap_common_net;
    bool result = false;
    char packetheader[PACKET_HEADERSIZE] = {'\0'};
    uint16_t packetid;
    uint32_t packetcheck, packetsize, packetindex;
    packet::Base* packet = NULL;

    if (isdisconnect()) return true;
    try {
      if (option) { //执行选项操作
      }
      for (;;) { //消费服务器需要及时处理所有消息
        if (!socket_inputstream_->peek(&packetheader[0], PACKET_HEADERSIZE)) {
          //数据不能填充消息头
          break;
        }
        memcpy(&packetid, &packetheader[0], sizeof(uint16_t));
        g_log->fast_save_log(kBillingLogFile, "packtid = %d", packetid);
        memcpy(&packetcheck, &packetheader[sizeof(uint16_t)], sizeof(uint32_t));
        packetsize = GET_PACKETLENGTH(packetcheck);
        packetindex = GET_PACKETINDEX(packetcheck);
        if (!packet::FactoryManager::isvalid_packetid(packetid)) {
          return false;
        }
        try {
          //check packet length
          if (socket_inputstream_->reallength() < 
              PACKET_HEADERSIZE + packetsize) {
            //message not receive full
            break;
          }
          //check packet size
          if (packetsize > 
              g_packetfactory_manager->getpacket_maxsize(packetid)) {
            char temp[FILENAME_MAX] = {0};
            snprintf(temp, 
                     sizeof(temp) - 1, 
                     "packet size error, packetid = %d", 
                     packetid);
            AssertEx(false, temp);
            return false;
          }
          //create packet
          packet = g_packetfactory_manager->createpacket(packetid);
          if (NULL == packet) return false;
          packet->setindex(static_cast<int8_t>(packetindex));
          
          //read packet
          result = socket_inputstream_->readpacket(packet);
          if (false == result) {
            g_packetfactory_manager->removepacket(packet);
            return result;
          }
          bool needremove = true;
          bool exception = false;
          uint32_t executestatus = 0;
          try {
            resetkick();
            try {
              executestatus = packet->execute(this);
            }
            catch(...) {
              SaveErrorLog();
              executestatus = kPacketExecuteStatusError;
            }
            if (kPacketExecuteStatusError == executestatus) {
              if (packet) g_packetfactory_manager->removepacket(packet);
              return false;
            }
            else if (kPacketExecuteStatusBreak == executestatus) {
              if (packet) g_packetfactory_manager->removepacket(packet);
              break;
            }
            else if (kPacketExecuteStatusContinue == executestatus) {
              //continue read last packet
            }
            else if (kPacketExecuteStatusNotRemove == executestatus) {
              needremove = false;
            }
            else if (kPacketExecuteStatusNotRemoveError == executestatus) {
              return false;
            }
            else {
              //unknown status
            }
          }
          catch(...) {
            SaveErrorLog();
            exception = true;
          }
          if (packet && needremove) 
            g_packetfactory_manager->removepacket(packet);
          if (exception) return false;
        }
        catch(...) {
          SaveErrorLog();
          return false;
        }
      }
    }
    catch(...) {
      SaveErrorLog();
      return false;
    }
    return true;
  __LEAVE_FUNCTION
    return false;
}

void Billing::cleanup() {
  using namespace pap_server_common_game::define;
  status_ = status::connection::kBillingEmpty;
  last_keeplive_time_ = 0;
  keeplive_sendnumber_ = 0;
  pap_server_common_net::connection::Base::cleanup();
}

bool Billing::heartbeat(uint32_t time) {
  __ENTER_FUNCTION
    bool result = false;
    result = pap_server_common_net::connection::Base::heartbeat(time);
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Billing::isserver() {
  return false;
}

bool Billing::isplayer() {
  return false;
}

bool Billing::isbilling() {
  return true;
}

bool Billing::islogin() {
  return false;
}

void Billing::setstatus(uint32_t status) {
  status_ = status;
}

uint32_t Billing::getstatus() {
  return status_;
}

void Billing::clear_keeplive_sendnumber() {
  keeplive_sendnumber_ = 0;
}

bool Billing::isvalid() {
  bool result = false;
  result = pap_server_common_net::connection::Base::isvalid();
  return result;
}

bool Billing::sendpacket(pap_common_net::packet::Base* packet) {
  __ENTER_FUNCTION  
    bool result = false;
    result = pap_server_common_net::connection::Base::sendpacket(packet);
    return result;
  __LEAVE_FUNCTION
    return false;
}

} //namespace connection
