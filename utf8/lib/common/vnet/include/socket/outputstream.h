/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vnet
 * $Id outputstream.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-26 11:37:45
 * @uses vnet socket output stream model
 */
#ifndef VNET_SOCKET_OUTPUTSTREAM_H_
#define VNET_SOCKET_OUTPUTSTREAM_H_

#include "socket/config.h"
#define SOCKETOUTPUT_BUFFERSIZE_DEFAULT (8192) //default size
#define SOCKETOUTPUT_DISCONNECT_MAXSIZE (100*1024) //if buffer more than it,
                                                  //will disconnect this socket.

uint32_t socket_outputstream_write(struct packet_t* packet, 
                                   const char* buffer, 
                                   uint32_t length);
uint32_t socket_outputstream_encodewrite(
    struct packet_t* packet, 
    const char* buffer, 
    uint32_t length
    struct endecode_param_t* endecode_param);
uint32_t socket_outputstream_reallength(packet_t packet);
int32_t socket_outputstream_flush(int32_t socketid, struct packet_t* packet);
bool socket_outputstream_resize(struct packet_t* packet, int32_t size);

#endif //VNET_SOCKET_OUTPUTSTREAM_H_
