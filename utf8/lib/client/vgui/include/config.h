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
#define VC_EXTRALEAN //Exclude rarely-used stuff from Windows headers
#define STRICT

// Works with Windows 2000 and later and Windows 98 or later
#undef _WIN32_IE
#undef WINVER
#undef _WIN32_WINDOWS
#undef _WIN32_WINNT
#define WINVER         0x0500 
#define _WIN32_WINDOWS 0x0410 
#define _WIN32_WINNT   0x0500 

#include <windows.h>

// TODO: reference additional headers your program requires here
#undef min
#undef max

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if (p) { delete (p); (p) = NULL; }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) if (p) { (p)->Release(); delete (p); (p) = NULL; }
#endif
/*macros }*/

/*class {*/
class Kernel;

/*class*/

#endif //VGUI_CONFIG_H_
