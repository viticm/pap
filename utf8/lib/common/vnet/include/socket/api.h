/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vnet
 * $Id api.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-25 14:17:07
 * @uses vnet socket system api extend functions
 */
#ifndef VNET_SOCKET_API_H_
#define VNET_SOCKET_API_H_

#include "socket/config.h"

#if defined(__LINUX__)
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#elif defined(__WINDOWS__)
#include <winsock.h>
#endif

const int8_t kSocketErrorWouldBlock = -100; //use in same model not use macro

#if defined(__LINUX__) //macros in linux
#define SOCKET_INVALID -1
#define SOCKET_ERROR -1
#endif

int32_t socketapi_socketex(int32_t domain, int32_t type, int32_t protocol);

bool socketapi_bindex(int32_t socket, 
                      const struct sockaddr* name, 
                      uint32_t namelength);

bool socketapi_connectex(int32_t socket, 
                         const struct sockaddr* name, 
                         uint32_t namelength);

bool socketapi_listenex(int32_t socket, uint32_t backlog);

int32_t socketapi_acceptex(int32_t socket, 
                           struct sockaddr* addr, 
                           uint32_t* addrlength);

bool socketapi_getsockopt_exb(int32_t socket, 
                              int32_t level, 
                              int32_t optname, 
                              void* optval, 
                              uint32_t* optlength);

uint32_t socketapi_getsockopt_exu(int32_t socket, 
                                  int32_t level, 
                                  int32_t optname, 
                                  void* optval, 
                                  uint32_t* optlength);

bool socketapi_setsockopt_ex(int32_t socket,
                             int32_t level,
                             int32_t optname,
                             const void* optval,
                             uint32_t optlength);

int32_t socketapi_sendex(int32_t socket, 
                         const void* buffer, 
                         uint32_t length, 
                         uint32_t flag);

int32_t socketapi_sendto_ex(int32_t socket, 
                            const void* buffer, 
                            int32_t length, 
                            uint32_t flag, 
                            const struct sockaddr* to, 
                            int32_t tolength);

int32_t socketapi_recvex(int32_t socket, 
                         void* buffer, 
                         uint32_t length, 
                         uint32_t flag);

int32_t socketapi_recvfrom_ex(int32_t socket, 
                              void* buffer, 
                              int32_t length, 
                              uint32_t flag, 
                              struct sockaddr* from, 
                              uint32_t* fromlength);

bool socketapi_closesocket_ex(int32_t socket);

bool socketapi_ioctlsocket_ex(int32_t socket, int64_t cmd, uint64_t* argp);

bool socketapi_get_nonblocking_ex(int32_t socket);

bool socketapi_set_nonblocking_ex(int32_t socket, bool on);

uint32_t socketapi_availableex(int32_t socket);

//uint32_t socketapi_shutdown_ex(int32_t socket, uint32_t how);

int32_t socketapi_selectex(int32_t maxfdp1, 
                           fd_set* readset, 
                           fd_set* writeset, 
                           fd_set* exceptset, 
                           struct timeval* timeout);

#endif //VNET_SOCKET_API_H_
