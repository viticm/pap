#ifndef PAP_SERVER_COMMON_DB_DEFINE_H_
#define PAP_SERVER_COMMON_DB_DEFINE_H_

#define MAX_SQL_LENGTH 4096
#define MAX_LONG_SQL_LENGTH 204800

struct DB_QUERY {
  char sql_str_[MAX_SQL_LENGTH];
  void clear() {
    memset(sql_str_, 0, MAX_SQL_LENGTH);
  }
  void parse(const char* temp, ...);
}

struct LONG_DB_QUERY {
  char sql_str_[MAX_LONG_SQL_LENGTH];
  void clear() {
    memset(sql_str_, 0, MAX_LONG_SQL_LENGTH);
  }
  void parse(const char* temp, ...);
}

#endif //PAP_SERVER_COMMON_DB_DEFINE_H_
