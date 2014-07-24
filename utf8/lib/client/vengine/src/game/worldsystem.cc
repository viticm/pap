#include "vengine/game/worldsystem.h"

namespace vengine_game {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_game::WorldSystem,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_game_WorldSystem);

} //namespace vengine_game
