/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-31 17:34:43
 * @uses server net model base config file
 */
#ifndef PAP_SERVER_COMMON_NET_CONFIG_H_
#define PAP_SERVER_COMMON_NET_CONFIG_H_

#include "common/base/type.h"

#define CONNECT_CACHESIZE_MAX 1024
#define CONNECT_KICKTIME 6000000 //超过该时间则断开连接
#define CONNECT_INCOME_KICKTIME 60000

typedef enum {
  kPacketFlagNone = 0,
  kPacketFlagRemove,
} packetflag_enum;

#endif //PAP_SERVER_COMMON_NET_CONFIG_H_
