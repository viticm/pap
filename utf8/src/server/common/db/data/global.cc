#include "server/common/db/data/global.h"

namespace pap_server_common_db {

namespace data {

Global::Global(ODBCInterface* odbc_interface) {
  __ENTER_FUNCTION
    db_type_ = kCharacterDatabase;
    result_ = false;
    result_count_ = 0;
    Assert(odbc_interface);
    odbc_interface_ = odbc_interface;
  __LEAVE_FUNCTION
}

Global::~Global() {
  //do nothing
}

bool Global::load() {
  __ENTER_FUNCTION
    bool result = false;
    db_query_t* query = get_internal_query();
    if (!query) Assert(false);
    query->clear();
    query->parse(kLoadGlobal);
    result = System::load();
    return result;
  __LEAVE_FUNCTION
}

bool Global::save(void* source) {
  __ENTER_FUNCTION
    bool result = true;;
    Assert(source);
    enum {
      kPoolid = 1,
      kData
    }
    uint32_t data = *(static_cast<uint32_t*>(source));
    //save
    db_query_t query = get_internal_query();
    if (!query) Assert(false);
    query->clear();
    query->parse(kSaveGlobal, poolid_, data);
    if (!System::save(source)) result = false;
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Global::_delete() {
  __ENTER_FUNCTION
    bool result = true;
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Global::parse_result(void* source) {
  __ENTER_FUNCTION
    bool result = true;
    enum {
      kPoolid = 1,
      kData
    }
    switch(op_type_) {
      case DB_LOAD: {
        Assert(source);
        Assert(odbc_interface_);
        int32_t error_code;
        if (!odbc_interface_) {
          result = false;
          break;
        }
        *(static_cast<uint32_t*>(source)) = odbc_interface_->get_uint(
            kData, error_code);
        break;
      }
      case DB_DELETE: {
        break;
      }
      default:
        break;
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

void Global::set_pool_id(int16_t id) {
  __ENTER_FUNCTION
    poolid_ = id;
  __LEAVE_FUNCTION
}

int16_t Global::get_pool_id() {
  __ENTER_FUNCTION
    return poolid_;
  __LEAVE_FUNCTION
    return -1;
}

} //namespace data

} //namespace pap_server_common_db
