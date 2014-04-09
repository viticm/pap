/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id buffer.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 20:14:03
 * @uses vengine sound buffer class
 */
#ifndef VENGINE_SOUND_BUFFER_H_
#define VENGINE_SOUND_BUFFER_H_

#include "vengine/config.h"

namespace vengine_sound {

class VENGINE_API Buffer {

 public:
   virtual bool read_wavbuffer(const STRING& name) = 0;
   virtual void release() = 0;

};

}; //namespace vengine_sound

#endif //VENGINE_SOUND_BUFFER_H_
