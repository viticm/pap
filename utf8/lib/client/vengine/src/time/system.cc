#include "vengine/capability/profile.h"
#include "vengine/time/system.h"

namespace vengine_time {

//保存所使用时间函数指针,防止用户使用简单的变速齿轮更改系统速度
typedef DWORD (__stdcall *function_gettime)();
static function_gettime g_gettime_pointer = ::timeGetTime;

//节点部分实现
VENGINE_KERNEL_IMPLEMENT_DYNAMIC(
    vengine_time::System, 
    VENGINE_KERNEL_GETCLASS(vengine_kernel::Node, vengine_kernel_Node),
    vengine_time_System);

void System::init(void*) {
  looptime_ = .0f;
  lastframe_time_ = .0f;
  runtime_ = .0f;
  nowtime_ = (*g_gettime_pointer)();
  FPS_ = .0f;
  servertime_ = 0;
  localtime_ = 0;
}

uint32_t System::get_difftime(uint32_t starttime, uint32_t endtime) {
  if (endtime < starttime) {
    return (static_cast<uint32_t>(0XFFFFFFFF) - starttime) + endtime;
  }
  else {
    return endtime - starttime;
  }
}

void System::tick() {
  static uint32_t last_ticktime = 0;
  ++tickcount_; //total tick count
  //save now time
  nowtime_ = (*g_gettime_pointer)();
  //记录距上一桢所花费的时间， 考虑跨时间阙的问题(49.71天)
  uint32_t difftime = get_difftime(last_ticktime, nowtime_);
  lastframe_time_ = static_cast<float>(difftime);
  //计算每帧平均花费时间，20ms计算一次
  const uint32_t kCalculateLoopTime = 20;
  static uint32_t loopcount = 0; //帧计算累计数
  static uint32_t looptime = 0; //时间累计数
  ++loopcount;
  looptime += difftime;
  if (looptime > kCalculateLoopTime) {
    looptime_ = (looptime / static_cast<float>(loopcount)) / 1000.0f;
    loopcount = 0;
    looptime = 0;
  }
  //计算帧率
  const uint32_t kCalculateFPS = 1000; //每一秒计算一次
  ++loopcount;
  looptime += difftime;
  if (looptime > kCalculateFPS) {
    FPS_ = static_cast<float>((loopcount * 1000) / looptime);
    loopcount = 0;
    looptime = 0;
  }
  last_ticktime = nowtime_;
  runtime_ += looptime_;
  //请求查询
  vengine_capability::profile::tick();
}

void System::set_servertime(time_t _time) {
  servertime_ = _time;
  time(&localtime_);
}

time_t System::get_servertime() {
  if (servertime_ < 0) return 0;
  time_t currenttime;
  time(&currenttime);
  return servertime_ + currenttime - localtime_;
}

uint32_t System::get_nowtime() const {
  return nowtime_;
}

float System::get_lastframe_time() const {
  return lastframe_time_;
}

uint32_t System::get_tickcount() const {
  return tickcount_;
}

} //namespace vengine_time
