/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-26 11:26:48
 * @uses vgui base system
 */
#ifndef VGUI_BASE_SYSTEM_H_
#define VGUI_BASE_SYSTEM_H_

#include <OgreRoot.h>
#include <imm.h>
#include "CEGUIString.h"
#include "vgui/config.h"
#include "vengine/ui/system.h"

/** ogre and cegui { **/

namespace Ogre {
class Root;
}; //namespace Ogre

namespace CEGUI {
class System;
class OgreCEGUIRenderer;
class FalagardActionButton;
class EventArgs;
class Window;
}; //namespace CEGUI

namespace vgui_script {
class Base;
}; //namespace vgui_script

/** }ogre and cegui **/

namespace vgui_base {


}; //namespace vgui_base

#endif //VGUI_BASE_SYSTEM_H_
