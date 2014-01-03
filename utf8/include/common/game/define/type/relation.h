/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id relation.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏关系类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_RELATION_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_RELATION_H_

namespace relation { //关系

typedef enum {
  kInvalid = -1,
  kEnemy = 0, //敌对
  kFriend = 1, //友好
  kCount,
} _enum;

typedef enum {
  kPlayerNone = 0, //空
  kPlayerFriend, //好友
  kPlayerBrother, //结拜
  kPlayerMarry, //结婚
  kPlayerBlack, //黑名单
  kPlayerTempFriend, //临时好友
  kPlayerStranger, //陌生人
  kPlayerProffer, //师傅关系
  kPlayerDisciple, //徒弟关系
  kPlayerCount,
} player_enum;

}; //namespace relation

#endif //PAP_COMMON_GAME_DEFINE_TYPE_RELATION_H_
