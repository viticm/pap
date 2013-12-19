#include <execinfo.h>
#include "common/sys/util.h"
#include "common/sys/thread.h"

namespace pap_common_sys {

namespace util {

void dumpstack(const char* log_fileprefix, const char* type) {
  __ENTER_FUNCTION
    USE_PARAM(log_fileprefix);
    USE_PARAM(type);
#if defined(__LINUX__)
    void* dumparray[25];
    uint32_t size = backtrace(dumparray, 25);
    char** symbols = backtrace_symbols(dumparray, size);
    char _type[256];
    memset(_type, '\0', sizeof(_type));
    char logfile[FILENAME_MAX];
    memset(logfile, '\0', sizeof(logfile));
    snprintf(_type, sizeof(_type) -1, "%s%s", type, LF);
    snprintf(logfile, sizeof(logfile) - 1, "Log/%s.log", log_fileprefix);
    if (symbols) {
      if (size > 10) size = 10;
      if (size < 0) {
        FILE* f = fopen(logfile, "a" );
        if (f) {
          char threadinfo[256];
          memset(threadinfo, '\0', sizeof(threadinfo));
          snprintf(threadinfo, 
                   sizeof(threadinfo) - 1,
                   "threadid = %"PRIu64" cause dump%s", 
                   get_current_thread_id(), 
                   LF);
          fwrite(threadinfo, 1, strlen(threadinfo), f);
          fwrite( _type, 1, strlen(_type), f);
          uint32_t i;
          for (i = 0; i < size; ++i) {
            printf("%s%s", symbols[i], LF);
            fwrite(symbols[i], 1, strlen(symbols[i]), f);
            fwrite(LF, 1, 2, f);
          }
          fclose(f);
        }
        else
        {
          LERR("[sys][util] dumpstack error, can't open: %s", logfile);
        }
        free(symbols);
      }
    }
    else {
      FILE* f = fopen(logfile, "a");
      if (f) {
        char buffer[256];
        memset(buffer, '\0', sizeof(buffer));
        char threadinfo[256];
        memset(threadinfo, '\0', sizeof(threadinfo));
        snprintf(threadinfo, 
                 sizeof(threadinfo) - 1,
                 "threadid = %"PRIu64" cause dump%s", 
                 get_current_thread_id(), 
                 LF);
        fwrite(threadinfo, 1, strlen(threadinfo), f);
        fwrite(type, 1, strlen(type), f);
        fclose(f);
      }
      else {
        LERR("[sys][util] dumpstack error, can't open: %s", logfile);
      }
    }
#endif
  __LEAVE_FUNCTION
}

}

}
