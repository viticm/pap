/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id database.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-2 9:55:46
 * @uses file as database class
 */
#ifndef PAP_COMMON_FILE_DATABASE_H_
#define PAP_COMMON_FILE_DATABASE_H_

#if defined(__LINUX__)
#include <hash_map>
#elif defined(__WINDOWS__)
#include <ext/hash_map>
#endif
#include "common/file/config.h"

namespace pap_common_file {

class Database {

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

   typedef vector<field_type_enum> field_type;
   
   union field_data {
     float float_value;
     int32_t int_value;
     const char* string_value; //can't change excel value in memory
     field_data() {/** do nothing **/}
     field_data(float value) {float_value = value;}
     field_data(int32_t value) {int_value = value;}
     field_data(const char* value) {string_value = value;}
   };

   typedef vector<field_data> data_buffer;

 public:
   Database();
   virtual ~Database();

 public:
   bool open_from_txt(const char* filename);
   bool open_from_memory(const char* memory, const char* end, const char* filename);
   virtual const field_data* search_index_equal(int32_t index) const;
   virtual const field_data* search_position(int32_t line, int32_t column) const;
   virtual const field_data* search_first_column_equal(int32_t column, const field_data &value) const;
   uint32_t get_id() const; //获得ID
   int32_t get_field_number() const;
   int32_t get_record_number() const;
   void create_index(int32_t column = 0, const char* filename = 0);

 public:
   static int32_t convert_string_tovector(const char* source
                                          vector<std::string> &result,
                                          const char* key,
                                          bool one_key,
                                          bool ignore_empty);
   static const char* get_line_from_memory(char* str, int32_t size, const char* memory, const char* end);
   template<field_type_enum TYPE>
   static bool field_equal(const field_data &a, const field_data &b); 

 protected:
#if defined(__SGI_STL_PORT)
   typedef std::hash_map<int32_t, field_data*> field_hashmap;
#elif defined(__WINDOWS__)
   typedef stdext::hash_map<int32_t, field_data*> field_hashmap;
#elif defined(__LINUX__)
   typedef __gnu_cxx::<int32_t, field_data*> field_hashmap;
#endif
   uint32_t id_;
   field_type_enum type_;
   int32_t record_number_;
   int32_t field_number_;
   data_buffer data_buffer_;
   char* string_buffer_;
   int32_t string_buffer_size_;
   field_hashmap hash_index_;
   int32_t index_column_;

 protected:
   bool open_from_memory_text(const char* memory, const char* end, const char* filename = 0);
   bool open_from_memory_binary(const char* memory, const char* end, const char* filename = 0);

};

}; //namespace pap_common_file

#endif //PAP_COMMON_FILE_DATABASE_H_
