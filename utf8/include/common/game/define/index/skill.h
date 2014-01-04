/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id skill.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 10:48:45
 * @uses 游戏常用技能索引的定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_INDEX_SKILL_H_
#define PAP_COMMON_GAME_DEFINE_INDEX_SKILL_H_

namespace skill {

typedef enum {
  kPetInvalid = -1,
  kPetControlByPlayer,
  kPetControlByAI,
  kPetControlByMeiPai,
  kPetCount,
} pet_enum;

}; //namespace skill

#endif //PAP_COMMON_GAME_DEFINE_INDEX_SKILL_H_
