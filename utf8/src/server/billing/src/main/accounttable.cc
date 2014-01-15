#include "server/billing/main/accounttable.h"
#include "common/file/database.h"

AccountTable g_accounttable;

bool AccountTable::init() {
  __ENTER_FUNCTION
    bool result = false;
    pap_common_file::Database account_dbfile(0);
    result = account_dbfile.open_from_txt("./config/account.txt");
    if (!result) return false;
    int32_t tablecount = account_dbfile.get_record_number();
    //int32_t tablecolumn = account_dbfile.get_field_number();
    if (tablecount <= 0) return false;
    password_ = new password_t[tablecount];
    strtable_.init(tablecount, ACCOUNTLENGTH_MAX);
    int32_t i;
    for (i = 0; i < tablecount; ++i) {
      strncpy(password_[i].str, 
              account_dbfile.search_position(i, 1)->string_value, 
              PASSWORDMAX);
      strtable_.add(account_dbfile.search_position(i, 0)->string_value, 
                    password_[i].str);
    }
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool AccountTable::check(const char* username, const char* password) {
  __ENTER_FUNCTION  
    bool result = false;
    Assert(username);
    char* rightpassword = static_cast<char*>(strtable_.get(username));
    if (NULL == rightpassword) return false;
    Assert(password);
    result = 0 == strcmp(password, rightpassword);
    return result;
  __LEAVE_FUNCTION
    return false;
}
