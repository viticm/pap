/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id provider.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 19:06:31
 * @uses vegine resource provider module
 */
#ifndef VENGINE_RESOURCE_PROVIDER_H_
#define VENGINE_RESOURCE_PROVIDER_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

namespace vengine_resource {

class VENGINE_API Provider : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(Provider);

 public:
   virtual uint64_t loadresource(const char* filename, 
                                 char*& memoryaddress, 
                                 const char* group = NULL) = 0;
   virtual bool unloadresource(char* memoryaddress, uint64_t size) = 0;

};

}; //namespace vengine_resource

#endif //VENGINE_RESOURCE_PROVIDER_H_
