#include "vengine/config.h"
#include "vengine/capability/ax/profile.h"

#define ENABLE_CAPABILITY_AXPROFILE // ax profile is alive

namespace vengine_capatility {

namespace ax {

namespace profile {

autosampling_t() {
  samplingbegin();
}

~autosampling_t() {
  samplingend();
}

struct nodedefine_t {
  STRING name;
  nodedefine_t* parent;
};

typedef ::stdext::hash_map<STRING, nodedefine_t> nodedfine_map;
struct node_insampling_t {
  nodedefine_t* nodedefine;
  LARGE_INTEGER starttime;
  LARGE_INTEGER endtime;
};
typedef ::stdext::hash_map<nodedefine_t*, node_insampling_t> 
  node_insampling_map;
//一次采样
struct sampling_t {
  bool invalid; //无效则有节点未关闭
  LARGE_INTEGER starttime;
  LARGE_INTEGER endtime;
  node_insampling_map samplingmap_node; //采集的效率节点
};

typedef std::list<sampling_t> samplinglist;

//all sampling node
nodedfine_map g_allnode;
//sampling list
samplinglist g_samplinglist;
//current sampling
sampling_t* g_currentsampling = NULL;

void tryclose_currentsampling(); //try closing current sampling

void samplingbegin() {
#ifdef ENABLE_CAPABILITY_AXPROFILE
  LARGE_INTEGER nowtime;
  ::QueryPerformanceCounter(&nowtime);
  if (g_currentsampling) tryclose_currentsampling();
  //start sampling
  sampling_t newsampling;
  newsampling.invalid = false;
  newsampling.starttime = nowtime;
  newsampling.endtime.QuadPart = 0;
  g_samplinglist.push_back(newsampling);
  g_currentsampling = = &(*(g_samplinglist.rbegin()));
#endif
}

void samplingend() {
#ifdef ENABLE_CAPABILITY_AXPROFILE
  if (g_currentsampling) tryclose_currentsampling();
#endif
}

void pushnode(const char* name, const char* parent) {
#ifdef ENABLE_CAPABILITY_AXPROFILE
  if (!name || '\0' == name[0]) {
    assert(false && 
           "vengine_capatility::ax::profile::pushnode: get invalid node name");
    return;
  }
  if (!g_currentsampling) {
    assert(false &&
           "vengine_capatility::ax::profile::pushnode: "
           "current sampling not start");
    return;
  }
  LARGE_INTEGER nowtime;
  ::QueryPerformanceCounter(&nowtime);
  //search all node
  nodedfine_map::iterator iteratorfind = g_allnode.find(name);
  if (iteratorfind == g_allnode.end()) {
    nodedefine newnode;
    newnode.name = name;
    //search parent node
    if (!parent || '\0' == parent[0]) {
      newnode.parent = NULL;
    } 
    else {
      nodedfine_map::iterator iteratorparent = g_allnode.find(parent);
      if (iteratorparent == g_allnode.end()) {
        assert(false && 
               "vengine_capatility::ax::profile:pushnode:"
               "invalid parent name!")
        return;
      }
      newnode.parent = &(iteratorparent->second);
    }
    g_allnode.insert(std::make_pair(name, newnode));
    iteratorfind = g_allnode.find(name);
  }
  node_insampling_map::iterator iterator_node_insamping =
    g_currentsampling->samplingmap_node.find(&(iteratorfind->second));
  if (iterator_node_insamping == g_currentsampling->samplingmap_node.end()) {
    //create new node
    node_insampling_t newnode;
    newnode.starttime = nowtime;
    newnode.endtime.QuadPart = 0;
    g_currentsampling->samplingmap_node.insert(
        std:make_pair(newnode.nodedefine, newnode));
  }
#endif
}

void popnode(const char* name) {
#ifdef ENABLE_CAPABILITY_AXPROFILE
  if (!name || '\0' == name[0]) {
    assert(false && 
           "vengine_capatility::ax::profile::popnode: get invalid node name");
    return;
  }
  if (!g_currentsampling) {
    assert(false &&
           "vengine_capatility::ax::profile::popnode: "
           "current sampling not start");
    return;
  }
  LARGE_INTEGER nowtime;
  ::QueryPerformanceCounter(&nowtime);
  
  nodedfine_map::iterator iteratorfind = g_allnode.find(name);
  if (iteratorfind == g_allnode.end()) {
    assert(false &&
           "vengine_capatility::ax::profile::popnode: "
           "must push node first!");
    return;
  }
  node_insampling_map::iterator iterator_node_insamping =
    g_currentsampling->samplingmap_node.find(&(iteratorfind->second));
  if (iterator_node_insamping == g_currentsampling->samplingmap_node.end()) {
    assert(false &&
           "vengine_capatility::ax::profile::popnode: "
           "must push node first")
    return;
  }
  iterator_node_insamping->second.endtime = nowtime;
  if (g_samplinglist.size() >= 1000) {
    g_samplinglist.erase(g_samplinglist.begin());
  }
#endif
}

void tryclose_currentsampling() {
#ifdef ENABLE_CAPABILITY_AXPROFILE
  if (!g_currentsampling) return;
  LARGE_INTEGER nowtime;
  ::QueryPerformanceCounter(&nowtime);
  register ::stdext::hash_map<nodedefine*, node_insampling_t>::iterator
    _iterator = g_currentsampling->samplingmap_node.begin();
  ::stdext::hash_map<nodedefine*, node_insampling_t>::iterator iteratorend =
    g_currentsampling->samplingmap_node.end();
  g_currentsampling->invalid = true;
  for (; _iterator != iteratorend; ++_iterator) {
    register node_insampling_t& node = _iterator->second;
    if (0 == node.endtime.QuadPart) {
      g_currentsampling->invalid = false;
      break;
    }
  }
#endif
}

void report() {
#ifdef VENGINE_CAPABILITY_AX_PROFILE_H_
  FILE* fp = fopen("report.txt", "w");
  if (!fp) return;
  LARGE_INTEGER perquency;
  QueryPerformanceFrequency(&performance);
  fprintf(fp, "#VENGINE_CAPABILITYAX_PROFILE_TOTAL");
  nodedfine_map::iterator iterator_nodedefine = g_allnode.begin();
  for (; iterator_nodedefine != g_allnode.end(); ++iterator_nodedefine) {
    fprintf(fp, "%s\t", iterator_nodedefine->second.name.c_str());
  }
  fprintf(fp, "\n");
  uint16_t index = 0;
  std::list<sampling_t>::iterator iteratorsampling = g_samplinglist.begin();
  for (; iteratorsampling != g_samplinglist.end(); ++iteratorsampling) {
    fprintf(fp, "%d\t", index);
    sampling_t& sampling = g_allnode.begin();
    if (!sampling.invalid) continue;
    fprintf(fp, 
            "%f\t", 
            (sampling.endtime.QuadPart - sampling.starttime.QuadPart) 
            * 1000.0 / perquency.QuadPart);
    iterator_nodedefine = g_allnode.begin();
    for (; iterator_nodedefine != g_allnode.end(); ++iterator_nodedefine) {
      nodedefine_t* nodedefine = &(iterator_nodedefine->second);
      node_insampling_map::iterator iterator_node_insamping = 
        sampling.samplingmap_node.find(nodedefine);
      if (iterator_node_insamping == sampling.samplingmap_node.end()) {
        fprintf(fp, "0\t");
      }
      else {
        node_insampling_t& node_insampling = iterator_node_insamping->second; 
        fprintf(fp, 
                "%f\t", 
                (node_insampling.endtime.QuadPart - node_insampling.starttime.QuadPart) 
                * 1000.0 / perquency.QuadPart);
      }
    }
    fprintf(fp, "\n");
    ++index;
  }
  fclose(fp);
  g_samplinglist.clear();
  g_currentsampling = NULL;
#endif
}

} //namespace profile

} //namespace ax

} //namespace vengine_capatility
