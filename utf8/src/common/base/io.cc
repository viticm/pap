#include <iostream>
#include "base/io.h"

void baseio_perror(const char* format, ....) {
  char buffer[2048];
#if defined(__linux__) /* { */
  const char* head = "\e[0;31;1m";
  const char* end = "\e[0m\n";
#elif defined(__windows__) /* }{ */
  const char* head = "(error)->";
  const char* end = "<-(error)";
#endif /* } */
  memset(buffer, '\0', sizeof(buffer));
  va_list argptr;
  vsnprintf(buffer, sizeof(buffer) - 1, newformat, argptr);
  va_end(argptr);
  std::cout<<head<<buffer<<end<<std::endl;
}

void baseio_pwarn(const char* format, ...) {
  char buffer[2048];
#if defined(__linux__) /* { */
  const char* head = "\e[0;33;1m";
  const char* end = "\e[0m\n";
#elif defined(__windows__) /* }{ */
  const char* head = "(warning)->";
  const char* end = "<-(warning)";
#endif /* } */
  memset(buffer, '\0', sizeof(buffer));
  va_list argptr;
  vsnprintf(buffer, sizeof(buffer) - 1, newformat, argptr);
  va_end(argptr);
  std::cout<<head<<buffer<<end<<std::endl;
}
