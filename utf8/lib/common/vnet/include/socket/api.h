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
#include <WS2tcpip.h>
#endif
#include <errno.h>
#define EINPROGRESS	WSAEINPROGRESS


#define SOCKET_ERROR_WOULD_BLOCK -100

int32_t socketapi_socketex(int32_t domain, int32_t type, int32_t protocol);
EINPROGRESS
bool socketapi_bindex(int32_t socketid, 
                      const struct sockaddr* name, 
                      uint32_t namelength);

bool socketapi_connectex(int32_t socketid, 
                         const struct sockaddr* name, 
                         uint32_t namelength);

bool socketapi_listenex(int32_t socketid, uint32_t backlog);

int32_t socketapi_acceptex(int32_t socketid, 
                           struct sockaddr* addr, 
                           uint32_t* addrlength);

bool socketapi_getsockopt_exb(int32_t socketid, 
                              int32_t level, 
                              int32_t optname, 
                              void* optval, 
                              uint32_t* optlength);

uint32_t socketapi_getsockopt_exu(int32_t socketid, 
                                  int32_t level, 
                                  int32_t optname, 
                                  void* optval, 
                                  uint32_t* optlength);

bool socketapi_setsockopt_ex(int32_t socketid,
                             int32_t level,
                             int32_t optname,
                             const void* optval,
                             uint32_t optlength);

int32_t socketapi_sendex(int32_t socketid, 
                         const void* buffer, 
                         uint32_t length, 
                         uint32_t flag);

int32_t socketapi_sendto_ex(int32_t socketid, 
                            const void* buffer, 
                            int32_t length, 
                            uint32_t flag, 
                            const struct sockaddr* to, 
                            int32_t tolength);

int32_t socketapi_recvex(int32_t socketid, 
                         void* buffer, 
                         uint32_t length, 
                         uint32_t flag);

int32_t socketapi_recvfrom_ex(int32_t socketid, 
                              void* buffer, 
                              int32_t length, 
                              uint32_t flag, 
                              struct sockaddr* from, 
                              uint32_t* fromlength);

bool socketapi_closeex(int32_t socketid);

bool socketapi_ioctlex(int32_t socketid, int64_t cmd, uint64_t* argp);

bool socketapi_get_nonblocking_ex(int32_t socketid);

bool socketapi_set_nonblocking_ex(int32_t socketid, bool on);

uint32_t socketapi_availableex(int32_t socketid);

bool socketapi_shutdown_ex(int32_t socketid, uint32_t how);

int32_t socketapi_selectex(int32_t maxfdp, 
                           fd_set* readset, 
                           fd_set* writeset, 
                           fd_set* exceptset, 
                           struct timeval* timeout);

int32_t socketapi_getlast_errorcode();
void socketapi_getlast_errormessage(char* buffer, uint16_t length);

#endif //VNET_SOCKET_API_H_
