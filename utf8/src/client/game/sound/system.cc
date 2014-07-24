#include "fmod.h"
#include "fmod_errors.h"
#include "vengine/exception/base.h"
#include "vengine/db/struct/all.h"
#include "client/game/procedure/base.h"
#include "client/game/database/system.h"
#include "client/game/event/system.h"
#include "client/game/variable/system.h"
#include "client/game/script/system.h"
#include "client/game/sound/buffer.h"
#include "client/game/sound/source.h"
#include "client/game/sound/system.h"

namespace sound {

const char System::allsound_disable_[] = "DisableAllSound";
const char System::background_soundvar_[] = "EnableBGSound";
const char System::the3dsound_var_[] = "Enable3DSound"; //环境音效
const char System::skillsound_var_[] = "EnableSKSound";
const char System::uisound_var_[] = "EnableUISound";

const char System::background_volumevar_[] = "VOLUME_BG";
const char System::the3dvolume_var_[] = "VOLUME_3D";
const char System::skillvolume_var_[] = "VOLUME_SK";
const char System::uivolume_var_[] = "VOLUME_UI";

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(
  sound::System,
  VENGINE_KERNEL_GETCLASS(vengine_sound::System, vengine_sound_System),
  sound_System);

System* System::self_ = NULL;

System::System() {
  self_ = this;
  muteall_ = false;
  mastergain_ = 1.0f;
  listenerposition_ = vengine_math::base::threefloat_vector_t(0.0f, 0.0f, 0.0f);
  soundpath_ = "../sound/";
  metatable_ = NULL;
}

System::~System() {
  if (metatable_) delete metatable_;
  metatable_ = NULL;
}

System* System::getself() {
  return self_;
}

void System::init(void*) {
  if (FSOUND_GetVersion() < FMOD_VERSION) {
    VENGINE_SHOW("sound::System::init: failed: "
                 "the fmod version should be: %.2f",
                 FMOD_VERSION);
  }
  FSOUND_SetOutput(FSOUND_OUTPUT_WINMM);
  FSOUND_SetDriver(0);
  FSOUND_SetMixer(FSOUND_MIXER_AUTODETECT);
  if (!FSOUND_Init(44100, 32, 0)) {
    VENGINE_SHOW("sound::System::init: failed: "
                 "Failed to create the FMod driver object");
  }
  DATABASE_DEFINEHANDLE(soundinfo, vengine_db::structs::sound::kInfoId);
  typedef vengine_db::structs::sound::info_t info_t;
  int32_t linenumber = soundinfo->get_record_number();
  int32_t i;
  for (i = 0; i < linenumber; ++i) {
    const info_t* line = reinterpret_cast<const info_t*>(
        soundinfo->search_line_equal(i));
    if (!line) continue;
    buffer_t buffer;
    buffer.define = line;
    buffer.buffer = NULL;
    bufferlist_.push_back(buffer);
    //insert to index
    idmap_[line->id] = &(bufferlist_.back());
    filemap_[line->file] = &(bufferlist_.back());
  }
  event::System::getself()->registerhandle("VARIABLE_CHANGED",
                                           on_variablechange_event);
  //设置如果未定义变量初始值
  variable::System::getself()->setvariable_default(background_soundvar_, "1");
  variable::System::getself()->setvariable_default(the3dsound_var_, "1");
  variable::System::getself()->setvariable_default(skillsound_var_, "1");
  variable::System::getself()->setvariable_default(uisound_var_, "1");
  //for lua
  metatable_ = new LuaPlus::LuaObject;
  *metatable_ = script::System::getself()
                ->get_luastate()
                ->GetGlobals().CreateTable("Sound");
  metatable_->SetObject("__index", *metatable_);
  metatable_->RegisterObjectFunctor("PlaySound", &System::lua_play);
  metatable_->RegisterObjectFunctor("StopSound", &System::lua_stop);
  LuaPlus::LuaObject variableobject = script::System::getself()
                                      ->get_luastate()
                                      ->BoxPointer(this);
  variableobject.SetMetaTable(*metatable_);
  script::System::getself()->get_luastate()->GetGlobals().SetObject(
      "Sound",
      variableobject);
}

void System::release() {
  std::list<source_t>::iterator source_iterator;
  for (source_iterator = sourcelist_.begin();
       source_iterator != sourcelist_.end();
       ++source_iterator) {
    source_t& source = *source_iterator;
    if (source.source) {
      delete source.source;
      source.source = NULL;
      if (source.source_reference != NULL) {
        source.source_reference = NULL;
      }
    }
  }
  sourcelist_.clear();
  std::list<buffer_t>::iterator buffer_iterator;
  for (buffer_iterator = bufferlist_.begin();
       buffer_iterator != bufferlist_.end();
       ++buffer_iterator) {
    buffer_t& buffer = *buffer_iterator;
    if (buffer.buffer) {
      delete buffer.buffer;
      buffer.buffer = NULL;
    }
  }
  bufferlist_.clear();
  idmap_.clear();
  filemap_.clear();
  FSOUND_Close();
}

bool System::is_typeenable(vengine_sound::Source::type_enum type) {
  variable::System* variablesystem = variable::System::getself();
  bool result = false;
  switch (type) {
    case vengine_sound::Source::kTypeBackground: {
      result = 1 == variablesystem->getint32(background_soundvar_);
      break;
    }
    case vengine_sound::Source::kTypeEnvironment: {
      result = 1 == variablesystem->getint32(the3dsound_var_);
      break;
    }
    case vengine_sound::Source::kTypeSkill: {
      result = 1 == variablesystem->getint32(skillsound_var_);
      break;
    }
    case vengine_sound::Source::kTypeUI: {
      result = 1 == variablesystem->getint32(uisound_var_);
      break;
    }
    default:
      break;
  }
  return result;
}

float System::get_typevolume(vengine_sound::Source::type_enum type) {
  if (muteall_) return 0.0f;
  variable::System* variablesystem = variable::System::getself();
  float gain = 0.0f;
  switch (type) {
    case vengine_sound::Source::kTypeBackground: {
      gain = variablesystem->getfloat(background_volumevar_);;
      break;
    }
    case vengine_sound::Source::kTypeEnvironment: {
      gain = variablesystem->getfloat(the3dvolume_var_);
      break;
    }
    case vengine_sound::Source::kTypeSkill: {
      gain = variablesystem->getfloat(skillvolume_var_);
      break;
    }
    case vengine_sound::Source::kTypeUI: {
      gain = variablesystem->getfloat(uivolume_var_);
      break;
    }
    default:
      break;
  }
  return gain;
}

void System::tick() {
  //对象系统未做，所以这里没有3D模式的设置
  vengine_math::base::threefloat_vector_t _value;
  memset(&_value, 0, sizeof(_value));
  set_listenerposition(_value);
  //更新声音源音量
  std::list<source_t>::iterator source_iterator, nextsource_iterator;
  for (source_iterator = sourcelist_.begin();
       source_iterator != sourcelist_.end();
       source_iterator = nextsource_iterator) {
    nextsource_iterator = source_iterator;
    ++nextsource_iterator;
    source_t& sourcesound = *source_iterator;
    sourcesound.source->updatestatus();
    if (sourcesound.autodestroy && sourcesound.source->isstoped()) {
      sourcesound.source->stop();
      delete sourcesound.source;
      sourcesound.source = NULL;
      if (sourcesound.source_reference != NULL) {
        sourcesound.source_reference = NULL;
      }
      sourcelist_.erase(source_iterator);
      continue;
    }
    sourcesound.source->updatevolume(); //更新音量
  }

  std::list<buffer_t>::iterator buffer_iterator;
  for (buffer_iterator = bufferlist_.begin();
       buffer_iterator != bufferlist_.end();
       ++buffer_iterator) {
    buffer_t& buffer = *buffer_iterator;
    if (buffer.buffer && 0 == buffer.buffer->get_reference()) {
      delete buffer.buffer;
      buffer.buffer = NULL;
    }
  }

  //如果窗口非激活，静音
  if (!procedure::Base::is_windowactive() && !muteall_) {
    muteall(true);
  }
  else if (procedure::Base::is_windowactive() && muteall_) {
    muteall(false);
  }
}

void System::muteall(bool flag) {
  if (flag = muteall_) return;
  std::list<source_t>::iterator iterator;
  for (iterator = sourcelist_.begin();
       iterator != sourcelist_.end();
       ++iterator) {
    source_t& source = *iterator;
    if (source.source && source.source->getchannel() >= 0) {
      FSOUND_SetMute(source.source->getchannel(), flag);
    }
  }
  muteall_ = flag;
}

vengine_sound::Buffer* System::createbuffer(int32_t id) {
  if (id <= 0) return NULL;
  std::map<int32_t, buffer_t*>::iterator iterator;
  iterator = idmap_.find(id);
  if (iterator == idmap_.end()) {
    VENGINE_SHOW("sound::System::createbuffer: invalid sound id: %d", id);
    return NULL;
  }
  return sourceload(*(iterator->second)); 
}

vengine_sound::Buffer* System::createbuffer(const char* filename) {
  if (!filename) return NULL;
  std::map<STRING, buffer_t*>::iterator iterator;
  iterator = filemap_.find(filename);
  if (iterator == filemap_.end()) {
    VENGINE_SHOW("sound::System::createbuffer: invalid sound file: %s", 
                 filename);
    return NULL;
  }
  return sourceload(*(iterator->second)); 
}

vengine_sound::Buffer* System::sourceload(buffer_t& buffer) {
  if (NULL == buffer.buffer) {
    Buffer* _buffer = new Buffer();
    if (!_buffer->read_wavbuffer(buffer.define->file)) {
      return NULL;
    }
    buffer.buffer = _buffer;
  }
  return buffer.buffer;
}

vengine_sound::Source* System::createsource(
    vengine_sound::Source::type_enum type, 
    bool is3d, 
    bool autodestroy) {
  static int32_t sourceid = 1;
  Source* source = new Source(++sourceid, type, is3d);
  source_t newsource;
  newsource.autodestroy = autodestroy;
  newsource.source = source;
  newsource.source_reference = NULL;
  sourcelist_.push_back(newsource);
  return dynamic_cast<vengine_sound::Source*>(source);
}

vengine_sound::Source* System::createsource(
    vengine_sound::Source::type_enum type,
    bool is3d,
    bool autodestroy,
    vengine_sound::Source** reference) {
  //和上面的方法可以使用多态
  static int32_t sourceid = 1;
  Source* source = new Source(++sourceid, type, is3d);
  source_t newsource;
  newsource.autodestroy = autodestroy;
  newsource.source = source;
  if (reference != NULL) {
    newsource.source_reference = reference;
  }
  sourcelist_.push_back(newsource);
  return dynamic_cast<vengine_sound::Source*>(source);
}

void System::destroysource(vengine_sound::Source* source) {
  std::list<source_t>::iterator iterator;
  for (iterator = sourcelist_.begin();
       iterator != sourcelist_.end();
       ++iterator) {
    source_t& _source = *iterator;
    if (_source.source == source) {
      delete _source.source;
      _source.source = NULL;
      if (_source.source_reference != NULL) {
        _source.source_reference = NULL;
      }
      sourcelist_.erase(iterator);
      return;
    }
  } //for loop
}

void System::destroysource(int32_t id) {
  std::list<source_t>::iterator iterator;
  for (iterator = sourcelist_.begin();
       iterator != sourcelist_.end();
       ++iterator) {
    source_t& source = *iterator;
    if (source.source && source.source->getid() == id) {
      delete source.source;
      source.source = NULL;
      if (source.source_reference != NULL) {
        source.source_reference = NULL;
      }
      sourcelist_.erase(iterator);
      return;
    }
  } //for loop
}

void System::play_uisound_function(int32_t id) {
  //创建3d声音播放源
  if (variable::System::getself()->getint32(uisound_var_) != 1) return;
  vengine_sound::Buffer* buffer = getself()->createbuffer(id);
  if (!buffer) return;
  vengine_sound::Source* source = getself()->createsource(Source::kTypeUI, false, true);
  if (!source) return;
  source->setbuffer(buffer);
  source->setlooping(false);
  source->play();
}

int32_t System::_playfunction(const char* filename, 
                              float* position, 
                              bool loop) {
  vengine_math::base::threefloat_vector_t gfx_vector(position[0],
                                                     position[1],
                                                     position[2]);
  vengine_math::base::threefloat_vector_t game_vector;
  /**
  if (!procedure::Base::rendersystem_->axistrans(
        vengine_render::System::kAxisTypeRender,
        gfx_vector,
        vengine_render::System::kAxisTypeGame,
        game_vector)) {
    return -1;
  }
  **/ //暂时不做
  
  vengine_sound::Buffer* buffer = getself()->createbuffer(filename);
  if (!buffer) return -1;
  vengine_sound::Source* source = getself()->createsource(Source::kTypeSkill, true, true);
  if (!source) return -1;
  source->setbuffer(buffer);
  source->setposition(gfx_vector);
  source->setlooping(loop);
  source->play();
  return (int32_t)(int32_t*)source;
}

void System::_stopfunction(int32_t handle) {
  if (-1 == handle) return;
  Source* sourcepointer = (Source*)(int32_t*)handle;
  std::list<source_t>::iterator iterator;
  for (iterator = sourcelist_.begin();
       iterator != sourcelist_.end();
       ++iterator) {
    source_t& source = *iterator;
    if (source.source == sourcepointer) {
      delete source.source;
      source.source = NULL;
      if (source.source_reference != NULL) {
        source.source_reference = NULL;
      }
      sourcelist_.erase(iterator);
      return;
    }
  } //for loop
}

void WINAPI System::on_variablechange_event(const vengine_game::event_t* event,
                                            uint32_t ownerdata) {
  if (event && 
      event->eventdefine && 
      vengine_game::event_id::kVariableChanged == event->eventdefine->id) {
    const STRING& variable = event->args[0];
    const STRING& value = event->args[1];
    bool enable = "1" == value;
    if (true == enable) {
      if (variable == allsound_disable_) {
        getself()->stopspecial(Source::kTypeSkill);
        getself()->stopspecial(Source::kTypeUI);
        getself()->stopspecial(Source::kTypeBackground);
        getself()->stopspecial(Source::kTypeEnvironment);
      }
    }
    else {
      if (variable == background_volumevar_) {
        getself()->stopspecial(Source::kTypeBackground);
      }
      else if (variable == the3dsound_var_) {
        getself()->stopspecial(Source::kTypeEnvironment);
      }
      else if (variable == skillsound_var_) {
        getself()->stopspecial(Source::kTypeSkill);
      }
      else if (variable == uisound_var_) {
        getself()->stopspecial(Source::kTypeUI);
      }
    }
  }
}

void System::stopspecial(Source::type_enum type) {
  std::list<source_t>::iterator source_iterator, nextsource_iterator;
  for (source_iterator = sourcelist_.begin();
       source_iterator != sourcelist_.end();
       source_iterator = nextsource_iterator) {
    nextsource_iterator = source_iterator;
    ++nextsource_iterator;
    source_t& sourcesound = *source_iterator;
    if (sourcesound.source->gettype() == type) {
      sourcesound.source->stop();
      delete sourcesound.source;
      sourcesound.source = NULL;
      if (sourcesound.source_reference != NULL) {
        sourcesound.source_reference = NULL;
      }
      sourcelist_.erase(source_iterator);
    }
  }
}

int32_t System::lua_play(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsInteger()) {
    VENGINE_ASSERT("sound::System::lua_play: param[2] error");
    return 0;
  }
  if (!args[3].IsBoolean()) {
    VENGINE_ASSERT("sound::System::lua_play: param[3] error");
    return 0;
  }
  int32_t sourceid = args[2].GetInteger();
  bool loop = args[3].GetBoolean();
  vengine_sound::Buffer* buffer = createbuffer(sourceid);
  if (!buffer) {
    luastate->PushInteger(-1);
    return 1;
  }
  vengine_sound::Source* source = createsource(Source::kTypeBackground,
                                               false,
                                               !loop);
  if (source) {
    source->setbuffer(buffer);
    source->setlooping(loop);
    source->play();
    luastate->PushInteger(source->getid());
    return 1;
  }
  luastate->PushInteger(-1);
  return 1;
}

int32_t System::lua_stop(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsInteger()) {
    VENGINE_SHOW("sound::System::lua_stop: param[2] error");
    return 0;
  }
  int32_t soundid = args[2].GetInteger();
  destroysource(soundid);
  return 0;
}

vengine_math::base::threefloat_vector_t& System::get_listenerposition() {
  return listenerposition_;
}

vengine_sound::function_play System::get_playfunction() {
  return playfunction;
}

vengine_sound::function_stop System::get_stopfunction() {
  return stopfunction;
}

int32_t WINAPI System::playfunction(const char* filename, float* position, bool loop) {
  return getself()->_playfunction(filename, position, loop);
}

void WINAPI System::stopfunction(int32_t handle) {
  getself()->_stopfunction(handle);
}

} //namespace sound
