/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id channel.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 频道操作结果所有定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_RESULT_CHANNEL_H_
#define PAP_COMMON_GAME_DEFINE_RESULT_CHANNEL_H_

namespace channel {

typedef enum {
  kCreate, //创建
  kAddMember, //添加成员
  kDismiss, //解散
  kKickMember, //踢出成员
  kCount,
} _enum;
 
}; //namespace channel

#endif //PAP_COMMON_GAME_DEFINE_RESULT_CHANNEL_H_
