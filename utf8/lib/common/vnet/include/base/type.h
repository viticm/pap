/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vnet
 * $Id type.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-25 9:44:03
 * @uses base define for vnet
 *       use in linux you need define macro __LINUX__
 *       use in windows you need define macro __WINDOWS__
 */
#ifndef VNET_BASE_TYPE_H_
#define VNET_BASE_TYPE_H_

#if defined(GAME_CLIENT)
#define __ENTER_FUNCTION 
#define __LEAVE_FUNCTION
#endif
//network size define
#ifndef FD_SETSIZE 
#define FD_SETSIZE 4906
#endif

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif //use c99

//system include
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <stdarg.h>
#if defined(__WINDOWS__) //diffrent system include
#pragma warning (disable: 4786)
#include <windows.h>
#include <crtdbg.h>
#elif defined(__LINUX__)
#include <string.h>
#include <sys/types.h>
#endif

#include "base/io.h"

#ifndef IP_SIZE
#define IP_SIZE 24 //max ip size
#endif

#if defined(__LINUX__)
#define HANDLE_INVALID (-1)
#elif defined(__WINDOWS__)
#define HANDLE_INVALID ((VOID*)0)
#endif

#ifndef ID_INVALID
#define ID_INVALID (-1)
#endif

#ifndef INDEX_INVALID
#define INDEX_INVALID (-1)
#endif

#ifndef VNET_CORE
#define VNET_CORE
#endif

#ifndef bool
#define bool uint8_t
#define true 1
#define false 0
#endif

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef BYTE_MAX
#define BYTE_MIN UCHAR_MIN
#define BYTE_MAX UCHAR_MAX
#endif

// common define
#if defined(__LINUX__)
#define LF "\r\n"
#elif defined(__WINDOWS__)
#define LF "\n"
#endif

//c output functions
#if defined(__WINDOWS__)
#ifndef snprintf
#define snprintf _snprintf
#endif
#ifndef stricmp
#define stricmp _stricmp
#endif
#ifndef vsnprintf
#define vsnprintf _vsnprintf
#endif
#elif defined(__LINUX__)
#ifndef stricmp
#define stricmp strcasecmp
#endif
#endif

#ifndef ERRORPRINTF
#define ERRORPRINTF(format,...) baseio_perror(format, __VA_ARGS__)
#endif

#ifndef WARNINGPRINTF
#define WARNINGPRINTF(format,...) baseio_pwarn(format, __VA_ARGS__)
#endif

#ifndef USE_PARAM
#define USE_PARAM(x) if (!x) {}
#endif
//根据指针调用free接口
#ifndef SAFE_FREE
#define SAFE_FREE(x) if((x)!=NULL) { free(x); (x)=NULL; }
#endif
//根据指针调用Release接口
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if((x)!=NULL) { (x)->Release(); (x)=NULL; }
#endif

#endif //VNET_BASE_TYPE_H_
