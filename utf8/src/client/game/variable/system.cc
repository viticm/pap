#include "vengine/exception/base.h"
#include "vengine/base/util.h"
#include "global.h"
#include "client/game/event/system.h"
#include "client/game/script/system.h"
#include "client/game/variable/system.h"

namespace variable {

const char* kSystemConfigFile = "client.cfg";
const char* kUserConfigFile = "../accounts/user.cfg";
const char* kSpecialSections[] = {
  "View_Fanhunjiao",
  "View_Aplomb",
  "Login_Area",
  "Login_Server",
  "Login_Provider",
  "View_Resoution",
  "View_PiFeng",
  "View_FullScreen",
  "View_MaxWindow"
}; //特殊的一些配置项


int32_t convertsection_invector(const char* sectionstr, 
                                int32_t length, 
                                std::vector<STRING>& sectionvector);

System* System::self_ = NULL;

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(System);

System::System() {
  self_ = this;
  metatable_ = NULL;
}

System::~System() {
  SAFE_DELETE(metatable_);
}

System* System::getself() {
  return self_;
}

void System::load(const char* filename, variablemap& buffer) {
  VENGINE_ASSERT(filename);
  HANDLE filehandle = ::CreateFile(filename,
                                   GENERIC_READ,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   NULL,
                                   OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL,
                                   NULL);
  if (INVALID_HANDLE_VALUE == filehandle) return;
  uint64_t high;
  uint64_t filesize = ::GetFileSize(filehandle, &high);
  ::CloseHandle(filehandle); filehandle = NULL;
  if (0 == filesize) return;
  char* temp = new char[filesize];
  if (!temp) return;
  ::GetPrivateProfileSection("Variable", temp, filesize, filename);
  //分解
  std::vector<STRING> tempvector;
  convertsection_invector(temp, filesize, tempvector);
  DELETE_ARRAY(temp);
  //加入变量定义
  int32_t i;
  for (i = 0; i < static_cast<int32_t>(tempvector.size()); ++i) {
    STRING& line = tempvector[i];
    STRING::size_type point = line.find_first_of("= \t");
    if (STRING::npos == point) continue;
    STRING name = line.substr(0, point);
    char _temp[1024] = {0};
    ::GetPrivateProfileString("Variable", 
                              name.c_str(), 
                              "", 
                              _temp, 
                              sizeof(temp) - 1, 
                              filename);
    setvariable(name.c_str(), _temp, false);
  }
}

void System::save(const char* filename, variablemap& buffer) {
  const char* kConfigFile = filename;
  uint32_t fileattribute = ::GetFileAttributes(kConfigFile);
  if (fileattribute != INVALID_FILE_ATTRIBUTES) {
    if (FILE_ATTRIBUTE_READONLY & fileattribute)
      ::SetFileAttributes(kConfigFile, 
                          fileattribute & (~FILE_ATTRIBUTE_READONLY));
  }
  variablemap::iterator iterator;
  for (iterator = buffer.begin();
       iterator != buffer.end();
       ++iterator) {
    if (false == iterator->second.temp) {
      ::WritePrivateProfileString("Variable", 
                                  iterator->first.c_str(), 
                                  iterator->second.value.c_str(), 
                                  kConfigFile);
    }
  }
}

bool System::getvariable(const char* name, STRING& save) {
  STRING namestr = name;
  if ("View_Resoution" == namestr) {}
  variablemap::iterator find_iterator = currentmap_.find(name);
  if (currentmap_.end() == find_iterator) return false;
  save = find_iterator->second.value;
  return true;
}

void System::setvariable(const char* name, 
                         const char* value, 
                         bool temp, 
                         bool fireevent) {
  if (!name || '\0' == name[0] || !value) return;
  STRING namestr = name;
  if ("View_Resoution" == namestr) {} //???
  variable_t oldvariable = currentmap_[name];
  variable_t newvariable;
  newvariable.value = value;
  newvariable.temp = temp;
  currentmap_[name] = newvariable;
  if (oldvariable.value != value && fireevent) { //变量改变产生事件
    std::vector<STRING> params;
    params.push_back(name);
    params.push_back(value);
    event::System::getself()->push(vengine_game::event_id::kVariableChanged,
                                   params);
  }
}

void System::setfloat(const char* name, float value, bool temp) {
  char _temp[33] = {0};
  snprintf(_temp, sizeof(_temp) - 1, "%f", value);
  setvariable(name, value, temp);
}

void System::setint32(const char* name, int32_t value, bool temp) {
  char _temp[33] = {0};
  snprintf(_temp, sizeof(_temp) - 1, "%d", value);
  setvariable(name, value, temp);
}

void System::setuint32(const char* name, uint32_t value, bool temp) {
  char _temp[33] = {0};
  snprintf(_temp, sizeof(_temp) - 1, "%u", value);
  setvariable(name, value, temp);
}

void System::set_twofloat_vector(const char* name, 
                                 float x, 
                                 float y, 
                                 bool temp) {
  char _temp[64] = {0};
  snprintf(_temp, sizeof(_temp) - 1, "%f, %f", x, y);
  setvariable(name, value, temp);
}

void System::setvariable_delay(const char* name, const char* value) {
  needsave_map_[name] = value;
}

void System::init(void*) {
  currentmap_.clear();
  load(kSystemConfigFile, currentmap_);
  if (0 == getint32("GameServer_ConnectDirect")) 
    load(kUserConfigFile, currentmap_);
  needsave_map_.clear();
  ::CreateDirectory("../accounts/", 0);
  metatable_ = new LuaPlus::LuaObject;
  *metatable_ = script::System::getself()
                ->get_luastate()
                ->GetGlobals().CreateTable("Variable");
  metatable_->SetObject("__index", *metatable_);
  metatable_->RegisterObjectFunctor("GetVariable", &System::lua_getglobal);
  metatable_->RegisterObjectFunctor("SetVariable", &System::lua_setglobal);
  LuaPlus::LuaObject variableobject = script::System::getself()
                                      ->get_luastate()
                                      ->BoxPointer(this);
  variableobject.SetMetaTable(*metatable_);
  script::System::getself()
    ->get_luastate()
    ->GetGlobals().SetObject("Variable", variableobject);
  setint32("DebugMode", g_debugmode);
}

void System::reset() {
  setint32("_Self_Data_Complete", 0);
  setint32("_Display_Guild_Leave_Word", 0);
  setint32("_FirstEnterScene_", 0);
  setint32("_Tab_Flashed_", 0);
}

void System::saveaccount() {
  if (1 == getint32("GameServer_ConnectDirect")) return;
  STRING account, user, gameconnect;
  variablemap userconfig_map;
  variablemap::const_iterator iterator = currentmap_.begin();
  for (;iterator != currentmap_.end(); ++iterator) {
    STRING key = (*iterator).first;
    variable_t value = (*iterator).second;
    userconfig_map[key] = value;
  }
  //移除特殊选项
  int32_t i;
  int32_t needremove_count = static_cast<int32_t>(
      sizeof(kSpecialSections) / sizeof(const char*));
  for (i = 0; i < needremove_count; ++i) {
    variablemap::iterator find_iterator = 
      userconfig_map.find(kSpecialSections[i]);
    if (find_iterator != userconfig_map.end())
      userconfig_map.erase(find_iterator);
  }
  getvariable("Game_Account", account);
  getvariable("Character_Name", user);
  if (account.empty() || user.empty()) return;
  char fullpath[MAX_PATH] = {0};
  STRING accountencrypt;
  stringencrypt(account, accountencrypt);
  snprintf(fullpath, sizeof(fullpath) - 1, "../accounts/%s", accountencrypt);
  ::CreateDirectory(fullpath, NULL);
  char full_filename[MAX_PATH] = {0};
  STRING userencrypt;
  stringencrypt(user, userencrypt); //加密角色名
  snprintf(full_filename, 
           sizeof(full_filename) - 1, 
           "%s/%s.pfc", 
           fullpath, 
           full_filename);
  ::DeleteFile(full_filename);
  save(full_filename, userconfig_map);
}

void System::release() {
  STRING account, user, gameconnect;
  if (getint32("GameServer_ConnectDirect") != 1) {
    variablemap userconfig_map;
    int32_t i;
    int32_t specialsection_count = static_cast<int32_t>(
        sizeof(kSpecialSections) / sizeof(const char*));
    for (i = 0; i < specialsection_count; ++i) {
      userconfig_map[kSpecialSections[i]] = currentmap_[kSpecialSections[i]];
      currentmap_.erase(currentmap_.find(kSpecialSections[i])); //移除
    }
    save(kUserConfigFile, userconfig_map);
    getvariable("Game_Account", account);
    getvariable("Character_Name", user);
    if (account.empty() || user.empty()) return;
    char fullpath[MAX_PATH] = {0};
    STRING accountencrypt;
    stringencrypt(account, accountencrypt);
    snprintf(fullpath, sizeof(fullpath) - 1, "../accounts/%s", accountencrypt);
    ::CreateDirectory(fullpath, NULL);
    char full_filename[MAX_PATH] = {0};
    STRING userencrypt;
    stringencrypt(user, userencrypt); //加密角色名
    snprintf(full_filename, 
             sizeof(full_filename) - 1, 
             "%s/%s.pfc", 
             fullpath, 
             full_filename);
    ::DeleteFile(full_filename);
    save(full_filename, currentmap_);
  }
  else {
    save(kSystemConfigFile, currentmap_); //just for debug
  }
}

const STRING& System::getstring(const char* name, bool* have) {
  variablemap::iterator find_iterator = currentmap_.find(name);
  if (find_iterator == currentmap_.end()) {
    static STRING blank = "";
    if (have) *have = false;
    return blank;
  }
  if (have) *have = true;
  return find_iterator->second.value;
}

int32_t System::getint32(const char* name, bool* have) {
  int32_t result = -1;
  variablemap::iterator find_iterator = currentmap_.find(name);
  if (find_iterator == currentmap_.end()) {
    if (have) *have = false;
    return result;
  }
  if (have) *have = true;
  result = atoi(find_iterator->second.value);
  return result;
}

uint32_t System::getuint32(const char* name, bool* have) {
  uint32_t result = 0;
  variablemap::iterator find_iterator = currentmap_.find(name);
  if (find_iterator == currentmap_.end()) {
    if (have) *have = false;
    return result;
  }
  if (have) *have = true;
  sscanf(find_iterator->second.value, "%d", &result);
  return result;
}

float System::getfloat(const char* name, bool* have) {
  float result = 0.0f;
  variablemap::iterator find_iterator = currentmap_.find(name);
  if (find_iterator == currentmap_.end()) {
    if (have) *have = false;
    return result;
  }
  if (have) *have = true;
  result = atof(find_iterator->second.value);
  return result;
}

vengine_math::base::twofloat_vector_t System::get_twofloat_vector(
    const char* name,
    bool* have) {
  vengine_math::base::twofloat_vector_t result(0.0f, 0.0f);
  variablemap::iterator find_iterator = currentmap_.find(name);
  if (find_iterator == currentmap_.end()) {
    if (have) *have = false;
    return result;
  }
  char temp[64] = {0};
  strncpy (temp, find_iterator->second.value, sizeof(temp) - 1);
  char* position = strchr(temp, ',');
  if (!position) return result;
  *position = '\0'; //截断
  result = vengine_math::base::twofloat_vector_t(
      atof(temp),
      atof(position + 1));
  return result;
}

int32_t System::lua_setglobal(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsString() || !args[3].IsString() || !args[4].IsInteger()) {
    VENGINE_SHOW("variable::System::lua_setglobal: param error!");
    return 0;
  }
  if (!args[5].IsInteger()) {
    System::getself()->setvariable(args[2].GetString(), 
                                   args[3].GetString(), 
                                   args[4].GetInteger());
  }
  else {
    System::getself()->setvariable(args[2].GetString(), 
                                   args[3].GetString(), 
                                   args[4].GetInteger(), 
                                   args[5].GetInteger());
  }
  return 0;
}

