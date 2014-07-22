#include "common/file/database.h"
#include "vengine/resource/provider.h"
#include "vengine/exception/base.h"
#include "vengine/base/util.h"
#include "global.h"
#include "procedure/base.h"
#include "client/game/database/file.h"

#pragma warning(disable : 4996)

namespace database {

File::File(int32_t id) {
  filedb_ = new pap_common_file::Database(id);
}

File::~File() {
  SAFE_DELETE(filedb_);
}
const File::field_data* File::search_index_equal(int32_t index) const {
  field_data* data = (field_data*)filedb_->search_index_equal(index);
  return data;
}

const File::field_data* File::search_line_equal(int32_t line) const {
  field_data* data = (field_data*)filedb_->search_position(line, 0);
  return data;
}

const File::field_data* File::search_position(int32_t line, 
                                              int32_t column) const {
  field_data* data = (field_data*)filedb_->search_position(line, column);
  return data;
}

const File::field_data* File::search_first_column_equal(
    int32_t column, 
    const field_data &value) const {
  field_data* data = 
    (field_data*)filedb_->search_first_column_equal(column, value.int_value);
  return data;
}

int32_t File::get_id() const {
  int32_t id = filedb_->get_id();
  return id;
}

int32_t File::get_field_number() const {
  int32_t result = filedb_->get_field_number();
  return result;
}

int32_t File::get_record_number() const {
  int32_t result = filedb_->get_record_number();
  return result;
}

bool File::open_fromtxt(const char* filename, 
                        pap_common_file::Database* filedb) {
  VENGINE_ASSERT(filename && filedb);
  bool result = false;
  STRING _filename = "../../public/config/";
  _filename += filename;
  if (::PathFileExists(_filename.c_str())) {
    result = filedb->open_from_txt(_filename.c_str());
    return result;
  }
  _filename = "../data/config/";
  _filename += filename;
  if (::PathFileExists(_filename.c_str())) {
    result = filedb->open_from_txt(_filename.c_str());
    return result;
  }
  char* address = NULL;
  uint64_t size = procedure::Base::resourceprovider_->loadresource(
      _filename.c_str(),
      address,
      "General");
  if (size > 0) {
    result = filedb->open_from_memory(address, address + size + 1);
    procedure::Base::resourceprovider_->unloadresource(address, size);
  }
  return result;
}

bool File::open_fromtxt(const char* filename) {
  return open_fromtxt(filename, filedb_);
}

bool File::get_splitdata(const char* data, uint32_t count, char* out) {
  if (NULL == data || NULL == out) return false;
  int32_t position1 = 0;
  if (count > 1) {
    position1 = get_charposition(data, '|', count - 1);
    if (-1 == position1) {
      position1 = 0;
    }
    else {
      ++position1;
    }
  }
  //找输出字符串的后一个"|"位置
  int32_t position2 = get_charposition(data, '|', count);
  if (-1 == position2) position2 = static_cast<int32_t>(strlen(data));
  //计算两个"|"之间的字符串
  int32_t copysize = position2 - position1;
  if (copysize > 0) {
    STRING temp(data);
    temp.copy(out, copysize, position1);
    return true;
  }
  return false;
}

int32_t File::get_charposition(const char* str, 
                               const char _char, 
                               uint32_t count) {
  if (NULL == str) return -1;
  int32_t number = 0;
  int32_t size = static_cast<int32_t>(strlen(str));
  int32_t i;
  for (i = 0; i < size; ++i) {
    if (_char == str[i]) {
      ++number;
      if ((uint32_t)number >= count) return i;
    }
  }
  return -1;
}

const pap_common_file::Database* File::get_databasefile() const {
  return filedb_;
}

} //namespace database
