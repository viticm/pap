#include "LuaPlus.h"
#include "vengine/variable/system.h"
#include "vengine/time/system.h"
#include "vengine/resource/provider.h"
#include "common/file/database.h"
#include "client/game/global.h"
#include "client/game/procedure/base.h"
#include "client/game/script/system.h"

#define FILE_SCRIPT "script.dat"

namespace script {

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(
    script::System,
    VENGINE_KERNEL_GETCLASS(vengine_script::System, vengine_script_System),
    script_System);

System* System::self_ = NULL;

System::System() {
  self_ = this;
}

System* System::getself() {
  return self_;
}

System::~System() {
  VENGINE_ASSERT(environmentlist_.empty());
}

LuaPlus::LuaState* System::_get_luastate() {
  static LuaPlus::LuaStateOwner luastate_owner;
  LuaPlus::LuaState* luastate = luastate_owner.Get();
  return luastate;
}

vengine_script::Environment* System::newenvironment(const char* name, 
                                                    const char* filename) {
  Environment* _new = new Environment(name, filename);
  environmentlist_.push_back(_new);
  return static_cast<vengine_script::Environment*>(_new);
}

void System::destroyenvironment(vengine_script::Environment* environment) {
  std::list<Environment*>::iterator iterator;
  for (iterator = environmentlist_.begin();
       iterator != environmentlist_.end();
       ++iterator) {
    if (*iterator == environment) {
      SAFE_DELETE(environment);
      environmentlist_.erase(iterator);
      return;
    }
  }
}

const STRING& System::get_questfile(int32_t id) {
  std::map<int, STRING>::iterator find_iterator;
  find_iterator = questfile_map_.find(id);
  if (find_iterator == questfile_map_.end()) return "";
  return find_iterator->second;
}

void System::init(void*) {
  //加载任务脚本列表
  load_qusetfile();
  //是否抛出异常
  bool have = false; //默认抛出
  enable_luacrash_ = procedure::Base::variablesystem_->getint32(
      "EnableLuaCrash", &have);
  if (!have) enable_luacrash_ = true;
  LuaPlus::LuaState* luastate = _get_luastate();
  LuaPlus::LuaObject globalobject = luastate->GetGlobals();

  /* lua exports{ */

  /* }lua exports */
}

void System::tick() {
  const uint32_t kCollectTime = 3 * 1000;
  static uint32_t last_collecttime = 0;
  uint32_t nowtime = procedure::Base::timesystem_->get_nowtime();
  if (procedure::Base::timesystem_->get_difftime(last_collecttime, nowtime) > 
      kCollectTime) { //释放垃圾内存
    System::getself()->get_luastate()->CollectGarbage();
    last_collecttime = nowtime;
  }
}

void System::release() {
  std::list<Environment*>::iterator iterator;
  for (iterator = environmentlist_.begin();
       iterator != environmentlist_.end();
       ++iterator) {
    SAFE_DELETE(*iterator);
  }
  environmentlist_.clear();
}

void System::set_activeenvironment(const char* name) {
  environmentname_ = name;
  char set_environmentscript[MAX_PATH] = {0};
  snprintf(set_environmentscript, 
           sizeof(set_environmentscript) - 1, 
           "setmetatable(_G, {__index = %s});", 
           environmentname_.c_str());
  get_luastate()->DoString(set_environmentscript);
}

struct loadquest_t {
  int32_t id;
  const char* str;
};

void System::load_qusetfile() {
  const char* kQuestFileIndexFile = "Script.tab";
  //const char* kBlankString = "\t";
  char* address = NULL;
  uint64_t size = procedure::Base::resourceprovider_->loadresource(
      kQuestFileIndexFile, address, "General");
  int32_t i;
  if (size > 0) {
    pap_common_file::Database filedb(0);
    filedb.open_from_memory(address, address + size + 1);
    int32_t count = filedb.get_record_number();
    for (i = 0; i < count; ++i) {
      loadquest_t* content = (loadquest_t*)filedb.search_position(i, 0);
      if (content) {
        questfile_map_.insert(std::make_pair(content->id, content->str));
      }
    } //for loop
    procedure::Base::resourceprovider_->unloadresource(address, size);
  }
  else {
    VENGINE_SHOW("script::System::load_qusetfile: can't open file: %s",
                 kQuestFileIndexFile);
  }
}

vengine_script::Environment* System::getenvironment(const char* name) {
  std::list<Environment*>::iterator iterator;
  for (iterator = environmentlist_.begin();
       iterator != environmentlist_.end();
       ++iterator) {
    Environment* environment = *iterator;
    if (0 == strncmp(name, environment->getname(), 255)) {
      return dynamic_cast<vengine_script::Environment*>(environment);
    }
  }
  return NULL;
}

LuaPlus::LuaState* System::get_luastate() {
  return getself()->_get_luastate();
}

} //namespace script
