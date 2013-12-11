/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id global.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-6 16:28:57
 * @uses the server database global data for database class
 *      cn: 这个是全局数据的操作实现类，负责与数据库的存取数据，
 *          以后考虑将格式统一，自动生成代码
 */
#ifndef PAP_SERVER_COMMON_DB_DATA_GLOBAL_H_
#define PAP_SERVER_COMMON_DB_DATA_GLOBAL_H_

#include "server/common/db/data/config.h"
#include "server/common/db/system.h"

namespace pap_server_common_db {

namespace data {

class Global : public System {

 public:
   Global(ODBCInterface* odbc_interface);
   ~Global();
   virtual bool load();
   virtual bool save(void* source);
   virtual bool _delete();
   virtual bool parse_result(void* result);
   void set_pool_id(int16_t id);
   int16_t get_pool_id();

 private:
   int16_t pool_id_;

};

}; //namespace data

}; //namespace pap_server_common_db

#endif //PAP_SERVER_COMMON_DB_DATA_GLOBAL_H_
