/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id share_memory.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-3 11:32:43
 * @uses system share memory model
 */
#ifndef PAP_COMMON_SYS_SHARE_MEMORY_H_
#define PAP_COMMON_SYS_SHARE_MEMORY_H_

#include "common/sys/config.h"

namespace pap_common_sys {

namespace share_memory {

//-- static define
const uint32_t kManagerUnitDataMax = 5000; //如果不需要引入外部，就不要使用宏
const uint8_t kObjMax = 20;

struct data_header_t {
  uint64_t key;
  int32_t size;
  uint32_t version;
  data_header_t();
  ~data_header_t();
};

typedef enum {
  kSmptShareMemory,
  kSmptWorld,
  kSmptServer,
} pool_type_enum;

//static define --

namespace api {

int32_t create(uint64_t key, uint32_t size);
int32_t open(uint64_t key, uint32_t size);
char* map(int32_t handle);
void unmap(char* pointer);
void close(int32_t handle);

}; //namespace api

class Base {

 public:
   int32_t cmd_model_; //命令行模式，几种模式在config.h定义

 public:
   bool create(uint64_t key, uint32_t size);
   void destory();
   bool attach(uint64_t key, uint32_t size);
   bool dump(const char* filename);
   bool merge_from_file(const char* filename);
   void set_head_version(uint32_t version);
   uint32_t get_head_version();
 private:
   uint32_t size_;
   char* data_pointer_;
   char* header_;
   int32_t handle_;
  
};

template <typename T> //template class must be in one file
class UnitManager {
 
 public:
   T* data_[kManagerUnitDataMax];
   int32_t count_;

 public:
   UnitManager() {
     __ENTER_FUNCTION
       count_ = 0;
       memset(data_, 0, sizeof(T*) * kManagerUnitDataMax);
     __LEAVE_FUNCTION
   };
   ~UnitManager() {
     //do nothing
   };
   void init() {
     __ENTER_FUNCTION
       count_ = 0;
     __LEAVE_FUNCTION
   };
   bool heartbeat(uint32_t time);
   bool add_data(T* data);
   bool delete_data(T* data);
   T* get_data(uint16_t id);

};

template<typename T> //模板类只能定义在一个文件内
class UnitPool {

 public:
   UnitPool();
   ~UnitPool();
   bool init(uint32_t max_count, uint64_t key, pool_type_enum pool_type);
   bool release();
   T* new_obj();
   void delete_obj(T* obj);
   T* get_obj(int32_t index);
   int32_t get_max_size();
   int32_t get_position();
   uint64_t get_key();
   bool dump(const char* filename);
   bool merge_from_file(const char* filename);
   uint32_t get_head_version();
   void set_head_version(uint32_t version);

 private:
   T** obj_;
   int32_t max_size_;
   int32_t position_;
   Base* ref_obj_pointer_;
   uint32_t key_;

};

}; //namespace share_memory

}; //namespace pap_common_sys

#endif //PAP_COMMON_SYS_SHARE_MEMORY_H_
