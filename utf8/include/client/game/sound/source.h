/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id source.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-9 10:42:46
 * @uses client game sound source
 */
#ifndef CLIENT_GAME_SOUND_SOURCE_H_
#define CLIENT_GAME_SOUND_SOURCE_H_

#include "vengine/sound/buffer.h"
#include "vengine/sound/source.h"

namespace sound {

class Source : public vengine_sound::Source {

 public: //implement from abstract
   virtual int32_t getid();
   //播放中不立即生效，需要stop后重新play
   virtual void setbuffer(vengine_sound::Buffer* buffer);
   virtual vengine_sound::Buffer* getbuffer();
   //循环播放
   virtual void setlooping(bool flag);
   virtual bool islooping() const;
   virtual void play();
   virtual void stop();
   virtual bool isplaying() const;
   virtual bool isstoped() const;
   virtual void setposition(
       const vengine_math::base::threefloat_vector_t& position);
   virtual const vengine_math::base::threefloat_vector_t& getposition();
   virtual void updatevolume();

 public:
   virtual void updatestatus();
   type_enum gettype() const;

 protected:
   Source(int32_t id, type_enum type, bool is_3dmode);
   virtual ~Source();
   int32_t getchannel() const;
   void setgain(float gain); //播放源音量([0, 1], default:1)
   int32_t compute_manual_rolloff(int32_t volumedb, 
                                  int32_t dbmin, 
                                  int32_t dbmax, 
                                  double alpha, 
                                  float sqrdist) const; //根据距离计算音量

 private:
   enum status_enum {
     kStatusStoped, //--停止状态
     kStatusPlaying, //--播放中
     kStatusSilencing, //--播放完毕
   };
   status_enum status_;
   int32_t id_;
   vengine_sound::Buffer* sample_;
   int32_t channel_;
   bool is_3dmode_; //3D模式，否为2D
   bool loop_;
   double alpha_;
   vengine_math::base::threefloat_vector_t position_;
   type_enum type_;

};

}; //namespace sound

#endif //CLIENT_GAME_SOUND_SOURCE_H_
