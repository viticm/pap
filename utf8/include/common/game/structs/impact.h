/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id impact.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 11:44:33
 * @uses 游戏所有效果常见结构
 */
#ifndef PAP_COMMON_GAME_STRUCTS_IMPACT_H_
#define PAP_COMMON_GAME_STRUCTS_IMPACT_H_

#include "server/common/game/config.h"

namespace impact {

struct filedb_directly_t { //impact_directly.txt
}; //特效

struct filedb_buff_t { //impact_buff.txt
}; //buff

typedef enum {
  kDropBox = -3, //drop
  kDie = -2, //die
  kMiss = -1, //miss
  kPhysicsDamage, //物理伤害
  kMagicDamage, //内功伤害
  kColdDamage, //冰伤害
  kFireDamage, //火伤害
  kElectricityDamage, //电伤害
  kPoisonDamage, //毒伤害
  kCutIre, //减怒气
} direct_type_enum;

struct direct_t {
};

class Own {
};

}; //namespace impact

#endif //PAP_COMMON_GAME_STRUCTS_IMPACT_H_
