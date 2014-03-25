/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-12 11:15:08
 * @uses the vengine kernel base class
 */
#include "vengine/config.h"
#include "vengine/kernel/node.h"

//插件必须导出一个名为DllMagicCode的U32整数,
//值等于 VENGINE_DLL_MAGIC_CODE|VENGINE_KERNEL_VERSION
#define VENGINE_DLL_MAGIC_CODE (static_cast<uint32_t>(0XC0DE0000))

namespace vengine_kernel {

//for plugin
typedef void (__stdcall* function_dllinit)(void*);
typedef void (__stdcall* function_dllrelease)(void);

class VENGINE_API Base {

 public:
   Base();
   virtual ~Base();

 public:
   //某个类注册到全局类检索表函数
   void registerclass(class_t* newclass);
   //检查两个类是否具有继承关系
   bool isinheritance(const class_t* thisclass, const class_t* baseclass) const;
   //根据类名获得定义类
   class_t* getclass(const char* name);

 //node operator
 public:
   virtual Node* newnode(const char* classname, 
                         const char* position, 
                         const char* nodename);
   virtual Node* newnode(const char* classname, 
                         Node* parentnode, 
                         const char* nodename);
   //get node by node name, sample: getnode("bin\\data")
   virtual Node* getnode(const char* name);
 
 //plugin
 public:
   bool loadplugin(const char* name, void* param);
   void shutdown(); //kernel close

 public:
   static Base* getself();
   static void* get_userdata();
   static void set_userdata(void* data);

 protected:
   static Base* self_;
   static void* userdata_;
   std::map<STRING, class_t*> classmap_; //is a map not a list
   class_t* firstclass_inmap_;
   Node noderoot_;

 protected:
   struct plugininfo_t {
     HMODULE hmodule;
     STRING pluginfile;
     function_dllinit dllinit_pointer;
     function_dllrelease dllrelease_pointer;
   };
   void free_allplugin();
   std::vector<plugininfo_t> pluginlist_; //all plugin in a vector
};

}; //namespace vengine_kernel