int32_t System::lua_getglobal(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!args[2].IsString()) {
    luastate->PushNil();
    return 1;
  }
  STRING result;
  bool exist = System::getself()->getvariable(args[2].GetString(), result);
  if (exist) {
    luastate->PushString(result.c_str());
  }
  else {
    luastate->PushNil();
  }
  return 1;
}

void System::setvariable_default(const char* name, const char* value) {
  STRING oldvariable;
  bool exist = getvariable(name, oldvariable);
  if (exist) return;
  setvariable(name, value, false);
}

void System::load_privateconfig() {
  STRING account, user;
  getvariable("Game_Account", account);
  getvariable("Character_Name", user);
  convert_oldsaving_pfc(account, user);
  ::WritePrivateProfileString("Variable", 
                              "Login_Area", 
                              getstring("Login_Area").c_str(), 
                              kUserConfigFile);
  ::WritePrivateProfileString("Variable", 
                              "Login_Server",
                              getstring("Login_Server").c_str(),
                              kUserConfigFile);
  ::WritePrivateProfileString("Variable", 
                              "Login_Provider",
                              getstring("Login_Provider").c_str(),
                              kUserConfigFile);
  STRING accountencrypt, userencrypt;
  stringencrypt(account, accountencrypt);
  stringencrypt(user, userencrypt);
  char temp[MAX_PATH] = {0};
  snprintf(temp, 
           sizeof(temp) - 1, 
           "../accounts/%s/%s.pfc", 
           accountencrypt, 
           userencrypt);
  load(temp, currentmap_);
  vengine_base::util::savelog("variable::System::load_privateconfig: %s, %s",
                              account.c_str(),
                              user.c_str());
}

