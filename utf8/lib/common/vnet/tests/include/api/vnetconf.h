/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vnet
 * $Id vnetconf.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-27 17:15:18
 * @uses the vnet api config(you can include this file in you code)
 */
#ifndef VNET_API_VNETCONF_H_
#define VNET_API_VNETCONF_H_

#include <stdint.h>

#ifndef bool
#define bool uint8_t
#define true 1
#define false 0
#endif

/*
@@ VNET_API is a mark for all core API functions.
@@ VNETLIB_API is a mark for all auxiliary library functions.
@@ VNETMOD_API is a mark for all standard library opening functions.
** CHANGE them if you need to define those functions in some special way.
** For instance, if you want to create one Windows DLL with the core and
** the libraries, you may want to use the following definition (define
** VNET_BUILD_AS_DLL to get it).
*/

#if defined(VNET_BUILD_AS_DLL) /* { */ 

#if defined(VNET_CORE) || defined(VNET_LIB) /* { */
#define VNET_API __declspec(dllexport)
#else /* }{ */
#define VNET_API __declspec(dllimport)
#endif

#else  /* }{ */ 

#define VNET_API extern

#endif /* } */

/* more often than not the libs go together with the core */
#define VNETLIB_API  VNET_API
#define VNETMOD_API  VNETLIB_API


/* all macros and defines */
struct packet_t {
  char* buffer;
  uint32_t bufferlength;
  uint32_t bufferlength_max;
  uint32_t headlength;
  uint32_t taillength;
};

struct endecode_param_t {
  unsigned char* in;
  uint32_t insize;
  unsigned char* out;
  uint32_t outsize;
  unsigned char const* key;
  uint32_t keysize;
  uint32_t param[2];
};

struct mytest_t {
  char* buffer1;
};

#define SOCKETINPUT_BUFFERSIZE_DEFAULT (64*1024) //default size
#define SOCKETINPUT_DISCONNECT_MAXSIZE (96*1024) //if buffer more than it,
                                                 //will disconnect this socket.
#define SOCKETOUTPUT_BUFFERSIZE_DEFAULT (8192)     //default size
#define SOCKETOUTPUT_DISCONNECT_MAXSIZE (100*1024)//if buffer more than it,
                                                  //will disconnect this socket.
#ifndef SOCKET_INVALID
#define SOCKET_INVALID -1
#endif

#if defined(__LINUX__)
#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif
#endif

#endif //VNET_API_VNETCONF_H_
