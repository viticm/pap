/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id file.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-22 18:08:41
 * @uses client game file database module
 */
#ifndef PAP_CLIENT_GAME_DATABASE_FILE_H_
#define PAP_CLIENT_GAME_DATABASE_FILE_H_

#include "vengine/db/file.h"

namespace database {

class File : public vengine_db::File {

 public:
   File(int32_t id);
   virtual ~File();

 //implement from abstract
 public:
   virtual const field_data* search_index_equal(int32_t index) const;
   virtual const field_data* search_line_equal(int32_t line) const;
   virtual const field_data* search_position(int32_t line, 
                                             int32_t column) const;
   virtual const field_data* search_first_column_equal(
       int32_t column, 
       const field_data &value) const;

 //implement from abstract
 public:
   virtual const pap_common_file::Database* get_databasefile() const;
   virtual int32_t get_id() const;
   virtual int32_t get_field_number() const;
   virtual int32_t get_record_number() const;

 public:
   static bool open_fromtxt(const char* filename, 
                            pap_common_file::Database* filedb);
   //切割字符串，将用"|"分割的字符串顺序拆分出来，并输出需求的字符。
   //参数：(需要解析的字符串， 第几块数据， 输出的字符串)
   static bool get_splitdata(const char* data, uint32_t count, char* out);

 protected:
   friend class System;
   pap_common_file::Database* filedb_;

 protected:
   bool open_fromtxt(const char* filename);
   static int32_t get_charposition(const char* str, 
                                   const char _char, 
                                   uint32_t count);

};

}; //namespace database

#endif //PAP_CLIENT_GAME_DATABASE_FILE_H_
