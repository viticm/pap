/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id socket.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-31 17:34:43
 * @uses server net model socket class
 */
#ifndef PAP_SERVER_COMMON_NET_SOCKET_H_
#define PAP_SERVER_COMMON_NET_SOCKET_H_

#include "common/net/socket/base.h"

namespace pap_server_common_net {

class Socket {

 public:
   Socket(uint16_t port, uint32_t backlog = 5);
   ~Socket();

 public:
   void close();
   bool accept(pap_common_net::socket::Base* socket);
   uint32_t getlinger() const;
   bool setlinger(uint32_t lingertime);
   bool is_nonblocking() const;
   bool set_nonblocking(bool on = true);
   uint32_t getreceive_buffersize() const;
   bool setreceive_buffersize(uint32_t size);
   uint32_t getsend_buffersize() const;
   bool setsend_buffersize(uint32_t size);
   int32_t getid() const;

 protected:
   pap_common_net::socket::Base* socket_;

};

}; //namespace pap_server_common_net

#endif //PAP_SERVER_COMMON_NET_SOCKET_H_
