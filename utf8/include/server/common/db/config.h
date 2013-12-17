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
#define SQL_LENGTH_MAX 4096
#define LONG_SQL_LENGTH_MAX 204800

struct db_query_t {
  char sql_str_[SQL_LENGTH_MAX];
  void clear() {
    memset(sql_str_, '\0', sizeof(sql_str_));
  }
  void parse(const char* temp, ...) {
    va_list argptr;
    va_start(argptr, temp);
    int nchars  = snprintf(static_cast<char*>(sql_str_), 
                           sizeof(SQL_LENGTH_MAX) - 1, 
                           temp, 
                           argptr);
    va_end(argptr);
    if (-1 == nchars || sizeof(sql_str_) - 1 < nchars) {
      Assert(false);
    }
  }
};

struct long_db_query_t {
  char sql_str_[LONG_SQL_LENGTH_MAX];
  void clear() {
    memset(sql_str_, '\0', LONG_SQL_LENGTH_MAX);
  }
  void parse(const char* temp, ...) {
    va_list argptr;
    va_start(argptr, temp);
    int nchars  = snprintf(static_cast<char*>(sql_str_), 
                           sizeof(sql_str_) - 1, 
                           temp,
                           argptr);
    va_end(argptr);
    if (-1 == nchars || sizeof(sql_str_) - 1 < nchars) {
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
