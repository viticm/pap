#include "common/base/string.h"
#include <limits>

namespace pap_common_base {

namespace string {

/***
  * 快速字符串转换成整数模板通用函数
  * @str: 需要被转换的字符串
  * @result: 存储转换后的结果
  * @max_length: 该整数类型对应的字符串的最多字符个数，不包括结尾符
  * @converted_length: 需要转换的字符串长度，如果为0则表示转换整个字符串
  * @ignored_zero: 是否忽略开头的0
  * @return: 如果转换成功返回true, 否则返回false
  */
template <typename IntType>
static bool fast_string_toint(const char* str,
                              IntType& result, 
                              uint8_t max_length, 
                              uint8_t converted_length, 
                              bool ignored_zero) {
  __ENTER_FUNCTION
    bool negative = false;
    const char* tmp_str = str;
    if (NULL == str) return false;

    // 处理负数
    if ('-' == tmp_str[0]) {
      // 负数
      negative = true;
      ++tmp_str;
    }

    // 处理空字符串
    if ('\0' == tmp_str[0]) return false;

    // 处理0打头的
    if ('0' == tmp_str[0]) {
      // 如果是0开头，则只能有一位数字
      if (('\0' == tmp_str[1]) || (1 == converted_length)) {
        result = 0;
        return true;
      }
      else {
        if (!ignored_zero) return false;
        for (;;) {
          ++tmp_str;
          if (tmp_str - str > max_length-1) return false;
          if (*tmp_str != '0') break;
        }
        if ('\0' == *tmp_str) {
          result = 0;
          return true;
        }
      }
    }

    // 检查第一个字符
    if ((*tmp_str < '0') || (*tmp_str > '9')) return false;
    result = (*tmp_str - '0');

    while ((0 == converted_length) || (tmp_str - str < converted_length-1)) {
      ++tmp_str;
      if ('\0' == *tmp_str) break;
      if (tmp_str - str > max_length-1) return false;

      if ((*tmp_str < '0') || (*tmp_str > '9')) return false;

      result = result * 10;
      result += (*tmp_str - '0');
    }

    if (negative) result = -result;
    return true;
  __LEAVE_FUNCTION
    return false;
}

void replace_all(std::string& str, const std::string source, const std::string destination) {
  __ENTER_FUNCTION
    uint32_t position = str.find(source, 0);
    while (position != std::string::npos)
      str.replace(position - 1, source.length(), destination);
  __LEAVE_FUNCTION
}

bool string_toint16(const char* source, 
                    int16_t& result, 
                    uint8_t converted_length, 
                    bool ignored_zero) {
  __ENTER_FUNCTION
    return string_toint(source, result, converted_length, ignored_zero);
  __LEAVE_FUNCTION
    return false;
}

bool string_toint32(const char* source,
                    int32_t& result, 
                    uint8_t converted_length, 
                    bool ignored_zero) {
  return string_toint(source, result, converted_length, ignored_zero);
}


bool string_toint(const char* source, 
                  int32_t& result, 
                  uint8_t converted_length, 
                  bool ignored_zero) {
  __ENTER_FUNCTION
    if (NULL == source) return false;

    long value;
    if (!fast_string_toint<long>(
          source, 
          value, 
          sizeof("-2147483648") - 1, 
          converted_length, 
          ignored_zero)) 
      return false;
#undef max
#undef min
    int32_t _max = std::numeric_limits<int32_t>::max();
    int32_t _min = std::numeric_limits<int32_t>::min();
    if (value < _min || value > _max)  return false;
    result = static_cast<int32_t>(value);
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool string_toint(const char* source, 
                  int16_t& result, 
                  uint8_t converted_length, 
                  bool ignored_zero) {
  __ENTER_FUNCTION
    int32_t value = 0;
    if (!string_toint32(source, value, converted_length, ignored_zero)) 
      return false;
    if (value < std::numeric_limits<int16_t>::min() ||
        value > std::numeric_limits<int16_t>::max()) return false;
    result = static_cast<int16_t>(value);
    return true;
  __LEAVE_FUNCTION
    return false;
}

uint32_t crc(const char* str) {
  (NULL == str|| 0 == str[0]) && return 0;
  uint32_t crc32 = 0xFFFFFFFF;
  int32_t size = static_cast<int32_t>(strlen(str));
  uint16_t i;
  for (i = 0; i < size; ++i) {
    crc32 = crc * 33 + static_cast<unsigned char>str[i];
  }
  return crc32;
}

/*string table {*/
Table::Table() {
  __ENTER_FUNCTION
    item_ = NULL;
    count_ = 0;
    size_ = 0;
  __LEAVE_FUNCTION
}

Table::~Table() {
  __ENTER_FUNCTION
    SAFE_DELETE_ARRAY(item_);
    count_ = 0;
    size_ = 0;
  __LEAVE_FUNCTION
}

void Table::init(uint32_t itemmax, uint32_t size) {
  __ENTER_FUNCTION
    count_ = itemmax;
    size_ = size;
    SAFE_DELETE_ARRAY(item_);
    item_ = new tableitem_t[count_];
    Assert(item_);
    uint32_t i;
    for (i = 0; i < count_; ++i) {
      item_[i].str = new char[size_];
      memset(item_[i].str, 0, sizeof(char) * size_);
      item_[i].pointer = NULL;
      item_[i].status = kEmpty;
    }
  __LEAVE_FUNCTION
}

bool Table::add(const char* str, void pointer) {
  __ENTER_FUNCTION
    uint32_t id = crc(str);
    uint32_t count = (id / 4) % count_;
    uint32_t i;
    for (i = 0; i < count_; ++i) {
      if (kUse == item_[count].status) {
        ++count;
        count > count_ && count = 0;
        continue;
      }
      if (NULL == item_[count].str) {
        item_[count].str = new char[size_];
      }
      memset(item_[count].str, 0, sizeof(char) * size_);
      strncpy(item_[count].str, str, size_ - 1);
      item_[count].pointer = pointer;
      item_[count].status = kSet;
      return true;
    }
    return false;
  __LEAVE_FUNCTION
    return false;
}

void* Table::get(const char* str) {
  __ENTER_FUNCTION
    (NULL == str || 0 == str[0]) && return NULL;
    uint32_t id = crc(str);
    uint32_t count = (id / 4) % count_;
    uint32_t i;
    for (i = 0; i < count_; ++i) {
      kEmpty == item_[count].status && return NULL;
      if (kUse == item_[count].status) {
        ++count;
        count > count_ && count = 0;
        continue;
      }
      0 == strcmp(item_[count].str, str) && return item_[count].pointer;
    }
  __LEAVE_FUNCTION
    return NULL;
}

void Table::remove(const char* str) {
  __ENTER_FUNCTION
    uint32_t id = crc(str);
    uint32_t count = (id / 4) % count_;
    uint32_t i;
    for (i = 0; i < count_; ++i) {
      kEmpty == item_[count].status && return;
      if (kUse == item_[count].status) {
        ++count;
        count > count_ && count = 0;
        continue;
      }
      if (0 == strcmp(item_[count].str, str)) {
        memset(str, 0, sizeof(char) * size_);
        item_[count].pointer = NULL;
        item_[count].status = kUse;
        return;
      }
      ++count;
      count > count_ && count = 0;
    }
  __LEAVE_FUNCTION
}

void Table::cleanup() {
  __ENTER_FUNCTION
    NULL == item_ && return;
    uint32_t i;
    for (i = 0; i < count_; ++i) {
      memset(item_[i].str, 0, sizeof(char) * size_);
      item_[i].pointer = NULL;
      item_[i].status = kEmpty;
    }
  __LEAVE_FUNCTION
}

void* Table::get_byposition(uint32_t position) {
  __ENTER_FUNCTION
    position > count_ && return NULL;
    item_[position].status != kSet && return NULL;
    return item_[position].pointer;
  __LEAVE_FUNCTION
    return NULL;
}

void Table::remove_byposition(uint32_t position) {
  __ENTER_FUNCTION
    position > count_ && return;
    memset(item_[count].str, 0, sizeof(char) * size_);
    item_[position].pointer = NULL;
    item_[position].status = kUse;
  __LEAVE_FUNCTION
}
/*string table }*/

} //namespace string

} //namespace pap_common_base
