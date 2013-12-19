#ifndef PAP_COMMON_BASE_STRING_H_
#define PAP_COMMON_BASE_STRING_H_

#include "common/base/config.h"

namespace pap_common_base {

namespace string {

  void replace_all(std::string& str, const std::string source, const std::string destination);
  bool string_toint(const char* source, int16_t& result, uint8_t converted_length = 0, bool ignored_zero = false);
  bool string_toint16(const char* source, int16_t& result, uint8_t converted_length = 0, bool ignored_zero = false);
  bool string_toint32(const char* source, int32_t& result, uint8_t converted_length = 0, bool ignored_zero = false);
  bool string_toint(const char* source, int32_t& result, uint8_t converted_length=0, bool ignored_zero=false);

} //namespace string

} //namespace pap_common_base
#endif //PAP_COMMON_BASE_STRING_H_
