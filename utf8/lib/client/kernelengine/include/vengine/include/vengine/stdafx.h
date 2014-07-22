/**
 * PAP Engine ( https://github.com/viticm/pap )
 * model vengine
 * $Id stdafx.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-3-16 11:33:48
 * @uses vc builder precompiled header
 */

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef VENGINE_STDAFX_H_
#define VENGINE_STDAFX_H_

#define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

// TODO: reference additional headers your program requires here
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Standard C++ Library
#include <string>
#include <vector>
#include <list>
#include <map>
#include <hash_map>
#include <algorithm>

extern HINSTANCE g_hInstance;

#endif //VENGINE_STDAFX_H_
