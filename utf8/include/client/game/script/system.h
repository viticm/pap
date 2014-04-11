/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-8 17:33:14
 * @uses client game script system
 */
#ifndef CLIENT_GAME_SCRIPT_SYSTEM_H_
#define CLIENT_GAME_SCRIPT_SYSTEM_H_

#include "vengine/script/system.h"
#include "client/game/script/environment.h"

namespace script {

class System : public vengine_script::System {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   System();
   virtual ~System();
   static System* getself();

 //implement for abstract
 public:
   virtual LuaPlus::LuaState* get_luastate(); //获得lua状态
   //创建新的脚本环境
   virtual vengine_script::Environment* newenvironment(const char* name, 
                                                       const char* filename);

   virtual void destroyenvironment(vengine_script::Environment* environment);
   virtual vengine_script::Environment* getenvironment(const char* name);

 public:
   STRING get_activeenvironment() const; 
   void set_activeenvironment(const char* name);
   bool isenable_luacrash() const;
   const STRING& get_questfile(int32_t id);
   LuaPlus::LuaState* _get_luastate();

 public:
   virtual void init(void*);
   virtual void release();
   virtual void tick();

 protected:
   static System* self_;
   std::list<Environment*> environmentlist_;
   bool enable_luacrash_; //lua有异常时是否抛出
   std::map<int32_t, STRING> questfile_map_;
   STRING environmentname_;

 protected:
   void load_qusetfile(); //加载任务数据

};

}; //namespace script

#endif //CLIENT_GAME_SCRIPT_SYSTEM_H_
