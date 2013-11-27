#include "server/common/db/system.h"
#include "common/base/util.h"

namespace pap_server_common_db {

System::System()
{
  __ENTER_FUNCTION
    result_ = 0;
    result_count_ = 0;
    op_type_ = OP_INIT_EMPTY;
  __LEAVE_FUNCTION
}

uint System::get_result_count() {
  __ENTER_FUNCTION
    return result_count_;
  __LEAVE_FUNCTION
}

DB_QUERY* System::get_internal_query() {
  __ENTER_FUNCTION
    return &odbc_interface_->get_query();
  __LEAVE_FUNCTION
}

LONG_DB_QUERY* System::get_long_internal_query() {
  __ENTER_FUNCTION
    return &odbc_interface_->get_long_query();
  __LEAVE_FUNCTION
}

int32_t System::get_internal_affect_count() {
  __ENTER_FUNCTION
    return odbc_interface_->get_affect_row_count();
  __LEAVE_FUNCTION
}

bool System::is_prepare() {
  __ENTER_FUNCTION
    return odbc_interface_->is_prepare();
  __LEAVE_FUNCTION
}

bool System::check_db_connect() {
  __ENTER_FUNCTION
    Assert(odbc_interface_);
    if (!odbc_interface_->is_connected()) {
      int i;
      for (i = 0; i <5; ++i) {
        pap_common_base::util::sleep(5000);
        if (odbc_interface_->connect())
        {
          return true;
        }
      }
      return false;
    }
  __LEAVE_FUNCTION
    return false;
}

bool System::load() {
  __ENTER_FUNCTION
    if (!is_prepare()) return false;
    if (!odbc_interface_) return false;
    op_type_ = DB_LOAD;
    result_ = odbc_interface_->excute();
    result_count_ = odbc_interface_->get_affect_row_count();
    return result_;
  __LEAVE_FUNCTION
    return false;
}

bool System::long_load() {
  __ENTER_FUNCTION
    if (!is_prepare()) return false;
    if (!odbc_interface_) return false;
    op_type_ = DB_LOAD;
    result_ = odbc_interface_->long_excute();
    result_count_ = odbc_interface_->get_affect_row_count();
    return result_;
  __LEAVE_FUNCTION
    return false;
}

bool System::add_new() {
  __ENTER_FUNCTION
    if (!is_prepare()) return false;
    if (!odbc_interface_) return false;
    op_type_ = DB_ADDNEW;
    result_ = odbc_interface_->excute();
    result_count_ = odbc_interface_->get_affect_row_count();
    return result_;
  __LEAVE_FUNCTION
    return false;
}

bool System::delete_() {
  __ENTER_FUNCTION
    if (!is_prepare()) return false;
    if (!odbc_interface_) return false;
    op_type_ = DB_DELETE;
    result_ = odbc_interface_->excute();
    result_count_ = odbc_interface_->get_affect_row_count();
    return result_;
  __LEAVE_FUNCTION
    return false;
}

bool System::save() {
  __ENTER_FUNCTION
    if (!is_prepare()) return false;
    if (!odbc_interface_) return false;
    op_type_ = DB_SAVE;
    result_ = odbc_interface_->excute();
    result_count_ = odbc_interface_->get_affect_row_count();
    return result_;
  __LEAVE_FUNCTION
    return false;
}

bool System::long_save() {
  __ENTER_FUNCTION
    if (!is_prepare()) return false;
    if (!odbc_interface_) return false;
    op_type_ = DB_SAVE;
    result_ = odbc_interface_->long_excute();
    result_count_ = odbc_interface_->get_affect_row_count();
    return result_;
  __LEAVE_FUNCTION
    return false;
}

void System::set_db_type(DB_TYPES db_type)
{
  __ENTER_FUNCTION
    db_type_ = db_type
  __LEAVE_FUNCTION
}

int32_t System::get_error_code() {
  __ENTER_FUNCTION
    return odbc_interface_->get_error_code();
  __LEAVE_FUNCTION
}

char* System::get_error_message() {
  __ENTER_FUNCTION
    return odbc_interface_->get_error_message();
  __LEAVE_FUNCTION
}

} //namespace pap_server_common_db
