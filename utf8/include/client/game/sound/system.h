/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-9 11:27:33
 * @uses client game sound system class
 */
#ifndef CLIENT_GAME_SOUND_SYSTEM_H_
#define CLIENT_GAME_SOUND_SYSTEM_H_

#include "vengine/game/eventsystem.h"
#include "vengine/sound/buffer.h"
#include "vengine/sound/source.h"
#include "vengine/sound/system.h"

struct FSOUND_STREAM;

namespace LuaPlus {
class LuaState;
class LuaObject;
}; //namespace LuaPlus

namespace vengine_db {

namespace structs {

namespace sound {
struct info_t;
}; //namespace sound

}; //namespace structs

}; //namespace vengine_db

namespace sound {

class Source;

class System : public vengine_sound::System {

VENGINE_KERNEL_DECLARE_DYNAMIC(sound_System);

 public:
   System();
   virtual ~System();
   static System* getself();

 public:
   virtual void init(void*);
   virtual void release();
   virtual void tick();

 public:
   static const char allsound_disable_[];
   static const char background_soundvar_[];
   static const char the3dsound_var_[];
   static const char skillsound_var_[];
   static const char uisound_var_[];

   static const char background_volumevar_[];
   static const char the3dvolume_var_[];
   static const char skillvolume_var_[];
   static const char uivolume_var_[];

 public: //implement from abstract
   virtual vengine_sound::Buffer* createbuffer(int32_t id); //创建一个声音资源
   virtual vengine_sound::Buffer* createbuffer(const char* filename);
   //创建/删除播放源
   //3D模式 - 音量会随着位置变化
   //自动删除模式 - 只播放一遍,然后自动释放
   virtual vengine_sound::Source* createsource(
       vengine_sound::Source::type_enum type, 
       bool is3d, 
       bool autodestroy);
   virtual vengine_sound::Source* createsource(
       vengine_sound::Source::type_enum type,
       bool is3d,
       bool autodestroy,
       vengine_sound::Source** reference);
   virtual void destroysource(vengine_sound::Source* source);
   virtual void destroysource(int32_t id);
   virtual void play_UIsound(int32_t id) {};

   //收听者
   virtual void set_listenerposition(
     vengine_math::base::threefloat_vector_t& position) {};
   virtual vengine_math::base::threefloat_vector_t& 
     get_listenerposition();
   
   virtual vengine_sound::function_play get_playfunction();
   virtual vengine_sound::function_stop get_stopfunction();

 public:
   static void WINAPI on_variablechange_event(
       const vengine_game::event_t* event,
       uint32_t ownerdata);
   static int32_t WINAPI playfunction(const char* filename, 
                                      float* position, 
                                      bool loop);
   static void WINAPI stopfunction(int32_t handle);
   static void play_uisound_function(int32_t id);
   //某种类型声音目前是否允许播放 
   bool is_typeenable(vengine_sound::Source::type_enum type);
   float get_typevolume(vengine_sound::Source::type_enum type);
   
 public: //exports
   int32_t lua_play(LuaPlus::LuaState* luastate);
   int32_t lua_stop(LuaPlus::LuaState* luastate);

 protected:
   static System* self_;
   LuaPlus::LuaObject* metatable_;
   STRING soundpath_; //声音资源目录
   float mastergain_; //主音量
   vengine_math::base::threefloat_vector_t listenerposition_;
   bool muteall_; //全部静音
   struct buffer_t {
     const vengine_db::structs::sound::info_t* define;
     vengine_sound::Buffer* buffer;
   };
   std::list<buffer_t> bufferlist_; //资源列表
   std::map<int32_t, buffer_t*> idmap_; //以ID作为索引
   std::map<STRING, buffer_t*> filemap_; //以文件名作为索引
   struct source_t {
     int32_t id;
     bool autodestroy;
     Source* source;
     vengine_sound::Source** source_reference;
     source_t() {
       source = NULL;
       source_reference = NULL;
     };
   };
   std::list<source_t> sourcelist_;

 protected:
   int32_t _playfunction(const char* filename, float* position, bool loop);
   void _stopfunction(int32_t handle);
   void _play_uisound_function(int32_t id);
   void muteall(bool mute);
   void stopspecial(vengine_sound::Source::type_enum type);
   vengine_sound::Buffer* sourceload(buffer_t& buffer);

};

}; //namespace sound

#endif //CLIENT_GAME_SOUND_SYSTEM_H_
