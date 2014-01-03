/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id attack.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏攻击类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_ATTACK_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_ATTACK_H_

namespace attack {

typedef enum {
  kPhysicalDamage, //物理伤害
  kMagicDamage, //魔法伤害
  kColdDamage, //冰伤害
  kFireDamage, //火伤害
  kElectricityDamage, //电伤害
  kPoisonDamage, //毒伤害
  kDamageCount,
} damage_enum; //伤害类型

}; //namespace attack

#endif //PAP_COMMON_GAME_DEFINE_TYPE_ATTACK_H_
