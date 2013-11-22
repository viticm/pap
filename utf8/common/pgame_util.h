/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id ptype.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-22 19:36:44
 * @uses some useful functions class, just have static function.(no active function)
 */
#include "ptype.h"
#include "md5.h"
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
   static uint str_length(const char* str);
   static void char_swap(char* str, uint source, uint destination);
   static void simple_encrypt_decrypt( char* str, uint str_length, uint key_begin = 0); //use first is encrypt and next to decrypt
   static int charset_convert(const char* from, 
                              const char* to, 
                              char* save, 
                              int savelen, 
                              char* src, 
                              int srclen) ;

 private:
   static void password_swap_chars(char* str);
}

#endif //PAP_COMMON_PGAME_UTIL_H_
