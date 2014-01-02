/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id packet.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-2 11:36:54
 * @uses server and client net pakcet class
 */
#ifndef PAP_COMMON_NET_PACKET_H_
#define PAP_COMMON_NET_PACKET_H_

#include "common/net/config.h"
#include "common/net/socket_inputstream.h"
#include "common/net/socket_outputstream.h"

#define GET_PACKETINDEX(a) ((a) >> 24)
#define SET_PACKETINDEX(a,index) ((a) = (((a) & 0xffffff) + ((index) << 24)))
#define GET_PACKETLENGTH(a) ((a) & 0xffffff)
#define SET_PACKETLENGTH(a,length) ((a) = ((a) & 0xff000000) + (length))
//note cn:
//消息头中包括：uint16_t - 2字节；uint32_t - 4字节中高位一个字节为消息序列号，
//其余三个字节为消息长度
//通过GET_PACKETINDEX和GET_PACKETLENGTH宏，
//可以取得UINT数据里面的消息序列号和长度
//通过SET_PACKETINDEX和SET_PACKETLENGTH宏，
//可以设置UINT数据里面的消息序列号和长度
#define GET_PACKETHEADER_SIZE (sizeof(uint16_t) + sizeof(uint32_t))

typedef enum {
  PACKET_EXECUTESTATUS_ERROR = 0, //表示出现严重错误，当前连接需要被强制断开 
  PACKET_EXECUTESTATUS_BREAK, //表示返回后剩下的消息将不在当前处理循环里处理
  PACKET_EXECUTESTATUS_CONTINUE, //表示继续在当前循环里执行剩下的消息
  PACKET_EXECUTESTATUS_NOTREMOVE, //表示继续在当前循环里执行剩下的消息,
                                  //但是不回收当前消息
  PACKET_EXECUTESTATUS_NOTREMOVE_ERROR,
} packet_executestatus_enum;

namespace pap_common_net {

class Connection;

class Packet {

 public:
   Packet();
   virtual ~Packet();
 
 public:
   int8_t status;
   int8_t index;

 public:
   virtual void cleanup();
   virtual bool read(SocketInputStream& inputstream) = 0;
   virtual bool write(SocketOutputStream& outputstream) const = 0;
   virtual uint32_t execute(Connection* connection) = 0;
   virtual uint16_t getid() const = 0;
   virtual uint32_t getsize() const = 0;
   int8_t getindex() const;
   void setindex(int8_t index);
   uint8_t getstatus() const;
   void setstatus(uint8_t status);

};

}; //namespace pap_common_net

#endif //PAP_COMMON_NET_PACKET_H_
