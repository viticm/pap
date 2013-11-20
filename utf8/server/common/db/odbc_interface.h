#ifndef PAP_SERVER_COMMON_DB_ODBC_INTERFACE_H_
#define PAP_SERVER_COMMON_DB_ODBC_INTERFACE_H_
#include "ptype.h"
#include "db_define.h"
#define USE_MYSQL
#define HOST_STR_LENGTH 30
#define CONNECTION_NAME_LENGTH 32
enum DB_NAMES
{
  CHARACTER_DATABASE = 1,
}
//include from odbc
#include "sql.h"
#include "sqlext.h"

#define MAX_COLUMN_NAME 30 //column name max length
#define MAX_COLUMN_BUFFER 2049 //normal one column value length
#define MAX_LONG_COLUMN_BUFFER 204800 //long column value length
#define MAX_ERROR_MSG_LENGHT 255

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
   char connect_str_[DATABASE_STR_LENGTH];
   char user_name[DB_USER_STR_LENGTH];
   char password_[DB_PASSWORD_STR_LENGTH];

   SQLLEN affect_count_;
   SQLHSTMT sql_hstmt_;
   SQLSMALLINT column_count_;
   SQLCHAR column_name_[MAX_COLUMN][MAX_COLUMN_NAME];
   SQLLEN column_locate_[MAX_COLUMN];
   
   DB_QUERY query_;
   LONG_DB_QUERY long_query_;
   SQLINTEGER error_code_;
   SQLCHAR error_msg_[MAX_ERROR_MSG_LENGHT];

 public:
   ODBCInterface();
   ~ODBCInterface();
   bool connect(char* host, char* user = NULL, char* password = NULL);
   bool connect();
   bool close();
   int get_error_code() {
     return error_code_;
   };
   char* get_error_msg() {
     return error_msg_;
   };
   bool is_connected() {
     return connectd_;
   };
   int get_affect_row_count() {
     return affect_count_;
   };
   bool is_prepare() {
     return connectd_;
   };
   void clear();
   void clear_not_commit();
   bool fetch();
   bool long_fetch();
   DB_QUERY& get_query() {
     return query_;
   };
   LONG_DB_QUERY& get_long_query() {
     return long_query_;
   };
   bool execute();
   bool long_execute();
   int get_int(int column_index, int &error_code);
   unsigned int get_uint(int column_index, int &error_code);
   float get_float(int column_index, int &error_code);
   unsigned short get_ushort(int column_index, int &error_code) {
     return static_cast<unsigned short>(get_int(column_index, error_code));
   };
   unsigned char get_byte(int column_index, int &error_code) {
     return static_cast<unsigned char>(get_int(column_index, error_code));
   };
   short get_short(int column_index, int &error_code) {
     return static_cast<short>(get_int(column_index, error_code));
   };
   void get_string(int column, char* buffer, int buffer_length, int &error_code);
   void get_field(int column, char* buffer, int buffer_length, int &error_code);
   void get_long_field(int column, char* buffer, int buffer_length, int &error_code);

   //分析
   void diag_state();
   void diag_state_ex();
   void save_error_log(const char* log);
   void save_warning(const char* log);
   void clear_env();
   void dump(int column);
};

#endif //PAP_SERVER_COMMON_DB_ODBC_INTERFACE_H_
