#include "vengine/capability/debuger.h"

namespace vengine_capability {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_capability::Debuger,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_capability_Debuger);

} //namespace vengine_capability
