#ifndef PAP_SERVER_COMMON_BASE_LOG_H_
#define PAP_SERVER_COMMON_BASE_LOG_H_

#include "common/base/type.h"
#include "common/game/define.h"
#include "common/sys/thread.h"
#include "server/common/base/define.h"

#define LOGIN_LOG "./log/login"
#define SERVER_LOG "./log/server"
#define SERVER_ERROR_LOG "./log/error"
#define SERVER_FUNCTION_LOG "./log/function"
#define WORLD_LOG "./log/world"
#define CONFIG_LOG "./log/config"
#define ASSERT_LOG "./log/assert"
#define RECYCLE_LOG "./log/recycle"
#define CRC32_LOG "./log/crc32"
#define SHARE_MEMROY_LOG "./log/share_memory"
#define BILLING_LOG "./log/billing"

typedef enum {
  kLogFile0 = 0,
  kLogFile1 = 1,
  kLogFile2 = 2,
  kLogFileCount,
} enum_log_id;

namespace pap_server_common_base {

#define LOG_BUFF_TEMP 4096
#define LOG_NAME_TEMP 128
#define DEFAULT_LOG_CACHE_SIZE (1024*1024*4)

class Log {

 public:
   Log();
   ~Log();

 public:
   static void disk_log(const char* file_name_prefix, const char* format, ...);
   bool init(int32_t cache_size = DEFAULT_LOG_CACHE_SIZE);
   void fast_save_log(enum_log_id log_id, const char* format, ...); //save in memory
   void fast_log(enum_log_id log_id);
   int32_t get_log_size(enum_log_id log_id);
   void get_log_file_name(enum_log_id log_id, char* file_name);
   void get_log_file_name(const char* file_name_prefix, char* file_name);
   void flush_all_log();
   static void get_serial(char* serial, int16_t world_id, int16_t server_id);
   static void save_log(const char* file_name_prefix, const char* format, ...);
   static void remove_log(const char* file_name);
   static void get_log_time_str(char* time_str, int32_t length);

 private:
   char* log_cache_[kLogFileCount];
   int32_t log_position_[kLogFileCount];
   pap_common_sys::ThreadLock log_lock_[kLogFileCount];
   int32_t cache_size_;
   uint32_t day_time_;

};

#if defined(__LINUX__)
#define SaveErrorLog();(pap_server_common_base::Log::SaveLog(SERVER_ERRORFILE_PREFIX, "%s %d %s", __FILE__, __LINE__, __PRETTY_FUNCTION__))
#elif defined(__WINDOWS__)
#define SaveErrorLog();(pap_server_common_base::Log::SaveLog(SERVER_ERRORFILE_PREFIX, "%s %d %s", __FILE__, __LINE__, __FUNCTION__))
#endif

}; //namespace pap_server_common_base

extern pap_server_common_base::Log* g_log;

#endif //PAP_SERVER_COMMON_BASE_LOG_H_
