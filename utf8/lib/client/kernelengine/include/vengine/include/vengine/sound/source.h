/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id source.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-20 11:41:14
 * @uses vengine sound source class
 */
#ifndef VENGINE_SOUND_SOURCE_H_
#define VENGINE_SOUND_SOURCE_H_

#include "vengine/config.h"
#include "vengine/sound/buffer.h"
#include "vengine/math/base.h"

namespace vengine_sound {

class VENGINE_API Source {

 public:
   typedef enum {
     kTypeBackground, //背景音乐
     kTypeSkill, //技能
     kTypeEnvironment, //环境音乐
     kTypeUI //UI特效
   } type_enum;
   
 public:
   virtual int32_t getid() const = 0;
   //播放中不立即生效，需要stop后重新play
   virtual void setbuffer(Buffer* buffer) = 0;
   virtual Buffer* getbuffer() = 0;
   //循环播放
   virtual void setlooping(bool flag) = 0;
   virtual bool islooping() const = 0;
   virtual void play() = 0;
   virtual void stop() = 0;
   virtual bool isplaying() const = 0;
   virtual bool isstoped() const = 0;
   virtual void setposition(
       const vengine_math::base::threefloat_vector_t& position) = 0;
   virtual const vengine_math::base::threefloat_vector_t& getposition() = 0;
   virtual void updatevolume() = 0;
};

}; //namespace vengine_sound

#endif //VENGINE_SOUND_SOURCE_H_
