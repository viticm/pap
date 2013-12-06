#include "server/share_memory/data/logic_manager.h"
#include "server/common/base/time_manager.h"

using namespace pap_server_common_game::db::share_memory;

//全局数据操作的实现
template<>
bool LogicManager<global_data_t>::save_all() {
  __ENTER_FUNCTION
    uint32_t data = 0;
    uint32_t run_time = g_time_manager->get_run_time();
    if (!pool_pointer_) {
      Assert(pool_pointer_);
      return false;
    }

  __LEAVE_FUNCTION
    return false;
}

