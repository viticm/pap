#include <stdarg.h>
#include "server/common/base/log.h"
#include "server/common/base/time_manager.h"

pap_server_common_base::Log* g_log = NULL;

namespace pap_server_common_base {

bool g_command_log_print = true;
bool g_command_log_active = true;
const char* kBaseXLogSaveDir = "./log";

const char* g_log_file_name[] = {
  "./log/login", //kLoginLogFile
  "./log/debug", //kDebugLogFile
  "./log/error", //kErrorLogFile
  "./log/share_memory",
  '\0',
};

pap_common_sys::ThreadLock g_log_lock;
bool g_log_in_one_file = false;


Log::Log() {
  __ENTER_FUNCTION
    int32_t i;
    for (i = 0; i < kLogFileCount; ++i) {
      log_cache_[i] = NULL;
      log_position_[i] = 0;
    }
    cache_size_ = 0;
    day_time_ = 0;
  __LEAVE_FUNCTION
}

Log::~Log() {
  __ENTER_FUNCTION
    int32_t i;
    for (i = 0; i < kLogFileCount; ++i) {
      SAFE_DELETE_ARRAY(log_cache_[i]);
    }
    cache_size_ = 0;
  __LEAVE_FUNCTION
}

void Log::get_log_time_str(char* time_str, int32_t length) {
  __ENTER_FUNCTION
    if (g_time_manager) {
        g_time_manager->reset_time();
        snprintf(time_str, length, 
                 " (%"PRIu64")(T0=%d-%d-%d_%d:%d:%d T1=%.4f)",
                 pap_common_sys::get_current_thread_id(), 
                 g_time_manager->get_year(),
                 g_time_manager->get_month() + 1,
                 g_time_manager->get_day(),
                 g_time_manager->get_hour(),
                 g_time_manager->get_minute(),
                 g_time_manager->get_second(),
                 static_cast<float>(g_time_manager->get_run_time())/1000.0);
    }
  __LEAVE_FUNCTION
}

void Log::disk_log(const char* file_name_prefix, const char* format, ...) {
  __ENTER_FUNCTION
    if (g_command_log_active != true) return;
    if (NULL == file_name_prefix || 0 == file_name_prefix[0]) return;
    char buffer[kLogBufferTemp];
    memset(buffer, '\0', sizeof(buffer));
    va_list argptr;
    try {
      va_start(argptr, format);
	    vsnprintf(buffer, 
                sizeof(kLogBufferTemp) - kLogNameTemp - 1, 
                format, 
                argptr);
      va_end(argptr);
      if (g_time_manager) {
        char time_str[kLogNameTemp] ;
				memset(time_str, '\0', sizeof(time_str));
        get_log_time_str(time_str, sizeof(time_str) - 1);        
        strncat(buffer, time_str, strlen(time_str));
      }
	  strncat(buffer, LF, sizeof(LF)); //add wrap
    }
		catch(...) {
      if (g_command_log_print) printf("ERROR: SaveLog unknown error!%s", LF); 
      return;
    }

    char log_file_name[FILENAME_MAX] ;
    try {
      memset(log_file_name, '\0', sizeof(log_file_name));
      snprintf(log_file_name, sizeof(log_file_name) - 1, "%s_%.4d-%.2d-%.2d.%u.log", 
               file_name_prefix, 
               g_file_name_fix / 10000,
               (g_file_name_fix % 10000) / 100,
               g_file_name_fix % 100,
               g_file_name_fix_last);
    } catch(...) {
    }
    
    g_log_lock.lock();
		
    try {
      FILE* fp = fopen(log_file_name, "a+");
      if (fp) {
        try {
          fwrite(buffer, 1, strlen(buffer), fp );
        }
        catch(...) {
        }
        fclose(fp);
      }
    }
    catch(...) {
    }
		
    g_log_lock.unlock();
    
    if (true == g_command_log_print) {
      printf("%s", buffer);
    }
  __LEAVE_FUNCTION
}


bool Log::init(int32_t cache_size) {
  __ENTER_FUNCTION
    cache_size_ = cache_size;
    int32_t i;
    for (i = 0; i < kLogFileCount; ++i) {
      log_cache_[i] = new char[cache_size_];
      if (NULL == log_cache_[i]) { //local memory is failed
        return false;
      }
      log_position_[i] = 0;
    }
    day_time_ = g_time_manager ? g_time_manager->get_day_time() : 6000;
    return true;
  __LEAVE_FUNCTION
    return false;
}

void Log::fast_save_log(enum_log_id log_id, const char* format, ...) {
  __ENTER_FUNCTION
    if (log_id < 0 || log_id >= kLogFileCount) return;
    char buffer[2049];
    va_list argptr;
    try {
      va_start(argptr, format);
      vsnprintf(buffer, sizeof(buffer) - 1, format, argptr);
      va_end(argptr);
      if (g_time_manager) {
        char time_str[256];
        memset(time_str, '\0', sizeof(time_str));
        get_log_time_str(time_str, sizeof(time_str) - 1);
        strncat(buffer, time_str, strlen(time_str));
      }
	  strncat(buffer, LF, sizeof(LF)); //add wrap
    }
    catch(...) {
      Assert(false);
      return;
    }
    int32_t length = static_cast<int32_t>(strlen(buffer));
    if (length <= 0) return;
    if (g_log_in_one_file) {
      //do nothing(one log file is not active in pap)
    }
    log_lock_[log_id].lock();
    try {
      memcpy(log_cache_[log_id] + log_position_[log_id], buffer, length);
      printf(buffer);
    }
    catch(...) {
      //do nogthing
    }
    log_position_[log_id] += length;
    log_lock_[log_id].unlock();
    if (log_position_[log_id] > 
        static_cast<int32_t>((kDefaultLogCacheSize * 2) / 3)) {
      flush_log(log_id);
    }
  __LEAVE_FUNCTION
}

void Log::get_log_file_name(enum_log_id log_id, char* file_name) {
  __ENTER_FUNCTION
    if (g_time_manager) {
      snprintf(file_name,
               FILENAME_MAX - 1,
               "%s_%d_%d_%d.log",
               g_log_file_name[log_id],
               g_time_manager->get_year(),
               g_time_manager->get_month(),
               g_time_manager->get_day());
    }
    else {
      snprintf(file_name,
               FILENAME_MAX - 1,
               "%s_%d.log",
               g_log_file_name[log_id],
               day_time_);
    }
  __LEAVE_FUNCTION
}

void Log::get_log_file_name(const char* file_name_prefix, char* file_name) { 
//remember the file_name_prefix is model name
  __ENTER_FUNCTION
     if (g_time_manager) {
      snprintf(file_name,
               FILENAME_MAX - 1,
               "%s/%s_%d_%d_%d.log", //structure BASE_SAVE_LOG_DIR/logfilename.log
               kBaseXLogSaveDir,
               file_name_prefix,
               g_time_manager->get_year(),
               g_time_manager->get_month(),
               g_time_manager->get_day());
    }
    else {
      snprintf(file_name,
               FILENAME_MAX - 1,
               "%s_%d.log",
               file_name_prefix,
               999999);
    }
   
  __LEAVE_FUNCTION
}

void Log::flush_log(enum_log_id log_id) {
  __ENTER_FUNCTION
    char log_file_name[FILENAME_MAX];
    memset(log_file_name, '\0', sizeof(log_file_name));
    get_log_file_name(log_id, log_file_name);
    log_lock_[log_id].lock();
    try {
      FILE* fp;
      fp = fopen(log_file_name, "ab");
      if (fp) {
        fwrite(log_cache_[log_id], 1, log_position_[log_id], fp);
        fclose(fp);
      }
    }
    catch(...) {
      //do nothing
    }
    log_lock_[log_id].unlock();
  __LEAVE_FUNCTION
}

void Log::flush_all_log() {
  __ENTER_FUNCTION
    int32_t i;
    for (i = 0; i < kLogFileCount; ++i) {
	  enum_log_id log_id = static_cast<enum_log_id>(i);
      flush_log(log_id);
    }
  __LEAVE_FUNCTION
}

void Log::save_log(const char* file_name_prefix, const char* format, ...) {
  __ENTER_FUNCTION
    g_log_lock.lock();
    char buffer[2049];
    memset(buffer, '\0', sizeof(buffer));
    va_list argptr;
    try {
      va_start(argptr, format);
      vsnprintf(buffer, sizeof(buffer) - 1, format, argptr);
      va_end(argptr);
      if (g_time_manager) {
        char time_str[256];
        memset(time_str, '\0', sizeof(time_str));
        get_log_time_str(time_str, sizeof(time_str) - 1);
        strncat(buffer, time_str, strlen(time_str));
      }
	  strncat(buffer, LF, sizeof(LF)); //add wrap
      char log_file_name[FILENAME_MAX];
      memset(log_file_name, '\0', sizeof(log_file_name));
      get_log_file_name(file_name_prefix, log_file_name);
      FILE* fp;
      fp = fopen(log_file_name, "ab");
      if (fp) {
        fwrite(buffer, 1, strlen(buffer), fp);
		
        fclose(fp);
      }
      printf(buffer);
    }
    catch(...) {
      printf("some log error here%s", LF);
    }
    g_log_lock.unlock();
  __LEAVE_FUNCTION
}

void Log::remove_log(const char* file_name) {
  __ENTER_FUNCTION
    g_log_lock.lock();
    FILE* fp;
    fp = fopen(file_name, "w");
    if (fp) fclose(fp);
    g_log_lock.unlock();
  __LEAVE_FUNCTION
}

void Log::get_serial(char* serial, int16_t world_id, int16_t server_id) {
  __ENTER_FUNCTION
    USE_PARAM(world_id);
    USE_PARAM(server_id);
	USE_PARAM(serial);
    //int32_t step = 100;
  __LEAVE_FUNCTION
}


} //namespace pap_server_common_base
