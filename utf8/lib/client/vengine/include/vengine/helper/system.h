/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 17:17:28
 * @uses vengine helper system module
 */
#ifndef VENGINE_HELPER_SYSTEM_H_
#define VENGINE_HELPER_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

namespace vengine_helper {

VENGINE_API class System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

}; 

}; //namespace vengine_helper

#endif //VENGINE_HELPER_SYSTEM_H_
