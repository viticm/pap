/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vnet
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-25 14:17:07
 * @uses vnet socket base extend functions
 */

#ifndef VNET_SOCKET_BASE_TYPE_H_
#define VNET_SOCKET_BASE_TYPE_H_

#include "socket/config.h"
#include "socket/api.h"

bool socketbase_create(const char* host, uint32_t port);
uint32_t socketbase_send(const void* buffer, 
                         uint32_t length, 
                         uint32_t flag = 0);
uint32_t socketbase_available(int32_t socketid);
int32_t socketbase_accept(struct sockaddr* addr, uint32_t* addrlength);
bool socketbase_bind(sockaddr_in _sockaddr_in);
bool socketbase_listen(int32_t socketid, int32_t backlog);
uint32_t socketbase_getlinger(int32_t socketid);
bool socketbase_setlinger(int32_t socketid, uint32_t lingertime);
bool socketbase_is_reuseaddr(int32_t socketid);
bool socketbase_set_reuseaddr(int32_t socketid, bool on = true);
bool socketbase_iserror(int32_t socketid);
bool socketbase_is_nonblocking(int32_t socketid);
bool socketbase_set_nonblocking(int32_t socketid, bool on = true);
uint32_t socketbase_getreceive_buffersize(int32_t socketid);
bool socketbase_setreceive_buffersize(int32_t socketid, uint32_t size);

#endif //VNET_SOCKET_BASE_TYPE_H_
