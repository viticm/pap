/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 09:35:51
 * @uses vengine time system module
 */
#ifndef VENGINE_TIME_SYSTEM_H_
#define VENGINE_TIME_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

namespace vengine_time {

class VENGINE_API System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   virtual void init(void*);
   virtual void tick();

 public:
   //取得最近20ms以来每祯平均花费的时间
   float get_looptime() const;
   //取得上一帧花费时间
   float get_lastframe_time() const;
   //根据looptime_取得运行时间
   float get_runtime() const;
   uint32_t get_nowtime() const;
   //获取帧率（FPS）
   float getFPS() const;
   //算时间差,考虑时间阙(49.71天)
   uint32_t get_difftime(uint32_t starttime, uint32_t endtime);
   //获得帧数
   uint32_t get_tickcount();
   //设置服务器时间
   void set_servertime(time_t _time);
   time_t get_servertime();
   
 protected:
   float looptime_;
   float lastframe_time_;
   float runtime_;
   uint32_t nowtime_;
   float FPS_;
   time_t servertime_;
   time_t localtime_;
   uint32_t tickcount_;
    
};

}; //namespace vengine_time

#endif //VENGINE_TIME_SYSTEM_H_
