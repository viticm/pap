/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id factorymanager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 10:11:38
 * @uses server and client net packet factory manager
 */
#ifndef PAP_COMMON_NET_PACKET_FACTORYMANAGER_H_
#define PAP_COMMON_NET_PACKET_FACTORYMANAGER_H_

#include "common/net/config.h"
#include "common/net/packet/factory.h"
#include "common/sys/thread.h"

namespace pap_common_net {

namespace packet {

class FactoryManager {

 public:
   FactoryManager();
   ~FactoryManager();

 public:
   uint32_t* packet_alloccount_;
 
 public:
   bool init();
   //根据消息类型从内存里分配消息实体数据（允许多线程同时调用）
   Base* createpacket(uint16_t pakcetid);
   //根据消息类型取得对应消息的最大尺寸（允许多线程同时调用）
   uint32_t getpacket_maxsize(uint16_t packetid);
   //删除消息实体（允许多线程同时调用）
   void removepacket(Base* packet);
   void lock();
   void unlock();
   static bool isvalid_packetid(uint16_t id); //packetid is valid

 private:
   Factory** factories_;
   uint16_t size_;
   pap_common_sys::ThreadLock lock_;

 private:
   void addfactory(Factory* factory);
   void addfactories_for_billinglogin();
   void addfactories_for_clientlogin();
   void addfactories_for_loginworld();
   void addfactories_for_serverworld();
   void addfactories_for_clientserver();

};

}; //namespace packet

}; //namespace pap_common_net

extern pap_common_net::packet::FactoryManager* g_packetfactory_manager;

#endif //COMMON_NET_PACKETFACTORY_H_
