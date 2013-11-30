#include "common/sys/thread.h"
#include "common/base/type.h"

namespace pap_common_sys {

//-- thread class

//thread class --

//-- thread lock class
ThreadLock::ThreadLock() {
  __ENTER_FUNCTION
#if defined(__LINUX__)
    pthread_mutex_init(&mutex_, NULL);
#elif defined(__WINDOWS__)
    InitializeCriticalSection(lock_);
#endif
  __LEAVE_FUNCTION
}

ThreadLock::~ThreadLock() {
  __ENTER_FUNCTION
#if defined(__LINUX__)
    pthread_mutex_destroy(&mutex_);
#elif defined(__WINDOWS__)
    DeleteCriticalSection(lock_);
#endif
  __LEAVE_FUNCTION
}

void ThreadLock::lock() {
  __ENTER_FUNCTION
#if defined(__LINUX__)
    pthread_mutex_lock(&mutex_);
#elif defined(__WINDOWS__)
    EnterCriticalSection(lock_);
#endif
  __LEAVE_FUNCTION
}

void ThreadLock::unlock() {
  __ENTER_FUNCTION
#if defined(__LINUX__)
    pthread_mutex_unlock(&mutex_);
#elif defined(__WINDOWS__)
    LeaveCriticalSection(lock_);
#endif
  __LEAVE_FUNCTION
}

uint64_t get_current_thread_id() {
  __ENTER_FUNCTION
#if defined(__LINUX__)
    return static_cast<uint64_t>(pthread_self());
#elif defined(__WINDOWS__)
    return static_cast<uint64_t>(GetCurrentThreadId());
#endif
  __LEAVE_FUNCTION
}

//thread lock class --

} //namespace pap_common_sys
