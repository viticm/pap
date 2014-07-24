#include "client/game/stdafx.h"
#include "OgreResourceGroupManager.h"
#include "OgreStringVector.h"
#include "OgreException.h"
#include "client/game/resource/provider.h"

namespace resource {

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(
    resource::Provider,
    VENGINE_KERNEL_GETCLASS(vengine_resource::Provider, vengine_resource_Provider),
    resource_Provider);

Provider::Provider() {
  //do nothing
}

Provider::~Provider() {
  //do nothing
}

uint64_t Provider::loadresource(const char* filename, 
                                char*& memoryaddress, 
                                const char* group) {
  if (!filename || '\0' == filename[0]) return 0;
  Ogre::ResourceGroupManager& resourcemanager = 
    Ogre::ResourceGroupManager::getSingleton();
  const Ogre::StringVector& group_strvector = 
    resourcemanager.getResourceGroups();
  int32_t i;
  for (i = 0; i < static_cast<int32_t>(group_strvector.size()); ++i) {
    if (group && group_strvector[i] != group) continue;
    try {
      if (resourcemanager.resourceExists(group_strvector[i], filename)) {
        Ogre::DataStreamPtr stream = resourcemanager.openResource(
            filename, group_strvector[i], false);
        if (stream.get() && stream.get()->size() > 0) {
          memoryaddress = new char[stream.get()->size() + 1];
          stream.get()->read(memoryaddress, stream.get()->size());
          memoryaddress[stream.get()->size()] = '\0';
          return static_cast<uint64_t>(stream.get()->size());
        }
      }
    }
    catch(const Ogre::Exception& exception) {
      return 0;
    }
    catch(...) {
      return 0;
    }
  } //for loop
  return 0;
}

bool Provider::unloadresource(char* memoryaddress, uint64_t size) {
  SAFE_DELETE_ARRAY(memoryaddress);
  return true;
}

}; //namespace resource
