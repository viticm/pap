/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id monster.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏怪物的类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_MONSTER_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_MONSTER_H_

namespace monster {

typedef enum { //怪物AI基本类型
  kAiBaseInvalid = -1,
  kAiBaseScan = 0, //主动攻击
  kAiBaseNotScan = 1, //非主动攻击
  kAiBaseCanNotAttack =2, //不可攻击
} ai_base_enum;

}; //namespace monster

#endif //PAP_COMMON_GAME_DEFINE_TYPE_MONSTER_H_
