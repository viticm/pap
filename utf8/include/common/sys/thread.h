/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id thread.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-23 10:27:23
 * @uses system about thread classes
 */
#ifndef PAP_COMMON_THREAD_H_
#define PAP_COMMON_THREAD_H_

#include "common/base/type.h"

namespace pap_common_sys {

class Thread {
 public:
   typedef enum { //线程的四种状态 (准备、运行中、退出中、已退出)
     kReady,
     kRunning,
     kExiting,
     kExit,
   }enum_thread_status;

 public:
   Thread();
   virtual ~Thread();
   void start();
   virtual void stop();
   void exit(void* retval = NULL);
   virtual void run();
   int64_t get_id();
   enum_thread_status get_status();
   void set_status(enum_thread_status status);

 private:
   int64_t id_;
   enum_thread_status status_;
#if defined(__WINDOWS__)
   HANDLE thread_handle_;
#endif

};

extern g_quit_thread_count;
#if defined(__LINUX__)
void* pap_thread_process(void* derived_thread);
#elif defined(__WINDOWS__)
DWORD WINAPI pap_thread_process(void* derived_thread);
#endif

class ThreadLock {
 public:
#if defined(__LINUX__)
   pthread_mutex_t mutex_;
#elif defined(__WINDOWS__)
    CRITICAL_SECTION lock_;
#endif
   ThreadLock();
   ~ThreadLock();
   lock();
   unlock();
};

uint64_t get_current_thread_id();

//thread lock
extern ThreadLock g_thread_lock;

}; //namespace pap_common_sys

extern uint16_t g_thread_quit_count;

#endif //PAP_COMMON_THREAD_H_
