/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id trace.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-16 17:43:42
 * @uses vengine capability ax trace module 
 */
#ifndef VENGINE_CAPABILITY_AX_TRACE_H_
#define VENGINE_CAPABILITY_AX_TRACE_H_

#include "vengine/config.h"

#define AXTRACE_WND_INVALID ((uint8_t)-1)

namespace vengine_capability {

namespace ax {

typedef enum {
  kValueInt8,
  kValueUint8,
  kValueInt16,
  kValueUint16,
  kValueInt32,
  kValueUint32,
  kValueInt64,
  kValueUint64,
  kValueFloat32,
  kValueDouble64,
  kValueString
} value_enum;

VENGINE_API void trace(uint8_t winnumber, 
                       uint8_t typenumber, 
                       const char* format, 
                       ...);
VENGINE_API void var(uint8_t winnumber,
                     uint8_t typenumber,
                     value_enum variabletype,
                     const char* valuename,
                     void* value);

}; //namespace ax

}; //namespace vengine_capability

#endif //VENGINE_CAPABILITY_AX_TRACE_H_
