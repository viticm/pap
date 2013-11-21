////////////////////////////////////////////////////////////////////////////////
//  Copyright(c) viticm@126.com
//
//  FileName    : ptype.h
//  Version     : 1.0
//  Creator     : viticm
//  Create Date : 2013-11-20 12:12:49
//  Comment     : 数据类型定义 基本宏定义
//
////////////////////////////////////////////////////////////////////////////////
#ifndef PAP_COMMON_PTYPE_H_
#define PAP_COMMON_PTYPE_H_

#if defined(GAME_CLIENT)
#define __ENTER_FUNCTION 
#define __LEAVE_FUNCTION
#endif
//network size define
#ifndef FD_SETSIZE 
#define FD_SETSIZE 4906
#endif
//system include
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <string>
#include <iostream>
#include <fstream>
#include "passert.h"
//warning the namespace can't use like this, but it must
using namespace std;

//基本数据类型定义
typedef unsigned char ubyte; //0~255
typedef char byte; //-128~127
typedef unsigned int uint;
typedef unsigned short ushort;

#define IP_SIZE 24 //max ip size
#define INVALID_HANDLE -1 
#define INVALID_ID -1
#define INVALID_TAB_PARAM_ID (-9999) //invalid id in excel param
#ifndef _MAX_PATH //max file path
#define _MAX_PATH 260
#endif

#ifndef UINT_MAX
#define UINT_MIN (0)
#define UINT_MAX (0xFFFFFFFF)
#endif

#ifndef INT_MAX
#define INT_MIN (-2147483648)
#define INT_MAX	(2147483647)
#endif

#ifndef DWORD_MAX
#define DWORD_MIN UINT_MIN
#define DWORD_MAX UINT_MAX
#endif

#ifndef USHORT_MAX
#define USHORT_MIN (0)
#define USHORT_MAX (0xFFFF)
#endif

#ifndef SHORT_MAX
#define SHORT_MIN (-32768)
#define SHORT_MAX (32767)
#endif

#ifndef WORD_MAX
#define WORD_MIN USHORT_MIN
#define WORD_MAX USHORT_MAX
#endif

#ifndef UCHAR_MAX
#define UCHAR_MIN (0)
#define UCHAR_MAX (0xFF)
#endif

#ifndef CHAR_MAX
#define CHAR_MIN (-128)
#define CHAR_MAX (127)
#endif

#ifndef BYTE_MAX
#define BYTE_MIN UCHAR_MIN
#define BYTE_MAX UCHAR_MAX
#endif

#if defined(NDEBUG)
    #define __ENTER_FUNCTION_FOXNET if(1){
    #define __LEAVE_FUNCTION_FOXNET }
#else
    #define __ENTER_FUNCTION_FOXNET if(1){
    #define __LEAVE_FUNCTION_FOXNET }
#endif

//根据指针值删除内存
#ifndef SAFE_DELETE
#if defined(__WINDOWS__)
#define SAFE_DELETE(x)	if((x)!=NULL) { Assert(_CrtIsValidHeapPointer(x));delete (x); (x)=NULL; }
#elif defined(__LINUX__)
#define SAFE_DELETE(x)	if((x)!=NULL) { delete (x); (x)=NULL; }
#endif
#endif
//根据指针值删除数组类型内存
#ifndef SAFE_DELETE_ARRAY
#if defined(__WINDOWS__)
#define SAFE_DELETE_ARRAY(x) if((x)!=NULL) { Assert(_CrtIsValidHeapPointer(x));delete[] (x); (x)=NULL; }
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
//根据指针调用free接口
#ifndef SAFE_FREE
#define SAFE_FREE(x) if((x)!=NULL) { free(x); (x)=NULL; }
#endif
//根据指针调用Release接口
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if((x)!=NULL) { (x)->Release(); (x)=NULL; }
#endif

#if defined(__WINDOWS__)
    #pragma warning (disable: 4786)
    #include <Windows.h>
    #include "crtdbg.h"
    #if defined(NDEBUG)
        #define __ENTER_FUNCTION {try{
        #define __LEAVE_FUNCTION }catch(...){AssertSpecial(FALSE,__FUNCTION__);}}
    #else
        #define __ENTER_FUNCTION {try{
        #define __LEAVE_FUNCTION }catch(...){AssertSpecial(FALSE,__FUNCTION__);}}
    #endif
    // add by viticm, fast output some debug info 
    #define LERR(...) {\
        char buffer[2048]; sprintf(buffer, __VA_ARGS__); \
        buffer[2047] = '\0'; \ //防止越界
        const char* start  = "[ERROR...]"; \
        const char* end    = "[...ERROR]\r\n"; \
        size_t format_length = sizeof(start) + sizeof(buffer) + sizeof(end); \
        char* format_str    = new CHAR[format_length + 1]; \
        strcpy(format_str, start); strcat(format_str, buffer); strcat(format_str, end); \
        printf(format_str); \
        delete[] format_str; \
        } 
    // common define
    #define LF "\r\n"
#elif defined (__LINUX__)    //linux
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <pthread.h>
    #include <cmath>
    #define __ENTER_FUNCTION {try{
    #define __LEAVE_FUNCTION }catch(...){AssertSpecial(FALSE,__PRETTY_FUNCTION__);}}
    // add by viticm, fast output some debug info 
    #define LERR(...) {\
        char buffer[2048]; sprintf(buffer, __VA_ARGS__); \
        buffer[2047] = '\0'; \
        const char* start = "\e[0;31;1m"; \
        const char* end  = "\e[0m\n"; \
        size_t format_length = sizeof(start) + sizeof(buffer) + sizeof(end); \
        char* format_str = new CHAR[format_length + 1]; \
        strcpy(format_str, start); strcat(format_str, buffer); strcat(format_str, end); \
        printf(format_str); \
        delete[] format_str; \
        } 
    // common define
    #define LF "\n"
#endif 

#endif //PAP_COMMON_PTYPE_H_
