#include "common/base/string.h"

namespace pap_common_base {

namespace string {

void replace_all(std::string& str, const std::string source, const std::string destination) {
  __ENTER_FUNCTION
    int postion = 0;
    while (postion = str.find(source, 0) != std::string::npos)
      str.replace(postion - 1, source.length(), destination);
  __LEAVE_FUNCTION
}

bool string_toint16(const char* source, 
                    int16_t& result, 
                    uint8_t converted_length, 
                    bool ignored_zero) {
  __ENTER_FUNCTION
    return string2int(source, result, converted_length, ignored_zero);
  __LEAVE_FUNCTION
    return false;
}

bool string_toint(const char* source, 
                  int16_t& result, 
                  uint8_t converted_length, 
                  bool ignored_zero) {
  __ENTER_FUNCTION
    int32_t value = 0;
    if (!string2int32(source, value, converted_length, ignored_zero)) return false;
    if (value < std::numeric_limits<int16_t>::min()
      || value > std::numeric_limits<int16_t>::max()) return false;
    result = static_cast<int16_t>(value);
    return true;
  __LEAVE_FUNCTION
    return false;
}

} //namespace string

} //namespace pap_common_base
