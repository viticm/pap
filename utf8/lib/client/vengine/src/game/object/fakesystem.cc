#include "vengine/game/object/fakesystem.h"

namespace vengine_game {

namespace object {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_game::object::FakeSystem,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_game_object_FakeSystem);

} //namespace object

} //namespace vengine_game
