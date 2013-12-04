/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-4 15:00:18
 * @uses standard config file.
 */
#ifndef PAP_SERVER_SHARE_MEMORY_DATA_CONFIG_H_
#define PAP_SERVER_SHARE_MEMORY_DATA_CONFIG_H_

#include "common/base/type.h"

const uint32_t kServerIdleTime = 5000; //服务器停止响应时间(毫秒)

typedef enum {
  kCmdUnkown,
  kCmdSaveAll,
  kCmdClearAll,
} command_enum;

typedef struct {
  command_enum type;
  union {
    int32_t int_param[6];
    float float_param[6];
    char string_param[24];
  };
} command_state_t;

struct command_config_t {
  command_state_t state;
  command_config_t() {
    state.type = kCmdUnkown;
  }
};

#endif //PAP_SERVER_SHARE_MEMORY_DATA_CONFIG_H_
