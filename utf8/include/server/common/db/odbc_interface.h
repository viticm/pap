/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id odbc_interface.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-22 19:29:37
 * @uses the odbc interface class(some op functions)
 */
#ifndef PAP_SERVER_COMMON_DB_ODBC_INTERFACE_H_
#define PAP_SERVER_COMMON_DB_ODBC_INTERFACE_H_

#include "server/common/db/config.h"
#include "server/common/base/define.h"
//include from odbc
#ifndef VOID
#define VOID void //for unixODBC
#endif

#include "sql.h"
#include "sqlext.h"

#define HOST_LENGTH 30
#define CONNECTION_NAME_LENGTH 32
#define MAX_COLUMN_NAME 30 //column name max length
#define MAX_COLUMN_BUFFER 2049 //normal one column value length
#define MAX_LONG_COLUMN_BUFFER 204800 //long column value length
#define MAX_ERROR_MESSAGE_LENGTH 255

namespace pap_server_common_db {

//#define USE_MYSQL

class ODBCInterface {
 public:
   enum
   {
     MAX_COLUMN = 100,
     BLOB_BATCH = 10000,
     QUERY_OK = 0,
     QUERY_NULL = -100,
     QUERY_EOF = -101,
     QUERY_NO_COLUMN = -102,
     QUERY_ERROR = -103,
   };
   bool connectd_;
   SQLHENV sql_henv_;
   SQLHDBC sql_hdbc_;
   SQLRETURN result_;
   char column_[MAX_COLUMN][MAX_COLUMN_BUFFER];
   char connection_name_[DB_CONNECTION_NAME_LENGTH];
   char user_[DB_USER_NAME_LENGTH];
   char password_[DB_PASSWORD_LENGTH];

   SQLLEN affect_count_;
   SQLHSTMT sql_hstmt_;
   SQLSMALLINT column_count_;
   SQLCHAR column_name_[MAX_COLUMN][MAX_COLUMN_NAME];
   SQLLEN column_locate_[MAX_COLUMN];
   
   db_query_t query_;
   long_db_query_t long_query_;
   SQLINTEGER error_code_;
   SQLCHAR error_message_[MAX_ERROR_MESSAGE_LENGTH];

 public:
   ODBCInterface();
   ~ODBCInterface();
   bool connect(const char* connection_name, 
                const char* user = NULL, 
                const char* password = NULL);
   bool connect();
   bool close();
   int32_t get_error_code();
   char* get_error_message();
   bool is_connected();
   int32_t get_affect_row_count();
   bool is_prepare();
   void clear();
   void clear_no_commit();
   bool fetch();
   bool long_fetch();
   db_query_t& get_query();
   long_db_query_t& get_long_query();
   bool execute();
   bool execute(const char* sql_str);
   bool long_execute();
   bool long_excute(const char* sql_str);
   int32_t get_int(int32_t column_index, int32_t &error_code);
   uint32_t get_uint(int32_t column_index, int32_t &error_code);
   float get_float(int32_t column_index, int32_t &error_code);
   uint16_t get_ushort(int32_t column_index, int32_t &error_code);
   uint8_t get_byte(int32_t column_index, int32_t &error_code);
   int16_t get_short(int32_t column_index, int32_t &error_code);
   void get_string(int32_t column, 
                   char* buffer, 
                   int32_t buffer_length, 
                   int32_t &error_code);
   void get_field(int32_t column, 
                  char* buffer, 
                  int32_t buffer_length, 
                  int32_t &error_code);
   void get_long_field(int32_t column, 
                       char* buffer, 
                       int32_t buffer_length, 
                       int32_t &error_code);

   //分析
   void diag_state();
   void diag_state_ex();
   void save_error_log(const char* log);
   void save_warning_log(const char* log);
   void clear_env();
   void dump(int32_t column);
};

}; //namespace pap_server_common_db

#endif //PAP_SERVER_COMMON_DB_ODBC_INTERFACE_H_
