#include "vengine/game/data/pool/ui.h"

namespace vengine_game {

namespace data_pool {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_game::data_pool::Ui,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_game_data_pool_Ui);

}; //namespace data_pool

}; //namespace vengine_game
