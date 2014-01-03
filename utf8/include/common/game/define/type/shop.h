/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id shop.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏商店类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_SHOP_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_SHOP_H_

namespace shop { //商店类型

typedef enum {
  kNpcAll = 1, //
  kNpcDefence, //防具
  kNpcAdorn, //饰品
  kNpcWeapon, //武器
  kNpcFood, //食物
  kNpcMetarial, //材料
  kNpcDrugs, //药品
} npc_enum;

}; //namespace shop

#endif //PAP_COMMON_GAME_DEFINE_TYPE_SHOP_H_
