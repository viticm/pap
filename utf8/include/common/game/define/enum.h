/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id enum.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:26:46
 * @uses 游戏中基本的枚举 注意全局以及命名空间包含的区别
 */
#ifndef PAP_COMMON_GAME_DEFINE_ENUM_H_
#define PAP_COMMON_GAME_DEFINE_ENUM_H_

typedef enum {
  kTimeZhi, //子
  kTimeChou, //丑
  kTimeYin, //寅
  kTimeMao, //卯
  kTimeChen, //辰
  kTimeSi, //巳
  kTimeWu, //午
  kTimeWei, //未
  kTimeShen, //申
  kTimeYou, //酉
  kTimeXu, //戌
  kTimeHai, //亥
} world_time_enum; //old china time

typedef enum {
  kGmExcuteLevelGm = 1,
  kGmExcuteLevelGmAdmin,
  kGmExcuteLevelAdmin,
  kGmExcuteLevelAll,
} gm_excute_level_enum; //GM命令模式

#endif //PAP_COMMON_GAME_DEFINE_ENUM_H_
