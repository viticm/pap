/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id class.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-17 16:28:41
 * @uses vengine kernel class module
 */
#ifndef VENGINE_KERNEL_CLASS_H_
#define VENGINE_KERNEL_CLASS_H_

#include "vengine/config.h"
#include "vengine/exception/base.h"

namespace vengine_kernel {

class Node;

struct VENGINE_API class_t {
  const char* classname; //class name
  int32_t objectsize; //class size
  Node* (__stdcall* newobject_pointer)(); //函数指针，用于生成一个Node类实例
  class_t* baseclass; //基类
  class_t* nextclass; //下一个类
  Node* newobject(const char* name); //生成对象方法
};

}; //namespace vengine_kernel

//据类名取得定义类
#define VENGINE_KERNEL_GETCLASS(classname) (&classname::class_##classname_)

//定义声明宏
#define VENGINE_KERNEL_DECLARE_DYNAMIC(classname) \
 public: \
   static vengine_kernel::class_t class_##classname_; \
   virtual const vengine_kernel::class_t* getclass() const; \
   static vengine_kernel::Node* __stdcall newobject();

//定义实现宏
#define VENGINE_KERNEL_IMPLEMENT_DYNAMIC(classname, baseclass) \
static char name_##classname[] = #classname; \
vengine_kernel::class_t classname::class_##classname_ = { \
  name_##classname, sizeof(classname), classname::newobject, baseclass, NULL \
}; \
const vengine_kernel::class_t* classname::getclass() const { \
  return &classname::class_##classname_; \
}; \
vengine_kernel::Node* classname::newobject() { \
  return new classname; \
}

//纯虚类类定义实现宏
#define VENGINE_KERNEL_IMPLEMENT_VIRTUAL_DYNAMIC(classname, baseclass) \
static char name_##classname[] = #classname; \
vengine_kernel::class_t classname::class_##classname_ = { \
  name_##classname, sizeof(classname), classname::newobject, baseclass, NULL \
}; \
const vengine_kernel::class_t* classname::getclass() const { \
  return &classname::class_##classname_; \
}; \
vengine_kernel::Node* classname::newobject() { \
  VENGINE_SHOW("pure a virtual class"); \
  return NULL; \
}

#endif //VENGINE_KERNEL_CLASS_H_
