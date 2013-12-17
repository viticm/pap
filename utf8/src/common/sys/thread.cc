#include "common/sys/thread.h"

uint16_t g_quit_thread_count;

namespace pap_common_sys {

//-- thread class
Thread::Thread() {
  __ENTER_FUNCTION
    id_ = 0;
    status_ = kReady;
#if defined(__WINDOWS__)
    thread_handle_ = NULL; 
#endif
  __LEAVE_FUNCTION
}

Thread::~Thread() {
  //do nothing
}

void Thread::start() {
  __ENTER_FUNCTION
    if (status_ != kReady) return;
#if defined(__LINUX__)
    pthread_create(&id_, NULL, pap_thread_process, this);
#elif defined(__WINDOWS__)
    thread_handle_ = ::CreateThread(NULL, 0, pap_thread_process, this, 0, &id_);
#endif
  __LEAVE_FUNCTION
}

void Thread::stop() {
  //do nothing
}

void Thread::exit(void* retval) {
  __ENTER_FUNCTION
#if defined(__LINUX__)
    pthread_exit(retval);
#elif defined(__WINDOWS__)
    ::CloseHandle(thread_handle_);
#endif
  __LEAVE_FUNCTION
}

void Thread::run() {
  //do nothing
}

#if defined(__LINUX__)
void* pap_thread_process(void* derived_thread) {
#elif defined(__WINDOWS__)
DWORD WINAPI pap_thread_process(void* derived_thread) {
#endif
  __ENTER_FUNCTION
    Thread* thread = static_cast<Thread*>(derived_thread);
    if (NULL == thread) return NULL;
    thread->set_status(Thread::kRunning);
    thread->run();
    thread->set_status(Thread::kExit);
    thread->exit(NULL);
    g_thread_lock.lock();
    ++g_quit_thread_count;
    g_thread_lock.unlock();
  __LEAVE_FUNCTION
#if defined(__WINDOWS__)
    return 0;
#endif
}

int64_t Thread::get_id() {
  return id_;
}

Thread::enum_thread_status Thread::get_status() {
  return status_;
}

void Thread::set_status(enum_thread_status status) {
  __ENTER_FUNCTION
    status_ = status;
  __LEAVE_FUNCTION
}

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
