/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-10 14:47:33
 * @uses client game cursor manager
 */
#ifndef PAP_CLIENT_GAME_CURSOR_MANAGER_H_
#define PAP_CLIENT_GAME_CURSOR_MANAGER_H_

#include "vengine/math/base.h"
#include "vengine/cursor/system.h"
#include "client/game/command.h"

namespace object {
class Base;
}; //namespace object

namespace vengine_game {
namespace action {
class Item;
}; //namespace action
}; //namespace vengine_game

namespace cursor {

class Manager : public vengine_cursor::System {

VENGINE_KERNEL_DECLARE_DYNAMIC(cursor_Manager);

 public:
   Manager();
   virtual ~Manager();
   static Manager* getself();
 
 //implement from abstract
 public:
   virtual void set(vengine_cursor::type_enum type);
   virtual HCURSOR get();
   virtual void init(void *handle);

   /* enter ui control model */
   virtual void enterui(HCURSOR hcursor);
   virtual void leaveui();

   /* 应WM_SETCURSOR */
   virtual void onset();
   /* 显示或隐藏 */
   virtual void show(bool flag);

 public:
   int32_t getstate();
   virtual void mousecommand_set(
       bool hover_inui, 
       const vengine_math::base::threefloat_vector_t position, 
       vengine_game::action::Item* activeskill);
   virtual mousecommand_t& mousecommand_getleft();
   virtual mousecommand_t& mousecommand_getright();
   virtual void mousecommand_active(mousecommand_t& cmd);
   virtual void mousecommand_clear();

 protected:
   static Manager* self_;
   bool show_;
   int32_t state_;
   HCURSOR cursorhandles_[vengine_cursor::kTypeNumber];
   HCURSOR uicursor_handle_;
   mousecommand_t current_mousecommand_left_; //左键待触发指令
   mousecommand_t current_mousecommand_right_; //右键待触发指令

};

}; //namespace cursor

#endif //PAP_CLIENT_GAME_CURSOR_MANAGER_H_
