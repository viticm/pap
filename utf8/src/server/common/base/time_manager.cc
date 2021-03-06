#include "server/common/base/time_manager.h"

pap_server_common_base::TimeManager* g_time_manager = NULL;
int32_t g_file_name_fix = 0;
uint32_t g_file_name_fix_last = 0;

namespace pap_server_common_base {

TimeManager::TimeManager() {
  __ENTER_FUNCTION
    current_time_ = 0;
  __LEAVE_FUNCTION
}

TimeManager::~TimeManager() {
  //do nothing
}

bool TimeManager::init() {
  __ENTER_FUNCTION
#if defined(__WINDOWS__)
    start_time_ = GetTickCount();
    current_time_ = GetTickCount();
#elif defined(__LINUX__)
    start_time_ = 0;
    current_time_ = 0;
    gettimeofday(&start_, &time_zone_);
#endif
    reset_time();
    g_file_name_fix = get_day_time();
    g_file_name_fix_last = get_current_time();
    return true;
  __LEAVE_FUNCTION
    return false;
}

uint32_t TimeManager::get_current_time() {
  __ENTER_FUNCTION
#if defined(__WINDOWS__)
    current_time_ = GetTickCount();
#elif defined(__LINUX__)
    gettimeofday(&end_, &time_zone_);
    double time1 = static_cast<double>(start_.tv_sec * 1000) +
                   static_cast<double>(start_.tv_usec / 1000);
    double time2 = static_cast<double>(end_.tv_sec * 1000) +
                   static_cast<double>(end_.tv_usec / 1000);
    current_time_ = static_cast<uint32_t>(time2 - time1);
#endif
    return current_time_;
  __LEAVE_FUNCTION
    return 0;
}

uint32_t TimeManager::get_current_date() {
  __ENTER_FUNCTION
    reset_time();
    uint32_t time;
    tm _tm;
    tm_totime(&_tm, time);
    return time;
  __LEAVE_FUNCTION
    return 0;
}

void TimeManager::reset_time() {
  __ENTER_FUNCTION
    time(&set_time_);
    tm* _tm = localtime(&set_time_);
    tm_ = *_tm;
  __LEAVE_FUNCTION
}

time_t TimeManager::get_ansi_time() {
  __ENTER_FUNCTION
    reset_time();
    return set_time_;
  __LEAVE_FUNCTION
    return set_time_;
}

void TimeManager::get_full_format_time(char* format_time, uint32_t length) {
  __ENTER_FUNCTION
    reset_time();
    strftime(format_time, length, "%Y-%m-%d %H:%M:%S", &tm_);
  __LEAVE_FUNCTION
}

uint16_t TimeManager::get_year() {
  __ENTER_FUNCTION
    return static_cast<uint16_t>(tm_.tm_year + 1900);
  __LEAVE_FUNCTION
    return 0;
}

uint8_t TimeManager::get_month() {
  __ENTER_FUNCTION
    return static_cast<uint8_t>(tm_.tm_mon);
  __LEAVE_FUNCTION
    return 0;
}

uint8_t TimeManager::get_day() {
  __ENTER_FUNCTION
    return static_cast<uint8_t>(tm_.tm_mday);
  __LEAVE_FUNCTION
    return 0;
}

uint8_t TimeManager::get_hour() {
  __ENTER_FUNCTION
    return static_cast<uint8_t>(tm_.tm_hour);
  __LEAVE_FUNCTION
    return 0;
}

uint8_t TimeManager::get_minute() {
  __ENTER_FUNCTION
    return static_cast<uint8_t>(tm_.tm_min);
  __LEAVE_FUNCTION
    return 0;
}

uint8_t TimeManager::get_second() {
  __ENTER_FUNCTION
    return static_cast<uint8_t>(tm_.tm_sec);
  __LEAVE_FUNCTION
    return 0;
}

uint8_t TimeManager::get_week() {
  __ENTER_FUNCTION
    return static_cast<uint8_t>(tm_.tm_wday);
  __LEAVE_FUNCTION
    return 0;
}

uint32_t TimeManager::tm_todword() {
  __ENTER_FUNCTION
    reset_time();
    uint32_t result = 0;
    result += get_year();
    result -= 2000;
    result *= 100;
    result += get_month() + 1;
    result *= 100;
    result += get_day();
    result = result * 100;
    result += get_hour();
    result *= 100;
    result += get_minute();
    return result;
  __LEAVE_FUNCTION
    return 0;
}

void TimeManager::dword_totm(uint32_t time, tm* _tm) {
  __ENTER_FUNCTION
    Assert(_tm);
    memset(_tm, 0 , sizeof(_tm));
    _tm->tm_year = (time / 100000000) + 2000 - 1900;
    _tm->tm_mon = (time % 100000000) / 1000000 - 1;
    _tm->tm_mday = (time % 1000000) / 10000;
    _tm->tm_min  = time % 100;
  __LEAVE_FUNCTION
}

uint32_t TimeManager::diff_dword_time(uint32_t time1, uint32_t time2) {
  __ENTER_FUNCTION
    tm _tm1, _tm2;
    dword_totm(time1, &_tm1);
    dword_totm(time2, &_tm2);
    time_t _time1, _time2;
    _time1 = mktime(&_tm1);
    _time2 = mktime(&_tm2);
    uint32_t result = static_cast<uint32_t>((abs(static_cast<int32_t>(difftime(_time2,_time1) / 60))));
    return result;
  __LEAVE_FUNCTION
    return 0;
}

int32_t TimeManager::diff_day_count(time_t ansi_time1, time_t ansi_time2) {
  __ENTER_FUNCTION
    int32_t result = static_cast<int32_t>(difftime(ansi_time1,ansi_time2) / (24 * 60 * 60));
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint32_t TimeManager::get_day_time() {
  __ENTER_FUNCTION
    uint32_t result = 0;
    result += get_year();
    result *= 100;
    result += get_month();
    result *= 100;
    result += get_day();
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint32_t TimeManager::get_run_time() {
  __ENTER_FUNCTION
    get_current_time();
    uint32_t result = current_time_ - start_time_;
    return result;
  __LEAVE_FUNCTION
    return 0;
}

void TimeManager::time_totm(uint32_t time, tm* _tm) {
  __ENTER_FUNCTION
    Assert(_tm);
    memset(_tm, 0, sizeof(_tm));
    _tm->tm_year = ((time >> 26) & 0xf) + 100;
    _tm->tm_mon  = (time >> 22) & 0xf;
    _tm->tm_mday = (time >> 17) & 0x1f;
    _tm->tm_hour = (time >> 12) & 0x1f;
    _tm->tm_min  = (time >> 6) & 0x3f;
    _tm->tm_sec  = time & 0x3f;
  __LEAVE_FUNCTION
}

void TimeManager::tm_totime(tm* _tm, uint32_t &time) {
  __ENTER_FUNCTION
    Assert(_tm);
    time = 0;
    time += (_tm->tm_year % 10) & 0xf;
    time = time << 4;
    time += _tm->tm_mon & 0xf;
    time = time << 5;
    time += _tm->tm_mday & 0x1f;
    time = time << 5;
    time += _tm->tm_hour & 0x1f;
    time = time << 6;
    time += _tm->tm_min & 0x3f;
    time = time << 6;
    time += _tm->tm_sec & 0x3f;
  __LEAVE_FUNCTION
}

uint32_t TimeManager::diff_time(uint32_t time1, uint32_t time2) {
  __ENTER_FUNCTION
    tm _tm1, _tm2;
    time_totm(time1, &_tm1);
    time_totm(time2, &_tm2);
    time_t timefirst = 0, timeNext = 0;
    uint32_t result = static_cast<uint32_t>(
        abs(static_cast<int32_t>(
        difftime(timefirst, timeNext))) * 1000);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint32_t TimeManager::get_days() {
  __ENTER_FUNCTION
    uint32_t result = 0;
    time_t _time_t;
    time(&_time_t);
    tm* _tm = localtime(&set_time_);
    result = (_tm->tm_year - 100) * 1000;
    result += _tm->tm_yday;
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint32_t TimeManager::get_hours() {
  __ENTER_FUNCTION
    uint32_t result = 0;
    time_t _time_t;
    time(&_time_t);
    tm* _tm = localtime(&set_time_);
    if (2008 == _tm->tm_year + 1900) {
      result = 365;
    }
    result += _tm->tm_yday;
    result *= 100;
    result += _tm->tm_hour * 4;
    result += static_cast<uint32_t>(_tm->tm_min / 15);
    return result;
  __LEAVE_FUNCTION
    return 0;
}

uint32_t TimeManager::get_weeks() {
  __ENTER_FUNCTION
    uint32_t result = 0;
    time_t _time_t;
    time(&_time_t);
    tm* _tm = localtime(&set_time_);
    result  = (_tm->tm_year - 100) * 1000;
    if (_tm->tm_yday <= _tm->tm_wday) return result;
    int32_t diff = _tm->tm_yday - _tm->tm_wday;
    result += static_cast<uint32_t>(ceil(static_cast<double>(diff / 7)));
    return result;
  __LEAVE_FUNCTION
    return 0;
}

world_time_enum TimeManager::get_world_time() {
  return world_time_;
}

void TimeManager::set_world_time(world_time_enum world_time) {
  __ENTER_FUNCTION
    world_time_ = world_time;
  __LEAVE_FUNCTION
}

} //namespace pap_server_common_base
