/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id environment.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 19:36:10
 * @uses vengine script environment module
 */
#ifndef VENGINE_SCRIPT_ENVIRONMENT_H_
#define VENGINE_SCRIPT_ENVIRONMENT_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

/* use luaplus */
namespace LuaPlus {

class LuaState;
class LuaObject;

}; //namespace LuaPlus

namespace vengine_script {

class Environment {

 public:
   virtual const char* getname() const = 0;
   virtual void executescript(const char* filename) = 0;
   virtual void executefunction(const char* functionname, 
                                const char* param = NULL) = 0;
   virtual void executestring(const char* str) = 0;
   virtual LuaPlus::LuaObject* get_luaobject() = 0;

};

}; //namespace vengine_script

#endif //VENGINE_SCRIPT_ENVIRONMENT_H_
