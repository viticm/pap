#ifndef PAP_SERVER_COMMON_DB_DB_SYSTEM_H_
#define PAP_SERVER_COMMON_DB_DB_SYSTEM_H_
#include "common/ptype.h"
#include "db_define.h"
class DBSystem {
 public:
   enum DBOP_TYPE {
     DB_LOAD,
     DB_SAVE, //insert and update
     DB_ADDNEW,
     DB_DELETE,
     DB_INIT_EMPTY, //db at init state
   };
#if defined(__WINDOWS__)
   enum ODBC_ERROR {
     DB_SAME_PRI_KEY = 2601, //repeat primary key
   }
#elif defined(__LINUX__)
   enum ODBC_ERROR {
     DB_SAME_PRI_KEY = 1026, //repeat primary key
   }
#endif
   DBSystem();
   void set_db_type(DB_TYPES db_type);
   uint get_result_count();
   int get_error_code();
   char* get_error_msg();
   virtual bool load();
   virtual bool add_new();
   virtual bool delete_();
   virtual bool save(void* source);
   virtual bool parse_result(void* result) = 0;

 protected:
   int result_count_;
   bool result_;
   DB_TYPES db_type_;
   DBOP_TYPE op_type_;
   ODBCInterface* odbc_interface_;
   DB_QUERY* get_internal_query();
   LONG_DB_QUERY* get_long_internal_query();
   int get_internal_affect_count();
   bool is_prepare();
   bool check_db_connect(); //check the connect if work, and repeat 5 times on fails
   bool long_load();
   bool long_save(void* source);
}
#endif //PAP_SERVER_COMMON_DB_DB_SYSTEM_H_
