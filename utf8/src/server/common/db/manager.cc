#include "server/common/db/manager.h"

namespace pap_server_common_db {

g_db_manager = NULL;

Manager::Manager() {
  __ENTER_FUNCTION
    db_type_ = ALL_DATABASE; //init as all database
    character_interface_ = NULL;
    user_interface_ = NULL;
  __LEAVE_FUNCTION
}

Manager::~DBManager() {
  __ENTER_FUNCTION
    SAFE_DELETE(user_interface_);
    SAFE_DELETE(character_interface_);
  __LEAVE_FUNCTION
}

bool Manager::init(DB_TYPES db_type) {
  __ENTER_FUNCTION
    db_type_ = db_type;
    char host[HOST_LENGTH];
    uint port;
    char connection_name[DB_CONNECTION_NAME_LENGTH];
    char user[DB_USER_NAME_LENGTH];
    char password[DB_PASSWORD_LENGTH]; //this password is use in mysql, not encrypt password
    if (ALL_DATABASE == db_type || CHARACTER_DATABASE == db_type) {
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
        Log::save_log(DB_LOG_FILE, 
                      "character_interface_->connect()...get error: %s, DB_TYPE: %d", 
                      character_interface_->get_error_message(), 
                      db_type);
      }
      if (ALL_DATABASE == db_type || CHARACTER_DATABASE == db_type) {
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
        Log::save_log(DB_LOG_FILE, 
                      "character_interface_->connect()...get error: %s, DB_TYPE: %d", 
                      character_interface_->get_error_message(), 
                      db_type);
      }
    }

    if (ALL_DATABASE == db_type || CHARACTER_DATABASE == db_type) {
      //init all variable in first(character db)
      user_interface_ = new ODBCInterface();
      memset(host, 0, HOST_LENGTH);
      port = 3306; //default mysql port
      memset(connection_name, 0, DB_CONNECTION_NAME_LENGTH);
      memset(user, 0, DB_USER_NAME_LENGTH);
      memset(password, 0, DB_PASSWORD_LENGTH);
      strncpy(host, g_config.login_info_.db_host_, HOST_LENGTH);
      port = g_config.login_info_.db_port_;
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
        Log::save_log(DB_LOG_FILE, 
                      "user_interface_->connect()...get error: %s, DB_TYPE: %d", 
                      user_interface_->get_error_message(), 
                      db_type);
      }
    }
  __LEAVE_FUNCTION
}

ODBCInterface* Manager::get_interface(DB_TYPES db_type) {
  __ENTER_FUNCTION
    ODBCInterface* odbc_interface;
    switch(db_type) {
      case CHARACTER_DATABASE: {
        odbc_interface = character_interface_;
        break;
      }
      case USER_DATABASE: {
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
