/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id file.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-22 18:08:41
 * @uses vengine file database module
 *       cn: 文件数据模块
 */
#ifndef VENGINE_DB_FILE_H_
#define VENGINE_DB_FILE_H_

#include "vengine/config.h"

/** 注意此处引用了公用文件，文件数据库 **/
namespace pap_common_file {

class Database;

}; //namespace pap_common_file

namespace vengine_db {

class VENGINE_API File {

 public:
   typedef struct {
     uint32_t identify; //标示
     int32_t field_number; //列数
     int32_t record_number; //记录数
     int32_t string_block_size; //字符串区大小
   } file_head_t;
   
   typedef enum { //field type
     kTypeInt = 0,
     kTypeFloat = 1,
     kTypeString = 2,
   } field_type_enum;

   union field_data {
     float float_value;
     int32_t int_value;
     const char* string_value; //can't change excel value in memory
     field_data() {/** do nothing **/}
     field_data(float value) {float_value = value;}
     field_data(int32_t value) {int_value = value;}
     field_data(const char* value) {string_value = value;}
   };
   
 public:
   virtual const field_data* search_index_equal(int32_t index) const = 0;
   virtual const field_data* search_position(int32_t line, 
                                             int32_t column) const = 0;
   virtual const field_data* search_first_column_equal(
       int32_t column, 
       const field_data &value) const = 0;

 public:
   virtual const pap_common_file::Database* get_databasefile() const = 0;
   virtual uint32_t get_id() const = 0;
   virtual int32_t get_field_number() const = 0;
   virtual int32_t get_record_number() const = 0;

};

}; //namespace vengine_db

#endif //VENGINE_DB_FILE_H_
