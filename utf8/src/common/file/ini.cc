#include "common/file/ini.h"
#include "common/base/type.h"

namespace pap_common_file {

Ini::Ini() {
  __ENTER_FUNCTION
    data_length_ = 0;
    data_info_ = NULL;
    section_number_ = 0;
    section_list_ = NULL;
  __LEAVE_FUNCTION
}

Ini::Ini(const char* file_name) {
  __ENTER_FUNCTION
    data_length_ = 0;
    data_info_ = NULL;
    section_number_ = 0;
    section_list_ = NULL;
    memset(file_name_, '\0', sizeof(file_name_));
    memset(value_, '\0', sizeof(value_));
    memset(ret_, '\0', sizeof(ret_));
    open(file_name);
  __LEAVE_FUNCTION
}

Ini::~Ini() {
  __ENTER_FUNCTION
    if (data_length_ > 0) {
      SAFE_DELETE(data_info_);
      data_length_ = 0;
    }
    if (section_number_ > 0) {
      SAFE_DELETE(section_list_);
      index_number_ = 0;
    }
  __LEAVE_FUNCTION
}

bool Ini::open(const char* file_name) {
  __ENTER_FUNCTION
    bool result = false;
    strncpy(file_name_, file_name, sizeof(file_name_) - 1);
    SAFE_FREE(data_info_);
    //get file length
    FILE* fp;
    fp = fopen(file_name_, "rb");
    if (!fp) {
      data_length_ = -1;
    }
    else {
      fseek(fp, 0L, SEEK_END);
      data_length_ = ftell(fp);
      fclose(fp);
    }
    if (data_length_ > 0) {
      data_info_ = static_cast<char*>(malloc(static_cast<size_t>(data_length_)));
      memset(data_info_, '\0', sizeof(data_info_));
      FILE* fp;
      fp = fopen(file_name_, "rb");
      pap_common_sys::AssertEx(fp != NULL, file_name_);
      fread(data_info_, data_length_, 1, fp);
      fclose(fp);
      init_index();
      result = true;
    }
    else {
      data_length_ = 1;
      data_info_ = static_cast<char*>(malloc(static_cast<size_t>(data_length_)));
      memset(data_info_, '\0', sizeof(data_info_));
      init_section();
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

void Ini::close() {
  __ENTER_FUNCTION
    if (data_length_ > 0) {
      SAFE_DELETE(data_info_);
      data_length_ = 0;
    }
    if (index_number_ > 0) {
      SAFE_DELETE(index_list_);
      index_number_ = 0;
    }
  __LEAVE_FUNCTION
}

bool Ini::save(char* file_name) { //save file_name
  __ENTER_FUNCTION
    FILE* fp;
    if (NULL == file_name) file_name = file_name_;
    fp = fopen(file_name, "wb");
    pap_common_sys::AssertEx(fp != NULL, file_name); 
    fwrite(data_info_, data_length_, 1, fp);
    fclose(fp);
  __LEAVE_FUNCTION
    return false;
}

char* Ini::get_data() {
  __ENTER_FUNCTION
    return data_info_;
  __LEAVE_FUNCTION
}

int32_t Ini::get_lines(int32_t current) {
  __ENTER_FUNCTION
    int32_t n = 1;
    int32_t i;
    for (i = 0; i < current; ++i) {
      if ('\n' == data_info_[i]) ++n;
    }
    return n;
  __LEAVE_FUNCTION
    return -1;
}

int32_t Ini::get_lines() {
  __ENTER_FUNCTION
    int32_t n = 1;
    int32_t i;
    for (i = 0; i < data_length_; ++i) {
      if ('\n' == data_info_[i]) ++n;
    }
    return n;
  __LEAVE_FUNCTION
    return -1;
}

void Ini::init_section() { //初始化节点数据
  __ENTER_FUNCTION
    section_number_ = 0;
    int32_t i;
    for (i = 0; i < data_length_; ++i) {
      if('[' == data_info_[i] && ('\n' == data_info_[i] || 0 == i)) {
        ++section_number_;
      }
    }
    SAFE_DELETE(section_list_);
    if (section_number_ > 0) section_list_ = new int32_t[section_number_];
    int32_t i, n = 0;
    for (i = 0; i < data_length_; ++i) {
      if('[' == data_info_[i] && ('\n' == data_info_[i] || 0 == i)) {
        section_list_[n] = i + 1;
        ++n;
      }
    }
  __LEAVE_FUNCTION
}

int32_t Ini::find_section_index(const char* section) {
  __ENTER_FUNCTION
    int32_t i;
    int32_t index = -1;
    for (i = 0; i < section_number_; ++i) {
      char* find_str = read_text(section_list_[i]);
      if (0 == strcmp(section, find_str)) {
        index = section_list_[i];
        break;
      }
    }
    return index;
  __LEAVE_FUNCTION
    return -1;
}

int32_t Ini::find_data_index(int32_t position, const char* data) {
  __ENTER_FUNCTION
    while (true) {
      position = goto_next_line(position);
      char* find_data = find_key(position);
      if (0 == strcmp(data, find_data)) break;
      if ('[' == name[0]) {
        position = -1;
        break;
      }
    }
    return position;
  __LEAVE_FUNCTION
    return -1;
}

int32_t Ini::goto_next_line(int32_t position) {
  __ENTER_FUNCTION
    int32_t i;
    for (i = position; i < data_length_; ++i) {
      if ('\n' == data_info_[i]) return i + 1;
    }
    return i;
  __LEAVE_FUNCTION
    return -1;
}

char* Ini::find_key(int32_t &position) {
  __ENTER_FUNCTION
    char _char;
    char* ret;
    int32_t m, i;
    m = 0;
    ret = new char[64];
    memset(ret, '\0', sizeof(ret));
    for (i = 0; i < data_length_; ++i) {
      _char = data_info_[i];
      if ('\r' == _char || '\n' == _char || '=' == _char || ';' == _char) {
        position = i + 1;
        break;
      }
      ret[m] = data_info_[i];
      ++m;
    }
    return ret;
  __LEAVE_FUNCTION
    return 0;
}

char* Ini::read_text(int32_t position) {
  __ENTER_FUNCTION
    char _char;
    char* ret;
    int32_t n = position, m = 0, i;
    int32_t line_number = goto_next_line(position) - position + 1;
    ret = static_cast<char*>(value_);
    memset(ret, '\0', sizeof(ret));
    for (i = 0; i < data_length_ - position; ++i) {
      _char = data_info_[n];
      if ('\r' == _char || '\n' == _char || '\t' == _char || ';' == _char || ']' == _char) {
        break;
      }
      ret[m] = _char;
      ++m;
      ++n;
    }
    return ret;
  __LEAVE_FUNCTION
    return 0;
}

bool Ini::add_section(const char* section) {
  __ENTER_FUNCTION
    char str[256];
    bool result = false;
    memset(str, '\0', sizeof(str));
    int32_t index = find_(name);
    if (-1 == index) {
      snprintf(str, sizeof(str), "%s[%s]", LF, name);
      data_info_ = static_cast<char*>(realloc(data_info_, data_length_+strlen(str)));
      snprintf(&data_info_[data_length_], "%s", str);
      data_length_ += static_cast<int64_t>(strlen(str));
      init_index();
      result = true;
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Ini::add_data(int32_t position, const char* key, const char* value) {
  __ENTER_FUNCTION
    char* str;
    int32_t length = static_cast<int32_t>(strlen(value));
    str = new char[length + 256];
    memset(str, '\0', sizeof(str));
    snprintf(str, sizeof(str), "%s=%s", key, value);
    length = static_cast<int32_t>(strlen(str));
    position = goto_next_line(position);
    data_info_ = static_cast<char*>(relloc(data_info_, data_length_ + length));
    char* temp = new char[data_length_ -  position];
    memcpy(temp, &data_info_[position], data_length_ - position);
    memcpy(&data_info_[position + length], temp, data_length_ - position); //the last
    memcpy(&data_info_[position], str, length);
    data_length_ += length;
    SAFE_DELETE(temp);
    SAFE_DELETE(str);
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool Ini::modify_data(int32_t position, const char* key, const char* value) {
  __ENTER_FUNCTION
    int32_t find_position = find_data_index(position, key);
    char* old_value = read_text(find_position); //old
    position = find_position + static_cast<int32_t>(strlen(old_value));
    int32_t new_length = static_cast<int32_t>(strlen(value));
    int32_t old_length = position - find_position;
    data_info_ = static_cast<char*>(data_info_, data_length_ + new_length - old_length); //reset memory
    char* temp = new char[data_length_ - position];
    memcpy(temp, &data_info_[position], data_length_ - position);
    memcpy(&data_info_[find_position + new_length], temp, data_length_ - position); //swap
    memcpy(&data_info_[find_position], temp, new_length);
    data_length_ += new_length - old_length;
    SAFE_DELETE(temp);
    return true;
  __LEAVE_FUNCTION
    return false;
}

int32_t Ini::goto_last_line(const char* section) {
  __ENTER_FUNCTION
    int32_t position = find_section_index(section);
    position = goto_next_line(position);
    while (true) {
      if ('\r' == data_info_[position] || 
          EOF == data_info_[position] || 
          -3 == data_info_[position] ||
          ' ' == data_info_[position] ||
          '/' == data_info_[position] ||
          '\t' == data_info_[position] ||
          '\n' == data_info_[position]) {
        break; //get it
      }
    }
    return position;
  __LEAVE_FUNCTION
    return -1;
}

//string
void Ini::read_text(const char* section, const char* key, char* str, int32_t length) {
  __ENTER_FUNCTION
    char temp[512];
    memset(temp, '\0', sizeof(temp));
    snprintf(temp, sizeof(temp), "[file:%s][section:%s][key:%s]", file_name_, section, key);
    int32_t section_index = find_section_index(section);
    pap_common_sys::AssertEx(section_index != -1, temp);
    if (-1 == section_index) return;
    int32_t data_index = find_data_index(section_index, key);
    if (-1 == data_index) return;
    char* ret = read_text(data_index);
    strncpy(str, ret, length);
  __LEAVE_FUNCTION
}

bool Ini::read_exist_text(const char* section, const char* key, char* str, int32_t length) {
  __ENTER_FUNCTION
    int32_t section_index = find_section_index(section);
    if (-1 == section_index) return false;
    int32_t data_index = find_data_index(key);
    if (-1 == data_index) return false;
    char* ret = read_text(data_index);
    strncpy(str, ret, length);
    return true;
  __LEAVE_FUNCTION
    return false;
}

void Ini::read_text(const char* section, int32_t line, char* str, int32_t length) {
  __ENTER_FUNCTION
    char temp[512];
    memset(temp, '\0', sizeof(temp));
    snprintf(temp, sizeof(temp), "[file:%s][section:%s][line:%d]", file_name_, section, line);
    int32_t section_index = find_section_index(section);
    pap_common_sys::AssertEx(section_index != -1, temp);
    int32_t position = section_index; //start from section
    position = goto_next_line(position);
    int32_t i;
    for (i = 0; i < line; ++i) {
      if (position < data_length_) position = goto_next_line(position);
    }
    //read
    while (position < data_length_) {
      if ('=' == data_info_[position]) {
        ++position;
        char* ret = read_text(position);
        strncpy(str, ret, length);
        break;
      }
      else if ('\r' == data_info_[position] ||
               '\n' == data_info_[position] ||
               '\t' == data_info_[position] ||
               ';' == data_info_[position]) { //value end flag
        break;
      }
    }
  __LEAVE_FUNCTION
}

void Ini::read_key(const char* section, int32_t line, char* str, int32_t length) {
  __ENTER_FUNCTION
    char temp[512];
    memset(temp, '\0', sizeof(temp));
    snprintf(temp, sizeof(temp), "[file:%s][section:%s][line:%d]", file_name_, section, line);
    int32_t section_index = find_section_index(section);
    pap_common_sys::AssertEx(section_index != -1, temp);
    int32_t position = section_index;
    position = goto_next_line(position);
    int32_t i;
    for (i = 0; i < line; ++i) {
      if (position < data_length_)
        position = goto_next_line(position);
    }
    char* result = find_key(position);
    strncpy(str, result, length);
  __LEAVE_FUNCTION
}

//int 
int64_t Ini::read_int64(const char* section, const char* key) {
  __ENTER_FUNCTION
    char temp[512];
    memset(temp, '\0', sizeof(temp));
    snprintf(temp, sizeof(temp), "[file:%s][section:%s][key:%s]", file_name_, section, key);
    int32_t section_index = find_section_index(section);
    pap_common_sys::AssertEx(section_index != -1, temp);
    int32_t data_index = find_data_index(section_index, key);
    pap_common_sys::AssertEx(data_index, temp);
    char* str = read_text(data_index);
    int64_t result = static_cast<int64_t>(atoll(str));
    return result;
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

bool Ini::read_exist_int64(const char* section, const char* key, int64_t &result) {
  __ENTER_FUNCTION
    int32_t section_index = find_section_index(section);
    if (-1 == section_index) return false;
    int32_t data_index = find_data_index(section_index, key);
    char* str read_text(data_index);
    result = static_cast<int64_t>(atoll(str));
    return true;
  __LEAVE_FUNCTION
    return false;
}

int64_t Ini::read_int64(const char* section, int32_t line) { //read in line
  __ENTER_FUNCTION
    char temp[512];
    memset(temp, '\0', sizeof(temp));
    snprintf(temp, sizeof(temp), "[file:%s][section:%s][line:%d]", file_name_, section, line);
    int32_t section_index = find_section_index(section);
    pap_common_sys::AssertEx(section_index != -1, temp);
    int32_t position = section_index; //start from section
    position = goto_next_line(position);
    int32_t i;
    int64_t result = ERROR_DATA;
    for (i = 0; i < line; ++i) {
      if (position < data_length_) position = goto_next_line(position);
    }
    //read
    while (position < data_length_) {
      if ('=' == data_info_[position]) {
        ++position;
        char* str = read_text(position);
        result = static_cast<int64_t>(atoll(str));
        break;
      }
      else if ('\r' == data_info_[position] ||
               '\n' == data_info_[position] ||
               '\t' == data_info_[position] ||
               ';' == data_info_[position]) { //value end flag
        break;
      }
    }
    return result;
  __LEAVE_FUNCTION
   return ERROR_DATA;
}
//float
float Ini::read_float(const char* section, const char* key) {
  __ENTER_FUNCTION
    char temp[512];
    memset(temp, '\0', sizeof(temp));
    snprintf(temp, sizeof(temp), "[file:%s][section:%s][key:%s]", file_name_, section, key);
    int32_t section_index = find_section_index(section);
    pap_common_sys::AssertEx(section_index != -1, temp);
    int32_t data_index = find_data_index(section_index, key);
    pap_common_sys::AssertEx(data_index, temp);
    char* str = read_text(data_index);
    float result = static_cast<float>(atof(str));
    return result;
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

bool Ini::read_bool(const char* section, const char* key) { 
  __ENTER_FUNCTION
    bool result = false;
    int64_t number = read_int64(section, key);
    result = number > 0 ? true : false;
    return result;
  __LEAVE_FUNCTION
    return false;
}

//int extend
int32_t Ini::read_int32(const char* section, const char* key) {
  __ENTER_FUNCTION
    return static_cast<int32_t>(read_int64(section, key));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

uint32_t Ini::read_uint32(const char* section, const char* key) {
  __ENTER_FUNCTION
    return static_cast<uint32_t>(read_int64(section, key));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

int16_t Ini::read_int16(const char* section, const char* key) {
  __ENTER_FUNCTION
    return static_cast<int16_t>(read_int64(section, key));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}
uint16_t Ini::read_uint16(const char* section, const char* key) {
  __ENTER_FUNCTION
    return static_cast<uint16_t>(read_int64(section, key));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

int8_t Ini::read_int8(const char* section, const char* key) {
  __ENTER_FUNCTION
    return static_cast<int8_t>(read_int64(section, key));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

uint8_t Ini::read_uint8(const char* section, const char* key) {
  __LEAVE_FUNCTION
    return static_cast<uint8_t>(read_int64(section, key));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

bool Ini::read_exist_int32(const char* section, const char* key, int32_t &result) {
  __ENTER_FUNCTION
    bool _result = false;
    int64_t temp;
    _result = read_exist_int64(section, key, temp);
    result = static_cast<int32_t>(temp);
    return _result;
  __LEAVE_FUNCTION
    return false;
}

bool Ini::read_exist_uint32(const char* section, const char* key, uint32_t &result) {
  __ENTER_FUNCTION
    bool _result = false;
    int64_t temp;
    _result = read_exist_int64(section, key, temp);
    result = static_cast<uint32_t>(temp);
    return _result;
  __LEAVE_FUNCTION
    return false;
}

bool Ini::read_exist_int16(const char* section, const char* key, int16_t &result) {
  __ENTER_FUNCTION
    bool _result = false;
    int64_t temp;
    _result = read_exist_int64(section, key, temp);
    result = static_cast<int16_t>(temp);
    return _result;
  __LEAVE_FUNCTION
    return false;
}

bool Ini::read_exist_uint16(const char* section, const char* key, uint16_t &result) {
  __ENTER_FUNCTION
    bool _result = false;
    int64_t temp;
    _result = read_exist_int64(section, key, temp);
    result = static_cast<uint16_t>(temp);
    return _result;
  __LEAVE_FUNCTION
    return false;
}

bool Ini::read_exist_int8(const char* section, const char* key, int8_t &result) {
  __ENTER_FUNCTION
    bool _result = false;
    int64_t temp;
    _result = read_exist_int64(section, key, temp);
    result = static_cast<int8_t>(temp);
    return _result;
  __LEAVE_FUNCTION
    return false;
}

bool Ini::read_exist_uint8(const char* section, const char* key, uint8_t &result) {
  __ENTER_FUNCTION
    bool _result = false;
    int64_t temp;
    _result = read_exist_int64(section, key, temp);
    result = static_cast<uint8_t>(temp);
    return _result;
  __LEAVE_FUNCTION
    return false;
}

int32_t Ini::read_int32(const char* section, int32_t line) {
  __ENTER_FUNCTION
    return static_cast<int32_t>(read_int64(section, line));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

uint32_t Ini::read_uint32(const char* section, int32_t line) {
  __ENTER_FUNCTION
    return static_cast<uint32_t>(read_int64(section, line));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

int16_t Ini::read_int16(const char* section, uint32_t line) {
  __ENTER_FUNCTION
    return static_cast<int16_t>(read_int64(section, line));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

uint16_t Ini::read_uint16(const char* section, uint32_t line) {
  __ENTER_FUNCTION
    return static_cast<uint16_t>(read_int64(section, line));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

int8_t Ini::read_int8(const char* section, uint32_t line) {
  __ENTER_FUNCTION
    return static_cast<int8_t>(read_int64(section, line));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

uint8_t Ini::read_uint8(const char* section, uint32_t line) {
  __ENTER_FUNCTION
    return static_cast<uint8_t>(read_int64(section, line));
  __LEAVE_FUNCTION
    return ERROR_DATA;
}

bool Ini::write(const char* section, const char* key, int32_t value) {
  __ENTER_FUNCTION
    bool result = false;
    int32_t section_index = find_section_index(section);
    int32_t line;
    char str[64];
    memset(str, '\0', sizeof(str));
    snprintf(str, sizeof(str), "%d", value);
    if (-1 == section_index) { //add new section
      add_section(section);
      section_index = find_section_index(section);
      line = goto_next_line(section);
      add_data(line, key, str);
      result = true;
    }
    else {
      int32_t data_index = find_data_index(section_index, key);
      if (-1 == data_index) {
        int32_t position;
        position = goto_last_line(section);
        add_data(position, key, str);
      }
      else {
        modify_data(position, key, str);
      }
      result = true;
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Ini::write(const char* section, const char* key, const char* value) {
  __ENTER_FUNCTION
    bool result = false;
    int32_t section_index = find_section_index(section);
    int32_t line;
    snprintf(str, sizeof(str), "%d", value);
    if (-1 == section_index) { //add new section
      add_section(section);
      section_index = find_section_index(section);
      line = goto_next_line(section);
      add_data(line, key, value);
      result = true;
    }
    else {
      int32_t data_index = find_data_index(section_index, key);
      if (-1 == data_index) {
        int32_t position;
        position = goto_last_line(section);
        add_data(position, key, value);
      }
      else {
        modify_data(position, key, value);
      }
      result = true;
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

int32_t Ini::get_continue_data_number(const char* section) {
  __ENTER_FUNCTION
    int32_t number = 0;
    int32_t section_index = find_section_index(section);
    int32_t position = goto_next_line(section_index);
    while (true) {
      if ('\r' == data_info_[position] ||
          '\n' == data_info_[position] ||
          EOF == data_info_[position] ||
          -3 == data_info_[position] ||
          ' ' == data_info_[position] ||
          '/' == data_info_[position] ||
          '\t' == data_info_[position]) {
        break;
      }
      ++number;
      if (position < data_length_) {
        position = goto_next_line(position);
      }
      else {
        break;
      }
    }
    return number;
  __LEAVE_FUNCTION
    return -1;
}

char* Ini::read_one_line(int32_t line) {
  __ENTER_FUNCTION
    int32_t start = find_one_line(line);
    memset(ret_, '\0', sizeof(_ret));
    int32_t i;
    for (i = start; i < data_length_; ++i) {
      if ('\r' == data_info_[i] ||
          '\n' == data_info_[i] ||
          '\t' == data_info_[i] ||
          ';' == data_info_[i]) {
        strncpy(ret_, &data_info_[start], i - start);
        break;
      }
    }
    return ret_;
  __LEAVE_FUNCTION
    return 0;
}

int32_t Ini::find_one_line(int32_t line) {
  __ENTER_FUNCTION
    if (line <= 0) return -1;
    if (1 == line) return 0;
    int32_t result = -1, i;
    int32_t position = 0;
    for (i = 0; i < data_length_; ++i) {
      if ('\n' == data_info_[i]) ++position;
      if (position - 1 == i) {
        result = i + 1;
        break;
      }
    }
    return result;
  __LEAVE_FUNCTION
    return -1;
}

int32_t Ini::get_line_number(const char* str) {
  __ENTER_FUNCTION
    int32_t result = -1;
    result = find_data(str);
    return result;
  __LEAVE_FUNCTION
    return -1;
}

} //namespace pap_common_file
