/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-20 15:03:13
 * @uses vengine sound system module
 */
#ifndef VENGINE_SOUND_SYSTEM_H_
#define VENGINE_SOUND_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"
#include "vengine/sound/buffer.h"
#include "vengine/sound/source.h"

namespace vengine_sound {

//外提供的声音播放接口,返回声音源HANDLE 
typedef int32_t (__stdcall* function_play)
  (const char* soundfile, float* position, bool loop);
//外提供声音的停止接口
typedef void (__stdcall* function_stop)(int32_t id);

class VENGINE_API System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(vengine_sound_System);

 public:
   virtual Buffer* createbuffer(int32_t id) = 0; //创建一个声音资源
   virtual Buffer* createbuffer(const char* filename) = 0; //创建一个声音资源
   //创建/删除播放源
   //3D模式 - 音量会随着位置变化
   //自动删除模式 - 只播放一遍,然后自动释放
   virtual Source* createsource(Source::type_enum type, 
                                bool is3d, 
                                bool autodestroy) = 0;
   virtual Source* createsource(Source::type_enum type,
                                bool is3d,
                                bool autodestroy,
                                Source** reference) = 0;
   virtual void destroysource(Source* source) = 0;
   virtual void destroysource(int32_t id) = 0;
   virtual void play_UIsound(int32_t id) = 0;

   //收听者
   virtual void set_listenerposition(
       vengine_math::base::threefloat_vector_t& position) = 0;
   virtual vengine_math::base::threefloat_vector_t& 
     get_listenerposition() = 0;
   
   virtual function_play get_playfunction() = 0;
   virtual function_stop get_stopfunction() = 0;

};

}; //namespace vengine_sound

#endif //VENGINE_SOUND_SYSTEM_H_
