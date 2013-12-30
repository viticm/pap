#include "socket/endecode.h"

bool socketendecode_make(struct endecode_param_t* endecode_param) {
  
  unsigned char const* in;
  uint32_t insize;
  unsigned char* out;
  uint32_t outsize;
  unsigned char const* key;
  uint32_t keysize;
  int32_t keyindex;
  int32_t index;
  in = (*endecode_param).in;
  if(NULL == in) {
    return false;
  }
  insize = (*endecode_param).insize;
  if(insize <= 0) {
    return false;
  }
  out = endecode_param->out;
  if(NULL == out) {
    return false;
  }
  outsize = (*endecode_param).outsize;
  if(outsize <= 0 || outsize < insize) {
    return false;
  }
  key = (*endecode_param).key;
  if(NULL == key) {
    return false;
  }
  keysize = (*endecode_param).keysize;
  if(keysize <= 0) {
    return false;
  }
  keyindex = (*endecode_param).param[0];
  for(index = 0; (int32_t)insize > index; ++index) {
    out[index] = in[index] ^ key[keyindex];
    ++keyindex;
    if(keyindex >= (int32_t)keysize) {
      keyindex -=keyindex;
    }
  }
  endecode_param->param[0] = keyindex;
  return true;
}

bool socketendecode_skip(struct endecode_param_t* endecode_param, 
                         int32_t length) {
  uint32_t keysize = 0;
  int32_t keyindex = 0;
  int32_t index = 0;
  keysize = (*endecode_param).keysize;
  if(keysize == 0) {
    return false;
  }
  keyindex = (*endecode_param).param[0];
  for(index = 0; index < length; ++index) {
    ++keyindex;
    if(keyindex >= (int32_t)keysize) {
      keyindex -= keysize;
    }
  }
  endecode_param->param[0] = keyindex;
  return true;
}
