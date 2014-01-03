/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id teammember.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏队伍成员属性的定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_ATTRIBUTE_TEAMMEMBER_H_
#define PAP_COMMON_GAME_DEFINE_ATTRIBUTE_TEAMMEMBER_H_

namespace teammember { //队伍成员

typedef enum {
  kInvalid = -1,
  kMeiPai, //门派
  kLevel, //等级
  kPosition, //位置
  kHP,
  kHPMax,
  kMP,
  kMPMax,
  kWeapon, //武器
  kCap, //帽子
  kArmor, //衣服
  kCuff, //护腕
  kBoot, //鞋子
  kBuff, 
  kDeadLink, //断线（与离线是不同概念）
  kDead, //死亡
  kFaceModel, //面部模型
  kHairModel, //头发模型
  kHairColor, //头发颜色
  kCount,
} _enum;

}; //namespace teammember

#endif //PAP_COMMON_GAME_DEFINE_ATTRIBUTE_TEAMMEMBER_H_
