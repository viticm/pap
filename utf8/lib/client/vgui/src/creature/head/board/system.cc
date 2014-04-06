#include "CEGUIWindowManager.h"
#include "CEGUIPropertyHelper.h"
#include "vgui/window/manager.h"
#include "vgui/creature/head/board/base.h"
#include "vgui/creature/head/board/behit_manager.h"
#include "vgui/creature/head/board/system.h"

namespace vgui_creature {

namespace head_board {

CEGUI::Window* System::groundsheet_ = NULL;
System* System::self_ = NULL;

System::System() {
  self_ = this;
  behit_manager_ = NULL;
  maxdistance_ = 324;
  maxdispear_distance_ = 625;
}

System::~System() {
  //do nothing
}

System* System::getself() {
  return self_;
}

CEGUI::Window* System::get_clientscreen() {
  return groundsheet_;
}

void System::init() {
  release();
  behit_count_ = 0;
  behit_manager_ = new BeHitManager();
	groundsheet_ = CEGUI::WindowManager::getSingleton().createWindow(
      (CEGUI::utf8*)"DefaultGUISheet", 
      (CEGUI::utf8*)"__CREATUREBOARDSHEET__");
  groundsheet_->setMouseHollow(true);
  if (vgui_window::Manager::get_clientscreen()) {
    vgui_window::Manager::get_clientscreen()->addChildWindow(groundsheet_);
    groundsheet_->setProperty("RiseOnClick", "False");
    groundsheet_->moveToBack();
  }
}

void System::release() {
  //清除所有信息板窗口
  std::list<Base*>::iterator base_iterator;
  for (base_iterator = boardlist_.begin();
       base_iterator != boardlist_.end();
       ++base_iterator) {
    if (*base_iterator) {
      delete (*base_iterator);
      (*base_iterator) = NULL;
    }
  }
  boardlist_.clear();
  for (base_iterator = datapool_.begin();
       base_iterator != datapool_.end();
       ++base_iterator) {
    if (*base_iterator) {
      delete (*base_iterator);
      (*base_iterator) = NULL;
    }
  }
  datapool_.clear();
  if (behit_manager_) {
    delete behit_manager_;
    behit_manager_ = NULL;
  }
}

Base* System::create() { //创建一个新的头顶板
  Base* board = NULL;
  if (datapool_.empty()) {
    static int32_t index = 0;
    board = new Base(index++);
  }
  else {
    board = *(datapool_.begin());
    datapool_.erase(datapool_.begin());
  }

  board->reset();
  boardlist_.push_back(board);
  get_clientscreen()->addChildWindow(board->get_mainwindow());
  board->show(false);
  return board;
}

void System::destroy(Base* board) {
  if (!board) return;
  get_clientscreen()->removeChildWindow(board->get_mainwindow());
  //从链表中删除
  std::list<Base*>::iterator base_iterator;
  for (base_iterator = boardlist_.begin();
       base_iterator != boardlist_.end();
       ++base_iterator) {
    if ((*base_iterator) == board) {
      boardlist_.erase(base_iterator);
      //放入池
      datapool_.push_back(board);
      board->show(false);
      break;
    }
  }
}

void System::add_new_behit(bool doublehit, //是否为重击
                           const char* value, //显示的字符串
                           float startx, //实际的屏幕坐标
                           float starty, 
                           int32_t type, 
                           int32_t movetype) {
  if (behit_boardlist_.size() > 100) return;
  BeHit* behit = BeHitManager::getself()->get_freewindow();
  if (behit) {
    if (doublehit) {
      type += 20;
      movetype += 20;
    }
    behit->doublehit_ = doublehit;
    behit->colortype_ = BeHitManager::getself()->colortype_[type];
    behit->back_colortype_ = BeHitManager::getself()->back_colortype_[type];
    behit_data_t* behit_data = &BeHitManager::getself()->behit_data_[movetype];
    behit->xspeed_ = behit_data->xspeed;
    behit->yspeed_ = behit_data->yspeed;
    behit->xacceleration_ = behit_data->xacceleration;
    behit->yacceleration_ = behit_data->yacceleration;
    behit->maxlife_ = behit_data->maxlife;
    behit->alphamode_ = behit_data->alphamode;
    behit->movemode_ = behit_data->movemode;
    behit->usetemp_position_ = behit_data->usetemp_position;
    behit->startx_ = behit_data->xposition;
    behit->starty_ = behit_data->yposition;
    behit->movetype_ = movetype;
    if (behit->usetemp_position_) {
      //判断是不是已经占用位置了
      std::list<BeHit*>::iterator iterator;
      bool temp[CEGUI::MAX_TEMP_TYPE_NUMBER];
      int32_t i;
      for (i = 0; i < CEGUI::MAX_TEMP_TYPE_NUMBER; ++i) {
        temp[i] = false;
      }
      for (iterator = behit_boardlist_.begin();
           iterator != behit_boardlist_.end();
           ++iterator) {
        BeHit* item = (*iterator);
        //如果同是自己的类型
        if (behit->movetype_ == item->movetype_) {
          if (abs(int32_t(item->starty_ - behit->starty_))) {
            temp[item->tempposition_index_] = true;
          }
        }
      } //for loop

      for (i = 0; i < CEGUI::MAX_TEMP_TYPE_NUMBER; ++i) {
        if (!temp[i]) {
          behit->tempposition_index_ = i;
          behit->startx_ += BeHitManager::getself()->temppoint_[i].d_x;
          behit->starty_ += BeHitManager::getself()->temppoint_[i].d_y;
        }
      }
    }
    behit->inuse(true);
    behit->resetdata(value);
    behit->update();
    behit_boardlist_.push_back(behit);
  }
}

void System::tick() {
  std::list<BeHit*>::iterator iterator;
  for (iterator = behit_boardlist_.begin();
       iterator != behit_boardlist_.end();) { //++can't write here
    BeHit* item = (*iterator);
    item->update();
    if (item->life_ < 0) {
      std::list<BeHit*>::iterator iterator1 = iterator++;
      BeHitManager::getself()->freewindow(item);
      behit_boardlist_.erase(iterator1);
    }
    else {
      ++iterator;
    }
  }
}

float System::get_maxdistance() {
  return maxdistance_;
}

float System::get_maxdispear_distance() {
  return maxdispear_distance_;
}

} //namespace head_board

} //namespace vgui_creature
