/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id time_manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-6 16:28:57
 * @uses the server base time manager class
 */
#ifndef PAP_SERVER_COMMON_BASE_TIME_MANAGER_H_
#define PAP_SERVER_COMMON_BASE_TIME_MANAGER_H_

#if defined(__LINUX__)
#include <sys/time.h>
#include <sys/utsname.h>
#endif
#include "common/game/define.h"
#include "common/base/type.h"

namespace pap_server_common_base {

class TimeManager {

 public:
   TimeManager();
   ~TimeManager();
   uint32_t start_time_;
   uint32_t current_time_;
   time_t set_time_;
   tm tm_;
   world_time_enum world_time_;
#if defined(__LINUX__)
   struct timeval start_, end_;
   struct timezone time_zone_;
#endif

 public:
   bool init();
   uint32_t get_current_time();
   uint32_t get_saved_time();
   uint32_t get_start_time();
   void reset_time();
   time_t get_ansi_time(); //standard
   tm get_tm();

 public:
   void get_full_format_time(char* format_time, uint32_t length); //2013-11-29 15:38:09
   uint16_t get_year();
   uint8_t get_month();
   uint8_t get_day();
   uint8_t get_hour();
   uint8_t get_minute();
   uint8_t get_second();
   uint8_t get_week();
   uint32_t tm_todword();
   void dword_totm(uint32_t time, tm* _tm);
   uint32_t diff_dword_time(uint32_t time1, uint32_t time2);
   int32_t diff_day_count(time_t ansi_time1, time_t ansi_time2);
   uint32_t get_day_time(); //20131129
   uint32_t get_current_date();
   uint32_t get_run_time();
   uint32_t diff_time(uint32_t time1, uint32_t time2); //两个时间的差值，毫秒
   void time_totm(uint32_t time, tm* _tm);
   void tm_totime(tm* _tm, uint32_t &time);
   uint32_t get_days(); //取得以天为单位的时间值, 千位数代表年份，其他三位代表时间（天数）
   uint32_t get_hours(); //12723表示本年度第127天的5(23/4)点的第3(23%4)刻钟时间
   uint32_t get_weeks(); //取得以周为单位的时间值, 千位数代表年份，其他三位代表时间（周数）
   world_time_enum get_world_time();
   void set_world_time(world_time_enum world_time);

};

}; //namespace pap_server_common_base

extern pap_server_common_base::TimeManager* g_time_manager;
extern uint32_t g_file_name_fix_last;
extern int32_t g_file_name_fix;

#endif //PAP_SERVER_COMMON_BASE_TIME_MANAGER_H_
