/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-3-11 10:12:52
 * @uses vgui base config and global set
 */
#ifndef VGUI_CONFIG_H_
#define VGUI_CONFIG_H_

/*macros {*/

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if (p) { delete (p); (p) = NULL; }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) if (p) { (p)->Release(); delete (p); (p) = NULL; }
#endif
/* }macros*/

/*class {*/ //from vengine

namespace vengine_kernel {
class Base;
}; //namespace vengine_kernel

namespace vengine_script {
class System;
}; //namespace vengine_script

namespace vengine_game {
class EventSystem;
class WorldSystem;

namespace action {
class System;
}; //namespace action

}; //namespace vengine_game

namespace vengine_input {
class System;
}; //namespace vengine_input

namespace vengine_render {
class System;
}; //namespace vengine_render

namespace vengine_cursor {
class System;
}; //namespace vengine_cursor

/* }class*/

#endif //VGUI_CONFIG_H_
