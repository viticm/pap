#include "socket/endecode.h"

bool socketendecode_make(struct endecode_param_t* endecode_param) {
  unsigned char const* in = (*endecode_param).in;
  if(NULL == in) {
    return false;
  }
  uint32_t insize = (*endecode_param).insize;
  if(insize <= 0) {
    return false;
  }
  unsigned char* out = endecode_param->out;
  if(NULL == out) {
    return false;
  }
  uint32_t outsize = (*endecode_param).outsize;
  if(outsize <= 0 || outsize < insize) {
    return false;
  }
  unsigned char const* key = (*endecode_param).key;
  if(NULL == key) {
    return false;
  }
  int32_t keysize = (*endecode_param).keysize;
  if(keysize <= 0) {
    return false;
  }
  int32_t keyindex = (*endecode_param).param[0];
  int32_t index;
  for(index = 0; insize > index; ++index) {
    out[index] = in[index] ^ key[keyindex];
    ++keyindex;
    if(keyindex >= keysize) {
      keyindex -=keyindex;
    }
  }
  endecode_param->param[0] = keyindex;
  return true;
}

bool socketendecode_skip(struct endecode_param_t* endecode_param, 
                         int32_t length) {
  uint32_t keysize = (*endecode_param).keysize;
  if(keysize == 0) {
    return false;
  }
  int32_t keyindex = (*endecode_param).param[0];
  int32_t index;
  for(index = 0; index < length; ++index) {
    ++keyindex;
    if(keyindex >= keysize) {
      keyindex -= keysize;
    }
  }
  endecode_param->param[0] = keyindex;
  return true;
}
