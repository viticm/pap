#include "client/game/timer/manager.h"
#include "client/game/interface/scriptsandbox/timer.h"

namespace interface {

namespace scriptsandbox {

namespace timer {

int32_t lua_set(LuaPlus::LuaState* luastate) {
  int32_t result = timer::Manager::getself()->lua_set(luastate);
  return result;
}

int32_t lua_kill(LuaPlus::LuaState* luastate) {
  int32_t result = timer::Manager::getself()->lua_kill(luastate);
  return result;
}

int32_t lua_clear(LuaPlus::LuaState* luastate) {
  int32_t result = timer::Manager::getself()->lua_clear(luastate);
  return result;
}

} //namespace scriptsandbox

} //namespace timer

} //namespace interface
