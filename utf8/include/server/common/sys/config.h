/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-22 18:00:40
 * @uses server sys class or namespace
 */

#ifndef PAP_SERVER_COMMON_SYS_CONFIG_H_
#define PAP_SERVER_COMMON_SYS_CONFIG_H_

#include "common/base/type.h"

typedef enum {
  kCmdModelClearAll = 1,
  kCmdModelLoadDump = 2,
} cmd_model_enum; //命令行模式

extern int32_t g_cmd_model;

#endif //PAP_SERVER_COMMON_SYS_CONFIG_H_
