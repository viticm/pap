#include "client/game/database/system.h"

namespace database {

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(System);

System* System::self_ = NULL;

System::System() {
  self_ = this;
}

System::~System() {
  //do nothing
}

System* System::getself() {
  return self_;
}

void System::init(void*) {
  open();
}

void System::release() {
  close();
}

void System::open() {
  struct dbdefine_t {
    int32_t id;
    const char* filename;
  };
  
  dbdefine_t filedb_toload[] = {
    //UI 布局定义
    {vengine_db::structs::ui::kLayoutDefineId, "ui_layoutdefine.txt"},
  };

  int32_t count = sizeof(filedb_toload) / sizeof(dbdefine_t);
  int32_t i;
  for (i = 0; i < count; ++i) {
    File* db = new File(filedb_toload[i].id); 
    if (!db) 
      VENGINE_SHOW("database::System::open: new File(%d) error", 
                   filedb_toload[i].id);
    if (!db->open_fromtxt(filedb_toload[i].filename)) {
      VENGINE_SHOW("database::System::open: open_fromtxt(%s) error",
                   filedb_toload[i].filename);
    }
    
    if (database_map_.find(filedb_toload[i].id) != database_map_.end()) {
      VENGINE_SHOW("database::System::open: reload file: %s", 
                   filedb_toload[i].filename);
    }
    database_map_.insert(std::make_pair(filedb_toload[i].id, db));
  }
}

} //namespace database
