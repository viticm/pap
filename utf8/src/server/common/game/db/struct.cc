#include "server/common/game/db/struct.h"

namespace pap_server_common_game {

namespace db {

namespace share_memory {

head_t::head_t() {
  __ENTER_FUNCTION
    clean_up();
  __LEAVE_FUNCTION
}

head_t::~head_t() {
  //do nothing
}

void head_t::clean_up() {
  __ENTER_FUNCTION
    using namespace pap_server_common_sys;
    pool_id = 0;
    id = -1;
    player_id = -1;
    use_status = share_memory::kUseFree;
    flag = share_memory::kFlagFree;
    save_time = 0;
  __LEAVE_FUNCTION
}

global_data_t::init() {
  __ENTER_FUNCTION
    global_data = 0;
  __LEAVE_FUNCTION
}

void global_data_t::lock(char type) {
  __ENTER_FUNCTION
    using namespace pap_server_common_sys;
    share_memory::lock(head.flag, type);
  __LEAVE_FUNCTION
}

void global_data_t::unlock(char type) {
  __ENTER_FUNCTION
    using namespace pap_server_common_sys;
    share_memory::unlock(head.flag, type);
  __LEAVE_FUNCTION
}

void global_data_t::set_pool_id(uint32_t id) {
  __ENTER_FUNCTION
    head.pool_id = id;
  __LEAVE_FUNCTION
}

uint32_t global_data_t::get_pool_id() {
  __ENTER_FUNCTION
    return head.pool_id;
  __LEAVE_FUNCTION
}

bool global_data_t::set_use_status(int32_t status, char type) {
  __ENTER_FUNCTION
    using namespace pap_server_common_sys;
    share_memory::lock(type);
    head.use_status = status;
    share_memory::unlock(type);
    return true;
  __LEAVE_FUNCTION
}

int32_t global_data_t::get_use_status(char type) {
  __ENTER_FUNCTION
    using namespace pap_server_common_sys;
    int32_t result = -1;
    share_memory::lock(type);
    result = head.use_status;
    share_memory::unlock(type);
    return result;
  __LEAVE_FUNCTION
    return -1;
}

uint32_t global_data_t::get_save_time() {
  __ENTER_FUNCTION
    using namespace pap_server_common_sys;
    uint32_t save_time = 0;
    share_memory::lock(type);
    save_time = head.save_time;
    share_memory::unlock(type);
    return save_time;
  __LEAVE_FUNCTION
    return 0;
}

void global_data_t::set_save_time(uint32_t time) {
  __ENTER_FUNCTION
    using namespace pap_server_common_sys;
    share_memory::lock(type);
    head.save_time = time;
    share_memory::unlock(type);
  __LEAVE_FUNCTION
}

uint32_t global_data_t::get_data(char type) {
  __ENTER_FUNCTION
    using namespace pap_server_common_sys;
    uint32_t data;
    share_memory::lock(type);
    data = global_data;
    share_memory::unlock(type);
    return data;
  __LEAVE_FUNCTION
    return 0;
}

} //namespace share_memory

} //namespace db

} //namespace pap_server_common_game
