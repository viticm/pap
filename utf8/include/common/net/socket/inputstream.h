#ifndef PAP_COMMON_NET_SOCKET_INPUTSTREAM_H_
#define PAP_COMMON_NET_SOCKET_INPUTSTREAM_H_

#include "common/net/config.h"
#include "common/lib/vnet/vnet.hpp"
#include "common/net/socket/base.h"
#include "common/net/packet/base.h"

namespace pap_common_net {

namespace socket {

class InputStream {

 public: //construct and destruct
   InputStream(
       Base* socket, 
       uint32_t bufferlength = SOCKETINPUT_BUFFERSIZE_DEFAULT, 
       uint32_t bufferlength_max = SOCKETINPUT_DISCONNECT_MAXSIZE);
   virtual ~InputStream();
   
 public:
   uint32_t read(char* buffer, uint32_t length);
   bool readpacket(packet::Base* packet);
   bool peek(char* buffer, uint32_t length);
   bool skip(uint32_t length);
   uint32_t fill();
   void init();
   bool resize(int32_t size);
   uint32_t reallength();
   bool isempty();
   void cleanup();
   void setkey(unsigned char const* key);
   int32_t get_keylength();

 private:
   socket::Base* socket_;
   struct packet_t* packet_;
   struct endecode_param_t* endecode_param_;

};

}; //namespace socket

}; //namespace pap_common_net

#endif //PAP_COMMON_NET_SOCKET_INPUTSTREAM_H_
