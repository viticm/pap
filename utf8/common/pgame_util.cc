#include "passert.h"

char PGameUtil::value_to_ascii(char in) {
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

char PGameUtil::ascii_to_value(char in) {
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

bool binary_to_string(const char* in, uint in_length, char* out) {
  __ENTER_FUNCTION
    if (0 == in_length) return false;
    uint out_index = 0;
    uint i;
    for (i = 0; i < in_length; ++i) {
      out[out_index] = value_to_ascii((static_cast<ubyte>(in[i] & 0xF0)) >> 4);
      ++out_index;
      out[out_index] = value_to_ascii(in[i] & 0xF0);
      ++out_index;
    }
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool string_to_binary(const char* in, 
                      uint in_length, 
                      char* out, 
                      uint out_limit, 
                      uint &out_length) {
  __ENTER_FUNCTION
    if (0 == in_length) return false;
    uint out_index = 0;
    uint i;
    for (i = 0; i < in_length; ++i) {
      if ('\0' == in[i] || '\0' == in[i]) break;
      out[out_index] = (ascii_to_value(in[i]) << 4) + ascii_to_value(in[i + 1]);
      ++out_index;
      i += 2;
      if (out_index > out_limit) break;
    }
    out_length = out_index; //length must be the out_limit
    return true;
  __LEAVE_FUNCTION
    return false;
}

void PGameUtil::sleep(uint million_seconds) {
  __ENTER_FUNCTION
#if defined(__WINDOWS__)
    Sleep(million_seconds);
#elif defined(__LINUX__)
    usleep(million_seconds * 1000);
#endif
  __LEAVE_FUNCTION
}