void System::getvariable_infile(const char* filename,  
                                const char* title,
                                const char* key,
                                char* save,
                                uint16_t size) {
  convert_oldsaving_cfg(filename);
  STRING deststr;
  STRING sourcestr = filename;
  stringencrypt(filename, deststr);
  char temp[MAX_PATH] = {0};
  snprintf(temp, 
           sizeof(temp) - 1, 
           "../accounts/%s/%s.cfg", 
           deststr.c_str(), 
           deststr.c_str());
  GetPrivateProfileString(title, key, "", value, size, temp);
}

void System::setvariable_infile(const char* filename,
                                const char* title,
                                const char* key,
                                const char* value) {
  STRING deststr;
  STRING sourcestr = filename;
  stringencrypt(filename, deststr);
  char fullpath[MAX_PATH] = {0};
  snprintf(fullpath, sizeof(fullpath) - 1, "../accounts/%s", deststr.c_str());
  ::CreateDirectory(fullpath, 0);
  char temp[MAX_PATH] = {0};
  snprintf(temp, 
           sizeof(temp) - 1, 
           "../accounts/%s/%s", 
           deststr.c_str(), 
           deststr.c_str());
  WritePrivateProfileString(title, key, value, temp);
}

void System::stringencrypt(const STRING& in, STRING& out) {
  out.clear();
  int32_t sourcelength = static_cast<int32_t>(in.size());
  out.append("#");
  int32_t i;
  for (i = 0; i < sourcelength; ++i) {
    const char* str = in.c_str();
    unsigned char _char = str[i];
    char tempstr[8] = {0};
    itoa(_char, tempstr, 16);
    out.append(tempstr);
  }
}

