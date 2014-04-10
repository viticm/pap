#ifndef PAP_CLIENT_GAME_STDAFX_H_
#define PAP_CLIENT_GAME_STDAFX_H_

#define WIN32_LEAN_AND_MEAN// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <windowsx.h>

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Standard C++ Library
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <hash_map>
#include <algorithm>
//
//TODO: reference additional headers your program requires here
#include "vengine/config.h"
#include "vengine/capability/ax/trace.h"

#endif //PAP_CLIENT_GAME_STDAFX_H_
