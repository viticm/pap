#include "vengine/helper/system.h"

namespace vengine_helper {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_helper::System,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_helper_System);  

} //namespace vengine_helper
