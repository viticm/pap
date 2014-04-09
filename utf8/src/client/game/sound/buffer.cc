#include <assert.h>
#include "fmod.h"
#include "vengine/resource/provider.h"
#include "vengine/exception/base.h"
#include "client/game/procedure/base.h"
#include "client/game/sound/buffer.h"

namespace sound {

Buffer::Buffer() {
  FMod_sample_ = NULL;
  reference_count_ = 0;
}

Buffer::~Buffer() {
  release();
}

void Buffer::release() {
  if (FMod_sample_) {
    FSOUND_Sample_Free(FMod_sample_);
    FMod_sample_ = NULL;
  }
}

bool Buffer::read_wavbuffer(const STRING& name) {
  release();
  char* address = NULL;
  uint64_t size = procedure::Base::resourceprovider_->loadresource(
      name.c_str(),
      address,
      "General");
  if (size > 0) {
    FMod_sample_ = FSOUND_Sample_Load(FSOUND_FREE,
                                      address,
                                      FSOUND_HW3D | FSOUND_LOADMEMORY,
                                      0,
                                      size);
    procedure::Base::resourceprovider_->unloadresource(address, size);
  }
  
  if (!FMod_sample_) {
    VENGINE_SHOW("sound::Buffer::read_wavbuffer: invalid sound file: %s",
                 name.c_str());
    return false;
  }
  FSOUND_Sample_SetMode(FMod_sample_, FSOUND_LOOP_OFF);
  return true;
}

void Buffer::add_reference(Source* source) {
  ++reference_count_;
}

void Buffer::reduce_reference(Source* source) {
  --reference_count_;
}

int32_t Buffer::get_reference() const {
  return reference_count_;
}

} //namespace sound
