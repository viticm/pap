/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-18 10:34:02
 * @uses 用户数据库管理器
 */
#ifndef PAP_SERVER_BILLING_DB_USER_MANAGER_H_
#define PAP_SERVER_BILLING_DB_USER_MANAGER_H_

#include "server/common/db/manager.h"

namespace db {

namespace user {

class Manager {

 public:
   Manager();
   virtual ~Manager();

 public:
   pap_server_common_db::Manager* dbmanager_;
   char sqlstr_[SQL_LENGTH_MAX];

 public:
   bool init();
   bool adduser(const char* name, 
                const char* password,
                const char* prompt,
                const char* answer,
                const char* truename,
                const char* idnumber,
                const char* email,
                const char* mobilenumber,
                const char* province,
                const char* city,
                const char* phonenumber,
                const char* address,
                const char* postalcode,
                uint8_t gender,
                const char* birthday,
                const char* qq,
                const char* password2); //register will in web, just for test
   bool changepassword(const char* username, const char* password);
   bool deleteuser(const char* username);
   uint32_t get_usercount();
   bool is_haveuser(const char* username);
   bool is_realuser(const char* username, const char* password);
   void passwordencrypt(const char* in, char* out);

 private:
   pap_server_common_db::ODBCInterface* user_odbcinterface_;

};

}; //namespace user

}; //namespace db

#endif //PAP_SERVER_BILLING_DB_USER_MANAGER_H_
