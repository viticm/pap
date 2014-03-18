#include "vengine/kernel/class.h"

namespace vengine_kernel {
  
Node* class_t::newobject(const char* name) {
  if (NULL == newobject_pointer) return NULL;
  Node* object = (*newobject_pointer)();
  object->name_ = name;
}

} //vengine_kernel
