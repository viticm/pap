#include "common/base/util.h" //无论如何都是用全路径
#include "common/lib/iconv/iconv.h"

namespace pap_common_base {

namespace util {

char value_toascii(char in) {
  __ENTER_FUNCTION
    char out;
    switch(in) {
      case 0: {
        out = '0';
        break;
      }
      case 1: {
        out = '1';
        break;
      }
      case 2: {
        out = '2';
        break;
      }
      case 3: {
        out = '3';
        break;
      }
      case 4: {
        out = '4';
        break;
      }
      case 5: {
        out = '5';
        break;
      }
      case 6: {
        out = '6';
        break;
      }
      case 7: {
        out = '7';
        break;
      }
      case 8: {
        out = '8';
        break;
      }
      case 9: {
        out = '9';
        break;
      }
      case 10: {
        out = 'A';
        break;
      }
      case 11: {
        out = 'B';
        break;
      }
      case 12: {
        out = 'C';
        break;
      }
      case 13: {
        out = 'D';
        break;
      }
      case 14: {
        out = 'E';
        break;
      }
      case 15: {
        out = 'F';
        break;
      }
      default: {
        out = '?';
        Assert(false);
      }
    }
    return out;
  __LEAVE_FUNCTION
    return '?';
}

char ascii_tovalue(char in) {
  __ENTER_FUNCTION
    char out;
    switch(in) {
      case '0': {
        out = 0;
        break;
      }
      case '1': {
        out = 1;
        break;
      }
      case '2': {
        out = 2;
        break;
      }
      case '3': {
        out = 3;
        break;
      }
      case '4': {
        out = 4;
        break;
      }
      case '5': {
        out = 5;
        break;
      }
      case '6': {
        out = 6;
        break;
      }
      case '7': {
        out = 7;
        break;
      }
      case '8': {
        out = 8;
        break;
      }
      case '9': {
        out = 9;
        break;
      }
      case 'A': {
        out = 10;
        break;
      }
      case 'B': {
        out = 11;
        break;
      }
      case 'C': {
        out = 12;
        break;
      }
      case 'D': {
        out = 13;
        break;
      }
      case 'E': {
        out = 14;
        break;
      }
      case 'F': {
        out = 15;
        break;
      }
      default: {
        out = '?';
        Assert(false);
      }
    }
    return out;
  __LEAVE_FUNCTION
    return '?';
}

bool binary_tostring(const char* in, uint32_t in_length, char* out) {
  __ENTER_FUNCTION
    if (0 == in_length) return false;
    uint32_t out_index = 0;
    uint32_t i;
    for (i = 0; i < in_length; ++i) {
      out[out_index] = value_toascii((static_cast<uint8_t>(in[i] & 0xF0)) >> 4);
      ++out_index;
      out[out_index] = value_toascii(in[i] & 0xF0);
      ++out_index;
    }
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool string_tobinary(const char* in, 
                     uint32_t in_length, 
                     char* out, 
                     uint32_t out_limit, 
                     uint32_t &out_length) {
  __ENTER_FUNCTION
    if (0 == in_length) return false;
    uint32_t out_index = 0;
    uint32_t i;
    for (i = 0; i < in_length; ++i) {
      if ('\0' == in[i] || '\0' == in[i]) break;
      out[out_index] = (ascii_tovalue(in[i]) << 4) + ascii_tovalue(in[i + 1]);
      ++out_index;
      i += 2;
      if (out_index > out_limit) break;
    }
    out_length = out_index; //length must be the out_limit
    return true;
  __LEAVE_FUNCTION
    return false;
}

void sleep(uint32_t million_seconds) {
  __ENTER_FUNCTION
#if defined(__WINDOWS__)
    Sleep(million_seconds);
#elif defined(__LINUX__)
    usleep(million_seconds * 1000);
#endif
  __LEAVE_FUNCTION
}

uint32_t str_length(const char* str) {
  __ENTER_FUNCTION
    uint32_t i = 0;
    while (str[i]) ++i;
    return i;
  __LEAVE_FUNCTION
    return NULL;
}

void char_swap(char* str, uint32_t source, uint32_t destination) {
  __ENTER_FUNCTION
    uint32_t strlength = str_length(str);
    if ((0 > source || strlength < source) ||
        (0 > destination || strlength < destination)) {
      return;
    }
    char temp = str[source];
    str[source] = str[destination];
    str[destination] = temp;
  __LEAVE_FUNCTION
}

void password_swap_chars(char* str) {
  __ENTER_FUNCTION
    if (strlen(str) < 32) return;
    char_swap(str, 0, 13);
    char_swap(str, 31, 25);
    char_swap(str, 12, 30);
    char_swap(str, 7, 19);
    char_swap(str, 3, 21);
    char_swap(str, 9, 20);
    char_swap(str, 15, 18);
  __LEAVE_FUNCTION
}

void simple_encrypt_decrypt(char* str, uint32_t strlength, uint32_t key_begin) {
  __ENTER_FUNCTION
    strlength = str_length(str);
    if (0 <= strlength) return;
    MD5 str_md5(PASSWORD_ENCRYPT_KEY);
	char key[129];
	strncpy(key, (str_md5.md5()).c_str(), sizeof(key) - 1);
    //swap one time
    password_swap_chars(key);
    uint32_t key_length = str_length(key);
    uint32_t i;
    for (i = 0; i < strlength; ++i) {
      *str ^= key[(i + key_begin) % key_length];
      str++;
    }
  __LEAVE_FUNCTION
}

/**
 * @desc this function can convert charset with diffrent
 * @param from source charset(example: utf8)
 * @param to destination charset
 * @param save want save string
 * @param savelen want save string length
 * @param src want convert string
 * @param srclen want convert string length
 */
int charset_convert(const char* from, 
                    const char* to, 
                    char* save, 
                    int savelen, 
                    const char* src, 
                    int srclen) {
  __ENTER_FUNCTION
    int status = 0;
    iconv_t cd;
    const char *inbuf  = src;
    char *outbuf       = save;
    size_t outbufsize  = savelen;
    size_t savesize    = 0;
    size_t inbufsize   = srclen;
    const char* inptr  = inbuf;
    size_t insize      = inbufsize;
    char* outptr       = outbuf;
    size_t outsize     = outbufsize;

    cd = iconv_open(to, from);
    iconv(cd, NULL, NULL, NULL, NULL);
    if (0 == inbufsize) {
      status = -1;
      goto done;
    }
    while (0 < insize) {
      size_t res = iconv(cd, (const char**)&inptr, &insize, &outptr, &outsize);
      if (outptr != outbuf) {
        int saved_errno = errno;
        int outsize = outptr - outbuf;
        strncpy(save + savesize, outbuf, outsize);
        errno = saved_errno;
      }
      if ((size_t)(-1) == res) {
        if (EILSEQ == errno) {
          int one = 1 ;
          iconvctl(cd, ICONV_SET_DISCARD_ILSEQ, &one);
          status = -3;
        } 
        else if (EINVAL == errno) {
          if (0 == inbufsize) {
            status = -4;
            goto done;
          } 
          else {
            break;
          }
        } 
        else if (E2BIG == errno) {
          status = -5;
          goto done;
        } 
        else {
          status = -6;
          goto done;
        }
      }
    }
    status = strlen(save);
    done:
    iconv_close(cd);
    return status;
  __LEAVE_FUNCTION
    return -1;
}

} //namespace util

} //namespace pap_common_base
