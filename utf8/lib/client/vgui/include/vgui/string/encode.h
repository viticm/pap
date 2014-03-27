/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id encode.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-27 10:11:37
 * @uses vgui string encode module
 */
#ifndef VGUI_STRING_ENCODE_H_
#define VGUI_STRING_ENCODE_H_

#include "vgui/config.h"

namespace vgui_string {

namespace encode {

//设置代码页
void set_code_page(int32_t code_page);
int32_t get_code_page();
//utf<->mbcs
void mbcs_to_utf8(const std::string& in, std::string& out);
void utf8_to_mbcs(const std::string& in, std::string& out);
int32_t encode_ucs_to_utf8(const wchar_t* src, 
                           unsigned char* dest, 
                           int32_t dest_len, 
                           int32_t src_len = 0);
int32_t encode_utf8_to_ucs(const unsigned char* src,
                           wchar_t* dest, 
                           int32_t dest_len, 
                           int32_t src_len = 0);
void mbcs_to_ucs16(int32_t code_page, 
                   const char* mbcs_string, 
                   int32_t mbcs_string_size, 
                   wchar_t* wchar_buf, 
                   int32_t wchar_buf_size);
void ucs16_to_mbcs(int32_t code_page, 
                   const wchar_t* wchar_string, 
                   int32_t wchar_char_counts, 
                   char* mbcs_buf, 
                   int32_t mbcs_buf_size);

}; //namespace encode

}; //namespace vgui_string

#endif //VGUI_STRING_ENCODE_H_
