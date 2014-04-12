#include "client/game/resource/loadlistener.h"

namespace resource {

void LoadListener::resourceGroupScriptingStarted(const Ogre::String& groupName, 
                                                 size_t scriptCount) {
  _groupName = groupName;
  _scriptCount = scriptCount;
  _scriptIndex = 0;
  _scriptName.clear();
}

void LoadListener::scriptParseStarted(const Ogre::String& scriptName,
                                      bool& skipThisScript) {
  _scriptName = scriptName;
}

void ScriptParsingListener::scriptParseEnded(const Ogre::String& scriptName, 
                                             bool skipped) {
  _scriptName.clear();
  ++_scriptIndex;
}

void ScriptParsingListener::resourceGroupScriptingEnded(
    const Ogre::String& groupName) {
  _groupName.clear();
  _scriptCount = 0;
}

} //namespace resource
