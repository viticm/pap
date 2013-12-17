/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id ptype.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-22 19:29:37
 * @uses the db system class, to provide some convenient operation functions.
 */
#ifndef PAP_SERVER_COMMON_DB_SYSTEM_H_
#define PAP_SERVER_COMMON_DB_SYSTEM_H_
#include "server/common/db/config.h"
#include "server/common/db/odbc_interface.h"

namespace pap_server_common_db {

class System {
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
   };
#elif defined(__LINUX__)
   enum ODBC_ERROR {
     DB_SAME_PRI_KEY = 1026, //repeat primary key
   };
#endif

 public:
   System();
   ~System();
   void set_db_type(db_type_enum db_type);
   uint32_t get_result_count();
   int get_error_code();
   char* get_error_message();
   virtual bool load();
   virtual bool add_new();
   virtual bool delete_();
   virtual bool save(void* source);
   virtual bool parse_result(void* result) = 0;

 protected:
   int32_t result_count_;
   bool result_;
   db_type_enum db_type_;
   DBOP_TYPE op_type_;
   ODBCInterface* odbc_interface_;
   db_query_t* get_internal_query();
   long_db_query_t* get_long_internal_query();
   int32_t get_internal_affect_count();
   bool is_prepare();
   bool check_db_connect(); //check the connect if work, 
                            //and repeat 5 times when fails
   bool long_load();
   bool long_save(void* source);
};

}; //namespace pap_server_common_db

#endif //PAP_SERVER_COMMON_DB_SYSTEM_H_
