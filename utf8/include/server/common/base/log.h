#ifndef PAP_SERVER_COMMON_BASE_LOG_H_
#define PAP_SERVER_COMMON_BASE_LOG_H_

#include "common/game/define.h"
#include "common/sys/thread.h"

#define LOGIN_LOGFILE_PREFIX "./log/login"
#define SERVER_LOGFILE_PREFIX "./log/server"
#define SERVER_LOGERRORFILE_PREFIX "./log/error"
#define SERVER_FUNCTIONFILE_PREFIX "./log/function"
#define WORLD_LOGFILE_PREFIX "./log/world"
#define CONFIG_LOGFILE_PREFIX "./log/config"
#define ASSERT_LOGFILE_PREFIX "./log/assert"
#define RECYCLE_LOGFILE_PREFIX "./log/recycle"
#define CRC32_LOGFILE_PREFIX "./log/crc32"
#define SHAREMEMROY_LOGFILE_PREFIX "./log/share_memory"
#define BILLING_LOGFILE_PREFIX "./log/billing"
#define DEFAULT_LOG_CACHE_SIZE (1024*1024*4)
#define LOG_BUFF_TEMP 4096
#define LOG_NAME_TEMP 128

typedef enum {
  kLogFile0 = 0,
  kLogFile1 = 1,
  kLogFile2 = 2,
  kLogFileCount,
} enum_log_id;

namespace pap_server_common_base {

class Log {

 public:
   Log();
   ~Log();

 public:
   static void disk_log(const char* file_name, const char* format, ...);
   bool init(cache_size = DEFAULT_LOG_CACHE_SIZE);
   void fast_save_log(enum_log_id log_id, const char* format, ...); //save in memory
   void fast_log(enum_log_id log_id);
   int32_t get_log_size(enum_log_id log_id);
   void get_log_name(enum_log_id log_id, char* name);
   void flush_all_log();

 private:
   char* log_cache_[kLogFileCount];
   int32_t log_position[kLogFileCount];
   pap_common_sys::ThreadLock log_lock_[kLogFileCount];
   int32_t cache_size_;
   uint32_t day_time_;

};

#if defined(__LINUX__)
#define SaveErrorLog();(Log::SaveLog(SERVER_ERRORFILE_PREFIX, "%s %d %s", __FILE__, __LINE__, __PRETTY_FUNCTION__))
#elif defined(__WINDOWS__)
#define SaveErrorLog();(Log::SaveLog(SERVER_ERRORFILE_PREFIX, "%s %d %s", __FILE__, __LINE__, __FUNCTION__))
#endif

}; //namespace pap_server_common_base

#endif //PAP_SERVER_COMMON_BASE_LOG_H_
