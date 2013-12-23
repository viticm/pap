#include "server/share_memory/data/logic_manager.h"
#include "server/common/base/time_manager.h"
#include "server/common/db/odbc_interface.h"
#include "server/common/db/manager.h"
#include "server/common/game/db/struct.h"
#include "server/common/db/data/global.h"
#include "server/common/sys/share_memory.h"
#include "server/common/base/log.h"

using namespace pap_server_common_game::db::share_memory;
using namespace pap_server_common_sys::share_memory;
using namespace pap_server_common_base;

const uint32_t kIntervalSaveTime = 30000; //需要循环保存数据储存的时间间隔

//全局数据操作的实现
template<>
bool LogicManager<global_data_t>::save_all() {
  __ENTER_FUNCTION
    using namespace pap_server_common_sys::share_memory;
    uint32_t data = 0;
    //uint32_t run_time = g_time_manager->get_run_time();
    if (!pool_pointer_) {
      Assert(pool_pointer_);
      return false;
    }
    int32_t max_pool_size = pool_pointer_->get_max_size();
#if defined(NDEBUG)
    USE_PARAM(max_pool_size);
#endif
    Assert(1 == max_pool_size);
    global_data_t* global_data = pool_pointer_->get_obj(0);
    if (!global_data) {
      Assert(global_data);
      return false;
    }
    data = global_data->get_data(kFlagSelfRead);
    //uint64_t key = pool_pointer_->get_key();
    pap_server_common_db::ODBCInterface* odbc_interface = 
      g_db_manager->get_interface(kCharacterDatabase);
    Assert(odbc_interface);
	  pap_server_common_db::data::Global _global_data(odbc_interface);
    _global_data.set_pool_id(100);
    int32_t error_code;
    if (_global_data.save(&data)) {
      _global_data.parse_result(&error_code);
    }
    else {
      Log::save_log("share_memory", "global data save error.");
      Assert(false);
    }
    Log::save_log("share_memory", "global data save ok.");
    return true;
  __LEAVE_FUNCTION
    return false;
}

template <>
bool LogicManager<global_data_t>::normal_save() {
  __ENTER_FUNCTION
    bool result = false;
    uint32_t run_time = g_time_manager->get_run_time();
    if (run_time > run_time + last_save_time_) {
      result = save_all();
      last_save_time_ = run_time;
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

template <>
bool LogicManager<global_data_t>::clear() {
  __ENTER_FUNCTION
    //do nothing
    return true;
  __LEAVE_FUNCTION
    return false;
}

template <>
bool LogicManager<global_data_t>::post_init() {
  __ENTER_FUNCTION
    if (!pool_pointer_) return false;
    if (kCmdModelClearAll == g_cmd_model) return true;
    //uint32_t run_time = g_time_manager->get_run_time();
    //int32_t max_pool_size = pool_pointer_->get_max_size();
    uint64_t key = pool_pointer_->get_key();
    global_data_t* global_data = pool_pointer_->get_obj(0);
    if (!global_data) {
      Assert(global_data);
      return false;
    }
    //uint32_t _data = global_data->get_data(kFlagSelfRead);
    pap_server_common_db::ODBCInterface* odbc_interface = 
      g_db_manager->get_interface(kCharacterDatabase);
    Assert(odbc_interface);
    uint32_t _data = 100; //test
	  pap_server_common_db::data::Global _global_data(odbc_interface);
    _global_data.set_pool_id(100);
    int32_t error_code;
    if (_global_data.load()) {
      _global_data.parse_result(&error_code);
    }
    if (_data > 0) {
      global_data->set_data(kFlagSelfWrite, _data);
      _data = global_data->get_data(kFlagSelfRead);
    }
    else {
      Assert(false);
    }
    ready_ = true;
    Log::save_log("share_memory", 
                  "global_data post_init from key=%"PRIu64" is success.", 
                  key);
    return true;
  __LEAVE_FUNCTION
    return false;
}
