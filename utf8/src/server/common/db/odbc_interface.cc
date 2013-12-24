#include "server/common/db/odbc_interface.h"
#include "server/common/base/log.h"
#include "common/base/util.h"

namespace pap_server_common_db {

ODBCInterface::ODBCInterface() {
  __ENTER_FUNCTION
    connectd_ = false;
    affect_count_ = -1;
    result_ = SQL_SUCCESS;
    sql_henv_ = NULL;
    sql_hdbc_ = NULL;
    sql_hstmt_ = NULL;
    memset(error_message_, '\0', sizeof(error_message_));
    memset(connection_name_, '\0', sizeof(connection_name_));
    memset(user_, '\0', sizeof(user_));
    memset(password_, '\0', sizeof(password_));
    query_.clear();
    long_query_.clear();
  __LEAVE_FUNCTION
}

ODBCInterface::~ODBCInterface() {
  __ENTER_FUNCTION
    if (sql_hstmt_) SQLFreeHandle(SQL_HANDLE_STMT, sql_hstmt_);
    if (sql_hdbc_) SQLDisconnect(sql_hdbc_);
    if (sql_hdbc_) SQLFreeHandle(SQL_HANDLE_DBC, sql_hdbc_);
    if (sql_henv_) SQLFreeHandle(SQL_HANDLE_ENV, sql_henv_);
  __LEAVE_FUNCTION
}

bool ODBCInterface::connect(const char* connection_name,
                            const char* user,
                            const char* password) {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;
    close(); //first disconnect
    strncpy(connection_name_, connection_name, sizeof(connection_name_) - 1);
    strncpy(user_, user, sizeof(user_) - 1);
    strncpy(password_, password, sizeof(password_) - 1);
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sql_henv_);
    SQLSetEnvAttr(sql_henv_, 
                  SQL_ATTR_ODBC_VERSION, 
                  reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 
                  SQL_IS_INTEGER);
    SQLAllocHandle(SQL_HANDLE_DBC, sql_henv_, &sql_hdbc_);
    result_ = SQLConnect(sql_hdbc_,
                         reinterpret_cast<SQLCHAR*>(connection_name_),
                         SQL_NTS,
                         reinterpret_cast<SQLCHAR*>(user_),
                         SQL_NTS,
                         reinterpret_cast<SQLCHAR*>(password_),
                         SQL_NTS);
    if (SQL_SUCCESS != result_ && SQL_SUCCESS_WITH_INFO != result_) {
      char log_buffer[512];
      memset(log_buffer, '\0', sizeof(log_buffer));
      snprintf(log_buffer, 
               sizeof(log_buffer) - 1,
               "connection name: %s", 
               connection_name_);
      snprintf(log_buffer, sizeof(log_buffer) - 1, "connect user: %s", user_);
      Log::save_log("odbc_interface", "[odbc] connect failed, %s", log_buffer);
      diag_state();
      return false;
    }
    result_ = SQLAllocHandle(SQL_HANDLE_STMT, sql_hdbc_, &sql_hstmt_);
    if (result_ != SQL_SUCCESS && result_ != SQL_SUCCESS_WITH_INFO) {
      sql_hstmt_ = NULL;
      return false;
    }
    connectd_ = true;
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool ODBCInterface::connect() {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;
    close(); //first disconnect
#ifdef MUST_CLOSE_HENV_HANDLE
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sql_henv_);
    SQLSetEnvAttr(sql_henv_, 
                  SQL_ATTR_ODBC_VERSION, 
                  static_cast<SQLPOINTER>(SQL_OV_ODBC3), 
                  SQL_IS_INTEGER);
#endif
    SQLAllocHandle(SQL_HANDLE_DBC, sql_henv_, &sql_hdbc_);
    result_ = SQLConnect(sql_hdbc_,
                         reinterpret_cast<SQLCHAR*>(connection_name_),
                         SQL_NTS,
                         reinterpret_cast<SQLCHAR*>(user_),
                         SQL_NTS,
                         reinterpret_cast<SQLCHAR*>(password_),
                         SQL_NTS);
    if (result_ != SQL_SUCCESS && result_ != SQL_SUCCESS_WITH_INFO) {
      char log_buffer[512];
      memset(log_buffer, '\0', sizeof(log_buffer));
      snprintf(log_buffer, 
               sizeof(log_buffer) - 1,
               "connection name: %s", 
               connection_name_); 
      snprintf(log_buffer, sizeof(log_buffer) - 1, "connect user: %s", user_);
      Log::save_log("odbc_interface", "[odbc] connect failed, %s", log_buffer);
      diag_state();
      return false;
    }
    result_ = SQLAllocHandle(SQL_HANDLE_STMT, sql_hdbc_, &sql_hstmt_);
    if (result_ != SQL_SUCCESS && result_ != SQL_SUCCESS_WITH_INFO) {
      sql_hstmt_ = NULL;
      return false;
    }
    connectd_ = true;
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool ODBCInterface::close() {
  __ENTER_FUNCTION
    if (sql_hstmt_) {
      try {
        SQLCloseCursor(sql_hstmt_);
        SQLFreeStmt(sql_hstmt_, SQL_UNBIND);
        SQLFreeHandle(SQL_HANDLE_STMT, sql_hstmt_);
        sql_hstmt_ = NULL;
      }
      catch(...) {
        sql_hstmt_ = NULL;
      }
    }

    if (sql_hdbc_) {
      try {
        SQLDisconnect(sql_hdbc_);
        SQLFreeHandle(SQL_HANDLE_DBC, sql_hdbc_);
        sql_hdbc_ = NULL;
      }
      catch(...) {
        sql_hdbc_ = NULL;
      }
    }

#ifdef MUST_CLOSE_HENV_HANDLE
    if (sql_henv_) {
      try {
        SQLFreeHandle(SQL_HANDLE_ENV, sql_henv_);
        sql_henv_ = NULL;
      }
      catch(...) {
        sql_henv_ = NULL;
      }
    }
#endif
    connectd_ = false;
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool ODBCInterface::execute() {
  try {
    //int column_index;
    result_ = SQLExecDirect(sql_hstmt_, 
                            reinterpret_cast<SQLCHAR*>(query_.sql_str_), 
                            SQL_NTS);
    if ((result_ != SQL_SUCCESS) && 
        (result_ != SQL_SUCCESS_WITH_INFO) &&
        (result_ != SQL_NO_DATA)) {
      diag_state();
      return false;
    }
    SQLRowCount(sql_hstmt_, &affect_count_);
    SQLNumResultCols(sql_hstmt_, &column_count_);
    if (MAX_COLUMN < column_count_) return false;
    if (0 >= affect_count_ && 0 >= column_count_) {
      clear();
      return true;
    }

    /**
    for (column_index = 0; column_index < column_count_; ++column_index) {
      SQLBindCol( sql_hstmt_, 
                  column_index + 1, 
                  SQL_C_CHAR,
                  column_[column_index],
                  MAX_COLUMN_BUFFER,
                  &column_locate_[column_index]);
      SQLDescribeCol(sql_hstmt_,
                     column_index + 1,
                     column_name_[column_index],
                     MAX_COLUMN_NAME,
                     NULL,
                     NULL,
                     NULL,
                     NULL,
                     NULL);
    }
    **/ //this code will be want the result to array, but now i don't known it.
    return true;
  }
  catch(...) {
     save_error_log("Huge Error occur:");
     save_error_log(static_cast<const char*>(query_.sql_str_));
     return false;
  }
}

bool ODBCInterface::execute(const char* sql_str) {
  __ENTER_FUNCTION
    memset(query_.sql_str_, '\0', sizeof(query_.sql_str_));
    strncpy(query_.sql_str_, sql_str, sizeof(query_.sql_str_) - 1);
    return execute();
  __LEAVE_FUNCTION
    return false;
}

bool ODBCInterface::long_execute() {
  __ENTER_FUNCTION
    //int column_index;
    result_ = SQLExecDirect(sql_hstmt_, 
                            reinterpret_cast<SQLCHAR*>(long_query_.sql_str_), 
                            SQL_NTS);
    if ((result_ != SQL_SUCCESS) && 
        (result_ != SQL_SUCCESS_WITH_INFO) &&
        (result_ != SQL_NO_DATA)) {
      diag_state_ex();
      return false;
    }
    SQLRowCount(sql_hstmt_, &affect_count_);
    SQLNumResultCols(sql_hstmt_, &column_count_);
    if (MAX_COLUMN < column_count_) return false;
    if (0 >= affect_count_ && 0 >= column_count_) {
      clear();
      return true;
    }
    /**
    for (column_index = 0; column_index < column_count_; ++column_index) {
      SQLBindCol( sql_hstmt_, 
                  column_index + 1, 
                  SQL_C_CHAR,
                  column_[column_index],
                  MAX_COLUMN_BUFFER,
                  &column_locate_[column_index]);
      SQLDescribeCol(sql_hstmt_,
                     column_index + 1,
                     column_name_[column_index],
                     MAX_COLUMN_NAME,
                     NULL,
                     NULL,
                     NULL,
                     NULL,
                     NULL);
    }
    **/ //this code will be want the result to array, but now i don't known it.
    return true;
  __LEAVE_FUNCTION
     save_error_log("Huge Error occur:");
     save_error_log(static_cast<const char*>(query_.sql_str_));
     return false;
}

bool ODBCInterface::long_excute(const char* sql_str) {
  __ENTER_FUNCTION
    memset(long_query_.sql_str_, '\0', sizeof(long_query_.sql_str_));
    strncpy(long_query_.sql_str_, sql_str, sizeof(long_query_.sql_str_) - 1);
    return long_execute();
  __LEAVE_FUNCTION
    return false;
}

void ODBCInterface::clear_no_commit() {
  __ENTER_FUNCTION
    SQLCloseCursor(sql_hstmt_);
    SQLFreeStmt(sql_hstmt_, SQL_UNBIND);
  __LEAVE_FUNCTION
}

void ODBCInterface::clear() {
  __ENTER_FUNCTION
    SQLCloseCursor(sql_hstmt_);
    SQLFreeStmt(sql_hstmt_, SQL_UNBIND);
  __LEAVE_FUNCTION
}

bool ODBCInterface::fetch() {
  __ENTER_FUNCTION
    result_ = SQLFetch(sql_hstmt_);
    if ((result_ != SQL_SUCCESS) && 
        (result_ != SQL_SUCCESS_WITH_INFO)) {
      diag_state();
      return false;
    }
    for (int column_index = 0; column_index < column_count_; ++column_index) {
      int get_total = 0;
      SQLLEN data_length = 0;
      while((result_ = SQLGetData(sql_hstmt_, 
                                  static_cast<SQLUSMALLINT>(column_index + 1), 
                                  static_cast<SQLUSMALLINT>(SQL_C_CHAR), 
                                  column_[column_index] + get_total, 
                                  MAX_COLUMN_BUFFER, 
                                  &data_length)) != SQL_NO_DATA) {
        break;
      }
    }
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool ODBCInterface::long_fetch() {
  __ENTER_FUNCTION
    result_ = SQLFetch(sql_hstmt_);
    if ((result_ != SQL_SUCCESS) && 
        (result_ != SQL_SUCCESS_WITH_INFO)) {
      diag_state();
      return false;
    }
    for (int32_t column_index = 0; 
         column_index < column_count_; ++column_index) {
      int32_t get_total = 0;
      SQLLEN data_length = 0;
      while((result_ = SQLGetData(sql_hstmt_, 
                                  static_cast<SQLUSMALLINT>(column_index + 1), 
                                  static_cast<SQLUSMALLINT>(SQL_C_CHAR), 
                                  column_[column_index] + get_total, 
                                  MAX_LONG_COLUMN_BUFFER, 
                                  &data_length)) != SQL_NO_DATA) {
        break;
      }
    }
    return true;
  __LEAVE_FUNCTION
    return false;
}

int32_t ODBCInterface::get_int(int32_t column_index, int32_t &error_code) {
  __ENTER_FUNCTION
    if (column_index > column_count_) {
      error_code = QUERY_NO_COLUMN;
      Assert(false);
      return QUERY_NO_COLUMN;
    }
    if (SQL_NULL_DATA == column_locate_[column_index - 1]) {
      error_code = QUERY_NULL;
      Assert(false);
      return QUERY_NULL;
    }
    else {
      error_code = QUERY_OK;
      return atoi(column_[column_index - 1]);
    }
  __LEAVE_FUNCTION
    return QUERY_NULL;
}

uint32_t ODBCInterface::get_uint(int32_t column_index, int32_t &error_code) {
  __ENTER_FUNCTION
    if (column_index > column_count_) {
      error_code = QUERY_NO_COLUMN;
      Assert(false);
      return 0;
    }
    if (SQL_NULL_DATA == column_locate_[column_index - 1]) {
      error_code = QUERY_NULL;
      Assert(false);
      return 0;
    }
    else {
      error_code = QUERY_OK;
      return static_cast<uint32_t>(atoi(column_[column_index - 1]));
    }
  __LEAVE_FUNCTION
    return 0;
}

float ODBCInterface::get_float(int32_t column_index, int32_t &error_code) {
  __ENTER_FUNCTION
    if (column_index > column_count_) {
      error_code = QUERY_NO_COLUMN;
      Assert(false);
      return QUERY_NO_COLUMN;
    }
    if (SQL_NULL_DATA == column_locate_[column_index - 1]) {
      error_code = QUERY_NULL;
      Assert(false);
      return QUERY_NULL;
    }
    else {
      error_code = QUERY_OK;
      return static_cast<float>(atof(column_[column_index - 1]));
    }
  __LEAVE_FUNCTION
    return QUERY_NULL;
}

void ODBCInterface::get_string(int32_t column_index, 
                               char* buffer, 
                               int32_t buffer_length, 
                               int32_t &error_code) {
  __ENTER_FUNCTION
    if (column_index > column_count_) {
      error_code = QUERY_NO_COLUMN;
      buffer[0] = '\0';
      Assert(false);
      return;
    }
    if (SQL_NULL_DATA == column_locate_[column_index - 1]) {
      error_code = QUERY_NULL;
      buffer[0] = '\0';
      Assert(false);
    }
    else {
      if (MAX_COLUMN_BUFFER > buffer_length) {
        strncpy(buffer, column_[column_index - 1], buffer_length);
      }
      else {
        strncpy(buffer, column_[column_index - 1], MAX_COLUMN_BUFFER);
      }
      error_code = QUERY_OK;
    }
  __LEAVE_FUNCTION
}

void ODBCInterface::get_field(int32_t column_index, 
                              char* buffer, 
                              int32_t buffer_length, 
                              int32_t & error_code) {
  __ENTER_FUNCTION
    if (column_index > column_count_) {
      error_code = QUERY_NO_COLUMN;
      buffer[0] = '\0';
      Assert(false);
      return;
    }
    if (SQL_NULL_DATA == column_locate_[column_index - 1]) {
      error_code = QUERY_NULL;
      buffer[0] = '\0';
      Assert(false);
    }
    else {
      if (MAX_COLUMN_BUFFER > buffer_length) {
        uint32_t out_length = 0;
        pap_common_base::util::string_tobinary(column_[column_index - 1], 
                                               MAX_COLUMN_BUFFER, 
                                               buffer, 
                                               buffer_length, 
                                               out_length);
        Assert(static_cast<int32_t>(out_length) <= buffer_length);
      }
      else {
        memcpy(buffer, column_[column_index - 1], MAX_COLUMN_BUFFER);
        Assert(false);
      }
      error_code = QUERY_OK;
    }
  __LEAVE_FUNCTION
}

void ODBCInterface::get_long_field(int32_t column_index, 
                                   char* buffer, 
                                   int32_t buffer_length, 
                                   int32_t & error_code) {
  __ENTER_FUNCTION
    if (column_index > column_count_) {
      error_code = QUERY_NO_COLUMN;
      buffer[0] = '\0';
      Assert(false);
      return;
    }
    if (SQL_NULL_DATA == column_locate_[column_index - 1]) {
      error_code = QUERY_NULL;
      buffer[0] = '\0';
      Assert(false);
    }
    else {
      if (MAX_COLUMN_BUFFER > buffer_length) {
        uint32_t out_length = 0;
        pap_common_base::util::string_tobinary(column_[column_index - 1], 
                                               MAX_LONG_COLUMN_BUFFER, 
                                               buffer, 
                                               buffer_length, 
                                               out_length);
        Assert(static_cast<int32_t>(out_length) <= buffer_length);
      }
      else {
        memcpy(buffer, column_[column_index - 1], MAX_LONG_COLUMN_BUFFER);
        Assert(false);
      }
      error_code = QUERY_OK;
    }
  __LEAVE_FUNCTION
}

void ODBCInterface::diag_state() {
  __ENTER_FUNCTION
    int32_t j = 1;
    SQLINTEGER native_error;
    SQLCHAR sql_state[6];
    SQLSMALLINT msg_length;
    memset(error_message_, 0, MAX_ERROR_MESSAGE_LENGTH);
    while ((result_ = SQLGetDiagRec(SQL_HANDLE_DBC, 
                                    sql_hdbc_,
                                    static_cast<SQLUSMALLINT>(j), 
                                    sql_state,
                                    &native_error,
                                    error_message_, 
                                    sizeof(error_message_), 
                                    &msg_length)) != SQL_NO_DATA) {
      ++j;
    }
    error_message_[MAX_ERROR_MESSAGE_LENGTH - 1] = '\0';
    if (0 == strlen(reinterpret_cast<const char*>(error_message_))) {
      result_ = SQLError(sql_henv_,
                         sql_hdbc_,
                         sql_hstmt_,
                         sql_state,
                         &native_error,
                         error_message_,
                         sizeof(error_message_),
                         &msg_length);
    }
    error_code_ = native_error;
    switch (error_code_) {
      case 2601: { //repeat
        break;
      }
      case 1062: {
        break;
      }
      default: {
        close();
      }
    }
    char error_buffer[512];
    memset(error_buffer, '\0', sizeof(error_buffer));
    snprintf(error_buffer,
             sizeof(error_buffer) - 1,
             "error code: %d, error msg: %s,error sql", 
             error_code_, error_message_);
    save_error_log(error_buffer);
    save_error_log(static_cast<const char*>(query_.sql_str_));
  __LEAVE_FUNCTION
}

void ODBCInterface::diag_state_ex() {
  __ENTER_FUNCTION
    int32_t j = 1;
    SQLINTEGER native_error;
    SQLCHAR sql_state[6];
    SQLSMALLINT msg_length;
    memset(error_message_, 0, MAX_ERROR_MESSAGE_LENGTH);
    while ((result_ = SQLGetDiagRec(SQL_HANDLE_DBC, 
                                    sql_hdbc_,
                                    static_cast<SQLUSMALLINT>(j), 
                                    sql_state,
                                    &native_error,
                                    error_message_, 
                                    sizeof(error_message_), 
                                    &msg_length)) != SQL_NO_DATA) {
      ++j;
    }
    error_message_[MAX_ERROR_MESSAGE_LENGTH - 1] = '\0';
    if (0 == strlen(reinterpret_cast<const char*>(error_message_))) {
      result_ = SQLError(sql_henv_,
                         sql_hdbc_,
                         sql_hstmt_,
                         sql_state,
                         &native_error,
                         error_message_,
                         sizeof(error_message_),
                         &msg_length);
    }
    error_code_ = native_error;
    switch (error_code_) {
      case 2601: { //repeat
        break;
      }
      case 1062: {
        break;
      }
      default: {
        close();
      }
    }
    char error_buffer[512];
    memset(error_buffer, '\0', sizeof(error_buffer));
    snprintf(error_buffer,
             sizeof(error_buffer) - 1,
             "error code: %d, error msg: %s,error sql", 
             error_code_, 
             error_message_);
    save_error_log(error_buffer);
    save_error_log(static_cast<const char*>(long_query_.sql_str_));
  __LEAVE_FUNCTION
}
void ODBCInterface::save_error_log(const char* log) {
  __ENTER_FUNCTION
    if (0 == strlen(log)) return;
     FILE* f = fopen("./Log/dberror.log", "a");
     if (f) {
       fwrite(log, 1, strlen(log), f);
       fwrite(LF, 1, sizeof(LF), f);
       fclose(f);
     }
  __LEAVE_FUNCTION
}

void ODBCInterface::save_warning_log(const char* log) {
  __ENTER_FUNCTION
    if (0 == strlen(log)) return;
     FILE* f = fopen("./Log/dbwarning.log", "a");
     if (f) {
       fwrite(log, 1, strlen(log), f);
       fwrite(LF, 1, sizeof(LF), f);
       fclose(f);
     }
  __LEAVE_FUNCTION
}

void ODBCInterface::clear_env() {
  __ENTER_FUNCTION
    if (sql_hstmt_) {
      SQLCloseCursor(sql_hstmt_);
      SQLFreeStmt(sql_hstmt_, SQL_UNBIND);
      SQLFreeHandle(SQL_HANDLE_STMT,sql_hstmt_);
      sql_hstmt_ = NULL;
    }
    if (sql_hdbc_) {
      SQLDisconnect(sql_hdbc_);
      SQLFreeHandle(SQL_HANDLE_DBC, sql_hdbc_);
      sql_hdbc_ = NULL;
    }
#ifdef MUST_CLOSE_HENV_HANDLE
    if (sql_henv_) {
      SQLFreeHandle(SQL_HANDLE_ENV, sql_henv_);
      sql_henv_ = NULL;
    }
#endif
  __LEAVE_FUNCTION
}
//dump field
void ODBCInterface::dump(int32_t column_index) {
  __ENTER_FUNCTION
    FILE* f = fopen("./Log/field", "a");
    if (f) {
      fwrite("begin", 1, 5, f);
      fwrite(column_[column_index - 1], 1, MAX_COLUMN_BUFFER, f);
      fclose(f);
    }
  __LEAVE_FUNCTION
}

uint16_t ODBCInterface::get_ushort(int32_t column_index, int32_t &error_code) {
  __ENTER_FUNCTION
    return static_cast<uint16_t>(get_int(column_index, error_code));
  __LEAVE_FUNCTION
    return 0;
}

uint8_t ODBCInterface::get_byte(int32_t column_index, int32_t &error_code) {
  __ENTER_FUNCTION
    return static_cast<uint8_t>(get_int(column_index, error_code));
  __LEAVE_FUNCTION
    return 0;
}

int16_t ODBCInterface::get_short(int32_t column_index, int32_t &error_code) {
  __ENTER_FUNCTION
    return static_cast<int16_t>(get_int(column_index, error_code));
  __LEAVE_FUNCTION
    return 0;
}

int32_t ODBCInterface::get_error_code() {
  __ENTER_FUNCTION
    return error_code_;
  __LEAVE_FUNCTION
    return 0;
}

char* ODBCInterface::get_error_message() {
  __ENTER_FUNCTION
    return reinterpret_cast<char*>(error_message_);
  __LEAVE_FUNCTION
    return NULL;
}

bool ODBCInterface::is_connected() {
  __ENTER_FUNCTION
    return connectd_;
  __LEAVE_FUNCTION
    return false;
}

int ODBCInterface::get_affect_row_count() {
  __ENTER_FUNCTION
    return affect_count_;
  __LEAVE_FUNCTION
    return 0;
}

bool ODBCInterface::is_prepare() {
  __ENTER_FUNCTION
    return connectd_;
  __LEAVE_FUNCTION
    return false;
}

db_query_t& ODBCInterface::get_query() {
   return query_;
}

long_db_query_t& ODBCInterface::get_long_query() {
  return long_query_;
}

} //namespace pap_server_common_db
