#include <shlobj.h>
#include "vengine/stdafx.h"
#include "vengine/resource.h"
#include "vengine/capability/xzip.h"
#include "vengine/exception/errorinfo.h"
#include "vengine/exception/base.h"

namespace vengine_exception {

namespace base {

void showstring(const char* format, ...) {
  va_list arglist;
  va_start(arglist, format);
  uint16_t size = _vsctprintf(format, arglist);
  STRING message;
  message.assign(size + 1, _T(' '));
  _vstprintf(reinterpret_cast<LPTSTR>(&(message[0])), format, arglist);
  va_end(arglist);
  throw std::exception(message.c_str());
}

void showassert(const char* filename, uint16_t fileline, const char* exception) {
  const char* assertformat = 
    _T("assert: "LF"")
    _T(""LF"")
    _T("file: %s"LF"")
    _T("line: %d"LF"");
    _T("exception: %s"LF"");
  uint16_t size = _sctprintf(assertformat, filename, fileline, exception);
  STRING message;
  message.assign(size + 1, _T(' '));
  _stprintf(reinterpret_cast<LPTSTR>(&(message[0])), 
            assertformat, 
            filename, 
            fileline, 
            exception);
  throw std::exception(message.c_str());
}

void process(PEXCEPTION_POINTERS exception, bool run_crashreport) throw() {
  uint16_t lasterror = ::GetLastError();
  if (!exception) return;
  char smallinfo_file[MAX_PATH] = {0};
  if (!errorinfo::create_smallinfo_dumpfile(exception, 
                                            smallinfo_file, 
                                            lasterror)) {
    return;
  }
  char biginfo_file[MAX_PATH] = {0};
  if (!errorinfo::create_biginfo_dumpfile(exception,
                                          biginfo_file,
                                          lasterror)) {
    return;
  }
  char dumpfile[MAX_PATH] = {0};
  errorinfo::create_dumphelp_file(exception, dumpfile);
  if (run_crashreport) { //show crash report
    char crashreport_file[MAX_PATH] = {0};
    ::GetModuleFileName(NULL, crashreport_file, sizeof(crashreport_file) - 1);
    ::PathRemoveFileSpec(crashreport_file);
    ::PathAppend(szCrashReportFile, _T("crashreport.exe"));
    char cmd[1024] = {0};
    _sntprintf(cmd, 
               sizeof(cmd) - 1, 
               _T("%s \"%s\" \"%s\" \"%s\""), 
               crashreport_file, 
               smallinfo_file, 
               biginfo_file, 
               dumpfile);
    //start bin crashreport.exe
    STARTUPINFO startupinfo;
    PROCESS_INFORMATION processinformation;
    ZeroMemory(&startupinfo, sizeof(STARTUPINFO));
    ZeroMemory(processinformation, sizeof(PROCESS_INFORMATION));
    startupinfo.cb = sizeof(STARTUPINFO);
    startupinfo.dwFlags = STARTF_USESHOWWINDOW;
    startupinfo.wShowWindow = SW_SHOWNORMAL;
    ::CreateProcess(NULL, 
                    cmd, 
                    NULL, 
                    NULL, 
                    FALSE,CREATE_DEFAULT_ERROR_MODE, 
                    NULL, 
                    NULL, 
                    &startupinfo, 
                    &processinformation);
  }
}

void centerdialog(HWND hdialog) {
  int32_t x, y;
  int32_t w, h;
  RECT rect;
  GetWindowRect(hdialog, &rect);
  w = rect.right - rect.left;
  h = rect.bottom - rect.top;
  x = (GetSystemMetrics(SM_CXMAXIMIZED) - w) / 2;
  y = (GetSystemMetrics(SM_CYMAXIMIZED) - h) / 2;
  MoveWindow(hdialog, x, y, w, h, true);
}

//global variables
STRING g_exceptiontitle;
STRING g_exceptioncontent;
STRING g_dumpfile;
char g_windbg[MAX_PATH];

bool is_windbg_enable() {
  DWORD type, size = MAX_PATH;
  if (ERROR_SUCCESS != ::SHGetValue(HKEY_CURRENT_USER, 
                                    "Software\\Microsoft\\DebuggingTools", 
                                    "WinDbg", 
                                    &type, 
                                    g_windbg, 
                                    &size)) {
    return false;
  }
  return true;
}

void sendinner_crashreport(HWND innerhwnd) {
  char currentdir[MAX_PATH] = {0};
  ::GetCurrentDirectory(sizeof(currentdir), currentdir);
  char crashfile[MAX_PATH] = {0};
  SYSTEMTIME nowtime;
  ::GetLocalTime(&nowtime);
	snprintf(crashfile, 
           sizeof(crashfile) - 1, 
           "crash%02d_%02d_%02d_%02d.zip", 
           nowtime.wMonth, 
           nowtime.wDay, 
           nowtime.wHour, 
           nowtime.wMinute,
           nowtime.wSecond);
  char localfile[MAX_PATH] = {0};
  strncpy(localfile, currentdir, sizeof(localfile) - 1);
  PathAppend(localfile, crashfile);
  HZIP hzip = vengine_capability::CreateZip(
    reinterpret_cast<void*>(localfile), 
    0, 
    ZIP_FILENAME);
  if (!hzip) {
     MessageBox(innerhwnd, 
                "create error.zip error!", 
                "crashreport", 
                MB_OK | MB_ICONSTOP);
     return;
  }
  vengine_capability::ZipAdd(hzip, 
                             "dump.dmp", 
                             reinterpret_cast<void*>(g_dumpfile.c_str()), 
                             0, 
                             ZIP_FILENAME);
  char logfile[MAX_PATH] = {0};
  strncpy(logfile, currentdir, sizeof(logfile) - 1);
  PathAppend(logfile, "fairy.log");
  vengine_capability::ZipAdd(hzip, 
                             "fairy.log", 
                             reinterpret_cast<void*>logfile, 
                             0, 
                             ZIP_FILENAME);
  strncpy(logfile, currentdir, sizeof(logfile) - 1);
  PathAppend(logfile, "cegui.log");
  vengine_capability::ZipAdd(hzip, 
                             "cegui.log", 
                             reinterpret_cast<void*>logfile, 
                             0, 
                             ZIP_FILENAME);

  vengine_capability::CloseZip(hzip); //zip close
  BROWSEINFO browseinfo; 
  ZeroMemory(&browseinfo, sizeof(browseinfo));
  browseinfo.hwndOwner = innerhwnd;
  browseinfo.pidlRoot = NULL;
  browseinfo.ulFlags = BIF_NEWDIALOGSTYLE|BIF_RETURNONLYFSDIRS;
  browseinfo.pszDisplayName = NULL;
  browseinfo.lpszTitle = "选择一个目录用以保存数据文件";
  LPITEMIDLIST findfolder = ::SHBrowseForFolder(&browseinfo);
  if (!findfolder) return;
  char result[MAX_PATH] = {0};
  ::SHGetPathFromIDList(findfolder, result);

  char saveas[MAX_PATH] = {0};
  strncpy(saveas, result, MAX_PATH);
  PathAppend(saveas, crashfile);
  CopyFile(localfile, saveas, false); //save as new file
}

CALLBACK bool inner_dialogprocess(HWND hdialog, 
                                  uint16_t message, 
                                  WPARAM wparam, 
                                  LPARAM lparam) {
  switch(message) {
    case WM_CTLCOLORSTATIC: {
      HWND hstatic = reinterpret_cast<HWND>(lparam);
      static HBRUSH s_yellowbrush = 0;
      if (hstatic == GetDlgItem(hdialog, IDC_STATIC_TYPE)) {
        SetBkMode(reinterpret_cast<HDC>(wparam), TRANSPARENT);
        SetBkColor((reinterpret_cast<HDC>(wparam), RGB(255, 255, 0));
        if (0 == s_yellowbrush) {
          s_yellowbrush = ::CreateSolidBrush(RGB(255, 255, 0));
          return static_cast<bool>(
            static_cast<int32_t>(reinterpret_cast<INT_PTR>(s_yellowbrush)));
        }
      }
      else {
        return false;
      }
      break;
    }
    case WM_INITDIALOG: {
      centerdialog(hdialog);
      ::SetWindowText(::GetDlgItem(hdialog, IDC_STATIC_TYPE), 
                      g_exceptiontitle.c_str());
      FILE* fp = fopen(g_exceptioncontent.c_str(), "rb");
      if (fp) {
        char temp[1024] = {0};
        fread(temp, sizeof(char), 1024, fp);
        fclose(fp); 
        fp = NULL;
        ::SetWindowText(::GetDlgItem(hdialog, IDC_EDIT_CONTENTS), temp);
      }
      ::EnableWindow(::GetDlgItem(hdialog, IDC_BUTTON_DEBUG), 
                     is_windbg_enable());
    }
    break;
  }
  case WM_COMMAND: {
     switch(LOWORD(wparam)) {
       case IDC_BUTTON_DEBUG: {
         EndDialog(hdialog, 3);
         break;
       }
       case IDC_BUTTON_SEND: {
         sendinner_crashreport(hdialog);
         EndDialog(hdialog, 2);
         break;
       }
       case IDC_BUTTON_THROW: {
         EndDialog(hdialog, 1);
         break;
       }
       case IDC_BUTTON_IGNORE: {
         EndDialog(hdialog, 0);
         break;
       }
       default:
         break;
     }
    break;
  }
  case WM_CLOSE: {
    EndDialog(hdialog, 0);
    DestroyWindow(hdialog);
    break;
  }
  default:
    return false;
  return true;
}

int32_t processinner(PEXCEPTION_POINTERS exception, 
                  HWND hparentwnd, 
                  const char* title) {
  DWORD lasterror = ::GetLastError();
  char smallinfo_file[MAX_PATH] = {0};
  //base
  if (!errorinfo::create_smallinfo_dumpfile(exception, 
                                            smallinfo_file, 
                                            lasterror)) {
    return 0;
  }
  /**
  char biginfo_file[MAX_PATH] = {0};
  //full
  if (!create_biginfo_dumpfile(exception, biginfo_file, lasterror)) {
    return;
  }
  **/
  char dumpfile[MAX_PATH] = {0};
  errorinfo::create_dumphelp_file(exception, dumpfile);
  g_exceptiontitle = title;
  g_exceptioncontent = smallinfo_file;
  g_dumpfile = dumpfile;
  int32_t result = ::DialogBox(g_hInstance, 
                               MAKEINTRESOURCE(IDD_INNER_EXCEPTION), 
                               hparentwnd, 
                               reinterpret_cast<DLGPROC>(inner_dialogprocess));
  return result;
}

} //namespace base

} //namespace vengine_exception
