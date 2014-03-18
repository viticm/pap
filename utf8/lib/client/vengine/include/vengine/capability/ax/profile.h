/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id profile.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-16 11:56:11
 * @uses the ax profile module, just for system performance
 */
#ifndef VENGINE_CAPABILITY_AX_PROFILE_H_
#define VENGINE_CAPABILITY_AX_PROFILE_H_

#include "vengine/config.h"

namespace vengine_capatility {

namespace ax {

namespace profile {

VENGINE_API void samplingbegin();
VENGINE_API void samplingend();
VENGINE_API void pushnode(const char* name, const char* parent = NULL);
VENGINE_API void popnode(const char* name);
VENGINE_API void report();

struct autosampling_t {
  autosampling_t();
  ~autosampling_t();
};

}; //namespace profile

}; //namespace ax

}; //namespace vengine_capatility


#endif //VENGINE_CAPABILITY_AX_PROFILE_H_
