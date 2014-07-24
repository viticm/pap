#include "vengine/game/eventsystem.h"

namespace vengine_game {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_game::EventSystem,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_game_EventSystem);

} //namespace vengine_game
