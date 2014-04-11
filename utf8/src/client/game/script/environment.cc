#include "LuaPlus.h"
#include "vengine/exception/base.h"
#include "client/game/procedure/base.h"
#include "client/game/script/system.h"
#include "client/game/script/environment.h"

namespace script {

Environment::Environment(const char* name, const char* filename) {
  VENGINE_ASSERT(name);
  name_ = name;
  filename_ = filename;
  name_inlua_ = filename_+"_Env";
  environmentobject_ = 
    System::getself()
    ->get_luastate()
    ->GetGlobals().CreateTable(name_inlua_.c_str());
}

Environment::~Environment() {
  //do nothing
}

void Environment::executescript(const char* filename) {
  char* address = NULL;
  uint64_t size = procedure::Base::resourceprovider_->loadresource(
      filename, address, "General");
  if (size > 0) {
    int32_t result = System::getself()->executestring(address);
    procedure::Base::resourceprovider_->unloadresource(address, size);
    return result;
  }
  return 0;
}

void Environment::executestring_withcpp_exception(const char* str) {
  try {
    //保存旧环境名
    STRING oldenvironment = System::getself()->get_activeenvironment();
    //设定环境
    System::getself()->set_activeenvironment(name_inlua_.c_str());
    //执行函数
    System::getself()->get_luastate()->DoString(str);
    //恢复环境
    if (!oldenvironment.empty()) {
      System::getself()->set_activeenvironment(oldenvironment.c_str());
    }
  }
  catch (const std::exception& exception) {
    static STRING cpp_exception;
    cpp_exception = exception.what();
    //转化为结构化异常
    LPVOID exception_pointer = &cpp_exception;
    ::RaiseException(0XE000C0DE,
                     EXCEPTION_NONCONTINUABLE, //不可继续的严重错误
                     1, //一个参数
                     (const ULONG_PTR*)&exception_pointer);
  }
  catch (...) {
    throw;
  }
}

void Environment::executestring_withgen_exception(const char* str) {
  char title[MAX_PATH] = {0};
  snprintf(title, sizeof(title) - 1, "lua: %s", filename_.c_str());
  __try {
    executestring_withcpp_exception(str);
  }
  __except (vengine_exception::base::processinner(
        GetExceptionInformation(), 
        g_mainwindow_handle, 
        title), EXCEPTION_EXECUTE_HANDLER) {}
}

void Environment::executestring(const char* str) {
  //容纳任何异常
  if (!System::getself()->isenable_luacrash()) {
    try {
      //保存旧环境名
      STRING oldenvironment = System::getself()->get_activeenvironment();
      //设定环境
      System::getself()->set_activeenvironment(name_inlua_.c_str());
      //执行函数
      System::getself()->get_luastate()->DoString(str);
      //恢复环境
      if (!oldenvironment.empty()) {
        System::getself()->set_activeenvironment(oldenvironment.c_str());
      }
    }
    catch(...) {
    }
    return;
  }
  //进入结构化异常块执行
  executestring_withgen_exception(str);
}

void Environment::executefunction(const char* functionname, 
                                  const char* param) {
  char functionstr[MAX_PATH] = {0};
  snprintf(functionstr, 
           sizeof(functionstr) - 1, 
           "%s(%s)", 
           functionname, param ? param : "");
  executestring(functionstr);
}

const char* Environment::getname() const {
  return name_.c_str();
}

LuaPlus::LuaObject* Environment::get_luaobject() {
  return &environmentobject_;
}

} //namespace script
