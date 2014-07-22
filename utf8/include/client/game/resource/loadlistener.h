/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id listener.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-12 14:18:17
 * @uses pap client game resource listener
 */
#ifndef PAP_CLIENT_GAME_RESOURCE_LOADLISTENER_H_
#define PAP_CLIENT_GAME_RESOURCE_LOADLISTENER_H_

#include "OgreResourceGroupManager.h"

namespace resource {

class LoadListener : public Ogre::ResourceGroupListener {

 public:
   Ogre::String _groupName;
   size_t _scriptCount;
   size_t _scriptIndex;
   Ogre::String _scriptName;

   LoadListener()
     : _groupName()
     , _scriptCount()
     , _scriptIndex()
     , _scriptName() {
      Ogre::ResourceGroupManager::getSingleton().addResourceGroupListener(this);
    }

   ~LoadListener() {
      Ogre::ResourceGroupManager::getSingleton().
        removeResourceGroupListener(this);
    }

   void resourceGroupScriptingStarted(const Ogre::String& groupName, 
                                      size_t scriptCount);

   void scriptParseStarted(const Ogre::String& scriptName,bool& skipThisScript);

   void scriptParseEnded(const Ogre::String& scriptName, bool skipped);

   void resourceGroupScriptingEnded(const Ogre::String& groupName);

   void  resourceGroupLoadStarted(const Ogre::String& groupName, 
                                  size_t resourceCount) {
     //do nothing
   }

   void resourceLoadStarted(const Ogre::ResourcePtr& resource) {
     //do nothing
   }

   void resourceLoadEnded() {
     //do nothing
   }

   void worldGeometryStageStarted(const Ogre::String& description) {
    //do nothing
   }

   void worldGeometryStageEnded() {
     //do nothing
   }

   void resourceGroupLoadEnded(const Ogre::String& groupName) {
     //do nothing
   }

};

}; //namespace resource

#endif //PAP_CLIENT_GAME_RESOURCE_LOADLISTENER_H_
