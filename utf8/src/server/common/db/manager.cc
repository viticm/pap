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
    bool connected = false;
    db_type_ = db_type;
    char host[HOST_LENGTH];
    uint16_t port;
    char connection_name[DB_CONNECTION_NAME_LENGTH];
    char user[DB_USER_NAME_LENGTH];
    char password[DB_PASSWORD_LENGTH]; //this password is use in mysql, 
                                       //not encrypt password
    if (kAllDatabase == db_type_ || kCharacterDatabase == db_type_) {
      //init all variable in first(character db)
      character_interface_ = new ODBCInterface();
      memset(host, 0, sizeof(host));
      port = 3306; //default mysql port
      memset(connection_name, 0, sizeof(connection_name));
      memset(user, 0, sizeof(user));
      memset(password, 0, sizeof(password));
#if defined(_PAP_LOGIN) //this diffrent from login server and share memory
      strncpy(host, 
              g_config.login_info_.db_ip, 
              sizeof(g_config.login_info_.db_ip) - 1);
      port = g_config.login_info_.db_port;
      strncpy(connection_name, 
              g_config.login_info_.db_connection_name, 
              sizeof(g_config.login_info_.db_connection_name) - 1);
      strncpy(user, 
              g_config.login_info_.db_user, 
              sizeof(g_config.login_info_.db_user));
      strncpy(password, 
              g_config.login_info_.db_password, 
              sizeof(g_config.login_info_.db_password) - 1);
#elif defined(_PAP_SHAREMEMORY)
      strncpy(host, 
              g_config.share_memory_info_.db_ip, 
              sizeof(g_config.share_memory_info_.db_ip) - 1);
      port = g_config.share_memory_info_.db_port;
      strncpy(connection_name, 
              g_config.share_memory_info_.db_connection_name, 
              sizeof(g_config.share_memory_info_.db_connection_name) - 1);
      strncpy(user, 
              g_config.share_memory_info_.db_user, 
              sizeof(g_config.share_memory_info_.db_user) - 1);
      strncpy(password, 
              g_config.share_memory_info_.db_password, 
              sizeof(g_config.share_memory_info_.db_password) - 1);
#endif

      Assert(character_interface_); //safe code
      connected = character_interface_->connect(connection_name, 
                                                user, 
                                                password);
      if (!connected) {
        Log::save_log(
            "dbmanager", 
            "character_interface_->connect()...get error: %s, db_type: %d", 
            character_interface_->get_error_message(), 
            db_type_);
      }
    }
    if (kAllDatabase == db_type_ || kUserDatabase == db_type_) {
      //init all variable in first(user db)
      user_interface_ = new ODBCInterface();
      memset(host, 0, HOST_LENGTH);
      port = 3306; //default mysql port
      memset(connection_name, 0, sizeof(connection_name));
      memset(user, 0, sizeof(user));
      memset(password, 0, sizeof(password));
#if defined(_PAP_BILLING)
      strncpy(host, 
              g_config.billing_info_.db_ip_, 
              sizeof(g_config.billing_info_.db_ip_) - 1);
      port = g_config.billing_info_.db_port_;
      strncpy(connection_name, 
              g_config.billing_info_.db_connection_name_, 
              sizeof(g_config.billing_info_.db_connection_name_) - 1);
      strncpy(user, 
              g_config.billing_info_.db_user_, 
              sizeof(g_config.billing_info_.db_user_) - 1);
      strncpy(password, 
              g_config.billing_info_.db_password, 
              sizeof(g_config.billing_info_.db_password) - 1);
#endif

      Assert(user_interface_); //safe code
      connected = user_interface_->connect(connection_name, user, password);
      if (!connected) {
        Log::save_log(
            "dbmanager", 
            "character_interface_->connect()...get error: %s, db_type: %d", 
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
    return NULL;
}

} //namespace pap_server_common_db