void System::convert_oldsaving_cfg(const STRING& account) {
  char temp[MAX_PATH] = {0};
  STRING dirfromat = "../accounts/%s";
  STRING fileformat = "../accounts/%s/%s.cfg";
  STRING accountencrypt = "";
  stringencrypt(account, accountencrypt);
  snprintf(temp, sizeof(temp) - 1, dirfromat.c_str(), account.c_str());
  STRING sourcedir = temp;
  snprintf(temp, sizeof(temp) - 1, dirfromat.c_str(), accountencrypt.c_str());
  STRING destinationdir = temp;
  ::MoveFile(sourcedir, destinationdir); //重命名
  snprintf(temp, 
           sizeof(temp) - 1, 
           filefromat.c_str(), 
           account.c_str(), 
           account.c_str());
  STRING sourcefile = temp;
  snprintf(temp, 
           sizeof(temp) - 1, 
           filefromat.c_str(), 
           accountencrypt.c_str(), 
           accountencrypt.c_str());
  STRING destinationfile = temp;
  ::MoveFile(sourcefile, destinationfile);
}

void System::convert_oldsaving_pfc(const STRING& account, 
                                   const STRING& character) {
  char temp[MAX_PATH] = {0};
  STRING dirfromat = "../accounts/%s";
  STRING fileformat = "../accounts/%s/%s.cfg";
  STRING accountencrypt = "";
  stringencrypt(account, accountencrypt);
  snprintf(temp, sizeof(temp) - 1, dirfromat.c_str(), account.c_str());
  STRING sourcedir = temp;
  snprintf(temp, sizeof(temp) - 1, dirfromat.c_str(), accountencrypt.c_str());
  STRING destinationdir = temp;
  ::MoveFile(sourcedir, destinationdir); //重命名
  STRING characterencrypt = "";
  stringencrypt(character, characterencrypt);
  snprintf(temp, 
           sizeof(temp) - 1, 
           filefromat.c_str(), 
           account.c_str(), 
           character.c_str());
  STRING sourcefile = temp;
  snprintf(temp, 
           sizeof(temp) - 1, 
           filefromat.c_str(), 
           accountencrypt.c_str(), 
           characterencrypt.c_str());
  STRING destinationfile = temp;
  ::MoveFile(sourcefile, destinationfile);
}

int32_t convertsection_invector(const char* sectionstr, 
                                int32_t length, 
                                std::vector<STRING>& sectionvector) {
  register const char* buffer = sectionstr;
  sectionvector.clear();
  for (;;) {
    if (('\0' == *buffer && '\0' == *(buffer - 1)) || 
        (buffer - sectionstr >= length)) {
      break;
    }
    if ('\0' == *buffer) {
      ++buffer;
      continue;
    }
    STRING single = buffer;
    sectionvector.push_back(single);
    buffer += strlen(buffer) + 1;
  }
  int32_t result = static_cast<int32_t>(sectionvector.size());
  return result;
}

} //namespace variable
