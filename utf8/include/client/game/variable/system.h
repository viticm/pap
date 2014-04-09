/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 16:27:01
 * @uses pap client game variable system module
 */
#ifndef PAP_CLIENT_GAME_VARIABLE_SYSTEM_H_
#define PAP_CLIENT_GAME_VARIABLE_SYSTEM_H_

#include "vengine/variable/system.h"

namespace LuaPlus {
class LuaState;
class LuaObject;
}; //namespace LuaPlus

namespace variable {

class System : public vengine_variable::System {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   System();
   virtual ~System();

 public:
   static System* self_;

 public:
   virtual void init(void*);
   virtual void release();

 //implement from abstract
 public:
   //得到某个变量的值，如果不存在，则返回false
   virtual bool getvariable(const char* name, STRING& save);
   //设置某个变量的值，如果不存在，则首先创建
   virtual void setvariable(const char* name, 
                            const char* value, 
                            bool temp = true, 
                            bool fireevent = true);

   //设置某个变量的值，但并不马上生效, 下一次启动时才会生效
   virtual void setvariable_delay(const char* name, const char* value);

   /* 快速设置方法 */
   virtual void setint32(const char* name, 
                         const char* value, 
                         bool temp = true);
   virtual void setuint32(const char* name, 
                          const char* value, 
                          bool temp = true);
   virtual void setfloat(const char* name, 
                         const char* value, 
                         bool temp = true);
   virtual void set_twofloat_vector(const char* name,
                                    const char* value,
                                    bool temp = true);

   /* 快速获取方法 */
   virtual const STRING& getstring(const char* name, bool* have = NULL);
   virtual int32_t getint32(const char* name, bool* have = NULL);
   virtual uint32_t getuint32(const char* name, bool* have = NULL);
   virtual float getfloat(const char* name, bool* have = NULL);
   virtual vengine_math::base::twofloat_vector_t get_twofloat_vector(
       const char* name, bool* have = NULL);
   virtual void setvariable_default(const char* name, const char* value);
   virtual void load_privateconfig();
   virtual void getvariable_infile(const char* filename,  
                                   const char* key,
                                   char* save,
                                   uint16_t size);
   virtual void setvariable_infile(const char* filename,
                                   const char* key,
                                   const char* value);
   virtual void reset();

 public: //for exports
   int32_t lua_setglobal(LuaPlus::LuaState* luastate);
   int32_t lua_getglobal(LuaPlus::LuaState* luastate);

 protected:
   static System* self_;
   LuaPlus::LuaObject* metatable_;
   struct variable_t {
     STRING value;
     bool temp;
   };
#ifdef __SGI_STL_PORT
   typedef std::hash_map<STRING, variable_t> variablemap;
#else
   typedef stdext::hash_map<STRING, variable_t> variablemap;
#endif
   variablemap currentmap_;
   variablemap needsave_map_;

 protected:
   void load(const char* filename, variablemap& buffer);
   void save(const char* filename, variablemap& buffer);
   void stringencrypt(const STRING& in, STRING& out);
   void convert_oldsaving_pfc(const STRING& account, const STRING& character);
   void convert_oldsaving_cfg(const STRING& account);
   void saveaccount(); //账号保存

};

}; //namespace variable

#endif //PAP_CLIENT_GAME_VARIABLE_SYSTEM_H_
