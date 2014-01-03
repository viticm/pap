/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id chat.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏聊天类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_CHAT_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_CHAT_H_

namespace chat {

typedef enum {
  kInvalid = -1,
  kNormal, //普通说话消息
  kTeam, //队伍消息
  kScene, //场景消息
  kTell, //私聊消息
  kSystem, //系统消息
  kChannel, //频道消息
  kGuild, //帮会消息
  kMeiPai, //门派消息
  kClient, //客户端专用
  kCount,
} _enum;

typedef enum {
  kConsumeNone = -1, //不需要消耗
  kConsumeVigor = 0, //消耗活力
} consume_enum;

}; //namespace chat

#endif //PAP_COMMON_GAME_DEFINE_TYPE_CHAT_H_
