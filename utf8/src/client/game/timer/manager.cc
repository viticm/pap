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
      ::SetTimer(NULL,(UINT_PTR)0, elapse, function));
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
  param2_iterator iterator1;
  for (iterator1 = map1_.begin();
       iterator1 != map1_.end();
       ++iterator1) {
    if (iterator1->second.function == function) {
      iterator1 = map1_.erase(iterator1);
      return;
    }
  }
}

} //namespace timer
