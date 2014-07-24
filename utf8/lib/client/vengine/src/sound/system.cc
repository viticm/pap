#include "vengine/sound/system.h"

namespace vengine_sound {

VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(
    vengine_sound::System,
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_sound_System);

}; //namespace vengine_sound