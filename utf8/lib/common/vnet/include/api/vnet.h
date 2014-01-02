/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vnet
 * $Id vnet.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-27 17:15:18
 * @uses the vnet base apis
 */
#ifndef VNET_API_VNET_H_
#define VNET_API_VNET_H_

#include "api/vnetconf.h"

/*socket {*/

/*base {*/
VNET_API int32_t vnet_socketbase_create(); //return socketid
//typecreate function will include header files
VNET_API int32_t vnet_socketbase_typecreate(int32_t type);
VNET_API void vnet_socketbase_close(int32_t socketid);
VNET_API bool vnet_socketbase_connect(int32_t socketid, 
                                      const char* host, 
                                      uint16_t port);
VNET_API int32_t vnet_socketbase_send(int32_t socketid,
                                      const void* buffer, 
                                      uint32_t length, 
                                      uint32_t flag);
VNET_API int32_t vnet_socketbase_receive(int32_t socketid,
                                         void* buffer, 
                                         uint32_t length, 
                                         uint32_t flag);
VNET_API uint32_t vnet_socketbase_available(int32_t socketid);
VNET_API int32_t vnet_socketbase_fastaccept(int32_t socketid); 
VNET_API int32_t vnet_socketbase_accept(int32_t socketid, uint16_t port);
VNET_API bool vnet_socketbase_bind(int32_t socketid, uint16_t port);
VNET_API bool vnet_socketbase_listen(int32_t socketid, uint32_t backlog);
VNET_API uint32_t vnet_socketbase_getlinger(int32_t socketid);
VNET_API bool vnet_socketbase_setlinger(int32_t socketid, uint32_t lingertime);
VNET_API bool vnet_socketbase_is_reuseaddr(int32_t socketid);
VNET_API bool vnet_socketbase_set_reuseaddr(int32_t socketid, bool on);
VNET_API bool vnet_socketbase_iserror(int32_t socketid);
VNET_API bool vnet_socketbase_is_nonblocking(int32_t socketid);
VNET_API bool vnet_socketbase_set_nonblocking(int32_t socketid, bool on);
VNET_API uint32_t vnet_socketbase_getreceive_buffersize(int32_t socketid);
VNET_API bool vnet_socketbase_setreceive_buffersize(int32_t socketid, 
                                                    uint32_t size);
VNET_API uint32_t vnet_socketbase_getsend_buffersize(int32_t socketid);
VNET_API bool vnet_socketbase_setsend_buffersize(int32_t socketid, 
                                                 uint32_t size);
VNET_API uint64_t vnet_sokectbase_getu64host(const char* host);
VNET_API int32_t vnet_socketbase_getlast_errorcode();
VNET_API void vnet_socketbase_getlast_errormessage(char* buffer, 
                                                   uint16_t length);
/*base }*/


/*inputstream {*/
VNET_API uint32_t vnet_socket_inputstream_read(struct packet_t* packet, 
                                               char* buffer, 
                                               uint32_t length);
VNET_API uint32_t vnet_socket_inputstream_encoderead(
    struct packet_t* packet, 
    char* buffer, 
    uint32_t length,
    struct endecode_param_t* endecode_param);
VNET_API bool vnet_socket_inputstream_resize(struct packet_t* packet, 
                                             int32_t size);
VNET_API uint32_t vnet_socket_inputstream_reallength(struct packet_t packet);
VNET_API bool vnet_socket_inputstream_peek(struct packet_t packet,
                                           char* buffer,
                                           uint32_t length);
VNET_API bool vnet_socket_inputstream_skip(struct packet_t* packet, 
                                           uint32_t length);
VNET_API bool vnet_socket_inputstream_encodeskip(
    struct packet_t* packet, 
    uint32_t length,
    struct endecode_param_t* endecode_param);
VNET_API int32_t vnet_socket_inputstream_fill(int32_t socketid, 
                                              struct packet_t* packet);
VNET_API void vnet_socket_inputstream_packetinit(struct packet_t* packet);
/*inputstream }*/

/*outputstream {*/
VNET_API uint32_t vnet_socket_outputstream_write(struct packet_t* packet, 
                                                 const char* buffer, 
                                                 uint32_t length);
VNET_API uint32_t vnet_socket_outputstream_encodewrite(
    struct packet_t* packet, 
    const char* buffer, 
    uint32_t length,
    struct endecode_param_t* endecode_param);
VNET_API uint32_t vnet_socket_outputstream_reallength(struct packet_t packet);
VNET_API int32_t vnet_socket_outputstream_flush(int32_t socketid, 
                                                struct packet_t* packet);
VNET_API bool vnet_socket_outputstream_resize(struct packet_t* packet, 
                                              int32_t size);

VNET_API void vnet_socket_outputstream_packetinit(struct packet_t* packet);
/*outputstream }*/

/*socket }*/

#endif //VNET_API_VNET_H_
