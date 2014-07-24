#include "vengine/variable/system.h"

namespace vengine_variable {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_variable::System,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_variable_System); //纯虚函数类节点实现

} //namespace vengine_variable
