/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-22 18:00:40
 * @uses 模块配置文件，放置本模块内的宏定义以及需要用到的宏方法，每个模块都需要新建出这个文件来(如果有冲突，可以更名为define.h)
 *       即每个模块下需要有define.h或config.h里面放置公用定义以及方法
 */
#ifndef PAP_COMMON_SYS_CONFIG_H_
#define PAP_COMMON_SYS_CONFIG_H_

#include "common/base/type.h"

#define INTERFACE_NAME_MAX 20
#ifndef LINE_MAX
#define LINE_MAX 1024
#endif
#define SYSTEM_NAME_MAX 126
#define CPU_NAME_MAX 256

#endif //PAP_COMMON_SYS_CONFIG_H_

