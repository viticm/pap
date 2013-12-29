#define VNET_CORE //export source file need first define this macros
#include "api/vnet.h"
#include "socket/base.h"
#include "socket/inputstream.h"
#include "socket/outputstream.h"

/*socket {*/

/*base {*/
VNET_API int32_t vnet_socketbase_create(int32_t type) {
  int32_t result = socketbase_create(type);
  return result;
}

VNET_API bool vnet_socketbase_connect(int32_t socketid, 
                                 const char* host, 
                                 uint32_t port) {
  bool result = socketbase_connect(socketid, host, port);
  return result;
}

VNET_API int32_t vnet_socketbase_send(int32_t socketid,
                                 const void* buffer, 
                                 uint32_t length, 
                                 uint32_t flag) {
  int32_t result = socketbase_send(socketid, buffer, length, flag);
  return result;
}

VNET_API int32_t vnet_socketbase_receive(int32_t socketid,
                                         void* buffer, 
                                         uint32_t length, 
                                         uint32_t flag) {
  int32_t result = socketbase_receive(socketid, buffer, length, flag);
  return result;
}

VNET_API uint32_t vnet_socketbase_available(int32_t socketid) {
  uint32_t result = socketbase_available(socketid);
  return result;
}

VNET_API int32_t vnet_socketbase_accept(int32_t socketid, 
                                        struct sockaddr* addr, 
                                        uint32_t* addrlength) {
  int32_t result = socketbase_accept(socketid, addr, addrlength);
  return result;
}

VNET_API bool vnet_socketbase_bind(int32_t socketid, uint32_t port) {
  bool result = socketbase_bind(socketid, port);
  return result;
}

VNET_API bool vnet_socketbase_listen(int32_t socketid, int32_t backlog) {
  bool result = socketbase_listen(socketid, backlog);
  return result;
}

VNET_API uint32_t vnet_socketbase_getlinger(int32_t socketid) {
  uint32_t result = socketbase_getlinger(socketid);
  return result;
}

VNET_API bool vnet_socketbase_setlinger(int32_t socketid, 
                                        uint32_t lingertime) {
  bool result = socketbase_setlinger(socketid, lingertime);
  return result;
}

VNET_API bool vnet_socketbase_is_reuseaddr(int32_t socketid) {
  bool result = socketbase_is_reuseaddr(socketid);
  return result;
}

VNET_API bool vnet_socketbase_set_reuseaddr(int32_t socketid, bool on) {
  bool result = socketbase_set_reuseaddr(socketid, on);
  return result;
}

VNET_API bool vnet_socketbase_iserror(int32_t socketid) {
  bool result = socketbase_iserror(socketid);
  return result;
}

VNET_API bool vnet_socketbase_is_nonblocking(int32_t socketid) {
  bool result = socketbase_is_nonblocking(socketid);
  return result;
}

VNET_API bool vnet_socketbase_set_nonblocking(int32_t socketid, bool on) {
  bool result = socketbase_set_nonblocking(socketid, on);
  return result;
}

VNET_API uint32_t vnet_socketbase_getreceive_buffersize(int32_t socketid) {
  uint32_t result = socketbase_getreceive_buffersize(socketid);
  return result;
}

VNET_API bool vnet_socketbase_setreceive_buffersize(int32_t socketid, 
                                                    uint32_t size) {
  bool result = socketbase_setreceive_buffersize(socketid, size);
  return result;
}
/*base }*/


/*inputstream {*/
VNET_API uint32_t vnet_socket_inputstream_read(struct packet_t* packet, 
                                               char* buffer, 
                                               uint32_t length) {
  uint32_t result = socket_inputstream_read(packet, buffer, length);
  return result;
}

VNET_API uint32_t vent_socket_inputstream_encoderead(
    struct packet_t* packet, 
    char* buffer, 
    uint32_t length,
    struct endecode_param_t* endecode_param) {
  uint32_t result = socket_inputstream_encoderead(packet, 
                                                  buffer, 
                                                  length,
                                                  endecode_param);
  return result;
}

VNET_API bool vent_socket_inputstream_resize(struct packet_t* packet, 
                                             int32_t size) {
  bool result = socket_inputstream_resize(packet, size);
  return result;
}

VNET_API uint32_t vnet_socket_inputstream_reallength(struct packet_t packet) {
  uint32_t result = socket_inputstream_reallength(packet);
  return result;
}

VNET_API bool vnet_socket_inputstream_peek(struct packet_t packet,
                                           char* buffer,
                                           uint32_t length) {
  bool result = socket_inputstream_peek(packet, buffer, length);
  return result;
}

VNET_API bool vnet_socket_inputstream_skip(struct packet_t* packet, 
                                           uint32_t length) {
  bool result = socket_inputstream_skip(packet, length);
  return result;
}

VNET_API bool vnet_socket_inputstream_encodeskip(
    struct packet_t* packet, 
    uint32_t length,
    struct endecode_param_t* endecode_param) {
  bool result = socket_inputstream_encodeskip(packet, length, endecode_param);
  return result;
}

VNET_API int32_t vnet_socket_inputstream_fill(int32_t socketid, 
                                              struct packet_t* packet) {
  int32_t result = socket_inputstream_fill(socketid, packet);
  return result;
}

VNET_API void vnet_socket_inputstream_packetinit(struct packet_t* packet) {
  socket_inputstream_packetinit(packet);
}
/*inputstream }*/

/*outputstream {*/
VNET_API uint32_t vnet_socket_outputstream_write(struct packet_t* packet, 
                                                 const char* buffer, 
                                                 uint32_t length) {
  uint32_t result = socket_outputstream_write(packet, buffer, length);
  return result;
}

VNET_API uint32_t vent_socket_outputstream_encodewrite(
    struct packet_t* packet, 
    const char* buffer, 
    uint32_t length,
    struct endecode_param_t* endecode_param) {
  uint32_t result = socket_outputstream_encodewrite(packet, 
                                                    buffer, 
                                                    length, 
                                                    endecode_param);
  return result;
}

VNET_API uint32_t vent_socket_outputstream_reallength(struct packet_t packet) {
  uint32_t result = socket_outputstream_reallength(packet);
  return result;
}

VNET_API int32_t vent_socket_outputstream_flush(int32_t socketid, 
                                           struct packet_t* packet) {
  int32_t result = socket_outputstream_flush(socketid, packet);
  return result;
}

VNET_API bool vnet_socket_outputstream_resize(struct packet_t* packet, 
                                              int32_t size) {
  bool result = socket_outputstream_resize(packet, size);
  return result;
}
/*outputstream }*/

/*socket }*/

