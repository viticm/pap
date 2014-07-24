/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-9 15:58:49
 * @uses pap client game database system class
 */
#ifndef PAP_CLIENT_GAME_DATABASE_SYSTEM_H_
#define PAP_CLIENT_GAME_DATABASE_SYSTEM_H_

#include "vengine/db/system.h"
#include "client/game/database/file.h"

namespace database {

class System : public vengine_db::System {

VENGINE_KERNEL_DECLARE_DYNAMIC(database_System);

 public:
   System();
   virtual ~System();

 public:
   static System* getself();

 public: //implement from abstract
   virtual void open(); //打开所有数据
   virtual void close(); //关闭所有数据
   virtual const File* get(int32_t id) const;

 public:
   virtual void init(void*);
   virtual void release();

 protected:
   std::map<int32_t, File*> database_map_; //文件数据索引
   static System* self_;
};

}; //namespace database

#define DATABASE_DEFINEHANDLE(dbname, id) \
  const static vengine_db::File* dbname = NULL; \
  if (!dbname) dbname = procedure::Base::dbsystem_->get(id); \
  VENGINE_ASSERT(dbname);

#endif //PAP_CLIENT_GAME_DATABASE_SYSTEM_H_
