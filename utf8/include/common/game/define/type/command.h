/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id command.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏命令类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_COMMAND_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_COMMAND_H_

namespace command { //指令分类

typedef enum {
  kGmNone = 0, //空指令
} gm_enum; //GM指令，后期考虑实现该功能

}; //namespace command

#endif //PAP_COMMON_GAME_DEFINE_TYPE_COMMAND_H_
