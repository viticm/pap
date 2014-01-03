/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id human.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏角色类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_HUMAN_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_HUMAN_H_

namespace human {

typedef enum {
  kDieInvalid = -1,
  kDieMatch, //切磋
  kDieMonsterKill, //被怪物杀死
  kDiePlayerKill, //被玩家杀死
  kDieCount,
} die_enum; //死亡类型

}; //namespace human

#endif //PAP_COMMON_GAME_DEFINE_TYPE_HUMAN_H_
