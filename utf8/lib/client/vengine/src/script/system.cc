#include "vengine/script/system.h"

namespace vengine_script {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_script::System,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_script_System);

} //namespace vengine_script
