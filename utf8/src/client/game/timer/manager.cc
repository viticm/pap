#include "common/sys/assert.h"
#include "vengine/exception/base.h"
#include "client/game/stdafx.h"
#include "client/game/script/system.h"
#include "client/game/timer/manager.h"

namespace timer {

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(
    Manager,
    VENGINE_KERNEL_GETCLASS(System));

Manager* Manager::self_ = NULL;

Manager::Manager() {
  self_ = this;
  map1_.clear();
  map2_.clear();
}

Manager::~Manager() {
  clear();
}

void Manager::init(void* pointer) {
  //do nothing
}

Manager* Manager::getself() {
  return self_;
}

int32_t Manager::add(timer_function function, uint32_t elapse) {
  uint32_t id = static_cast<uint32_t>(
      ::SetTimer(NULL,(UINT_PTR)0, elapse, function));
  AssertEx(id > 0, "timer::Manager::add: ::SetTimer failed!");
  if (0 == id) return id;
  param1_t param;
  param.id = id;
  param.function = function;
  map1_.insert(std::make_pair(id, param));
  return id;
}

int32_t Manager::add(const STRING& environment,
                     const STRING& function,
                     uint32_t elapse) {
  uint32_t id = static_cast<uint32_t>(
    ::SetTimer(NULL,(UINT_PTR)0, elapse, Manager::default_eventfunction));
  AssertEx(id > 0, "timer::Manager::add: ::SetTimer failed!");
  if (0 == id) return id;
  param2_t param;
  param.id = id;
  param.function = function;
  param.environment = environment;
  map2_.insert(std::make_pair(id, param));
  return id;
}

void Manager::remove(uint32_t id) {
  param1_iterator iterator1 = map1_.find(id);
  if (iterator1 != map1_.end()) {
    ::KillTimer(NULL, id);
    return;
  }
  param2_iterator iterator2 = map2_.find(id);
  if (iterator2 != map2_.end()) {
    ::KillTimer(NULL, id);
    return;
  }
}

void Manager::remove(timer_function function) {
  param1_iterator iterator1;
  for (iterator1 = map1_.begin();
       iterator1 != map1_.end();
       ++iterator1) {
    if (iterator1->second.function == function) {
      iterator1 = map1_.erase(iterator1);
      return;
    }
  }
}

void Manager::remove(const STRING& function) {
  param2_iterator iterator2;
  for (iterator2 = map2_.begin();
       iterator2 != map2_.end();
       ++iterator2) {
    if (iterator2->second.function == function) {
      iterator2 = map2_.erase(iterator2);
      return;
    }
  }
}

void Manager::get_scriptenvironment(uint32_t id, 
                                    STRING& environment, 
                                    STRING& script) {
  param2_iterator iterator2;
  for (iterator2 = map2_.begin();
       iterator2 != map2_.end();
       ++iterator2) {
    if (iterator2->first == id) {
      environment = iterator2->second.environment;
      script = iterator2->second.function;
      return;
    }
  }
}

void __stdcall Manager::default_eventfunction(HWND, 
                                              UINT, 
                                              UINT id, 
                                              DWORD) {
  if (Manager::getself()) {
    STRING environment, script;
    Manager::getself()->get_scriptenvironment(id, environment, script);
    if (environment != "" && script != "") {
      environment += "_Env";
      try {
        //保存旧环境名
        STRING oldenvironment = 
          script::System::getself()->get_activeenvironment();
        //设定环境
        script::System::getself()->set_activeenvironment(environment.c_str());
        //执行函数
        script::System::getself()->get_luastate()->DoString(script.c_str());
        //恢复环境
        if (!oldenvironment.empty()) {
          script::System::getself()->set_activeenvironment(
              oldenvironment.c_str());
        }
      }
      catch(...) {
        STRING str = "执行环境:"+environment+",函数:"+script;
        throw str;
        //MessageBox(NULL, str.c_str(), "定时器使用错误" ,MB_ICONSTOP|MB_OK);
      }
    }
  }
}

void Manager::clear() {
  param1_iterator iterator1;
  for (iterator1 = map1_.begin();
       iterator1 != map1_.end();
       ++iterator1) {
    ::KillTimer(NULL, iterator1->first);
  }
  map1_.clear();
  param2_iterator iterator2;
  for (iterator2 = map2_.begin();
       iterator2 != map2_.end();
       ++iterator2) {
    ::KillTimer(NULL, iterator2->first);
  }
  map2_.clear();
}

int32_t Manager::lua_set(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[1].IsString() || args[2].IsString() || !args[3].IsInteger()) {
    luastate->PushInteger(-1);
    return 1;
  }
  STRING environment = args[1].GetString();
  STRING function = args[2].GetString();
  uint32_t elapse = args[3].GetInteger();
  int32_t id = add(environment, function, elapse);
  luastate->PushInteger(id);
  return 1;
}

int32_t Manager::lua_kill(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (args[1].IsInteger()) {
    uint32_t id = args[1].GetInteger();
    remove(id);
    luastate->PushBoolean(true);
    return 1;
  }

  if (args[1].IsString()) {
    STRING function = args[1].GetString();
    remove(function);
    luastate->PushBoolean(true);
    return 1;
  }
  luastate->PushBoolean(false);
  return 1;
}

} //namespace timer
