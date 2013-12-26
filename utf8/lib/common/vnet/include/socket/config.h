/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vnet
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-25 9:44:03
 * @uses vnet socket model config file
 */
#ifndef VNET_SOCKET_CONFIG_H_
#define VNET_SOCKET_CONFIG_H_

#include "base/type.h"

typedef struct {
  char* buffer;
  uint32_t bufferlength;
  uint32_t bufferlength_max;
  uint32_t headlength;
  uint32_t taillength;
} packet_t;

typedef struct {
  unsigned char* in;
  uint32_t insize;
  unsigned char* out;
  uint32_t outsize;
  unsigned const* key;
  uint32_t param[2];
} endecode_param_t;

#endif //VNET_SOCKET_CONFIG_H_
