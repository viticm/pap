#include "vengine/variable/system.h"

namespace vengine_variable {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    System,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node)); //纯虚函数类节点实现

} //namespace vengine_variable
