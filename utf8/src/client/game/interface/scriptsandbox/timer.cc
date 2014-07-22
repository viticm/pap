#include "client/game/timer/manager.h"
#include "client/game/interface/scriptsandbox/timer.h"


using namespace _interface::scriptsandbox::timer;

int32_t lua_set(LuaPlus::LuaState* luastate) {
  timer::Manager::getself()->lua_kill(luastate);
  int32_t result = timer::Manager::getself()->lua_kill(luastate);
  return result;
}

int32_t lua_kill(LuaPlus::LuaState* luastate) {
  int32_t result = timer::Manager::getself()->lua_kill(luastate);
  return result;
}

int32_t lua_clear(LuaPlus::LuaState* luastate) {
  int32_t result = 0; //timer::Manager::getself()->lua_clear(luastate);
  return result;
}
