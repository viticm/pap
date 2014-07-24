#include "vengine/kernel/node.h"

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(vengine_kernel::Node, NULL, vengine_kernel_Node); //类节点部分实现

namespace vengine_kernel {


Node::Node() : parent_(NULL) {
  //do nothing
}

Node::Node(const char* name) {
  name_ = name;
}

Node::~Node() {
  release();
}

int32_t Node::get_childnumber() const {
  int32_t result = static_cast<int32_t>(childlist_.size());
  return result;
}

const STRING& Node::getname() const {
  return name_;
}

std::list<Node*>& Node::get_childlist() {
  return childlist_;
}

Node* Node::getparent() const {
  return parent_;
}

//找子节点,如果没有找到,返回NULL
Node* Node::lookup_child(const char* name) {
  register std::list<Node*>::iterator nodelist_iterator;
  for (nodelist_iterator = childlist_.begin(); 
       nodelist_iterator != childlist_.end(); 
       ++nodelist_iterator) {
    if ((*nodelist_iterator)->getname() == name) {
      return *nodelist_iterator;     
    }
  }
  return NULL;
}

void Node::addchild(Node* node) {
  if (!node) return;
  node->parent_ = this;
  childlist_.push_back(node);
}

bool Node::removechild(Node* node) {
  if (get_childlist().empty()) return false;
  register std::list<Node*>::iterator nodelist_iterator;
  for (nodelist_iterator = childlist_.begin();
       nodelist_iterator != childlist_.end();
       ++nodelist_iterator) {
    if (node == *nodelist_iterator) {
      childlist_.erase(nodelist_iterator);
      return true;
    }
  }
  return false;
}

void Node::remove_allchild() {
  if (get_childlist().empty()) return;
  childlist_.clear();
}

void Node::release() {
  if (get_childlist().empty()) return;
  register std::list<Node*>::iterator nodelist_iterator;
  for (nodelist_iterator = childlist_.begin();
       nodelist_iterator != childlist_.end();
       ++nodelist_iterator) {
    (*nodelist_iterator)->release();
    delete (*nodelist_iterator);
    *nodelist_iterator = NULL;
  }
  childlist_.clear();
}

void Node::tick() {
  if (get_childlist().empty()) return;
  register std::list<Node*>::iterator nodelist_iterator = childlist_.end(),
           nodelist_nextiterator;
  --nodelist_iterator;
  for (;;) {
    nodelist_nextiterator = nodelist_iterator;
    if (childlist_.begin() == nodelist_iterator) {
      nodelist_nextiterator = childlist_.end();
    }
    else {
      --nodelist_nextiterator;
    }
    (*nodelist_iterator)->tick();
    if (nodelist_nextiterator == childlist_.end()) break;
    nodelist_iterator = nodelist_nextiterator;
  }
}

} //namespace vengine_kernel
