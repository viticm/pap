/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id info.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-23 10:27:23
 * @uses system info namespace, can get system some info just like cpu or memory(use some JianYi code)
 *       use the code url: http://code.google.com/p/mooon/source/browse/trunk/common_library/include/sys
 *       (thanks eyjian@gmail.com)
 */
#ifndef PAP_COMMON_SYS_INFO_H_
#define PAP_COMMON_SYS_INFO_H_

#include <sys/config.h>
#include <stdint.h>
#include <vector>
#include "common/base/type.h"
namespace pap_common_sys {

namespace info {

//current system info
typedef struct {
  int64_t uptime_second; //Seconds since boot
  uint64_t average_load[3]; //1, 5, and 15 minute load averages
  uint64_t ram_total; //Total usable main memory size
  uint64_t ram_free; //Available memory size
  uint64_t ram_shared; //Amount of shared memory
  uint64_t ram_buffer; //Memory used by buffers
  uint64_t swap_total; //Total swap space size
  uint64_t swap_free; //swap space still available
  ushort process_number; //Number of current processes
} sys_info_t;

//current process info
typedef struct {
  int64_t user_time; //user time
  int64_t system_time; //system time
  int64_t user_time_child; 
  int64_t system_time_child;
} process_info_t;

//current cpu info
typedef struct {
  //单位: jiffies, 1jiffies=0.01秒,下面的时间都是从系统启动开始累计到当前时刻
  uint64_t total; 
  uint32_t user; //处于用户态的运行时间，不包含 nice值为负进程
  uint32_t nice; //nice值为负的进程所占用的CPU时间
  uint32_t system; //处于核心态的运行时间
  uint32_t idle; //除IO等待时间以外的其它等待时间
  uint32_t iowait; //IO等待时间(2.5.41)
  uint32_t irq; //硬中断时间(2.6.0)
  uint32_t softirq;//软中断时间(2.6.0)
  uint ;
} cpu_info_t;

bool get_sys_info();

} //namespace info

} //namespace pap_common_sys

#endif //PAP_COMMON_SYS_INFO_H_
