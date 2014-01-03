/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id ability.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 生活技能ID定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_ID_ABILITY_H_
#define PAP_COMMON_GAME_DEFINE_ID_ABILITY_H_

#include "common/game/define/macros.h"

namespace ability {

typedef enum {
  kGemCompound = CHARACTER_ABILITYMAX + 1,
  kGemInlay
} gem_enum;

}; //namespace ability

#endif //PAP_COMMON_GAME_DEFINE_ID_ABILITY_H_
