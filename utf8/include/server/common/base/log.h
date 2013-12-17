/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id log.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-4 16:18:56
 * @uses server log class
 */
#ifndef PAP_SERVER_COMMON_BASE_LOG_H_
#define PAP_SERVER_COMMON_BASE_LOG_H_

#include "common/base/type.h"
#include "common/game/define.h"
#include "common/sys/thread.h"
#include "server/common/base/define.h"

/**
#define LOGIN_LOG "./log/login" //I would not want to use macros, modules do wrong name.
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
**/

typedef enum {
  kLoginLogFile = 0,
  kDebugLogFile = 1,
  kErrorLogFile = 2,
  kShareMemoryLogFile = 3,
  kLogFileCount,
} enum_log_id;

namespace pap_server_common_base {

const char* kBaseLogSaveDir = "./log"; //如果不要外部使用，就别使用宏
const uint32_t kLogBufferTemp = 4096;
const uint32_t kLogNameTemp = 128;
const uint32_t kDefaultLogCacheSize = 1024 * 1024 * 4;

class Log {

 public:
   Log();
   ~Log();

 public:
   static void disk_log(const char* file_name_prefix, const char* format, ...);
   bool init(int32_t cache_size = kDefaultLogCacheSize);
   void fast_save_log(enum_log_id log_id, const char* format, ...); //save in memory
   void flush_log(enum_log_id log_id);
   int32_t get_log_size(enum_log_id log_id);
   void get_log_file_name(enum_log_id log_id, char* file_name);
   static void get_log_file_name(const char* file_name_prefix, char* file_name);
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
