/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id ptype.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-22 19:29:37
 * @uses the db manager class, just for server use dbs.
 */
#ifndef PAP_SERVER_COMMON_DB_DB_MANAGER_H_
#define PAP_SERVER_COMMON_DB_DB_MANAGER_H_
#include "db_define.h"
#include "odbc_interface.h"

class DBManager {
 public:
   DBManager();
   ~DBManager();
   bool init(DB_TYPES db_type = ALL_DATABASE);
   ODBCInterface* get_interface(DB_TYPES db_type);

 private:
   DB_TYPES db_type_;
   ODBCInterface* character_interface_;
   ODBCInterface* user_interface_;
}

#endif //PAP_SERVER_COMMON_DB_DB_MANAGER_H_
