#include "vengine/game/itemtransfer_system.h"

namespace vengine_game {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_game::ItemTransferSystem,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_game_ItemTransferSystem);

}; //namespace vengine_game
