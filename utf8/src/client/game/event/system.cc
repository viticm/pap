#include "vengine/exception/base.h"
#include "vengine/time/system.h"
#include "procedure/base.h"
#include "client/game/event/system.h"

namespace event {

using namespace vengine_game::event_id; //using in source, not redefined 

//具体说明查看ID定义
vengine_game::eventdefine_t g_eventdefine[] = {
  {kApplicationInit, "ApplicationInit"},
  {kSceneCutover, "SceneCutover"},
  {kLoginShowSystemInfoAndCloseNet, "LoginShowSystemInfoAndCloseNet"},
  {kLoginShowSystemInfo,"LoginShowSystemInfo"},
  {kLoginCloseSystemInfo, "LoginCloseSystemInfo"},
  {kLoginOpenSelectServer, "LoginOpenSelectServer"},
  {kLoginOpenAccountInput, "LoginOpenAccountInput"},
  {kLoginCloseAccountInput, "LoginCloseAccountInput"},
  {kLoginShowSystemInfoNoButton,"LoginShowSystemInfoNoButton"},
  {kLoginShowSystemInfoYesOrNo, "LoginShowSystemInfoYesOrNo"},
  {kLoginSelectLoginServer, "LoginSelectLoginServer"},
  {kLoginCleanAccount, "LoginCleanAccount"},
  {kLoginSelectArea, "LoginSelectArea"},
  {kUIToggleSystemFrame, "UIToggleSystemFrame"},
  {kUICloseSecondMenu, "UICloseSecondMenu"},
  {kUIChatAdjustMoveCtl, "UIChatAdjustMoveCtl"},
  {kChatChangePrivateName, "ChatChangePrivateName"},
  {kChatContexMenu, "ChatContexMenu"},
  {kNewDebugMessage, "NewDebugMessage"},
  {kNetClose, "NetClose"},
  {kVariableChanged, "VariableChanged"},
};

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(
    System,
    VENGINE_KERNEL_GETCLASS(vengine_game::EventSystem));

System* System::self_ = NULL;

System::System() {
  self_ = this;
  last_tickcount_ = 0;
}

System::~System() {
  //do nothing
}

System* System::getself() {
  return self_;
}

void System::init(void*) {
  int32_t eventnumber = static_cast<int32_t>(
      sizeof(g_eventdefine) / sizeof(vengine_game::eventdefine_t));
  int32_t i;
  for (i = 0; i < eventnumber; ++i) {
    index_asname_map_[g_eventdefine[i].event] = &(g_eventdefine[i]); 
    index_asid_map_[g_eventdefine[i].id] = &(g_eventdefine[i]);
  }
}

void System::release() {
  //do nothing
}

void System::tick() {
 //do nothing
}

void System::push(const vengine_game::event_t& event) {
  if (!event.eventdefine) return;
  if (event.eventdefine->delayprocess) { //慢速处理队列
    delayquene_.push_back(event);
  }
  else {
    queue_.push_back(event);
  }
}

void System::push(_enum id,std::vector<STRING> param) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  event.args = param;
  push(event);
}

void System::push(_enum id) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  push(event);
}

void System::push(_enum id, int32_t arg0) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%d", arg0);
  event.args.push_back(temp);
  push(event);
}

void System::push(_enum id, int32_t arg0, int32_t arg1) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%d", arg0);
  event.args.push_back(temp);
  snprintf(temp, sizeof(temp) - 1, "%d", arg1);
  event.args.push_back(temp);
  push(event);
}

void System::push(_enum id, int32_t arg0, int32_t arg1, int32_t arg2) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%d", arg0);
  event.args.push_back(temp);
  snprintf(temp, sizeof(temp) - 1, "%d", arg1);
  event.args.push_back(temp);
  snprintf(temp, sizeof(temp) - 1, "%d", arg2);
  event.args.push_back(temp);
  push(event);
}

void System::push(_enum id, float arg0) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%f", arg0);
  event.args.push_back(temp);
  push(event);
}

void System::push(_enum id, const char* arg0) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  event.args.push_back(arg0);
  push(event);
}

void System::push(_enum id, const char* arg0, const char* arg1) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  event.args.push_back(arg0);
  event.args.push_back(arg1);
  push(event);
}

void System::push(_enum id, const char* arg0, const char* arg1, int32_t arg2) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  event.args.push_back(arg0);
  event.args.push_back(arg1);
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%d", arg2);
  event.args.push_back(temp);
  push(event);
}

void System::push(_enum id, 
                  const char* arg0, 
                  const char* arg1, 
                  int32_t arg2,
                  int32_t arg3) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  event.args.push_back(arg0);
  event.args.push_back(arg1);
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%d", arg2);
  event.args.push_back(temp);
  snprintf(temp, sizeof(temp) - 1, "%d", arg3);
  event.args.push_back(temp);
  push(event);
}

