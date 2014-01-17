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
    if (tablecount <= 0) return false;
    int32_t i;
    for (i = 0; i < tablecount; ++i) {
      strmap_[account_dbfile.search_position(i, 0)->string_value] = 
        account_dbfile.search_position(i, 1)->string_value;
    }
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool AccountTable::check(const char* username, const char* password) {
  __ENTER_FUNCTION  
    bool result = false;
    Assert(username);
    const char* rightpassword = strmap_[username].c_str();
    if (NULL == rightpassword) return false;
    Assert(password);
    result = 0 == strcmp(password, rightpassword);
    return result;
  __LEAVE_FUNCTION
    return false;
}
