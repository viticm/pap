#include "CEGUIWindow.h"
#include "CEGUIWindowManager.h"

#include "FalActionButton.h"
#include "FalSuperTooltip.h"
#include "FalagardMeshWindow.h"
#include "FalagardComplexWindow.h"
#include "FalChatHistory.h"

#include "LuaPlus.h"

#include "vengine/kernel/base.h"
#include "vengine/db/system.h"
#include "vengine/db/structs/all.h"
#include "vengine/script/system.h"
#include "vengine/capability/profile.h"
#include "vengine/game/object/basesystem.h"
#include "vengine/game/eventdefine.h"
#include "vengine/variable/system.h"
#include "vengine/sound/system.h"

#include "vgui/script/base.h"
#include "vgui/luacontrol/all.h"
#include "vgui/string/system.h"
#include "vgui/base/system.h"

#include "vgui/window/manager.h"

namespace vgui_window {

CEGUI::Window* Manager::background_sheet_ = NULL;
Manager* Manager::self_ = NULL;

//初始化窗口管理器
Manager::Manager() {
  self_ = this;
}

Manager::~Manager() {
  itemlist::iterator iterator;
  for (iterator = itemlist_.begin(); iterator != itemlist_.end(); ++iterator) {
    if ((*iterator)) {
      delete (*iterator);
      *iterator = NULL;
    }
  }
  itemlist_.clear();
}

void Manager::init() { //窗口管理器初始化
	background_sheet_ = CEGUI::WindowManager::getSingleton().createWindow(
      (CEGUI::utf8*)"DefaultGUISheet", 
      (CEGUI::utf8*)"__BACKGOUNDSHEET__");
  background_sheet_->setMouseHollow(true);
  background_sheet_->moveToFront();
  background_sheet_->setDistributesCapturedInputs(true);
  CEGUI::System::getSingleton().setGUISheet(background_sheet_);
  
  //ui load
  vengine_db::System* filedb_system = 
    dynamic_cast<vengine_db::System*>(g_kernel->getnode("bin\\dbc"));
  VENGINE_ASSERT(filedb_system);
  const vengine_db::File* layoutdefine = filedb_system->get(
      vengine_db::structs::ui::kLayoutDefineId);
  typedef vengine_db::structs::ui::layoutdefine_t layoutdefine_t;
  uint32_t i;
  for (i = 0; 
       i < static_cast<uint32_t>(layoutdefine->get_record_number()); 
       ++i) {
    const layoutdefine_t* line = 
      reinterpret_cast<layoutdefine_t*>(layoutdefine->search_line_equal(i));
    //产生一个新的window item
    Item* item = new Item(line);
    item->set_openclose_sound(line->opensound, line->closesound);
    //窗口预加载
    item->pre_loadwindow();
    itemlist_.push_back(item);
  }
}

void Manager::hideall() {
  itemlist::iterator iterator;
  for (iterator = itemlist_.begin(); iterator != itemlist_.end(); ++iterator) {
    (*iterator)->show(false);
  }
}

bool Manager::isshow(const char* uiname, const char* childname) {
  VENGINE_ASSERT(uiname);
  itemlist::iterator iterator;
  for (iterator = itemlist_.begin(); iterator != itemlist_.end(); ++iterator) {
    if (0 == strcmp((*iterator)->get_windowname(), uiname)) {
      if (NULL == childname) {
        return (*iterator)->is_windowshow();
      }
      else {
        return (*iterator)->is_child_windowshow(childname);
      }
    }
  }
  return false;
}

void Manager::demisetest(Item* item, bool show) {
  if (item->is_candemise() && show) {
    switch (item->get_demisetype()) {
      case 2: {
        itemlist::iterator iterator;
        for (iterator = itemlist_.begin();
             iterator != itemlist_.end();
             ++iterator) {
          if (2 == (*iterator)->get_demisetype()) { //关掉所有的是2的窗口
            //如果打开，而且是自己，并且已经打开了，就不处理 
            if (show && ((*iterator) == item) && (*iterator)->is_windowshow())
              return;
            if ((*iterator)->is_windowshow()) (*iterator)->show(false);
          }
        } //for loop
        break;
      }
      case 3: {
        itemlist::iterator iterator;
        for (iterator = itemlist_.begin();
             iterator != itemlist_.end();
             ++iterator) {
          if (3 == (*iterator)->get_demisetype()) { //关掉所有的是3的窗口
            //如果打开，而且是自己，并且已经打开了，就不处理 
            if (show && ((*iterator) == item) && (*iterator)->is_windowshow())
              return;
            if ((*iterator)->is_windowshow()) (*iterator)->show(false);
          }
        } //for loop
        break;
      }
      case 4:
        break;
      case 5: { //自适应
        item->positionself();
        break;
      }
      case 6: {
        closeall();
        break;
      }
      default:
        break;
    }
  }
}

//禅让窗口操作
void Manager::demise(Item* item, bool show) {
  demisetest(item, show);
}

bool Manager::closeall() {
  bool closeone = false;
  itemlist::iterator iterator;
  for (iterator = itemlist_.begin(); iterator != itemlist_.end(); ++iterator) {
    //如果打开，而且是自己，而且已经打开了，就不处理
    if ((*iterator)->get_demisetype() != 0 &&
        (*iterator)->get_demisetype() != 7 &&
        (*iterator)->is_windowshow()) {
      if ((*iterator)->is_windowshow()) {
        (*iterator)->show(false);
        closeone = true;
      }
    }
  } //for loop
  return closeone;
}

void Manager::on_sizechange() {
  itemlist::iterator iterator;
  for (iterator = itemlist_.begin(); iterator != itemlist_.end(); ++iterator) {
    if ((*iterator)->is_windowshow()) (*iterator)->on_sizechange();
  }
}

void Manager::onescape() { //响应Esc键
  if (closeall()) return;
  //如果没有窗口显示了，就开开系统菜单
  g_game_eventsystem->push(vengine_game::event_id::kGameUIToggleSystemFrame);
  g_game_eventsystem->push(vengine_game::event_id::kGameUICloseSecondMenu, 
                           0, 
                           0);
}

void Manager::open(const STRING& name) {
  Item* item = finditem(name);
  if (item) item->show(true);
}

void Manager::close(const STRING& name) {
  Item* item = finditem(name);
  if (item) item->show(false);
}

void Manager::toggle(const STRING& name) {
  Item* item = finditem(name);
  if (item) {
    bool show = false == item->is_windowshow() ? true : false;
    item->show(show);
  }
}

Item* Manager::finditem(const STRING& childname) {
  itemlist::iterator iterator;
  for (iterator = itemlist_.begin(); iterator != itemlist_.end(); ++iterator) {
    if ((*iterator)->get_windowname() == childname) return (*iterator);
  }
  return NULL;
}

bool Manager::reloadscript(const char* uiname) {
  itemlist::iterator iterator;
  for (iterator = itemlist_.begin(); iterator != itemlist_.end(); ++iterator) {
    Item* item = *iterator;
    if (0 == strncmp(item->get_windowname(), uiname, 255 )) {
      item->reloadscript();
      return true;
    }
  }
  return false;
}

} //namespace vgui_window
