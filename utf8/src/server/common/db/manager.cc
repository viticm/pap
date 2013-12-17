#include "server/common/db/manager.h"
#include "server/common/base/log.h"
#include "server/common/base/config.h"

pap_server_common_db::Manager* g_db_manager = NULL;

namespace pap_server_common_db {

Manager::Manager() {
  __ENTER_FUNCTION
    db_type_ = kAllDatabase; //init as all database
    character_interface_ = NULL;
    user_interface_ = NULL;
  __LEAVE_FUNCTION
}

Manager::~Manager() {
  __ENTER_FUNCTION
    SAFE_DELETE(user_interface_);
    SAFE_DELETE(character_interface_);
  __LEAVE_FUNCTION
}

bool Manager::init(db_type_enum db_type) {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;
    db_type_ = db_type;
    char host[HOST_LENGTH];
    uint16_t port;
    char connection_name[DB_CONNECTION_NAME_LENGTH];
    char user[DB_USER_NAME_LENGTH];
    char password[DB_PASSWORD_LENGTH]; //this password is use in mysql, not encrypt password
    if (kAllDatabase == db_type_ || kCharacterDatabase == db_type_) { //share memory
      //init all variable in first(character db)
      character_interface_ = new ODBCInterface();
      memset(host, 0, HOST_LENGTH);
      port = 3306; //default mysql port
      memset(connection_name, 0, DB_CONNECTION_NAME_LENGTH);
      memset(user, 0, DB_USER_NAME_LENGTH);
      memset(password, 0, DB_PASSWORD_LENGTH);
#if defined(_PAP_LOGIN) //this diffrent from login server and share memory
      strncpy(host, g_config.login_info_.db_host_, HOST_LENGTH);
      port = g_config.login_info_.db_port_;
      strncpy(connection_name, g_config.login_info_.db_connection_name_, DB_CONNECTION_NAME_LENGTH);
      strncpy(user, g_config.login_info_.db_user_, DB_USER_NAME_LENGTH);
      strncpy(password, g_config.login_info_.db_password_, DB_PASSWORD_LENGTH);
#elif defined(_PAP_SHARE_MEMORY)
      strncpy(host, g_config.share_memory_info_.db_host_, HOST_LENGTH);
      port = g_config.share_memory_info_.db_port_;
      strncpy(connection_name, g_config.share_memory_info_.db_connection_name_, DB_CONNECTION_NAME_LENGTH);
      strncpy(user, g_config.share_memory_info_.db_user_, DB_USER_NAME_LENGTH);
      strncpy(password, g_config.share_memory_info_.db_password_, DB_PASSWORD_LENGTH);
#endif
      host[HOST_LENGTH - 1] = '\0';
      connection_name[DB_CONNECTION_NAME_LENGTH - 1] = '\0';
      user[DB_USER_NAME_LENGTH - 1] = '\0';
      password[DB_PASSWORD_LENGTH - 1] = '\0';

      Assert(character_interface_); //safe code
      bool connected = character_interface_->connect(connection_name, user, password);
      if (!connected) {
        Log::save_log("dbmanager", 
                      "character_interface_->connect()...get error: %s, db_type: %d", 
                      character_interface_->get_error_message(), 
                      db_type_);
      }
      if (kAllDatabase == db_type_ || kCharacterDatabase == db_type_) { //login
      //init all variable in first(user db)
      character_interface_ = new ODBCInterface();
      memset(host, 0, HOST_LENGTH);
      port = 3306; //default mysql port
      memset(connection_name, 0, DB_CONNECTION_NAME_LENGTH);
      memset(user, 0, DB_USER_NAME_LENGTH);
      memset(password, 0, DB_PASSWORD_LENGTH);
#if defined(_PAP_LOGIN) //this diffrent from login server and share memory
      strncpy(host, g_config.login_info_.db_host_, HOST_LENGTH);
      port = g_config.login_info_.db_port_;
      strncpy(connection_name, g_config.login_info_.db_connection_name_, DB_CONNECTION_NAME_LENGTH);
      strncpy(user, g_config.login_info_.db_user_, DB_USER_NAME_LENGTH);
      strncpy(password, g_config.login_info_.db_password_, DB_PASSWORD_LENGTH);
#elif defined(_PAP_SHARE_MEMORY)
      strncpy(host, g_config.share_memory_info_.db_host_, HOST_LENGTH);
      port = g_config.share_memory_info_.db_port_;
      strncpy(connection_name, g_config.share_memory_info_.db_connection_name_, DB_CONNECTION_NAME_LENGTH);
      strncpy(user, g_config.share_memory_info_.db_user_, DB_USER_NAME_LENGTH);
      strncpy(password, g_config.share_memory_info_.db_password_, DB_PASSWORD_LENGTH);
#endif
      host[HOST_LENGTH - 1] = '\0';
      connection_name[DB_CONNECTION_NAME_LENGTH - 1] = '\0';
      user[DB_USER_NAME_LENGTH - 1] = '\0';
      password[DB_PASSWORD_LENGTH - 1] = '\0';

      Assert(character_interface_); //safe code
      bool connected = character_interface_->connect(connection_name, user, password);
      if (!connected) {
        Log::save_log("dbmanager", 
                      "character_interface_->connect()...get error: %s, db_type: %d", 
                      character_interface_->get_error_message(), 
                      db_type_);
      }
    }

    if (kAllDatabase == db_type_ || kUserDatabase == db_type_) { //billing
      //init all variable in first(character db)
      user_interface_ = new ODBCInterface();
      memset(host, 0, HOST_LENGTH);
      port = 3306; //default mysql port
      memset(connection_name, 0, DB_CONNECTION_NAME_LENGTH);
      memset(user, 0, DB_USER_NAME_LENGTH);
      memset(password, 0, DB_PASSWORD_LENGTH);
      strncpy(host, g_config.billing_info_.db_ip_, HOST_LENGTH);
      port = g_config.billing_info_.db_port_;
      strncpy(connection_name, g_config.billing_info_.db_connection_name_, DB_CONNECTION_NAME_LENGTH);
      strncpy(user, g_config.billing_info_.db_user_, DB_USER_NAME_LENGTH);
      strncpy(password, g_config.billing_info_.db_password_, DB_PASSWORD_LENGTH);
      host[HOST_LENGTH - 1] = '\0';
      connection_name[DB_CONNECTION_NAME_LENGTH - 1] = '\0';
      user[DB_USER_NAME_LENGTH - 1] = '\0';
      password[DB_PASSWORD_LENGTH - 1] = '\0';

      Assert(user_interface_); //safe code
      bool connected = user_interface_->connect(connection_name, user, password);
      if (!connected) {
        Log::save_log("dbmanager", 
                      "user_interface_->connect()...get error: %s, db_type: %d", 
                      user_interface_->get_error_message(), 
                      db_type_);
      }
    }
	return connected;
  __LEAVE_FUNCTION
    return false;
}

ODBCInterface* Manager::get_interface(db_type_enum db_type) {
  __ENTER_FUNCTION
    ODBCInterface* odbc_interface;
    switch(db_type) {
      case kCharacterDatabase: {
        odbc_interface = character_interface_;
        break;
      }
      case kUserDatabase: {
        odbc_interface = user_interface_;
        break;
      }
      default: {
        odbc_interface = NULL;
      }
    }
    return odbc_interface;
  __LEAVE_FUNCTION
}

} //namespace pap_server_common_db
