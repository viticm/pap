#include "vgui/creature/head/board/behit_manager.h"

namespace vgui_creature {

namespace head_board {

BeHitManager* BeHitManager::self_ = NULL;

BeHitManager::BeHitManager() {
  self_ = this;
  CEGUI::Window* window = 
    CEGUI::WindowManager::getSingleton().loadWindowLayout(
        "Schema\\BeHit.layout.xml");
  window = CEGUI::WindowManager::getSingleton().getWindow("auto_BeHitBoard");
  CEGUI::IFalagardBeHitBoard* behit_window = 
    dynamic_cast<CEGUI::IFalagardBeHitBoard*>(
        dynamic_cast<CEGUI::FalagardBeHitBoard*>(window));
  uint32_t i;
  for (i = 0; i < CEGUI::MAX_MOVE_TYPE_NUMBER; ++i) {
    behit_data_[i].xspeed = float(behit_window->getXSpeed(i));
    behit_data_[i].yspeed = float(behit_window->getYSpeed(i));
    behit_data_[i].xposition = float(behit_window->getXPos(i));
    behit_data_[i].yposition = float(behit_window->getYPos(i));
    behit_data_[i].xacceleration = float(behit_window->getXAcceleration(i));
    behit_data_[i].yacceleration = float(behit_window->getYAcceleration(i));
    behit_data_[i].alphamode = behit_window->getAlpha(i);
    behit_data_[i].maxlife = behit_window->getLife(i);
    behit_data_[i].movemode = behit_window->getMoveMode(i);
    behit_data_[i].usetemp_position = behit_window->getTempPosUse(i);
  }
  
  for (i = 0; i < CEGUI::MAX_COLOR_TYPE_NUMBER; ++i) {
    colortype_[i] = behit_window->getColorType(i);
    back_colortype_[i] = behit_window->getBackColorType(i); 
  }

  for (i = 0; i < CEGUI::MAX_TEMP_TYPE_NUMBER; ++i) {
    temppoint_[i] = behit_window->getTempPos(i);
  }
  normalsize_ = behit_window->getNormalSize();
  doublesize_ = behit_window->getDoubleSize();
  doubleend_size_ = behit_window->getDoubleEndSize();
  doubletime_ = behit_window->getDoubleTime();
  CEGUI::WindowManager::getSingleton().destroyWindow("BeHitBoard");
  count_ = 0;
}

BeHitManager::~BeHitManager() {
  std::list<BeHit*>::iterator iterator;
  for (iterator = windowlist_.begin(); 
       iterator != windowlist_.end();
       ++iterator) {
    BeHit* item = (*iterator);
    if (item) {
      delete item;
      item = NULL;
    }
  }
  return windowlist_.clear();
}

//一个没有用得窗口
BeHit* BeHitManager::get_freewindow() {
  std::list<BeHit*>::iterator iterator;
  for (iterator = windowlist_.begin(); 
       iterator != windowlist_.end();
       ++iterator) {
    if (false == (*iterator)->is_inuse) {
      return (*iterator);
    }
  }
  return newwindow();
}

//告诉管理器,有一个窗口释放了.
void BeHitManager::freewindow(BeHit* window) {
  std::list<BeHit*>::iterator iterator;
  for (iterator = windowlist_.begin(); 
       iterator != windowlist_.end();
       ++iterator) {
    if ((*iterator) == window) {
      (*iterator)->inuse(false);
      break;
    }
  }
}

//得到一个新的窗口
BeHit* BeHitManager::newwindow() {
  BeHit* behit = new BeHit();
  snprintf(behit->windowname_, 
           sizeof(behit->windowname_) - 1, 
           "BeHitBoard_%d", 
           count_);
  behit->window_ = 
    CEGUI::WindowManager::getSingleton().createWindow("WoWLook/BeHitBoard", 
                                                      behit->windowname_);
  behit->window_->setProperty("RiseOnClick", "False");
  behit->window_->setProperty("HorzFormatting", "HorzCentred");
  behit->window_->setProperty("MouseHollow", "True");
  behit->window_->setProperty("FitType", "Bottom");
  windowlist_.push_back(behit);
  ++count_;
  return behit;
}

} //namespace head_board

} //namespace vgui_creature
