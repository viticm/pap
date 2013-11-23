#include "server/common/db/odbc_interface.h"
#include "common/pgame_util.h"
ODBCInterface::ODBCInterface() {
  __ENTER_FUNCTION
    connectd_ = false;
    affect_count_ = -1;
    result_ = SQL_SUCCESS;
    sql_henv_ = NULL;
    sql_hdbc_ = NULL;
    sql_hstmt_ = NULL;
    memset(error_message_, 0, MAX_ERROR_MESSAGE_LENGTH);
    memset(connection_name_, 0, DB_CONNECTION_NAME_LENGTH);
    memset(user_, 0, DB_USER_NAME_LENGTH);
    memset(password_, 0, DB_PASSWORD_LENGTH);
    query_.clear();
    long_quer_.clear();
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
    close(); //first disconnect
    strncpy(connection_name_, connection_name, DB_CONNECTION_NAME_LENGTH);
    strncpy(user_, user, DB_USER_NAME_LENGTH);
    strncpy(password_, password, DB_PASSWORD_LENGTH);
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sql_henv_);
    SQLSetEnvAttr(sql_henv_, SQL_ATTR_ODBC_VERSION, static_cast<SQLPOINTER>(SQL_OV_ODBC3), SQL_IS_INTEGER);
    SQLAllocHandle(SQL_HANDLE_DBC, sql_henv_, &sql_hdbc_);
    result_ = SQLConnect(hDbc,
                         static_cast<SQLCHAR*>(connection_name_),
                         SQL_NTS,
                         static_cast<SQLCHAR*>(user_),
                         SQL_NTS,
                         static_cast<SQLCHAR*>(password_),
                         SQL_NTS);
    if (SQL_SUCCESS != result_ && SQL_SUCCESS_WITH_INFO != result_) {
      char log_buffer[512] = {0};
      sprintf(log_buffer, "connection name: %s", connection_name_);
      sprintf(log_buffer, "connect user: %s", user_);
      diag_state();
      return false;
    }
    result_ = SQLAllocHandle(SQL_HANDLE_STMT, sql_hdbc_, &sql_hstmt_);
    if (SQL_SUCCESS != result_ && SQL_SUCCESS_WITH_INFO != result_) {
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
    close(); //first disconnect
#ifdef MUST_CLOSE_HENV_HANDLE
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sql_henv_);
    SQLSetEnvAttr(sql_henv_, SQL_ATTR_ODBC_VERSION, static_cast<SQLPOINTER>(SQL_OV_ODBC3), SQL_IS_INTEGER);
