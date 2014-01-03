/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id skill.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 技能ID定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_ID_SKILL_H_
#define PAP_COMMON_GAME_DEFINE_ID_SKILL_H_

namespace skill {

typedef enum {
  kSystemMeleeAttack, //近战
  kSystemPetCapture, //扑捉宠物
  kSystemPetCallUp, //召唤宠物
} system_enum;

}; //namespace skill

#endif //PAP_COMMON_GAME_DEFINE_ID_SKILL_H_
