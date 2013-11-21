////////////////////////////////////////////////////////////////////////////////
//  Copyright(c) viticm@126.com
//
//  FileName    : pgame_util.h
//  Version     : 1.0
//  Creator     : viticm
//  Create Date : 2013-11-21 14:36:37
//  Comment     : 常用方法类 (!注意这里所有方法都为静态方法)
//
////////////////////////////////////////////////////////////////////////////////
#include "ptype.h"
#ifndef PAP_COMMON_PGAME_UTIL_H_
#define PAP_COMMON_PGAME_UTIL_H_
class PGameUtil {
 public:
   PGameUtil();
   ~PGameUtil();
   static char value_to_ascii(char in);
   static char ascii_to_value(char in);
   static bool binary_to_string(const char* in, uint in_length, char* out);
   static bool string_to_binary(const char* in, 
                                uint in_length, 
                                char* out, 
                                uint out_limit, 
                                uint &out_length);
   static void sleep(uint million_seconds);
}
#endif //PAP_COMMON_PGAME_UTIL_H_
