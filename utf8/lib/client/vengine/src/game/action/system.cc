#include "vengine/game/action/system.h"

namespace vengine_game {

namespace action {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    System,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node));

} //namespace action

} //namespace vengine_game
