/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id monster.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏怪物属性的定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_ATTRIBUTE_MONSTER_H_
#define PAP_COMMON_GAME_DEFINE_ATTRIBUTE_MONSTER_H_

namespace monster { //怪物

typedef enum {
  kAiParamScanEnemyTime = 0, //扫描敌人的时间间隔，如果是-1，则不会主动攻击
  kAiParamRandMoveTime = 1, //随机移动的时间间隔，如果是-1，则不会随机移动
  kAiParamCanNotAttack = 2, //不能被攻击（无敌）
  kAiParamReturnDistance = 3, //离开出生地的距离大于此值时，放弃追赶敌人
  kAiParamScanEnemyDistance = 4, //扫描敌人的最大距离
  kAiParamScanTeammateDistance = 5, //扫描队友的最大距离
  kAiParamResetTargetDistance = 6, //如果当前的移动目标和敌人的位置之间的距离
                                   //大于此数值,则需要重新设定移动目标
  kAiParamPatrolTime = 7, //巡逻的时间间隔
  kAiParamStrikeBack = 8, //是否会还击
  kAiParamUseLuaScript = 9, //是否有扩展脚本
  kAiParamCallOther = 10, //是否召唤其他怪物
  kAiParamCount,
} ai_param_enum;

}; //namespace monster

#endif //PAP_COMMON_GAME_DEFINE_ATTRIBUTE_MONSTER_H_
