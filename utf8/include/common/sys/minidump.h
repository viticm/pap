#ifndef PAP_COMMON_SYS_MINIDUMP_H_
#define PAP_COMMON_SYS_MINIDUMP_H_

#include "common/sys/config.h"

namespace pap_common_sys {

namespace minidump {

#if defined(__WINDOWS__)
#include <windows.h>
LONG WINAPI unhandled_exceptionfilter(
    struct _EXCEPTION_POINTERS* exceptioninfo);
#endif

}; //namespace minidump

}; //namespace pap_common_sys

#endif //PAP_COMMON_SYS_MINIDUMP_H_
