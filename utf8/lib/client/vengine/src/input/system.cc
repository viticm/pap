#include "vengine/input/system.h"

namespace vengine_input {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_input::System,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_input_System);

} //namespace vengine_input
