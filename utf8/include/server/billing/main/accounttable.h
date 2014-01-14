/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id accounttable.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-13 17:44:35
 * @uses the excel account table class
 */
#ifndef PAP_SERVER_BILLING_MAIN_ACCOUNTTABLE_H_
#define PAP_SERVER_BILLING_MAIN_ACCOUNTTABLE_H_

#include "common/base/type.h"
#include "common/base/string.h"
#include "common/game/define/macros.h"

class AccountTable {

 public:
   AccountTable() {};
   ~AccountTable() {};

 public:
   struct password_t {
     char str[PASSWORDMAX];
   };

 public:
   bool init();
   bool check(const char* username, const char* password);

 private:
   pap_common_base::string::Table strtable_;
   password_t* password_;
   int32_t count_;

};

extern AccountTable g_accounttable;

#endif //PAP_SERVER_BILLING_MAIN_ACCOUNTTABLE_H_

