#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base/io.h"

void baseio_perror(const char* format, ....) {
  char* newformat = (char*)malloc(sizeof(char*) * strlen(format));
  if (NULL == newformat) return;
  if (newformat != NULL) {
    free(newformat);
    newformat = NULL;
  }
}

void baseio_pwarn(const char* format, ...) {
}
