#include "server/billing/db/user/manager.h"
#include "common/base/md5.h"

namespace db {

namespace user {

Manager::Manager() {
  //do nothing
}

Manager::~Manager() {
  __ENTER_FUNCTION
    SAFE_DELETE(dbmanager_);
  __LEAVE_FUNCTION
}

bool Manager::init() {
  __ENTER_FUNCTION
    dbmanager_ = new pap_server_common_db::Manager();
    if (!dbmanager_->init()) return false;
    user_odbcinterface_ = dbmanager_->get_interface(kUserDatabase);
    snprintf(sqlstr_, sizeof(sqlstr_) - 1, "USE userdb");
    strncpy(user_odbcinterface_->query_.sql_str_, sqlstr_);
    user_odbcinterface_->clear();
    if (!userdb_odbcinterface_->execute()) return false;
    return true;
  __LEAVE_FUNCTION
    return false;
}

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
             const char* password2) {
  __ENTER_FUNCTION
    char encryptpassword[36] = {0};
    char encryptpassword2[36] = {0};
    passwordencrypt(password, encryptpassword);
    passwordencrypt(password2, encryptpassword2);
    snprintf(sqlstr_, 
             sizeof(sqlstr_) - 1,
             "call adduser('%s', '%s', '%s', '%s', '%s', '%s', '%s', "
             "'%s', '%s', '%s', '%s', '%s', %d, '%s', '%s', '%s')",
             name,
             encryptpassword,
             prompt,
             answer,
             truename,
             idnumber,
             email,
             mobilenumber,
             province,
             city,
             phonenumber,
             postalcode,
             gender,
             birthday,
             qq,
             encryptpassword2);
    strncpy(user_odbcinterface_->query_.sql_str_,
            sizeof(user_odbcinterface_->query_.sql_str_) - 1,
            sqlstr_);
    user_odbcinterface_->clear();
    if (!user_odbcinterface_->execute() || 
        user_odbcinterface_->affect_count_ <= 0) return false;
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool Manager::changepassword(const char* username, const char* password) {
  __ENTER_FUNCTION
    char encryptpassword[36] = {0};
    passwordencrypt(password, encryptpassword);
    snprintf(sqlstr_, 
             sizeof(sqlstr_) - 1,
             "call changepassword('%s', '%s')", 
             username, 
             encryptpassword);
    user_odbcinterface_->clear();
    if (!user_odbcinterface_->execute()) return false;
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool Manager::deleteuser(const char* username) {
  __ENTER_FUNCTION
    snprintf(sqlstr_, 
             sizeof(sqlstr_) - 1, 
             "DELETE FROM `users` WHERE name = '%s'", 
             username);
    user_odbcinterface_->clear();
    if (!user_odbcinterface_->execute() || 
        user_odbcinterface_->affect_count_ <= 0) return false;
    return true;
  __LEAVE_FUNCTION
    return false;
}

uint32_t Manager::get_usercount() {
  __ENTER_FUNCTION
    uint32_t result = 0;
    snprintf(sqlstr_,
             sizeof(sqlstr_) - 1,
             "SELECT COUNT(id) AS counts FROM `users`");
    user_odbcinterface_->clear();
    if (user_odbcinterface_->execute()) {
      user_odbcinterface_->fetch();
      result = static_cast<uint32_t>(atoi(user_odbcinterface_->column_[0]));
    }
    return result;
  __LEAVE_FUNCTION
    return 0;
}

bool Manager::is_haveuser(const char* username) {
  __ENTER_FUNCTION
    bool result = false;
    return result;
  __LEAVE_FUNCTION
    return false;
}

} //namespace user

} //namespace db
