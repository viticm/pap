#include "socket/base.h"

int32_t socketbase_create(int32_t type) {
  int32_t socketid;
  socketid = socketapi_socketex(AF_INET, type, 0);
  return socketid;
}

void socketbase_close(int32_t socketid) {
  if (!socketbase_iserror(socketid)) socketapi_closeex(socketid);
}

bool socketbase_connect(int32_t socketid, const char* host, uint32_t port) {
  bool result = true;
  struct sockaddr_in connect_sockaddr_in;
  connect_sockaddr_in.sin_addr.s_addr = inet_addr(host);
  connect_sockaddr_in.sin_port = htons((uint16_t)port);
  result = socketapi_connectex(socketid, 
                               (const struct sockaddr*)&connect_sockaddr_in, 
                               sizeof(connect_sockaddr_in));
  return result;
}

int32_t socketbase_send(int32_t socketid,
                        const void* buffer, 
                        uint32_t length, 
                        uint32_t flag) {
  int32_t result = 0;
  result = socketapi_sendex(socketid, buffer, length, flag);
  return result;
}

int32_t socketbase_receive(int32_t socketid,
                           void* buffer,
                           uint32_t length,
                           uint32_t flag) {
  int32_t result = 0;
  result = socketapi_recvex(socketid, buffer, length, flag);
  return result;
}

uint32_t socketbase_available(int32_t socketid) {
  uint32_t result = 0;
  result = socketapi_availableex(socketid);
  return result;
}

int32_t socketbase_accept(int32_t socketid, 
                          struct sockaddr* addr, 
                          uint32_t* addrlength) {
  int32_t result = 0;
  result = socketapi_acceptex(socketid, addr, addrlength);
  return result;
}

bool socketbase_bind(int32_t socketid, uint32_t port) {
  bool result = true;
  struct sockaddr_in connect_sockaddr_in;
  connect_sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
  connect_sockaddr_in.sin_port = htons((uint16_t)port);
  result = socketapi_bindex(socketid, 
                            (const struct sockaddr*)&connect_sockaddr_in, 
                            sizeof(connect_sockaddr_in));
  return result;
}

bool socketbase_listen(int32_t socketid, int32_t backlog) {
  bool result = true;
  result = socketapi_listenex(socketid, backlog);
  return result;
}

uint32_t socketbase_getlinger(int32_t socketid) {
  uint32_t result = 0;
  struct linger getlinger;
  uint32_t length = sizeof(getlinger);
  socketapi_getsockopt_exb(socketid, 
                           SOL_SOCKET, 
                           SO_LINGER, 
                           &getlinger, 
                           &length);
  result = getlinger.l_linger;
  return result;
}

bool socketbase_setlinger(int32_t socketid, uint32_t lingertime) {
  bool result = true;
  struct linger setlinger;
  setlinger.l_onoff = lingertime > 0 ? 1 : 0;
  setlinger.l_linger = (uint16_t)lingertime;
  result = socketapi_setsockopt_ex(socketid, 
                                   SOL_SOCKET, 
                                   SO_LINGER, 
                                   &setlinger, 
                                   sizeof(setlinger));
  return result;
}

bool socketbase_is_reuseaddr(int32_t socketid) {
  bool result = true;
  int32_t reuse = 0;
  uint32_t length = sizeof(reuse);
  socketapi_getsockopt_exb(socketid, 
                           SOL_SOCKET, 
                           SO_REUSEADDR, 
                           &reuse,
                           &length);
  result = 1 == reuse;
  return result;
}

bool socketbase_set_reuseaddr(int32_t socketid, bool on) {
  bool result = true;
  int32_t opt = true == on ? 1 : 0;
  result = socketapi_setsockopt_ex(socketid, 
                                   SOL_SOCKET, 
                                   SO_REUSEADDR, 
                                   &opt, 
                                   sizeof(opt));
  return result;
}

bool socketbase_iserror(int32_t socketid) {
  bool result = false;
  int32_t error = 0;
  uint32_t length = sizeof(error);
  uint32_t optresult = 0;
  optresult = socketapi_getsockopt_exu(socketid, 
                                       SOL_SOCKET, 
                                       SO_ERROR, 
                                       &error, 
                                       &length);
  result = 0 == optresult ? false : true;
  return result;
}

bool socketbase_is_nonblocking(int32_t socketid) {
  bool result = true;
  result = socketapi_get_nonblocking_ex(socketid);
  return result;
}

bool socketbase_set_nonblocking(int32_t socketid, bool on) {
  bool result = true;
  result = socketapi_set_nonblocking_ex(socketid, on);
  return result;
}

uint32_t socketbase_getreceive_buffersize(int32_t socketid) {
  uint32_t receive_buffersize = 0;
  uint32_t length = sizeof(receive_buffersize);
  socketapi_getsockopt_exb(socketid, 
                           SOL_SOCKET, 
                           SO_RCVBUF, 
                           &receive_buffersize, 
                           &length);
  return receive_buffersize;
}

bool socketbase_setreceive_buffersize(int32_t socketid, uint32_t size) {
  bool result = true;
  result = socketapi_setsockopt_ex(socketid, 
                                   SOL_SOCKET, 
                                   SO_RCVBUF, 
                                   &size, 
                                   sizeof(size));
  return result;
}
