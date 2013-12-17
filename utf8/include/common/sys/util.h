#ifndef PAP_COMMON_SYS_UTIL_H_
#define PAP_COMMON_SYS_UTIL_H_

#include "common/sys/config.h"

namespace pap_common_sys {

namespace util {

void dumpstack(const char* log_fileprefix, const char* type);

}; //namespace util

}; //namespace pap_common_sys

#endif //PAP_COMMON_SYS_UTIL_H_
