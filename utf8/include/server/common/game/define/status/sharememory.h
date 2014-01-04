/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id sharememory.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 11:06:39
 * @uses 游戏服务器共享内存状态的所有定义
 */
#ifndef PAP_SERVER_COMMON_GAME_DEFINE_STATUS_SHAREMEMORY_H_
#define PAP_SERVER_COMMON_GAME_DEFINE_STATUS_SHAREMEMORY_H_

namespace sharememory {

typedef enum {
  kUseNever = 0, //从未使用过
  kUseServer = 1, //server 占用
  kUseServerHasClean = 2, //server 正常shutdown ，已经清除
  kUseWorld = 3, //world 占用
  kUseWorldHasClean = 3, //world 正常shutdown ，已经清除
} use_enum;

}; //namespace share_memory

#endif //PAP_SERVER_COMMON_GAME_DEFINE_STATUS_SHAREMEMORY_H_

