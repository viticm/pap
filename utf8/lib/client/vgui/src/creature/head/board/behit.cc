#include "CEGUIWindowManager.h"
#include "FalagardBeHitBoard.h"
#include "vengine/time/system.h"
#include "vgui/string/system.h"
#include "vgui/creature/head/board/behit_manager.h"
#include "vgui/creature/head/board/system.h"
#include "vgui/creature/head/board/behit.h"

namespace vgui_creature {

namespace head_board {

BeHit::BeHit() {
  life_ = 0;
  alpha_ = 1.0f;
  doubletime_ = 1000;
  is_inuse_ = false;
  tempposition_index_ = 0;
}

BeHit::~BeHit() {
  is_inuse_= false;
  CEGUI::WindowManager::getSingleton().destroyWindow(windowname_);
}

void BeHit::resetdata(const char* text) {
  CEGUI::String32 str;
  char temp[128] = {0};
  //如果设置了背景颜色，则给输出文字字符串加上背景颜色附加字符串
  if (0 == back_colortype_.getARGB()) {
    vgui_string::System::getself()->parsestring_runtime(text, str);
  }
  else {
		snprintf(temp,
             sizeof(temp) - 1,
            "#e%02X%02X%02X%s",
            int32_t(back_colortype_.getRed() * 255),
            int32_t(back_colortype_.getGreen() * 255), 
            int32_t(back_colortype_.getBlue() * 255), 
            text);
    vgui_string::System::getself()->parsestring_runtime(text, str);
  }
  if (doublehit_) {
    zoomon_ = true;
    scale_ = BeHitManager::getself()->get_doubleend_size();
  }
  else {
    zoomon_ = false;
    scale_ = BeHitManager::getself()->get_normalsize();
  }
  (dynamic_cast<CEGUI::IFalagardBeHitBoard*>
   (dynamic_cast<CEGUI::FalagardBeHitBoard*>(window_)))
    ->SetTextColor(colortype_);
  (dynamic_cast<CEGUI::IFalagardBeHitBoard*>
   (dynamic_cast<CEGUI::FalagardBeHitBoard*>(window_)))
    ->setTextScale(scale_, scale_);
  window_->setText(str);
  //如果渐变消失属性设置为false，则一定要重新设置alpha的值，否则会导致冒字不显示
  if (!alphamode_) {
    alpha_ = 1.0f;
    window_->setAlpha(alpha_);
  }
}

void BeHit::update() {
  xspeed_ += (float(xacceleration_) / 1000) * 
             g_timesystem->get_lastframe_time();
  yspeed_ += (float(yacceleration_) / 1000) * 
             g_timesystem->get_lastframe_time();
  startx_ += (float(xspeed_) / 1000) * g_timesystem->get_lastframe_time();
  starty_ += (float(yspeed_) / 1000) * g_timesystem->get_lastframe_time();
  life_ = static_cast<int32_t>(g_timesystem->get_lastframe_time());
  if (alphamode_) alpha_ = float(life_) / float(maxlife_);
  if (doublehit_) {
    if (zoomon_) {
      scale_ += doubletime_ / g_timesystem->get_lastframe_time();
      if (scale_ > BeHitManager::getself()->get_doublesize()) {
        zoomon_ = false;
      }
    }
    else {
      scale_ -= doubletime_ / g_timesystem->get_lastframe_time(); 
    }
    if (scale_ < BeHitManager::getself()->get_doubleend_size()) {
      scale_ = BeHitManager::getself()->get_doubleend_size();
      doublehit_ = false;
    }
    (dynamic_cast<CEGUI::IFalagardBeHitBoard*>
     (dynamic_cast<CEGUI::FalagardBeHitBoard*>(window_)))
      ->setTextScale(scale_, scale_);
  }
  if (life_ > 0) {
    CEGUI::Point position;
    position.d_x = float(startx_);
    position.d_y = float(starty_);
    (dynamic_cast<CEGUI::IFalagardBeHitBoard*> 
     (dynamic_cast<CEGUI::FalagardBeHitBoard*>(window_))) 
      ->setDisplayCenter(position.d_x, position.d_y);
    if (alphamode_) window_->setAlpha(alpha_);
  }
}

void BeHit::inuse(bool flag) {
  is_inuse_ = flag;
  if (is_inuse_) {
    System::get_clientscreen()->addChildWindow(window_);
  }
  else {
    System::get_clientscreen()->removeChildWindow(window_);
  }
}

bool BeHit::is_inuse() {
  return is_inuse_;
}

} //namespace head_board

} //namespace vgui_creature
