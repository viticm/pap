/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id connection.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-2 11:17:20
 * @uses server net connect information
 */
#ifndef PAP_SERVER_COMMON_NET_CONNECTION_H_
#define PAP_SERVER_COMMON_NET_CONNECTION_H_

#include "server/common/net/config.h"
#include "common/net/packet.h"
#include "common/net/socket.h"
#include "common/net/socket_inputstream.h"
#include "common/net/socket_outputstream.h"

struct packet_async_t {
  pap_common_net::Packet* packet;
  uint16_t pakcetid;
  uint32_t flag;
  packet_async_t() {
    packet = NULL;
    packetid = ID_INVALID;
    flag = kPacketFlagNone;
  };

  ~packet_async_t() {
    SAFE_DELETE(packet);
    packetid = ID_INVALID;
    flag = kPacketFlagNone;
  };
};

namespace pap_server_common_net {

extern const char* g_kModelName;
extern const uint8_t g_kModelSaveLogId;

class Connection {

 public:
   Connection(bool flag_isserver = false);
   ~Connection();

 public:
   virtual bool processinput();
   virtual bool processoutput();
   virtual bool processcommand(bool option = true);
   virtual bool heartbeat(uint32_t time = 0, uint32_t flag);
   virtual bool sendpacket(pap_common_net::Packet* packet);

 public:
   virtual bool isserver() = 0;
   virtual bool isplayer() = 0;
   //读取设置玩家连接ID的接口，该ID是由ConnectionPool类分配出来的索引值
   //用于标识一个客户端连接在整个系统中的数据位置信息
   uint16_t getid();
   void setid(uint16_t id);
   //读取设置玩家UID的接口，userid是由UserPool类分配出来的索引值
   //用于标识玩家的游戏存储位置信息
   uint16_t get_userid();
   void set_userid(uint16_t id);
   //读取设置玩家连接管理器ID，managerid 是由ConnectionManager类分配的索引值
   //用于标识当前玩家所在的某个PlayerManager中的位置信息，每个
   //ConnectionManager位于一个独立的线程里
   uint16_t get_managerid();
   void set_managerid(uint16_t id);
   //读取当前连接的socket对象
   pap_common_net::Socket* getsocket();
   //断开网络连接
   virtual void disconnect();
   //当前连接是否有效
   virtual bool isvalid();
   virtual void cleanup();
   //判断当前连接是否为空块，是则释放用于新连接
   bool isempty();
   void setempty(bool status = true);
   bool isdisconnect();
   void setdisconnect(bool status = true);
   virtual void resetkick();

 protected:
   uint16_t id_;
   uint16_t userid_;
   uint16_t managerid_;
   pap_common_net::Socket* socket_;
   pap_common_net::SocketInputStream* socket_inputstream_;
   pap_common_net::SocketOutputStream* socket_outputstream_;
   int8_t packetindex_;

 private:
   bool isempty_;
   bool isdisconnect_;

};

}; //namespace pap_common_net

#endif //PAP_SERVER_COMMON_NET_CONNECTION_H_
