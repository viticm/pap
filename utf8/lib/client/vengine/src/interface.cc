#include "vengine/stdafx.h"

HINSTANCE g_hInstance = NULL;

//windows dllmain function, use the default style
BOOL APIENTRY DllMain(HANDLE hModule, 
                      UINT ul_reason_for_call, 
                      LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
      g_hInstance = (HINSTANCE)hModule;
      break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
    return TRUE;
}
