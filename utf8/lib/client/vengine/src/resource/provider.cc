#include "vengine/resource/provider.h"

namespace vengine_resource {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_resource::Provider,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_resource_Provider);

} //namespace provider
