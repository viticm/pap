#include "vengine/stdafx.h"
#include "vengine/exception/base.h"
#include "vengine/capability/profile.h"

namespace vengine_capability {

namespace profile {

bool g_askdump = false; //是否有查询请求进入
function_dump g_functiondump; //查询请求函数指针

stack_t& getstack() {
  static stack_t stack;
  return stack;
}

tree_t& gettree() {
  static tree_t tree;
  static bool first = true;
  if (first) {
    tree.rootnode.name = "root";
    tree.rootnode.parentnode = NULL;
    tree.rootnode.invokecount = 0;
    tree.rootnode.totaltime.QuadPart = 0;
    tree.currentnode = &(tree.rootnode);
    first = false;
  }
  return tree;
}

stacknode_t::stacknode_t(const char* _name, const char* extensionname) {
  QueryPerformanceCounter(&starttime);
  if (!_name) {
    name.reserve(128);
  }
  else {
    name = _name;
    if (extensionname) {
      name += ".";
      name += extensionname;
    }
  }
  treenode = NULL;  
}

treenode_t::~treenode_t() {
  hash_treenode::iterator treenode_iterator;
  for (treenode_iterator = childmap.begin(); 
      treenode_iterator != childmap.end(); 
      ++treenode_iterator) {
    if (treenode_iterator->second) {
      delete treenode_iterator->second;
      treenode_iterator->second = NULL;
    }
  }
  childmap.clear();
}

extern "C"
void pushnode(const char* name, const char* extensionname) {
  stacknode_t node(name, extensionname);
  stacknode_t* nodepointer = &node;
  //检查目前的堆中是否有重名
  stack_t::hash_nameset::iterator hashname_iterator = 
    getstack().hashname.find(nodepointer->name);
  if (hashname_iterator != getstack().hashname.end()) {
    VENGINE_SHOW("vengine_capability::profile::pushnode: "
                 "repeat node name: %s",
                 nodepointer->name.c_str());
    return;
  }
  //检查堆栈是否溢出
  if (getstack().topindex >= stack_t::kStackNumberMax) {
    VENGINE_SHOW("vengine_capability::profile::pushnode: "
                 "stack is overflow, %d", getstack().topindex);
    return;
  }
  //create new node in tree
  treenode_t::hash_treenode::iterator childiterator = 
    gettree().currentnode->childmap.find(nodepointer->name);
  //not exist, then create
  if (childiterator == gettree().currentnode->childmap.end()) {
    treenode_t* new_treenode = new treenode_t;
    new_treenode->name = new_treenode->name;
    new_treenode->parentnode = gettree().currentnode;
    new_treenode->invokecount = 0;
    new_treenode->totaltime.QuadPart = 0;

    //insert to tree
    gettree().currentnode->childmap.insert(
        std::make_pair(new_treenode->name, new_treenode));
    childiterator = gettree().currentnode->childmap.find(new_treenode->name);
  }

  //change tree
  gettree().currentnode = childiterator->second;
  //push in stack
  stacknode_t& topnode = getstack().stacknode_list[getstack().topindex];
  topnode.name = nodepointer->name;
  topnode.starttime = nodepointer->starttime;
  topnode.treenode = childiterator->second;
  ++(topnode.treenode->invokecount);
  ++(getstack().topindex);
  //int32_t a = getstack().topindex;
  //int32_t b = 1;
}

extern "C"
void popnode(const char* name) {
  if (getstack().topindex <= 0) {
    VENGINE_SHOW("vengine_capability::profile::popnode: can't pop node,"
                 "because the stack is empty");
    return;
  }
  //处理堆栈中节点
  stacknode_t& top_stacknode = 
    getstack().stacknode_list[getstack().topindex - 1];
  //检查配置是否正确
  if (name) {
    if (strncmp(top_stacknode.name.c_str(), name, strlen(name))) {
      VENGINE_SHOW("vengine_capability::profile::popnode: the stack error!");
    }
  }
  //计算过程时间
  LARGE_INTEGER nowtime;
  QueryPerformanceCounter(&nowtime);
  LARGE_INTEGER processtime;
  processtime.QuadPart = nowtime.QuadPart - top_stacknode.starttime.QuadPart;
  --(getstack().topindex);
  //处理树中节点
  treenode_t& current_treenode = *(gettree().currentnode);
  current_treenode.totaltime.QuadPart += processtime.QuadPart;
  gettree().currentnode = current_treenode.parentnode;
  tick(); //select
}

void tick() {
  //条件为：有查询请求并且堆栈为空
  if (g_askdump && g_functiondump && 0 == getstack().topindex) {
    //计算根节点总时间
    gettree().rootnode.totaltime.QuadPart = 0;
    treenode_t::hash_treenode::iterator treenode_iterator;
    for (treenode_iterator = gettree().rootnode.childmap.begin();
         treenode_iterator != gettree().rootnode.childmap.end();
         ++treenode_iterator) {
      gettree().rootnode.totaltime.QuadPart += 
        treenode_iterator->second->totaltime.QuadPart;
    }
    (g_functiondump)(&gettree());
    g_askdump = false;
  }
}

extern "C"
void dumpstack(function_dump function) {
  VENGINE_ASSERT(function);
  g_askdump = true;
  g_functiondump = function;
}

} //namespace profile

} //namespace vengine_capability
