/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-28 10:22:16
 * @uses vgui creature head board system
 */
#ifndef VGUI_CREATURE_HEAD_BOARD_SYSTEM_H_
#define VGUI_CREATURE_HEAD_BOARD_SYSTEM_H_

#include "vengine/config.h"
#include "IFalagardBeHitBoard.h"
#include "CEGUIVector.h"
#include "vgui/config.h"

namespace CEGUI {
class Window;
}; //namespace CEGUI

namespace vgui_creature {

namespace head_board {

class System {

 public:
   System();
   virtual ~System();
   static System* getself();

 public:
   void init();
   void release();
   void tick();

 public:
   System* self_;

 public:
   static CEGUI::Window* get_clientscreen();
   static CEGUI::Window* groundsheet_; //客户端窗口底板
   Base* create();
   void destroy(Base* board);
   //击中效果消息框
   void add_new_behit(bool doublehit, //是否为重击
                      const char* value, //显示的字符串
                      float startx, //实际的屏幕坐标
                      float starty, 
                      int32_t type = 0, 
                      int32_t movetype = 0);

 public:
   float get_maxdistance();
   float get_maxdispear_distance();

 protected:
   uint32_t behit_count_;
   float maxdistance_; //最大的显示范围
   float maxdispear_distance_; //超过这个范围就消失
   //所有信息链表
   std::list<Base*> boardlist_;
   std::list<BeHit*> behit_boardlist_;
   BeHitManager* behit_manager_;
   //信息板池
   std::list<Base*> datapool_;

};

}; //namespace head_board

}; //namespace vgui_creature

#endif //VGUI_CREATURE_HEAD_BOARD_SYSTEM_H_
