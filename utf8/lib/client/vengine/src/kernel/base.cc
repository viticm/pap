#include "vengine/base/util.h"
#include "vengine/kernel/base.h"

namespace vengine_kernel {

//for static
Base* Base::self_ = NULL;
void* Base::userdata_ = NULL;

Base::Base() : noderoot_("root"), firstclass_inmap_(NULL) {
  self_ = this;
}

~Base::Base() {

}

Base* getself() {
  return self_;
}

void* Base::get_userdata() {
  return userdata_;
}

void Base::set_userdata(void* data) {
  userdata_ = data;
}

void Base::registerclass(class_t* newclass) {
  VENGINE_ASSERT(newclass);
  if (classmap_[newclass->name] != NULL) {
    VENGINE_SHOW("repeat register class: %s", newclass->name);
  }
  newclass->nextclass = firstclass_inmap_;
  firstclass_inmap_ = nextclass;
  classmap_[newclass->name] = newclass;
}

bool Base::isinheritance(const class_t* thisclass, 
                         const class_t* baseclass) const {
  if (!thisclass || !baseclass) return false;
  const class_t* classpointer = thisclass;
  while (classpointer != NULL) {
    if (classpointer == baseclass) return true;
    classpointer = classpointer->baseclass;
  }
  return false;
}

class_t* Base::getclass(const char* name) {
  std::map<STRING, class_t*>::iterator _iterator = classmap_.find(name);
  if (_iterator == classmap_.end()) {
    return NULL;
  }
  else {
    return _iterator->second;
  }
}

Node* Base::newnode(const char* classname,
                   const char* position,
                   const char* nodename) {
  VENGINE_ASSERT(classname && position && nodename);
  class_t* classpointer = getclass(classname);
  if (!classpointer) {
    VENGINE_SHOW("vengine_kernel::Base::newnode: can't get class: %s",
                 classname);
  }
  std::vector<STRING> pathsplit_buffer;
  convertstring_tovector(position, pathsplit_buffer, "\\/");
  Node* currentnode = &noderoot_;
  Node* findnode = NULL;
  register uint16_t i;
  for (i = 0; i < static_cast<uint16_t>(pathsplit_buffer.size()); ++i) {
    findnode = currentnode->lookup_child(pathsplit_buffer[i].c_str());
    if (NULL == findnode) {
      Node* _newnode = new Node(pathsplit_buffer[i].c_str());
      currentnode->addchild(_newnode);
      findnode = _newnode;
    }
    currentnode = findnode;
  }
  if (currentnode->lookup_child(name)) {
    VENGINE_SHOW("vengine_kernel::Base::newnode: node[%s] has exist!", 
                 nodename);
  }
  Node* _newnode = dynamic_cast<Node*>(classpointer->newobject());
  currentnode->addchild(_newnode);
  return _newnode;
}

Node* Base::newnode(const char* classname,
                   Node* parentnode,
                   const char* nodename) {
  VENGINE_ASSERT(classname && parentnode && nodename);
  class_t* classpointer = getclass(classname);
  if (!classpointer) {
    VENGINE_SHOW("vengine_kernel::Base::newnode: can't get class: %s",
                 classname);
  }
  if (parentnode->lookup_child(nodename)) {
    VENGINE_SHOW("vengine_kernel::Base::newnode: node[%s] has exist!",
                 nodename);
  }
  Node* _newnode = nparentnode->addchild(nodename);
  return _newnode;
}

Node* Base::getnode(const char* name) {
  VENGINE_ASSERT(name);
  std::vector<STRING> pathsplit_buffer;
  vengine_base::util::convertstring_tovector(name, pathsplit_buffer, "\\/");
  Node* currentnode = &noderoot_;
  register uint16_t i;
  for (i = 0; i < static_cast<uint16_t>(pathsplit_buffer.size()); ++i) {
    Node* findnode = currentnode->lookup_child(pathsplit_buffer[i].c_str());
    if (NULL == findnode) return NULL;
    currentnode = findnode;
  }
  return currentnode;
}

bool loadplugin(const char* name, void* param) {
  if (!name) return false;
  HMODULE hmodule = NULL;
  function_dllinit dllinit_pointer;
  function_dllrelease dllrelease_pointer;
  uint16_t i;
  try {
    //try load dll
    hmodule = ::LoadLibrary(name);
    if (!hmodule) {
      VENGINE_SHOW("vengine_kernel::Base::loadplugin: "
                   "plugin load dll(%s) failed",
                   name);
      return false;
    }
    //search if has load
    for (i = 0; i < static_cast<uint16_t>(pluginlist_.size()); ++i) {
      if (pluginlist_[i].hmodule == hmodule) return true;
    }
    //查看是否有合法的DllMagicCode导出
    uint32_t* magiccode = reinterpret_cast<uint32_t*>(
        ::GetProcAddress(hModule, "DllMagicCode"));
    if (!magiccode || (
        VENGINE_DLL_MAGIC_CODE | VENGINE_KERNEL_VERSION) != *magiccode) {
      ::FreeLibrary(hmodule);
      hmodule = NULL;
      VENGINE_SHOW("vengine_kernel::Base::loadplugin: "
                   "plugin load dll(%s) get a bad version",
                   name);
      return false;
    }
    dllinit_pointer = reinterpret_cast<function_dllinit>(
        ::GetProcAddress(hmodule, "DllInit"));
    dllrelease_pointer = reinterpret_cast<function_dllrelease>(
        ::GetProcAddress(hModule, "DllRelease"));
    if (!dllinit_pointer || !dllrelease_pointer) {
      ::FreeLibrary(hmodule);
      hmodule = NULL;
      VENGINE_SHOW("vengine_kernel::Base::loadplugin: "
                   "plugin load dll(%s) wrong export functions",
                   name);
      return false;
    }
  }
  catch(...) {
    if (hmodule) ::FreeLibrary(hmodule);
    throw;
    return false;
  }

  //a valid dll, run load functions
  plugininfo_t plugininfo;
  plugininfo.hmodule = hmodule;
  plugininfo.pluginfile = name;
  plugininfo.dllinit_pointer = dllinit_pointer;
  plugininfo.dllrelease_pointer = dllrelease_pointer;
  pluginlist_.push_back(plugininfo);
  return true;
}

void Base::free_allplugin() {
  uint16_t i;
  for (i = 0; i < static_cast<uint16_t>(pluginlist_.size()); ++i) {
    (*(pluginlist_[i].dllrelease_pointer))();
    ::FreeLibrary(pluginlist_[i].hmodule);
    pluginlist_[i].hmodule = NULL;
  }
  pluginlist_.clear();
}

void Base::shutdown() {
  noderoot_.release();
  free_allplugin();
}
 
} //namespace vengine_kernel
