/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id actionsystem.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 17:59:35
 * @uses vengine game action system module
 */
#ifndef VENGINE_GAME_ACTIONSYSTEM_H_
#define VENGINE_GAME_ACTIONSYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"
#include "vengine/game/action/item.h"

namespace vengine_game {

namespace action {

class VENGINE_API System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(vengine_game_action_System);

 public:
   virtual Item* get(int32_t id) = 0;
   //当前正在显示Tootips的按钮
   virtual Item* get_tooltips_focus() = 0;
   virtual void save() = 0;
   //得到缺省操作
   virtual Item* getdefault() = 0;
   //设置缺省操作
   virtual void setdefault(Item* action) = 0;
   virtual void set_systemkey_state(int32_t keystate, bool is_Fkey) = 0;

};

} //namespace action

}; //namespace vengine_game

#endif //VENGINE_GAME_ACTIONSYSTEM_H_
