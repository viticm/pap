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

void VENGINE_API samplingbegin();
void VENGINE_API samplingend();
void VENGINE_API pushnode(const char* name, const char* parent = NULL);
void VENGINE_API popnode(const char* name);
void VENGINE_API report();

struct autosampling_t {
  autosampling_t();
  ~autosampling_t();
};

}; //namespace profile

}; //namespace ax

}; //namespace vengine_capatility


#endif //VENGINE_CAPABILITY_AX_PROFILE_H_
