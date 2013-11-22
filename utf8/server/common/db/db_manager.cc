#include "db_manager.h"

DBManager::DBManager() {
  __ENTER_FUNCTION
    db_type_ = ALL_DATABASE; //init as all database
    character_interface_ = NULL;
    user_interface_ = NULL;
  __LEAVE_FUNCTION
}

DBManager::~DBManager() {
  __ENTER_FUNCTION
    SAFE_DELETE(user_interface_);
    SAFE_DELETE(character_interface_);
  __LEAVE_FUNCTION
}

bool DBManager::init(DB_TYPES db_type) {
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
    }
  __LEAVE_FUNCTION
}
