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
#include <math.h>
#include <stdarg.h>
#if defined(__WINDOWS__) //diffrent system include
#pragma warning (disable: 4786)
#include <windows.h>
#include <crtdbg.h>
#elif defined(__LINUX__)
#include <string.h>
#include <sys/types.h>
#include <cmath>
#endif

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

#ifndef bool
#define bool uint8_t
#define true 1
#define false 0
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

//根据指针值删除内存
#ifndef SAFE_DELETE
#if defined(__WINDOWS__)
#define SAFE_DELETE(x)	if((x)!=NULL) { Assert(_CrtIsValidHeapPointer(x)); \
                        delete (x); (x)=NULL; }
#elif defined(__LINUX__)
#define SAFE_DELETE(x)	if((x)!=NULL) { delete (x); (x)=NULL; }
#endif
#endif
//根据指针值删除数组类型内存 
//其中注意_CrtIsValidHeapPointer前的定义，在relase需要定义NDEBUG
#ifndef SAFE_DELETE_ARRAY
#if defined(__WINDOWS__)
#define SAFE_DELETE_ARRAY(x) if((x)!=NULL) { \
                             Assert(_CrtIsValidHeapPointer(x)); \
                             delete[] (x); (x)=NULL; }
#elif defined(__LINUX__)
#define SAFE_DELETE_ARRAY(x) if((x)!=NULL) { delete[] (x); (x)=NULL; }
#endif
#endif

//删除指针型数据(应尽量使用SAFE_DELETE_ARRAY)
#ifndef DELETE_ARRAY
#if defined(__WINDOWS__)
#define DELETE_ARRAY(x)	if((x)!=NULL) { delete[] (x); (x)=NULL; }
#elif defined(__LINUX__)
#define DELETE_ARRAY(x)	if((x)!=NULL) { delete[] (x); (x)=NULL; }
#endif
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

#if defined(__WINDOWS__) //normal functions
// add by viticm, fast output some debug info 
#ifndef PRINTFERROR
#define PRINTFERROR(...) {\
  char buffer[2048]; sprintf(buffer, __VA_ARGS__); \
  buffer[2048] = '\0'; \
  const char* start  = "[ERROR...]"; \
  const char* end    = "[...ERROR]"LF""; \
  size_t format_length = sizeof(start) + sizeof(buffer) + sizeof(end); \
  char* format_str    = new char[format_length + 1]; \
  strcpy(format_str, start); strcat(format_str, buffer); \
  strcat(format_str, end);\
  printf(format_str); \
  delete[] format_str; \
}
#endif
#elif defined(__LINUX__)    //linux
#ifndef PRINTFERROR
#define PRINTFERROR(...) {\
  char buffer[2048]; sprintf(buffer, __VA_ARGS__); \
  buffer[2047] = '\0'; \
  const char* start = "\e[0;31;1m"; \
  const char* end  = "\e[0m"LF""; \
  size_t format_length = sizeof(start) + sizeof(buffer) + sizeof(end); \
  char* format_str = new char[format_length + 1]; \
  strcpy(format_str, start); strcat(format_str, buffer); \
  strcat(format_str, end); \
  printf(format_str); \
  delete[] format_str; \
}
#endif
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

#endif //VNET_BASE_TYPE_H_