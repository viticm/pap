#include "vengine/cursor/system.h"

namespace vengine_cursor {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_cursor::System,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_cursor_System);

} //namespace vengine_cursor
