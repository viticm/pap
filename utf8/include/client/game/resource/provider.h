/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id provider.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-12 14:32:16
 * @uses pap client game resource provider class
 */
#ifndef PAP_CLIENT_GAME_RESOURCE_PROVIDER_H_
#define PAP_CLIENT_GAME_RESOURCE_PROVIDER_H_

#include "vengine/resource/provider.h"

namespace Ogre {
class PakFileSystemArchive;
class ResourceGroupManager;
class OgreStringVector;
}; //namespace Ogre

namespace resource {

class Provider : public vengine_resource::Provider {

VENGINE_KERNEL_DECLARE_DYNAMIC(Provider);

 public:
   Provider();
   virtual ~Provider();

 public: //implement from abstract
   virtual uint64_t loadresource(const char* filename, 
                                 char*& memoryaddress, 
                                 const char* group = NULL);
   virtual bool unloadresource(char* memoryaddress, uint64_t size);

};

}; //namespace resource

#endif //PAP_CLIENT_GAME_RESOURCE_PROVIDER_H_
