/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id channel.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏频道错误的定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_ERROR_CHANNEL_H_
#define PAP_COMMON_GAME_DEFINE_ERROR_CHANNEL_H_

namespace channel {

typedef enum {
  kExist = 0, //已经有频道
  kFull, //频道满了
  kNotExist, //频道不存在
  kMemberFull, //频道用户已满
  kMemberExist, //用户已在该频道
  kMemberNotExist, //用户不在该频道
} _enum;

}; //namespace channel

#endif //PAP_COMMON_GAME_DEFINE_ERROR_CHANNEL_H_
