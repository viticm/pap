/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-12 11:15:08
 * @uses the base config macros and defines, also with system include
 */
#ifndef VENGINE_CONFIG_H_
#define VENGINE_CONFIG_H_

/*system include {*/
#include <windows.h>
#include <shlwapi.h>
#include <Mmsystem.h>

#include <tchar.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <string.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <hash_map>
#include <algorithm>
#include <stdint.h>
#include <stdio.h>
/*system include }*/

/*
@@ VENGINE_API is a mark for all core API functions.
@@ VENGINELIB_API is a mark for all auxiliary library functions.
@@ VENGINEMOD_API is a mark for all standard library opening functions.
** CHANGE them if you need to define those functions in some special way.
** For instance, if you want to create one Windows DLL with the core and
** the libraries, you may want to use the following definition (define
** VENGINE_BUILD_AS_DLL to get it).
*/

#if defined(VENGINE_BUILD_AS_DLL) /* { */ 

#if defined(VENGINE_CORE) || defined(VENGINE_LIB) /* { */
#define VENGINE_API __declspec(dllexport)
#else /* }{ */
#define VENGINE_API __declspec(dllimport)
#endif

#else  /* }{ */ 

#define VENGINE_API extern

#endif /* } */

/* more often than not the libs go together with the core */
#define VENGINELIB_API  VENGINE_API
#define VENGINEMOD_API  VENGINELIB_API

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#pragma warning (disable : 4251)

//version
#define VENGINE_VERSION ((uint16_t)101)

//types
#define UID_INVALID (-1)

//string
#ifdef UNICODE
  typedef std::wstring STRING;
#else
  typedef std::string STRING;
#endif

//just for windows
#define LF "\r\n"

#ifndef snprintf
#define snprintf _snprintf
#endif

#ifndef vsnprintf
#define vsnprintf _vsnprintf
#endif

#define VENGINE_MODULENAME "vengine"

#ifndef USE_PARAM
#define USE_PARAM(x) if (!x) {}
#endif

#endif //VENGINE_CONFIG_H_
