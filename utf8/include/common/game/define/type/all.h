/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id all.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏所有类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_ALL_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_ALL_H_

namespace type {

#include "common/game/define/type/attack.h"
#include "common/game/define/type/chat.h"
#include "common/game/define/type/command.h"
#include "common/game/define/type/event.h"
#include "common/game/define/type/human.h"
#include "common/game/define/type/mail.h"
#include "common/game/define/type/monster.h"
#include "common/game/define/type/relation.h"
#include "common/game/define/type/setting.h"
#include "common/game/define/type/shop.h"
#include "common/game/define/type/skill.h"

/* global { */
typedef enum {
  kSexInvalid = -1,
  kSexFemale, //雌 女
  kSexMale, //雄 男
  kSexCount,
} sex_enum;

typedef enum {
  kCurrencyMoney = 0, //普通金钱
  kCurrencyGoodAndEvil, //善恶值
  kCurrencyProfferMoralPoint, //师德点
} currency_enum;
/* global } */

}; //namespace type

#endif //PAP_COMMON_GAME_DEFINE_TYPE_ALL_H_
