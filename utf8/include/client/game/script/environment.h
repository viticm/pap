/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id environment.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-8 17:40:06
 * @uses client game script environment module
 */
#ifndef CLIENT_GAME_SCRIPT_ENVIRONMENT_H_
#define CLIENT_GAME_SCRIPT_ENVIRONMENT_H_

#include "LuaPlus.h"
#include "vengine/script/environment.h"

namespace script {

class Environment : public vengine_script::Environment {

 public:
   virtual const char* getname() const;
   virtual void executescript(const char* filename);
   virtual void executefunction(const char* functionname, 
                                const char* param = NULL);
   virtual void executestring(const char* str);
   virtual LuaPlus::LuaObject* get_luaobject();


 protected:
   friend class System;
   STRING name_;
   STRING name_inlua_;
   STRING filename_;
   LuaPlus::LuaObject environmentobject_;

 protected:
   Environment(const char* name, const char* filename);
   virtual ~Environment();

};

}; //namespace script

#endif //CLIENT_GAME_SCRIPT_ENVIRONMENT_H_
