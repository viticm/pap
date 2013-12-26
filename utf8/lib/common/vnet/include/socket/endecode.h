/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vnet
 * $Id endecode.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-26 11:37:45
 * @uses vnet socket packet encode and decode model
 *       cn: 简单的加密模块，提供对数据的加解密处理
 */
#ifndef VNET_SOCKET_ENDECODE_H_
#define VNET_SOCKET_ENDECODE_H_

#include "socket/config.h"

bool socketendecode_make(struct endecode_param_t* endecode_param);
bool socketendecode_skip(struct endecode_param_t* endecode_param, 
                         int32_t length);

#endif //VNET_SOCKET_ENDECODE_H_
