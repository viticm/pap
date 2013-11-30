/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id ptype.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-22 19:36:44
 * @uses some useful base util functions 
 */
#ifndef PAP_COMMON_BASE_UTIL_H_
#define PAP_COMMON_BASE_UTIL_H_

#include "common/base/md5.h"
#include "common/base/config.h"

namespace pap_common_base {

namespace util {

char value_toascii(char in);
char ascii_tovalue(char in);
bool binary_tostring(const char* in, uint in_length, char* out);
bool string_tobinary(const char* in, 
                     uint32_t in_length, 
                     char* out, 
                     uint32_t out_limit, 
                     uint32_t &out_length);
void sleep(uint32_t million_seconds);
uint32_t str_length(const char* str);
void char_swap(char* str, uint source, uint32_t destination);
void simple_encrypt_decrypt( char* str, uint32_t str_length, uint32_t key_begin = 0); //use first is encrypt and next to decrypt
int charset_convert(const char* from, 
                    const char* to, 
                    char* save, 
                    int savelen, 
                    char* src, 
                    int srclen) ;
void password_swap_chars(char* str); //string will more than 32

} //namespace util

} //namespace pap_common_base

#endif //PAP_COMMON_BASE_UTIL_H_
