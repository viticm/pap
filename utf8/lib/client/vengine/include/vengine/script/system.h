/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 19:49:05
 * @uses vengine script system module
 */
#ifndef VENGINE_SCRIPT_SYSTEM_H_
#define VENGINE_SCRIPT_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"
#include "vengine/script/environment.h"

/* use luaplus */
namespace LuaPlus {

class LuaState;
class LuaObject;

}; //namespace LuaPlus

namespace vengine_script {

VENGINE_API class System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   virtual LuaPlus::LuaState* get_luastate() = 0; //获得lua状态
   //创建新的脚本环境
   virtual Environment* newenvironment(const char* name, 
                                       const char* filename) = 0;

   virtual void destroyenvironment(Environment* environment) = 0;
   virtual Environment* getenvironment(const char* name);

};

}; //namespace vengine_script

#endif //VENGINE_SCRIPT_SCRIPT_H_
