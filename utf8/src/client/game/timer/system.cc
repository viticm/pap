#include "client/game/timer/system.h"

namespace timer {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    timer::System,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    timer_System);

} //namespace timer
