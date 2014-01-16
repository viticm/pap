#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "common/base/io.h"

void baseio_perror(const char* format, ...) {
  char buffer[2048];
#if defined(__LINUX__) /* { */
  const char* head = "\e[0;31;1m";
  const char* end = "\e[0m";
#elif defined(__WINDOWS__) /* }{ */
  const char* head = "(error)->";
  const char* end = "<-(error)";
#endif /* } */
  va_list argptr;
  memset(buffer, '\0', sizeof(buffer));
  va_start(argptr, format);
  vsnprintf(buffer, sizeof(buffer) - 1, format, argptr);
  va_end(argptr);
  std::cout<<head<<buffer<<end<<std::endl;
}

void baseio_pwarn(const char* format, ...) {
  char buffer[2048];
#if defined(__LINUX__) /* { */
  const char* head = "\e[0;33;1m";
  const char* end = "\e[0m";
#elif defined(__WINDOWS__) /* }{ */
  const char* head = "(warning)->";
  const char* end = "<-(warning)";
#endif /* } */
  va_list argptr;
  memset(buffer, '\0', sizeof(buffer));
  va_start(argptr, format);
  vsnprintf(buffer, sizeof(buffer) - 1, format, argptr);
  va_end(argptr);
  std::cout<<head<<buffer<<end<<std::endl;
}
