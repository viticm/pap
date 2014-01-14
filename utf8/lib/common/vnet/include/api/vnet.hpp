// vnet.hpp  
// vnet header files for C++
// <<extern "C">> not supplied automatically because vnet also compiles as C++

extern "C" {
#include "common/lib/vnet/vnet.h"
#include "common/lib/vnet/vnetapi.h"
#include "common/lib/vnet/vnetlib.h"
#undef bool
#undef true
#undef false
}
