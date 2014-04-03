/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id reference.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 19:17:02
 * @uses vengine game action reference class
 */
#ifndef VENGINE_GAME_ACTION_REFERENCE_H_
#define VENGINE_GAME_ACTION_REFERENCE_H_

#include "vengine/config.h"

namespace vengine_game {

namespace action {

//UI引用类
class VENGINE_API Reference {

 public:
   //逻辑Action消失
   virtual void bedestroyed() = 0;
   //数据更新
   virtual void update() = 0;
   //按钮按下
   virtual void setcheck(bool check) = 0;
   //按钮设置成default的状态
   virtual void setdefault(bool flag) = 0;
   //进入冷却
   virtual void enter_cooldown(int32_t time, float percent) = 0;
   //显示字符, _char所显示的字符，0不显示
   typedef enum {
     kCornerNumberPositionTopLeft = 0,
     kCornerNumberPositionTopRight,
     kCornerNumberPositionFootLeft,
     kCornerNumberPositionFootRight
   } cornernumber_position_enum;
   virtual void set_cornerchar(cornernumber_position_enum position,
                               const char* _char) = 0;
   virtual void enable() = 0;
   virtual void disable() = 0;

};

}; //namespace action

}; //namespace vengine_game

#endif //VENGINE_GAME_ACTION_REFERENCE_H_
