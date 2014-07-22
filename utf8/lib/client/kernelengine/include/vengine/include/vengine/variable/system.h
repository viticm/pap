/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 16:27:01
 * @uses vengine variable system module
 */
#ifndef VENGINE_VARIABLE_SYSTEM_H_
#define VENGINE_VARIABLE_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"
#include "vengine/math/base.h"

namespace vengine_variable {

class VENGINE_API System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   //得到某个变量的值，如果不存在，则返回false
   virtual bool getvariable(const char* name, STRING& save) = 0;
   //设置某个变量的值，如果不存在，则首先创建
   virtual void setvariable(const char* name, 
                            const char* value, 
                            bool temp = true, 
                            bool fireevent = true) = 0;

   //设置某个变量的值，但并不马上生效, 下一次启动时才会生效
   virtual void setvariable_delay(const char* name, const char* value) = 0;

   /* 快速设置方法 */
   virtual void setint32(const char* name, 
                         int32_t value, 
                         bool temp = true) = 0;
   virtual void setuint32(const char* name, 
                          uint32_t value, 
                          bool temp = true) = 0;
   virtual void setfloat(const char* name, 
                         float value, 
                         bool temp = true) = 0;
   virtual void set_twofloat_vector(const char* name,
                                    float value1,
                                    float value2,
                                    bool temp = true) = 0;

   /* 快速获取方法 */
   virtual const STRING& getstring(const char* name, bool* have = NULL) = 0;
   virtual int32_t getint32(const char* name, bool* have = NULL) = 0;
   virtual uint32_t getuint32(const char* name, bool* have = NULL) = 0;
   virtual float getfloat(const char* name, bool* have = NULL) = 0;
   virtual vengine_math::base::twofloat_vector_t get_twofloat_vector(
       const char* name, bool* have = NULL) = 0;
   virtual void setvariable_default(const char* name, const char* value) = 0;
   virtual void load_privateconfig() = 0;
   virtual void getvariable_infile(const char* filename,  
                                   const char* title,
                                   const char* key,
                                   char* save,
                                   uint16_t size) = 0;
   virtual void setvariable_infile(const char* filename,
                                   const char* title,
                                   const char* key,
                                   const char* value) = 0;
   virtual void reset() = 0;

};

}; //namespace vengine_variable

#endif //VENGINE_VARIABLE_SYSTEM_H_
