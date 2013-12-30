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

int32_t socketbase_create();
int32_t socketbase_typecreate(int32_t type);
void socketbase_close(int32_t socketid);
bool socketbase_connect(int32_t socketid, const char* host, uint16_t port);
int32_t socketbase_send(int32_t socketid,
                        const void* buffer, 
                        uint32_t length, 
                        uint32_t flag);
int32_t socketbase_receive(int32_t socketid,
                           void* buffer, 
                           uint32_t length, 
                           uint32_t flag);
uint32_t socketbase_available(int32_t socketid);

//cn: (note) socketbase_accept
//accept()连接请求队列中获得连接信息，创建新的套接字，
//并返回该套接字的文件描述符。
//新创建的套接字用于服务器与客户机的通信，而原来的套接字仍然处于监听状态
int32_t socketbase_accept(int32_t socketid,  uint16_t port);
bool socketbase_bind(int32_t socketid, uint16_t port);
bool socketbase_listen(int32_t socketid, int32_t backlog);
uint32_t socketbase_getlinger(int32_t socketid);
bool socketbase_setlinger(int32_t socketid, uint32_t lingertime);
bool socketbase_is_reuseaddr(int32_t socketid);
bool socketbase_set_reuseaddr(int32_t socketid, bool on);
bool socketbase_iserror(int32_t socketid);
bool socketbase_is_nonblocking(int32_t socketid);
bool socketbase_set_nonblocking(int32_t socketid, bool on);
uint32_t socketbase_getreceive_buffersize(int32_t socketid);
bool socketbase_setreceive_buffersize(int32_t socketid, uint32_t size);

#endif //VNET_SOCKET_BASE_TYPE_H_
