#include "vengine/capability/ax/trace.h"

// Window class name used by the main window of the TRACEWIN applet.
#define WATCHER_WINDOW_TITLE ("TRACEWIN")
// ID sent as COPYDATASRUCT::dwData to identify the WM_COPYDATA message
// as coming from an app using TraceWin.
#define ID_COPYDATA_TRACEMSG MAKELONG(MAKEWORD('t','w'),MAKEWORD('i','n'))
HWND g_hwatcher_wnd = NULL;

namespace vengine_capability {

namespace ax {

const uint16_t kContentLength = 2048;
typedef struct {
  uint8_t type;
  uint8_t winnumber;
  uint8_t typenumber;
  uint8_t reserve;
  char content[kContentLength];
} tracedata_t, FAR* lp_tracedata;

void VENGINE_API trace(uint8_t winnumber, 
                       uint8_t typenumber, 
                       const char* format, 
                       ...) {
#ifndef DISABLE_VENGINE_CAPABILITY_AX_TRACE
  try {
    //find window
    g_hwatcher_wnd = ::FindWindowA(NULL, WATCHER_WINDOW_TITLE);
    static tracedata_t tracedata;
    static COPYDATASTRUCT copydata;
    ZeroMemory(&tracedata, sizeof(tracedata_t));
    ZeroMemory(&copydata, sizeof(COPYDATASTRUCT));
    //message type
    tracedata.type = 1;
    tracedata.winnumber = AXTRACE_WND_INVALID == winnumber ? 
      static_cast<uint8_t>(:: GetCurrentProcessId() % 256) : winnumber;
    tracedata.typenumber = typenumber;
    va_list vapointer;
    va_start(vapointer, format);
    int32_t result = _vsnprintf(tracedata.content, 
                                sizeof(tracedata.content) - 1, 
                                format, 
                                vapointer);
    if (result >= 0 && result <= sizeof(tracedata.content) - 1) {
      tracedata.content[strlen(tracedata.content)] = '\n';
    }
    va_end(vapointer);
    copydata.dwData = ID_COPYDATA_TRACEMSG;
    copydata.cbData = sizeof(uint8_t) * 4 + 
                      sizeof(int32_t) + 
                      static_cast<DWORD>strlen(tracedata.content) + 
                      1;
    copydata.lpData = static_cast<char*>(tracedata.content);
    if (!g_hwatcher_wnd) {
      OutputDebugString(reinterpret_cast<LPCSTR>(copydata.lpData));
    }
    else {
      SendMessage(g_hwatcher_wnd, 
                  WM_COPYDATA, 
                  NULL, 
                  reinterpret_cast<LPARAM>(&copydata));
    }
  } 
  catch(...) {

  }
#endif
}

void VENGINE_API var(uint8_t winnumber,
                     uint8_t typenumber,
                     value_enum variabletype,
                     const char* valuename,
                     void* value) {
#ifndef DISABLE_VENGINE_CAPABILITY_AX_TRACE
  try {
    if (!g_hwatcher_wnd) {
      //find window
      g_hwatcher_wnd = ::FindWindowA(NULL, WATCHER_WINDOW_TITLE);
      if (!g_hwatcher_wnd) return;
    }
    static tracedata_t tracedata;
    static COPYDATASTRUCT copydata;
    ZeroMemory(&copydata, sizeof(COPYDATASTRUCT));
    tracedata.type = 2;
    tracedata.winnumber = winnumber;
    switch (variabletype) {
      case kValueInt8: {
         _snprintf(tracedata.content,
                  sizeof(tracedata.content) - 1,
                  "%d|%s|%d",
                  variabletype,
                  valuename,
                  *(reinterpret_cast<int8_t*>(value)));
        break;
      }
      case kValueUint8: {
        _snprintf(tracedata.content,
                  sizeof(tracedata.content) - 1,
                  "%d|%s|%d",
                  variabletype,
                  valuename,
                  *(reinterpret_cast<uint8_t*>(value)));
        break;
      }
      case kValueInt16: {
        _snprintf(tracedata.content,
                  sizeof(tracedata.content) - 1,
                  "%d|%s|%d",
                  variabletype,
                  valuename,
                  *(reinterpret_cast<int16_t*>(value)));
        break;
      }
      case kValueUint16: {
        _snprintf(tracedata.content,
                  sizeof(tracedata.content) - 1,
                  "%d|%s|%d",
                  variabletype,
                  valuename,
                  *(reinterpret_cast<uint16_t*>(value)));
        break;
      }
      case kValueInt32: {
         _snprintf(tracedata.content,
                  sizeof(tracedata.content) - 1,
                  "%d|%s|%d",
                  variabletype,
                  valuename,
                  *(reinterpret_cast<int32_t*>(value)));
        break;
      }
      case kValueUint32: {
         _snprintf(tracedata.content,
                  sizeof(tracedata.content) - 1,
                  "%d|%s|%d",
                  variabletype,
                  valuename,
                  *(reinterpret_cast<uint32_t*>(value)));
         break;
      }
     case kValueInt64: {
         _snprintf(tracedata.content,
                  sizeof(tracedata.content) - 1,
                  "%d|%s|%d",
                  variabletype,
                  valuename,
                  *(reinterpret_cast<int64_t*>(value)));
        break;
      }
      case kValueUint64: {
         _snprintf(tracedata.content,
                  sizeof(tracedata.content) - 1,
                  "%d|%s|%d",
                  variabletype,
                  valuename,
                  *(reinterpret_cast<uint64_t*>(value)));
         break;
      }
      default:
        return;
    }
    copydata.dwData = 0;
    copydata.cbData = sizeof(uint8_t) * 4 + 
                      sizeof(int32_t) + 
                      static_cast<DWORD>(strlen(tracedata.content)) + 
                      1;
    copydata.lpData = &tracedata;
    SendMessage(g_hwatcher_wnd, 
                WM_COPYDATA, 
                NULL, 
                reinterpret_cast<LPARAM>(&copydata));
  }
  catch(...) {

  }
#endif
}


} //namespace ax

} //namespace vengine_capability
