/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-22 19:29:37
 * @uses the database define for server.
 */
#ifndef PAP_SERVER_COMMON_DB_DEFINE_H_
#define PAP_SERVER_COMMON_DB_DEFINE_H_
#include "common/base/type.h"
#define MAX_SQL_LENGTH 4096
#define MAX_LONG_SQL_LENGTH 204800

struct DB_QUERY {
  char sql_str_[MAX_SQL_LENGTH];
  void clear() {
    memset(sql_str_, 0, MAX_SQL_LENGTH);
  }
  void parse(const char* temp, ...) {
    va_list argptr;
    va_start(argptr, temp);
    int nchars  = tvsnprintf(static_cast<char*>(sql_str_), MAX_SQL_LENGTH, temp, argptr);
    va_end(argptr);
    if (-1 == nchars || MAX_SQL_LENGTH < nchars) {
      Assert(false);
    }
  }
};

struct LONG_DB_QUERY {
  char sql_str_[MAX_LONG_SQL_LENGTH];
  void clear() {
    memset(sql_str_, 0, MAX_LONG_SQL_LENGTH);
  }
  void parse(const char* temp, ...) {
    va_list argptr;
    va_start(argptr, temp);
    int nchars  = tvsnprintf(static_cast<char*>(sql_str_), MAX_LONG_SQL_LENGTH, temp, argptr);
    va_end(argptr);
    if (-1 == nchars || MAX_SQL_LENGTH < nchars) {
      Assert(false);
    }
  }
};

typedef enum {
  kAllDatabase = -1,
  kCharacterDatabase = 1,
  kUserDatabase = 2,
} db_type_enum;

#endif //PAP_SERVER_COMMON_DB_DEFINE_H_
