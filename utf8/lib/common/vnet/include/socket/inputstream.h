/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vnet
 * $Id inputstream.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-26 11:37:45
 * @uses vnet socket input stream model
 */
#ifndef VNET_SOCKET_INPUTSTREAM_H_
#define VNET_SOCKET_INPUTSTREAM_H_

#include "socket/config.h"
#define SOCKETINPUT_BUFFERSIZE_DEFAULT (64*1024) //default size
#define SOCKETINPUT_DISCONNECT_MAXSIZE (96*1024) //if buffer more than it,
                                                  //will disconnect this socket.

uint32_t socket_inputstream_read(struct packet_t* packet, 
                                 char* buffer, 
                                 uint32_t length);
uint32_t socket_inputstream_encoderead(struct packet_t* packet, 
                                       char* buffer, 
                                       uint32_t length
                                       struct endecode_param_t* endecode_param);
bool socket_inputstream_resize(struct packet_t* packet, int32_t size);
uint32_t socket_inputstream_reallength(struct packet_t packet);
bool socket_inputstream_peek(struct packet_t packet,
                             char* buffer,
                             uint32_t length);
bool socket_inputstream_skip(struct packet_t* packet, uint32_t length);
bool socket_inputstream_encodeskip(struct packet_t* packet, 
                                   uint32_t length
                                   struct endecode_param_t* endecode_param);
int32_t socket_inputstream_fill(int32_t socketid, struct packet_t* packet);
void socket_inputstream_packetinit(struct packet_t* packet);

#endif //VNET_SOCKET_INPUTSTREAM_H_
