#include "common/net/packetfactory_manager.h"
#include "server/common/game/define/all.h"

#if defined(_PAP_NET_BILLING) || defined(_PAP_NET_LOGIN)

#include "server/common/net/packets/login_tobilling/askauth.h"
#include "server/common/net/packets/billing_tologin/resultauth.h"

#endif

pap_common_net::PacketFactoryManager* g_packetfactory_manager = NULL;

namespace pap_common_net {

PacketFactoryManager::PacketFactoryManager() {
  __ENTER_FUNCTION
    using namespace pap_server_common_game::define::packet; //every need it
    factories_ = NULL;
    size_ = 0;
#if defined(_PAP_NET_BILLING) || defined(_PAP_NET_LOGIN)
    size_ += billinglogin::kLast - billinglogin::kFirst - 1;
    size_ += billing_tologin::kLast - billing_tologin::kFirst - 1;
    size_ += login_tobilling::kLast - billing_tologin::kFirst - 1;
#endif
    Assert(size_ > 0);
    factories_ = new PacketFactory * [size_];
    Assert(factories_);
    packet_alloccount_ = new uint32_t[size_];
    Assert(packet_alloccount_);
    uint16_t i;
    for (i = 0; i < size_; ++i) {
      factories_[i] = NULL;
      packet_alloccount_[i] = 0;
    }
  __LEAVE_FUNCTION
}

PacketFactoryManager::~PacketFactoryManager() {
  __ENTER_FUNCTION
    Assert(factories_ != NULL);
    uint16_t i;
    for (i = 0; i < size_; ++i) {
      SAFE_DELETE(factories_[i]);
    }
    SAFE_DELETE(packet_alloccount_);
  __LEAVE_FUNCTION
}
bool PacketFactoryManager::init() {
  __ENTER_FUNCTION

    return true;
  __LEAVE_FUNCTION
    return false;
}

Packet* PacketFactoryManager::createpacket(uint16_t pakcetid) {
  __ENTER_FUNCTION
    if (NULL == factories_[packetid]) {
      Assert(false);
      return NULL;
    }
    Packet* packet = NULL;
    lock();
    try {
      packet = factories_[packetid]->createpacket();
      ++(packet_alloccount_[packetid]);
    }
    catch(...) {
      packet = NULL;
    }
    unlock();
    return packet;
  __LEAVE_FUNCTION
    return NULL;
}

uint32_t PacketFactoryManager::getpacket_maxsize(uint16_t packetid) {
  __ENTER_FUNCTION
    uint32_t result = 0;
    if (NULL == factories_[packetid]) {
      char temp[FILENAME_MAX] = {0};
      snprintf(temp, 
               sizeof(temp) - 1, 
               "packetid: %d not register in factory!", 
               packetid);
      AssertEx(false, temp);
      return result;
    }
    lock();
    result = factories_[packetid]->get_packet_maxsize();
    unlock();
    return result;
  __LEAVE_FUNCTION
    return 0;
}

void PacketFactoryManager::removepacket(Packet* packet) {
  __ENTER_FUNCTION
    if (NULL == packet) {
      Assert(false);
      return;
    }
    lock();
    try {
      SAFE_DELETE(packet);
      --(packet_alloccount_[packet->get_packetid()]);
    }
    catch(...) {
      
    }
  __LEAVE_FUNCTION
}

void PacketFactoryManager::lock() {

}

void PacketFactoryManager::unlock() {

}

void PacketFactoryManager::addfactory(PacketFactory* factory) {
  __ENTER_FUNCTION
    if (factories_[factory->get_packetid()] != NULL) {
      Assert(false);
      return;
    }
    factories_[factory->get_packetid()] = factory;
  __LEAVE_FUNCTION
}

void PacketFactoryManager::addfactory_for_billinglogin() {

}

void PacketFactoryManager::addfactory_for_clientlogin() {

}

void PacketFactoryManager::addfactory_for_loginworld() {

}

void PacketFactoryManager::addfactory_for_serverworld() {

}
void PacketFactoryManager::addfactory_for_clientserver() {

}

} //namespace pap_common_net
