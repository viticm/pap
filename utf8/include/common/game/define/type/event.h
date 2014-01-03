/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id event.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏聊天类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_EVNET_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_EVNET_H_

namespace event { //事件类型

typedef enum {
  kTaskKillMonster = 0, //杀死怪物
  kTaskEnterArea, //进入事件区域
  kTaskItemChange, //物品变化
  kTaskPetChange, //宠物变化
} task_enum;

}; //namespace event 

#endif //PAP_COMMON_GAME_DEFINE_TYPE_EVNET_H_
