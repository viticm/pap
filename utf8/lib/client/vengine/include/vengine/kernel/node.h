/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id node.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-12 11:15:08
 * @uses vengine kernel node class module
 */
#ifndef VENGINE_KERNEL_NODE_H_
#define VENGINE_KERNEL_NODE_H_

#include "vengine/config.h"
#include "vengine/kernel/class.h"

namespace vengine_kernel {

class VENGINE_API Node {
 public:
   Node();
   Node(const char* name);
   virtual ~Node();
   //返回子节点数目
   int32_t get_childnumber() const;
   //获得子节点名称
   virtual const STRING& getname() const;
   //获得子节点列表
   virtual std::list<Node*>& get_childlist();
   //返回父节点
   virtual Node* getparent() const;
   //初始化节点
   virtual void init(void*); //空指针，子类可以用这个继承这个指针初始化
   //逻辑轮循环
   virtual void tick();

 public:
   //查找子节点,如果没有找到,返回NULL
   virtual Node* lookup_child(const char* name);
   //添加子节点
   virtual void addchild(Node* node);
   //删除子节点，如果该子节点存在则返回true,否则为false
   virtual bool removechild(Node* node);
   //删除所有子节点
   virtual void remove_allchild();
   //释放资源
   virtual void release();
 
VENGINE_KERNEL_DECLARE_DYNAMIC(Node); //类节点自动定义实现

 protected:
   typedef std::list<Node*> childlist;
   STRING name_; //节点名
   childlist childlist_; //子节点列表
   Node* parent_; //父节点指针
   friend struct class_t;
   
};

}; //namespace vengine_kernel

#endif //VENGINE_KERNEL_NODE_H_
