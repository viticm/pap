/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id buffer.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-9 09:58:45
 * @uses client game sound buffer class
 */
#ifndef CLIENT_GAME_SOUND_BUFFER_H_
#define CLIENT_GAME_SOUND_BUFFER_H_

#include "vengine/sound/buffer.h"

struct FSOUND_SAMPLE;

namespace sound {

class Source;

class Buffer : public vengine_sound::Buffer {

 public:
   virtual bool read_wavbuffer(const STRING& name);
   virtual void release();
   void add_reference(Source* source);
   void reduce_reference(Source* source);
   int32_t get_reference() const;

 protected:
   FSOUND_SAMPLE* FMod_sample_;
   int32_t reference_count_;

 protected:
   Buffer();
   virtual ~Buffer();

 protected:
   friend class System;
   friend class Source;

};

}; //namespace sound

#endif //CLIENT_GAME_SOUND_BUFFER_H_
