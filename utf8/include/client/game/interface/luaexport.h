/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id luaexport.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-12 11:38:18
 * @uses client game interface for lua export template class
 */
#ifndef PAP_CLIENT_GAME_INTERFACE_LUAEXPORT_H_
#define PAP_CLIENT_GAME_INTERFACE_LUAEXPORT_H_

#include "vengine/exception/base.h"
#include "client/game/global.h"
#include "client/game/script/system.h"

namespace interface {

template <class T>
class LuaExport {

 public:
   LuaExport(const char* name, LuaPlus::LuaState* luastate = NULL) {
     VENGINE_ASSERT(name);
     self_ = dynamic_cast<T*>(this);
     LuaPlus::LuaState* _luastate = 
       luastate ? luastate : script::System::getself()->_get_luastate();
     metatable_ = new LuaPlus::LuaObject;
     *metatable_ = _luastate->GetGlobals().CreateTable(name);
     metatable_->SetObject("__index", *metatable_);
     LuaPlus::LuaObject luaobjcet = _luastate->BoxPointer(self_);
     luaobjcet.SetMetaTable(*metatable_);
     _luastate->GetGlobals().SetObject(name, luasobject);
   };

   ~LuaExport() {
     SAFE_DELETE(metatable_); 
   };

   template <class Callee>
   void registerfunction(const char* functionname, 
                         (int32_t Callee::*function_)(LuaPlus::LuaState*)) {
     metatable_->RegisterObjectFunctor(functionname, function);
   };

   static T* getself() { return self_; }

 protected:
   static T* self_;
   static LuaPlus::LuaState* metatable_;

 private:
   LuaExport(const LuaExport& object);
   LuaExport& operator=(const LuaExport& object);

};

}; //namespace interface

#endif //PAP_CLIENT_GAME_INTERFACE_LUAEXPORT_H_
