#ifndef PAP_SERVER_COMMON_THREAD_H_
#define PAP_SERVER_COMMON_THREAD_H_

class Thread {
 public:
   enum THREAD_STATUS { //线程的四种状态 (准备、运行中、退出中、已退出)
     READY,
     RUNNING,
     EXITING,
     EXIT,
   };

 public:
   Thread();
   virtual ~Thread();
   start();
   virtual void stop();
   void exit(void* retval = NULL);
   virtual void run();
   int64_t get_thread_id();
   THREAD_STATUS get_status();
   void set_status(THREAD_STATUS status);

 private:
   int64_t thread_id_;
   THREAD_STATUS thread_status_;
#if defined(__WINDOWS__)
   HANDLE thread_handle_;
#endif

};

extern g_quit_thread_count;
#if defined(__LINUX__)
void* pap_thread_process(void* derived_thread);
#elif defined(__WINDOWS__)
DWORD WINAPI pap_thread_process(void* derived_thread);
#endif //PAP_SERVER_COMMON_THREAD_H_
