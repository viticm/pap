/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id struct.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-4 16:18:56
 * @uses server used game database struct
 */
#ifndef PAP_SERVER_COMMON_GAME_DB_STRUCT_H_
#define PAP_SERVER_COMMON_GAME_DB_STRUCT_H_

#include "server/common/game/db/config.h"
#include "server/common/sys/share_memory.h"
#include "common/game/struct.h"

#pragma pack(push, 1)

namespace pap_server_common_game {

namespace db {

class HumanData; //角色数据

namespace share_memory {

struct head_t {
  uint32_t pool_id;
  int32_t id;
  int32_t use_status;
  char flag;
  int16_t player_id;
  uint32_t save_time;
  head_t();
  ~head_t();
  void clean_up();
};

struct global_data_t {
  head_t head;
  uint32_t global_data;
  void lock(char type);
  void unlock(char type);
  void set_pool_id(uint32_t id);
  uint32_t get_pool_id();
  bool set_use_status(int32_t status, char type);
  int32_t get_use_status(char type);
  uint32_t get_save_time();
  void set_save_time(uint32_t time);
  uint32_t get_data(char type);
  void set_data(char type, uint32_t data);
  void init();
};

}; //namespace share_memory

}; //namespace db

}; //namespace pap_server_common_game
#pragma pack(pop)

#endif //PAP_SERVER_COMMON_GAME_DB_STRUCT_H_