#endif
    SQLAllocHandle(SQL_HANDLE_DBC, sql_henv_, &sql_hdbc_);
    result_ = SQLConnect(hDbc,
                         static_cast<SQLCHAR*>(database_),
                         SQL_NTS,
                         static_cast<SQLCHAR*>(user_),
                         SQL_NTS,
                         static_cast<SQLCHAR*>(password_),
                         SQL_NTS);
    if (SQL_SUCCESS != result_ && SQL_SUCCESS_WITH_INFO != result_) {
      char log_buffer[512] = {0};
      sprintf(log_buffer, "connect database: %s", database_);
      sprintf(log_buffer, "connect user: %s", user_);
      diag_state();
      return false;
    }
    result_ = SQLAllocHandle(SQL_HANDLE_STMT, sql_hdbc_, &sql_hstmt_);
    if (SQL_SUCCESS != result_ && SQL_SUCCESS_WITH_INFO != result_) {
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

bool ODBCInterface::excute() {
  __ENTER_FUNCTION
    //int column_index;
    result_ = SQLExecDirect(sql_hstmt_, static_cast<SQLCHAR*>(query_.sql_str_), SQL_NTS);
    if ((SQL_SUCCESS != result_) && 
        (SQL_SUCCESS_WITH_INFO != result_) &&
        (SQL_NO_DATA != result_)) {
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
  __LEAVE_FUNCTION
     save_error_log("Huge Error occur:");
     save_error_log(static_cast<const char*>(query_.sql_str_));
     return false;
}

bool ODBCInterface::excute(const char* sql_str) {
  __ENTER_FUNCTION
    memset(query_.sql_str_, 0, MAX_SQL_LENGTH);
    strncpy(query_.sql_str_, sql_str_, MAX_SQL_LENGTH);
    return execute();
  __LEAVE_FUNCTION
    return false;
}

bool ODBCInterface::long_excute() {
  __ENTER_FUNCTION
    //int column_index;
    result_ = SQLExecDirect(sql_hstmt_, static_cast<SQLCHAR*>(long_query_.sql_str_), SQL_NTS);
    if ((SQL_SUCCESS != result_) && 
        (SQL_SUCCESS_WITH_INFO != result_) &&
        (SQL_NO_DATA != result_)) {
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
    memset(long_query_.sql_str_, 0, MAX_LONG_SQL_LENGTH);
    strncpy(long_query_.sql_str_, sql_str_, MAX_LONG_SQL_LENGTH);
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
    if ((SQL_SUCCESS != result_) && 
        (SQL_SUCCESS_WITH_INFO != result_)) {
      diag_state();
      return false;
    }
    for (int column_index = 0; column_index < column_count_; ++column_index) {
      int get_total = 0;
      SQLLEN data_length = 0;
      while((result_ = SQLGetData(sql_hstmt_, 
                                    column_index + 1, 
                                    SQL_C_CHAR, 
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
    if ((SQL_SUCCESS != result_) && 
        (SQL_SUCCESS_WITH_INFO != result_)) {
      diag_state();
      return false;
    }
    for (int column_index = 0; column_index < column_count_; ++column_index) {
      int get_total = 0;
      SQLLEN data_length = 0;
      while((result_ = SQLGetData(sql_hstmt_, 
                                   column_index + 1, 
                                   SQL_C_CHAR, 
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

int ODBCInterface::get_int(int column_index, int &error_code) {
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

uint32_t ODBCInterface::get_uint(int column_index, int &error_code) {
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
      return static_cast<uint32_t>(atoi(column_[column_index - 1]));
    }
  __LEAVE_FUNCTION
    return QUERY_NULL;
}

float ODBCInterface::get_float(int column_index, int &error_code) {
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
      return atof(column_[column_index - 1]);
    }
  __LEAVE_FUNCTION
    return QUERY_NULL;
}

void ODBCInterface::get_string(int column_index, 
                               char* buffer, 
                               int buffer_length, 
                               int &error_code) {
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

void ODBCInterface::get_field(int column_index, 
                              char* buffer, 
                              int buffer_length, 
                              int & error_code) {
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
        PGameUtil::string_to_binary(column_[column_index - 1], 
                                    MAX_COLUMN_BUFFER, 
                                    buffer, 
                                    buffer_length, 
                                    out_length);
        Assert(static_cast<int>(out_length) <= buffer_length);
      }
      else {
        memcpy(buffer, column_[column_index - 1], MAX_COLUMN_BUFFER);
        Assert(false);
      }
      error_code = QUERY_OK;
    }
  __LEAVE_FUNCTION
}

void ODBCInterface::get_long_field(int column_index, 
                                   char* buffer, 
                                   int buffer_length, 
                                   int & error_code) {
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
        PGameUtil::string_to_binary(column_[column_index - 1], 
                                    MAX_LONG_COLUMN_BUFFER, 
                                    buffer, 
                                    buffer_length, 
                                    out_length);
        Assert(static_cast<int>(out_length) <= buffer_length);
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
    int j = 1;
    SQLINTEGER native_error;
    SQLCHAR sql_state[6];
    SQLSMALLINT msg_length;
    memset(error_message_, 0, MAX_ERROR_MESSAGE_LENGTH);
    while ((result_ = SQLGetDiagRec(SQL_HANDLE_DBC, 
                                    sql_hdbc_,
                                    j, 
                                    sql_state,
                                    &native_error,
                                    error_message_, 
                                    sizeof(error_message_), 
                                    &msg_length)) !=SQL_NO_DATA) {
      ++j;
    }
    error_message_[MAX_ERROR_MSG_LENGHT - 1] = '\0';
    if (0 == strlen(static_cast<const char*>(error_message_))) {
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
    char error_buffer[512] = {0};
    sprintf(error_buffer,"error code: %d, error msg: %s,error sql", error_code_, error_message_);
    save_error_log(error_buffer);
    save_error_log(static_cast<const char*>(query_.sql_str_));
  __LEAVE_FUNCTION
}

void ODBCInterface::diag_state_ex() {
  __ENTER_FUNCTION
    int j = 1;
    SQLINTEGER native_error;
    SQLCHAR sql_state[6];
    SQLSMALLINT msg_length;
    memset(error_message_, 0, MAX_ERROR_MESSAGE_LENGTH);
    while ((result_ = SQLGetDiagRec(SQL_HANDLE_DBC, 
                                    sql_hdbc_,
                                    j, 
                                    sql_state,
                                    &native_error,
                                    error_message_, 
                                    sizeof(error_message_), 
                                    &msg_length)) !=SQL_NO_DATA) {
      ++j;
    }
    error_message_[MAX_ERROR_MSG_LENGHT - 1] = '\0';
    if (0 == strlen(static_cast<const char*>(error_message_))) {
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
    char error_buffer[512] = {0};
    sprintf(error_buffer,"error code: %d, error msg: %s,error sql", error_code_, error_message_);
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
void ODBCInterface::dump(int column_index) {
  __ENTER_FUNCTION
    FILE* f = fopen("./Log/field", "a");
    if (f) {
      fwrite("begin", 1, 5, f);
      fwrite(column_[column_index - 1], 1, MAX_COLUMN_BUFFER, f);
      fclose(f);
    }
  __LEAVE_FUNCTION
}

ushort ODBCInterface::get_ushort(int column_index, int &error_code) {
  __ENTER_FUNCTION
    return static_cast<unsigned short>(get_int(column_index, error_code));
  __LEAVE_FUNCTION
}

ubyte ODBCInterface::get_byte(int column_index, int &error_code) {
  __ENTER_FUNCTION
    return static_cast<unsigned char>(get_int(column_index, error_code));
  __LEAVE_FUNCTION
}

short ODBCInterface::get_short(int column_index, int &error_code) {
  __ENTER_FUNCTION
    return static_cast<short>(get_int(column_index, error_code));
  __LEAVE_FUNCTION
}

int ODBCInterface::get_error_code() {
  __ENTER_FUNCTION
    return error_code_;
  __LEAVE_FUNCTION
}

char* ODBCInterface::get_error_message() {
  __ENTER_FUNCTION
     return error_message_;
  __LEAVE_FUNCTION
}

bool ODBCInterface::is_connected() {
  __ENTER_FUNCTION
     return connectd_;
  __LEAVE_FUNCTION
}

int ODBCInterface::get_affect_row_count() {
  __ENTER_FUNCTION
     return affect_count_;
  __LEAVE_FUNCTION
}

bool ODBCInterface::is_prepare() {
  __ENTER_FUNCTION
    return connectd_;
  __LEAVE_FUNCTION
}

DB_QUERY& ODBCInterface::get_query() {
  __ENTER_FUNCTION
    return query_;
  __LEAVE_FUNCTION
}

LONG_DB_QUERY& ODBCInterface::get_long_query() {
  __ENTER_FUNCTION
    return long_query_;
  __LEAVE_FUNCTION
}
