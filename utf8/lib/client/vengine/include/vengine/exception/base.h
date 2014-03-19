/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-17 10:57:14
 * @uses vengine exception base functions
 */
#ifndef VENGINE_EXCEPTION_BASE_H_
#define VENGINE_EXCEPTION_BASE_H_

#include "vengine/config.h"

//ref from http://www.codeproject.com/tools/minidump.asp
//generate stack frame pointers for all functions - same as /Oy- in the project
#pragma optimize("y", off)

namespace vengine_exception {

namespace base {

VENGINE_API void process(PEXCEPTION_POINTERS exception, bool run_crashreport);
VENGINE_API void showstring(const char* format, ...);
VENGINE_API void showassert(const char* filename, 
                            uint16_t fileline, 
                            const char* exception);
VENGINE_API int32_t processinner(PEXCEPTION_POINTERS exception, 
                                 HWND hparentwnd, 
                                 const char* title);
}; //namespace base

}; //namespace vengine_exception

#define VENGINE_SHOW vengine_exception::base::showstring
#define VENGINE_ASSERT(condition) \
  do { \
    if (!condition) { \
      vengine_exception::base::showassert(__FILE__, \
                                          __LINE__, \
                                          #condition); \
    } \
  } while (0);

#endif //VENGINE_EXCEPTION_BASE_H_
