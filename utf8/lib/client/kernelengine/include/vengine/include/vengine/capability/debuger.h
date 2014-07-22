/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id debuger.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-26 10:34:10
 * @uses vengine capability debuger module
 */
#ifndef VENGINE_CAPABILITY_DEBUGER_H_
#define VENGINE_CAPABILITY_DEBUGER_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

namespace vengine_capability {

class Debuger : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(Debuger);

 public:
   virtual void infotrack_reset(int32_t width, int32_t height) = 0;
   virtual void infotrack_addpoint(int32_t x, int32_t y) = 0;

};

}; //namespace vengine_capability

#endif //VENGINE_CAPABILITY_DEBUGER_H_
