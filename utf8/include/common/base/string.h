#ifndef PAP_COMMON_BASE_STRING_H_
#define PAP_COMMON_BASE_STRING_H_

#include <map> 
#include "common/base/config.h"

namespace pap_common_base {

namespace string {

/*typedef {*/
typedef std::map<std::string, std::string> map; //my map
/*typedef }*/

void replace_all(std::string& str, 
                 const std::string source, 
                 const std::string destination);
bool string_toint(const char* source, 
                  int16_t& result, 
                  uint8_t converted_length = 0, 
                  bool ignored_zero = false);
bool string_toint16(const char* source, 
                    int16_t& result, 
                    uint8_t converted_length = 0, 
                    bool ignored_zero = false);
bool string_toint32(const char* source, 
                    int32_t& result, 
                    uint8_t converted_length = 0, 
                    bool ignored_zero = false);
bool string_toint(const char* source, 
                  int32_t& result, 
                  uint8_t converted_length = 0, 
                  bool ignored_zero = false);

/*string table class {*/
//cn: 数据量不大的时候可以用这个，否则用map
/*string table class {*/                                                           
struct tableitem_t {                                                               
  char* str;                                                                       
  void* pointer;                                                                   
  uint32_t status;                                                                 
  tableitem_t() {                                                                  
    str = NULL;                                                                    
    pointer = NULL;                                                                
    status = 0;                                                                    
  };                                                                               
  ~tableitem_t() {                                                                 
      SAFE_DELETE_ARRAY(str);                                                        
      pointer = NULL;                                                                
      status = 0;                                                                    
  };                                                                               
};      
class Table {

 public:
   Table();
   ~Table();

 public:
   enum {
     kEmpty = 0,
     kSet = 1,
     kUse = 2,
   };

 public:
   void init(uint32_t itemmax, uint32_t size);
   bool add(const char* str, void* pointer);
   void* get(const char* str);
   void remove(const char* str);
   void cleanup();
   void* get_byposition(uint32_t position);
   void remove_byposition(uint32_t position);

 private:
   tableitem_t* item_;
   uint32_t count_;
   uint32_t size_;

};
/*strint table class}*/

} //namespace string

} //namespace pap_common_base
#endif //PAP_COMMON_BASE_STRING_H_
