/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id skill.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏技能的类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_SKILL_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_SKILL_H_

namespace skill {

typedef enum {
  kUserPlayer = 0,
  kUserMonster = 1,
  kUserPet = 2,
  kUserItem = 3,
} user_enum; //技能使用者分类

typedef enum {
  kPetInvalid = -1, 
  kPetPlayer = 0, //玩家触发
  kPetAI, //AI触发
  kPetPassive, //被动技能，增强属性
  kPetCount
} pet_enum; //宠物的技能操作类型

}; //namespace skill

#endif //PAP_COMMON_GAME_DEFINE_TYPE_SKILL_H_
