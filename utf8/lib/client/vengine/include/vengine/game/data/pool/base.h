/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 17:40:04
 * @uses vengine game data pool base class
 */
#ifndef VENGINE_GAME_DATA_POOL_BASE_H_
#define VENGINE_GAME_DATA_POOL_BASE_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

namespace vengine_game {

namespace data_pool {

class VENGINE_API Base : public vengine_kernel::Node {

  VENGINE_KERNEL_DECLARE_DYNAMIC(vengine_game_data_pool_Base);

};

}; //namespace data_pool

}; //namespace vengine_game

#endif //VENGINE_GAME_DATA_POOL_BASE_H_
