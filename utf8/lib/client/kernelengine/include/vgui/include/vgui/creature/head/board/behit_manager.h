/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-28 11:40:06
 * @uses vgui creature be hit head board manager
 */
#ifndef VGUI_CREATURE_HEAD_BOARD_BEHIT_MANAGER_H_
#define VGUI_CREATURE_HEAD_BOARD_BEHIT_MANAGER_H_

#include "vengine/config.h"
#include "vgui/config.h"
#include "vgui/creature/head/board/behit.h"

namespace vgui_creature {

namespace head_board {

class BeHitManager {

 public:
   BeHitManager();
   virtual ~BeHitManager();

 public:
   static BeHitManager* self_;
   int32_t autosize_; //自动增长尺寸
   std::list<BeHit*> windowlist_;
   behit_data_t behit_data_[CEGUI::MAX_MOVE_TYPE_NUMBER];
   CEGUI::colour colortype_[CEGUI::MAX_COLOR_TYPE_NUMBER];
   CEGUI::colour back_colortype_[CEGUI::MAX_COLOR_TYPE_NUMBER];
   CEGUI::Point temppoint_[CEGUI::MAX_TEMP_TYPE_NUMBER];

 public:
   static BeHitManager* getself();
   BeHit* get_freewindow();
   void freewindow(BeHit* window);
   float get_doubleend_size();
   float get_normalsize();
   float get_doublesize();
   float get_doubletime();

 private:
   uint32_t count_;
   BeHit* newwindow();
   float normalsize_;
   float doublesize_;
   float doubleend_size_;
   float doubletime_;

}; 

}; //namespace head_board

}; //namespace vgui_creature

#endif //VGUI_CREATURE_HEAD_BOARD_BEHIT_MANAGER_H_
