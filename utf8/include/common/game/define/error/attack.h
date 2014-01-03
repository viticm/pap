/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id attack.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏攻击错误的定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_ERROR_ATTACK_H_
#define PAP_COMMON_GAME_DEFINE_ERROR_ATTACK_H_

namespace attack { //攻击

typedef enum {
  kNotLive = -1, //目标死了，攻击无效
  kNotSameScene = -2, //目标不在当前场景
  kNotInRange = -3, //超出范围
  kTargetInvalid = -4, //目标无效
  kNotHit = -5, //未命中
  kTargetDead = -6, //目标已死亡
  kBreak = -7, //攻击被打断
  kCanNotAttack = -8, //目标不能被攻击
} _enum;

}; //namespace attack


#endif //PAP_COMMON_GAME_DEFINE_ERROR_ATTACK_H_
