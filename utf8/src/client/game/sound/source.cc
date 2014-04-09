#include <assert.h>
#include <math.h> 
#include "fmod.h"
#include "fmod_errors.h"
#include "vengine/base/util.h"
#include "vengine/exception/base.h"
#include "client/game/sound/buffer.h"
#include "client/game/sound/system.h"
#include "client/game/sound/source.h"

namespace sound {

Source::Source(int32_t id, type_enum type, bool is_3dmode) {
  id_ = id;
  sample_ = NULL;
  status = kStatusStoped;
  loop_ = false;
  is_3dmode_ = is_3dmode;
  alpha_ = 0.0f;
  position_ = vengine_math::base::threefloat_vector_t(0.0f, 0.0f, 0.0f);
  channel_ = -1;
  type_ = type;
}

Source::~Source() {
  if (sample_) {
    ((Buffer*)sample_)->reduce_reference(this);
  }
  stop();
}

void Source::setbuffer(vengine_sound::Buffer* buffer) {
  VENGINE_ASSERT(buffer);
  if (sample_) {
    ((Buffer*)sample_)->reduce_reference(this);
  }
  sample_ = buffer;
  ((Buffer*)sample_)->add_reference(this);
}

vengine_sound::Buffer* Source::getbuffer() {
  return sample_;
}

void Source::setlooping(bool flag) {
  if (flag != loop_) {
    loop_ = flag;
    if (channel_ != -1) {
      FSOUND_SetPaused(channel_, true);
      FSOUND_SetLoopMode(channel_, 
                         loop_ ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF);
      FSOUND_SetPaused(channel_, false);
    }
  }
}

void Source::play() {
  stop();
  if (sample_ && Source::getself()->is_typeenable(gettype())) {
    Buffer* buffer = dynamic_cast<Buffer*>(sample_);
    status_ = kStatusPlaying;
    if (buffer->FMod_sample_) {
      channel_ = FSOUND_PlaySoundEx(FSOUND_FREE, 
                                    buffer->FMod_sample_, 
                                    NULL, 
                                    true);
    }

    if (channel_ != -1) {
      FSOUND_SetLoopMode(channel_, 
                         loop_ ? FSOUND_LOOP_NORMAL : FSOUND_LOOP_OFF);
      updatevolume();
      FSOUND_SetPaused(channel_, false);
    }
  }
}

void Source::stop() {
  status_ = kStatusStoped;
  if (channel_ != -1) {
    FSOUND_StopSound(channel_);
    channel_ = -1;
  }
}

bool Source::isplaying() const {
  return kStatusPlaying == status_;
}

bool Source::isstoped() const {
  return kStatusSilencing == status_ || kStatusStoped == status_;
}

void Source::setposition(vengine_math::base::threefloat_vector_t& position) {
  position_ = position;
  if (is_3dmode) {
    updatevolume();
  }
}

void Source::updatevolume() {
  if (-1 == channel_) return;
  float gain = System::getself()->get_typevolume(gettype());
  if (is_3dmode_) {
    //得到与听者距离平方
    float distancesquare = vengine_base::util::get_squaredistance(
        getposition(),
        System::getself()->get_listenerposition());
    int32_t volumedb = static_cast<int32_t>(floor(2000.0 * log10(gain)));
    const static int32_t kVolumnMin = -10000;
    const static int32_t kVolumnMax = 0;
    vengine_base::util::clamp(volumedb, kVolumnMin, kVolumnMax);
    volumedb = compute_manual_rolloff(volumedb,
                                      kVolumnMin,
                                      kVolumnMax,
                                      alpha_,
                                      distancesquare);
    //计算线性值
    double attribute_gain = pow(10.0, static_cast<double>(volumedb) / 2000.0);
    vengine_base::util::clamp(attribute_gain, 0.0f, 1.0f);
    FSOUND_SetVolume(channel_, static_cast<uint32_t>(attribute_gain * 255));
  }
  else {
    FSOUND_SetVolume(channel_, static_cast<uint32_t>(gain * 255));
  }
}

void Source::updatestatus() {
  if (channel_ != -1 && isplaying()) {
    if (!FSOUND_IsPlaying(channel_)) { //播放结束
      status_ = kStatusSilencing;
    }
  }
}

int32_t Source::compute_manual_rolloff(int32_t volumedb, 
                                       int32_t dbmin, 
                                       int32_t dbmax, 
                                       double alpha, 
                                       float sqrdist) const {
  float min = 0.0f;
  float max = 40.0f;
  if (sqrdist < min * min) {
    return volumedb;
  }
  else if (sqrdist > max * max) {
    return dbmin;
  }
  else {
    double dist = static_cast<double>(sqrt(sqrdist));
    double db1 = dbmin * (dist - min) / (max - min);
    if (0.0 == alpha) {
      volumedb += static_cast<int32_t>(db1);
    }
    else if (alpha > 0.0) {
      double amp2 = 0.0001 + 0.9999 * (max - dist) / (max - min);
      double db2 = 2000.0 * log10(amp2);
      volumedb += static_cast<int32_t>(((1.0 - alpha) * db1 + alpha * db2));
    }
    else if (alpha < 0.0) {
      double amp3 = min / dist;
      double db3 = 2000.0 * log10(amp3);
      volumedb += static_cast<int32_t>(((1.0 + alpha) * db1 - alpha * db3));
    }
    vengine_base::util::clamp(volumedb, dbmin, dbmax);
    return volumedb;
  }
}

int32_t Source::getid() const {
  return id_;
}

int32_t Source::islooping() const {
  return loop_;
}

const vengine_math::base::threefloat_vector_t& Source::getposition() {
  return position_;
}

Source::type_enum Source::gettype() {
  return type_;
}

int32_t Source::getchannel() const {
  return channel_;
}

} //namespace sound
