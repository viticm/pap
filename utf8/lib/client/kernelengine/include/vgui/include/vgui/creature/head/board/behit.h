/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id hit.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-28 10:38:58
 * @uses vgui creature head hit board class
 */
#ifndef VGUI_CREATURE_HEAD_BOARD_BEHIT_H_
#define VGUI_CREATURE_HEAD_BOARD_BEHIT_H_

#include "vengine/config.h"
#include "IFalagardBeHitBoard.h"
#include "CEGUIColourRect.h"
#include "CEGUIVector.h"
#include "vgui/config.h"

namespace CEGUI {
class Window;
}; //namespace CEGUI

namespace vgui_creature {

namespace head_board {

class Base;
typedef struct {
  float xposition;
  float yposition;
  float xspeed; //X象素级移动速度
  float yspeed; //Y像素级移动速度
  float xacceleration;
  float yacceleration; //两个方向的加速度
  int32_t maxlife;
  bool alphamode; //是否为alpha模式
  int32_t movemode;
  int32_t usetemp_position;
  CEGUI::colour colortype;
  CEGUI::colour back_colortype;
  float width;
  float heigth;
} behit_data_t;

class BeHit {

 public:
   BeHit();
   virtual ~BeHit();

 public:
   CEGUI::Window* window_;
   char windowname_[128];
   bool doublehit_;
   float startx_;
   float starty_;
   float alpha_;
   int32_t life_;
   CEGUI::colour colortype_;
   CEGUI::colour back_colortype_;
   float xspeed_;
   float yspeed_;
   float xacceleration_;
   float yacceleration_;
   int32_t maxlife_;
   bool alphamode_;
   float scale_;
   behit_data_t* data_;
   float doubletime_;
   bool zoomon_;
   int32_t movemode_;
   int32_t usetemp_position_;
   int32_t tempposition_index_;
   int32_t movetype_;

 public:
   void resetdata(const char* text);
   void update();
   void inuse(bool flag);
   bool is_inuse();
   
 public:
   bool is_inuse_; //是否正在使用

};

}; //namespace head_board

}; //namespace vgui_creature


#endif //VGUI_CREATURE_HEAD_BOARD_BEHIT_H_