void System::push(_enum id, 
                  const char* arg0, 
                  const char* arg1, 
                  const char* arg2) {
  if (index_asid_map_.find(id) == index_asid_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asid_map_[id];
  event.args.push_back(arg0);
  event.args.push_back(arg1);
  event.args.push_back(arg2);
  push(event);
}

void System::push(const STRING& eventname, std::vector<STRING> param) {
  if (index_asname_map_.find(eventname) == index_asname_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asname_map_[eventname];
  event.args = param;
  push(event);
}

void System::push(const STRING& eventname) {
  if (index_asname_map_.find(eventname) == index_asname_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asname_map_[eventname];
  push(event);
}

void System::push(const STRING& eventname, int32_t arg0) {
  if (index_asname_map_.find(eventname) == index_asname_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asname_map_[eventname];
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%d", arg0);
  event.args.push_back(temp);
  push(event);
}

void System::push(const STRING& eventname, float arg0) {
  if (index_asname_map_.find(eventname) == index_asname_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asname_map_[eventname];
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%f", arg0);
  event.args.push_back(temp);
  push(event);
}

void System::push(const STRING& eventname, int32_t arg0, int32_t arg1) {
  if (index_asname_map_.find(eventname) == index_asname_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asname_map_[eventname];
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%d", arg0);
  event.args.push_back(temp);
  snprintf(temp, sizeof(temp) - 1, "%d", arg1);
  event.args.push_back(temp);
  push(event);
}

void System::push(const STRING& eventname, const char* arg0) {
  if (index_asname_map_.find(eventname) == index_asname_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asname_map_[eventname];
  event.args.push_back(arg0);
  push(event);
}

void System::push(const STRING& eventname, 
                  const char* arg0, 
                  const char* arg1) {
  if (index_asname_map_.find(eventname) == index_asname_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asname_map_[eventname];
  event.args.push_back(arg0);
  event.args.push_back(arg1);
  push(event);
}

void System::push(const STRING& eventname, 
                  const char* arg0, 
                  const char* arg1,
                  int32_t arg2) {
  if (index_asname_map_.find(eventname) == index_asname_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asname_map_[eventname];
  event.args.push_back(arg0);
  event.args.push_back(arg1);
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%d", arg2);
  event.args.push_back(temp);
  push(event);
}

void System::push(const STRING& eventname, 
                  const char* arg0, 
                  const char* arg1,
                  int32_t arg2,
                  int32_t arg3) {
  if (index_asname_map_.find(eventname) == index_asname_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asname_map_[eventname];
  event.args.push_back(arg0);
  event.args.push_back(arg1);
  char temp[32] = {0};
  snprintf(temp, sizeof(temp) - 1, "%d", arg2);
  event.args.push_back(temp);
  snprintf(temp, sizeof(temp) - 1, "%d", arg3);
  event.args.push_back(temp);
  push(event);
}

void System::push(const STRING& eventname, 
                  const char* arg0, 
                  const char* arg1,
                  const char* arg2) {
  if (index_asname_map_.find(eventname) == index_asname_map_.end()) return;
  vengine_game::event_t event;
  event.eventdefine = index_asname_map_[eventname];
  event.args.push_back(arg0);
  event.args.push_back(arg1);
  event.args.push_back(arg2);
  push(event);
}

void System::registerhandle(const STRING& name,
                            vengine_game::function_eventhandle handle,
                            uint32_t ownerdata) {
  if (!handle) return;
  vengine_game::eventdefine_t* eventdefine = index_asname_map_[name];
  if (!eventdefine) return;
  eventdefine->listenfunction_notify.push_back(
      std::make_pair(handle, ownerdata));
}

void System::processall() {
  //处理慢速队列
  if (!delayquene_.empty()) {
    const uint32_t kWorkStep = 2;
    uint32_t now_tickcount = procedure::Base::timesystem_->get_tickcount();
    uint32_t step_tickcount = procedure::Base::timesystem_->get_difftime(
        last_tickcount_, now_tickcount);
    if (step_tickcount > kWorkStep) {
      last_tickcount_ = now_tickcount;
      const vengine_game::event_t& event = *(delayquene_.begin());
      process(event);
      delayquene_.erase(delayquene_.begin());
    }
  }

  register std::list<vengine_game::event_t>::iterator iterator;
  register std::list<vengine_game::event_t>::iterator prev_iterator;
  for (iterator = queue_.begin(); iterator != queue_.end(); ++iterator) {
    const vengine_game::event_t& event = *iterator;
    bool multipushed = false; //是否有同样的事件已经处理过
    for (prev_iterator = queue_.begin(); 
         prev_iterator != iterator; 
         ++prev_iterator) {
      if (*prev_iterator == *iterator) {
        multipushed = true;
        break;
      }
    } //for loop
    if (multipushed) continue;
    process(event);
  } //for loop
  queue_.clear(); //普通队列一帧内处理完
}

void System::process(const vengine_game::event_t& event) {
  vengine_game::eventdefine_t* eventdefine = event.eventdefine;
  if (!eventdefine) return;
  if (!eventdefine->listenfunction_notify.empty()) {
    vengine_game::eventdefine_t::registerstruct::iterator iterator;
    for (iterator = eventdefine->listenfunction_notify.begin();
         iterator != eventdefine->listenfunction_notify.end();
         ++iterator) {
      if ((*iterator).first) {
        (*iterator).first(&event, (*iterator).second);
      }
    } //for loop
  }
}

void System::unregisterhandle(const STRING& name,
                            vengine_game::function_eventhandle handle,
                            uint32_t ownerdata) {
  if (!handle) return;
  vengine_game::eventdefine_t* eventdefine = index_asname_map_[name];
  if (!eventdefine) return;
  eventdefine->listenfunction_notify.remove(
      std::make_pair(handle, ownerdata));
}


};
