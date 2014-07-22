/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id profile.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 13:42:44
 * @uses vengine capability profile module
 */
#ifndef VENGINE_CAPABILITY_PROFILE_H_
#define VENGINE_CAPABILITY_PROFILE_H_

#include <hash_set>
#include <hash_map>
#include "vengine/config.h"

namespace vengine_capability {

namespace profile {

struct treenode_t;

//堆栈中的节点(用于push/pop)
struct VENGINE_API stacknode_t {
  STRING name; //名称
  LARGE_INTEGER starttime;
  treenode_t* treenode; //树形节点指针
  stacknode_t(const char* _name = NULL, const char* extensionname = NULL);
};

//堆栈
struct stack_t {
  stack_t() {};
  enum {
    kStackNumberMax = 256,
  };
  //节点堆
  stacknode_t stacknode_list[kStackNumberMax];
  //栈顶指针，初始为0
  uint16_t topindex;
#ifdef __SGI_STL_PORT
  typedef std::hash_set<STRING> hash_nameset;
#else
  typedef stdext::hash_set<STRING> hash_nameset;
#endif
  hash_nameset hashname;
};

//tree node, 用于统计
struct treenode_t {
#ifdef __SGI_STL_PORT
  typedef std::hash_map<STRING, treenode_t*> hash_treenode;
#else
  typedef stdext::hash_map<STRING, treenode_t*> hash_treenode;
#endif
  STRING name;
  uint32_t invokecount; //运行（调用）次数
  hash_treenode childmap;
  treenode_t* parentnode;
  LARGE_INTEGER totaltime; //占用时间
  ~treenode_t();
};

//节点树
struct tree_t {
  treenode_t rootnode;
  treenode_t* currentnode;
};

//节点树函数指针
typedef void (__stdcall* function_dump)(const tree_t* nodetree);

extern "C" {
  VENGINE_API void pushnode(const char* name, const char* extensionname = NULL);
  VENGINE_API void popnode(const char* name = NULL);
  VENGINE_API void dumpstack(function_dump function); //查询节点信息
};

void tick(); //for vengine time system

}; //namespace profile

}; //namespace vengine_capability

#endif //VENGINE_CAPABILITY_PROFILE_H_
