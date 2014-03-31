#include "CEGUIWindowManager.h"
#include "CEGUIWindow.h"
#include "CEGUIUDim.h"
#include "elements/CEGUIProgressBar.h"
#include "CEGUIAnimateManager.h"
#include "FalagardAnimate.h"
#include "elements/CEGUIStaticImage.h"
#include "CEGUIPropertyHelper.h"
#include "CEGUIColourRect.h"
#include "elements/CEGUIPushButton.h"
#include "CEGUIPropertyHelper.h"
#include "FalagardSelfFitWindow.h"
#include "IFalagardSelfFitWindow.h"
#include "FalButton.h"

#include "vengine/db/system.h"
#include "vengine/db/struct/all.h"
#include "vgui/window/manager.h"
#include "vgui/creature/head/board/behit.h"
#include "vgui/creature/head/board/behit_manager.h"
#include "vgui/creature/head/board/system.h"

#include "vgui/creature/head/board/base.h"

namespace vgui_creature {

namespace head_board {

Base::Base(int32_t index) {
  /** variables init { **/
  window_ = NULL;
  namewindow_ = NULL;
  countrytitle_window_ = NULL;
  guildtitle_window_ = NULL;
  titlewindow_ = NULL;
  salewindow_ = NULL;
  show_ = true;
  show_hplevel_ = false;
  show_levelicon_ = false;
  showstall_ = false;
  leaderflag_ = false;
  teamflag_ = false;
  countrytitle_ = false;
  guildtitle_ = false;
  title_ = false;
  titletype_ = kTitleTypeDimness;
  guildposition_ = kGuildPositionNone;
  /** } variables init **/
  debugindex_ = index;
  lastx_ = lasty_ = -100;

  window_ = 
    CEGUI::WindowManager::getSingleton().createWindow("WoWLook/CreatureBoard");
  VENGINE_ASSERT(window_);

  //设置大小
  window_->setProperty("Position", "x:0 y:0");
  window_->setProperty("Size", "w:1 h:1");

  //玩家名称
  namewindow_ = CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_playername__");
  namewindow_->hide();

  //血条和等级的背景
  hplevel_window_ = CEGUI::WindowManager::getSingleton().getWindow(
      window_->getName() + "__auto_playerhplevel__");
  hplevel_window_->hide();

  //血条
  hpwindow_ = CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_playerhp__");

  //等级
  leveltext_window_ = CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_playerleveltext__");
  levelicon_window_ = CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_playerlevelico__");


  //PK标记（只有主角显示）
  pkwindow_ = CEGUI::WindowManager::getSingleton().getWindow(
      window_->getName() + "__auto_playerpktag__");

  //摆摊按钮
  salewindow_ = CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_salessign__");
  salewindow_->subscribeEvent(CEGUI::PushButton::EventClicked, 
    CEGUI::Event::Subscriber(&handle_salesign_clicked, this));


  //国家称号
  countrytitle_window_ = CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_playercountrytitle__");
  
  //帮会称号
  guildtitle_window_ = CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_playerguildtitle__");

  //称号
  titlewindow_ = CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_playertitle__");

  //国家标记
  countryflag_ = CEGUI::WindowManager::getSingleton().getWindow(
    windowname_->getName() + "__auto_countryflag__");

  //帮派权限小图标
  guildflag_ = CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_bangpaiflag__");

  //队长标志
  leaderflag_ = CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_leaderflag__");

  // 聊天泡泡
  paopao_ =  CEGUI::WindowManager::getSingleton().getWindow(
    window_->getName() + "__auto_paopao__");

  infostate_ = kPlayerInfoStateNormal;
  missionstate_ = -1;
}

Base::~Base() {
  CEGUI::WindowManager::getSingleton().destroyWindow(window_);
}

void Base::reset() {
  showstall_ = false;
  leaderflag_ = false;
  teamflag_ = false;
  name_ = "";
  
  namewindow_->setText("");
  namewindow_->hide();

  hplevel_window_->hide();
  hpwindow_->hide();
  leveltext_window_->hide();
  levelicon_window_->hide();

  salewindow_->setText("");
  salewindow_->hide();

  countrytitle_window_->setText("");
  countrytitle_window_->hide();

  guildtitle_window_->setText("");
  guildtitle_window_->hide();

  titlewindow_->setText("");
  titlewindow_->hide();

  countryflag_->hide();
  leaderflag_->hide();
  guildflag_->hide();
  pkwindow_->hide();

  paopao_->setText("");
  paopao_->hide();

  window_->hide();
}

void Base::destroy() {
  if (System::getself()) System::getself()->destroy(this);
}

vengine_math::base::twofloat_vector_t Base::getposition() {
  CEGUI::Point point= CEGUI::PropertyHelper::stringToPoint(
      namewindow_->getProperty("FitPosition"));
  return vengine_math::base::twofloat_vector_t(point.d_x, point.d_y);
}

//设置在屏幕上的坐标(像素)
void Base::setposition(float x, float y) {
  float alpha = 1.0f;
  if (distance_ > System::getself()->get_maxdispear_distance()) {
    window_->hide();
    return;
  }
  if (distance_ > System::getself()->get_maxdistance()) {
    alpha -= (distance_ - System::getself()->get_maxdistance()) / 
      (System::getself()->get_maxdispear_distance() - 
       System::getself()->get_maxdistance());
  }
  CEGUI::Point point(x, y);
  float offset = 0;
  float _y = point.d_y;
  CEGUI::Size size;
  //判断是否要显示
  if (show_hplevel_) {
    if (hplevel_window_ && hpwindow_) {
      //计算位置
      offset = hplevel_window_->getAbsoluteHeight();
      point.d_x += offset;
      point.d_y -= hplevel_window_->getAbsoluteHeight() / 2.0f;
      hplevel_window_->setPosition(CEGUI::Absolute, point);

      //血量
      hpwindow_->setPosition(CEGUI::Absolute, point);

      //进度设置
      (dynamic_cast<CEGUI::ProgressBar*>(hpwindow_))
        ->setProgress(hpprogross_);
    }
  }

  //恢复x偏移
  point.d_x = x;
  point.d_y = y;
  point.d_x += offset;
  (dynamic_cast<CEGUI::IFalagardSelfFitWindow*>(
    dynamic_cast<CEGUI::FalagardSelfFitWindow*>(namewindow_)))
    ->setCenter(point);
  offset -= namewindow_->getAbsoluteHeight();
  
  //名字
  if (namewindow_->isVisible() && !(namewindow_->getText().empty())) {
    window_->show();
    debuginfo();
  }
  else {
    //摆摊状态时，其他玩家名字不显示时，信息板还要显示
    if (false == showstall_) {
      window_->hide();
    }
    else {
      window_->show();
    }
  }
  
  //级别显示在玩家名字后面
  if (show_hplevel_) {
    CEGUI::Point levelposition = namewindow_->getAbsolutePosition(); 
    CEGUI::Size namesize = namewindow_->getAbsoluteSize();
    levelposition.d_x += namesize.d_width;
    (dynamic_cast<CEGUI::IFalagardSelfFitWindow*>(
      dynamic_cast<CEGUI::FalagardSelfFitWindow*>(leveltext_window_)))
      ->setCenter(levelposition);
    leveltext_window_->setPosition(CEGUI::Absolute, levelposition);
    levelicon_window_->setPosition(CEGUI::Absolute, levelposition);
    if (!show_levelicon_) {
      leveltext_window_->show();
    }
    else {
      size = namewindow_->getAbsoluteSize();
      size.d_width = size.d_height;
      levelicon_window_->setSize(CEGUI::Absolute, size);
      levelicon_window_->show();
    }
  }

  //国家称号
  if (countrytitle_ && !(countrytitle_window_->getText().empty())) {
    point.d_y = _y + offset;
    (dynamic_cast<CEGUI::IFalagardSelfFitWindow*>(
      dynamic_cast<CEGUI::FalagardSelfFitWindow*>(countrytitle_window_)))
      ->setCenter(point);
    offset -= countrytitle_window_->getAbsoluteHeight();
    countrytitle_window_->show();
  }

  //帮会称号
  if (guildtitle_ && !(guildtitle_window_->getText().empty())) {
    point.d_y = _y + offset;
    (dynamic_cast<CEGUI::IFalagardSelfFitWindow*>(
      dynamic_cast<CEGUI::FalagardSelfFitWindow*>(guildtitle_window_)))
      ->setCenter(point);
    guildtitle_window_->show();
  }

  //称号
  if (title_ && !(titlewindow_.getText().empty())) {
    point.d_y = _y + offset;
    (dynamic_cast<CEGUI::IFalagardSelfFitWindow*>(
      dynamic_cast<CEGUI::FalagardSelfFitWindow*>(titlewindow_)))
      ->setCenter(point);
    titlewindow_->show();
  }

  //摆摊
  if (salewindow_->isVisible()) {
    point.d_y = _y + offset;
    salewindow_->setProperty("HookPosition", 
                             CEGUI::PropertyHelper::pointToString(point));
    (dynamic_cast<CEGUI::PushButton*>(salewindow_))->resizeWithText();
    offset -= salewindow_->getAbsoluteHeight();
  }

  //聊天泡泡
  if (paopao_->isVisible()) {
    point.d_y = _y + offset;
    (dynamic_cast<CEGUI::IFalagardSelfFitWindow*>(
      dynamic_cast<CEGUI::FalagardSelfFitWindow*>(paopao_)))
      ->setCenter(point);
    offset -= paopao_->getAbsoluteHeight();
  }

  //PK标识，任务标识
  if (pkwindow_->isVisible()) {
    CEGUI::Size pksize;
    offset -= pkwindow_->getAbsoluteHeight();
    point.d_x = x - pkwindow_->getAbsoluteHeight() / 2.0f;
    point.d_y = _y + offset;
    pksize = CEGUI::AnimateManager::getSingleton().getAnimate(
        (CEGUI::utf8*)"questsign_accept" )->getSize();
    pkwindow_->setSize(CEGUI::Absolute, pksize);
    pkwindow_->>setPosition(CEGUI::Absolute, point);
  }
  
  //国家标识
  size = namewindow_->getAbsoluteSize();
  point = namewindow_->getAbsolutePosition();

  point.d_x -= size.d_height;
  countryflag_->setposition(CEGUI::Absolute, point);

  size.d_width = size.d_height;
  countryflag_->setSize(CEGUI::Absolute, size);

  //队长标识
  size = namewindow_->getAbsoluteSize();
  point = namewindow_->getAbsolutePosition();
  CEGUI::Size leveltext_size = leveltext_window_->getAbsoluteSize();
  point.d_x += size.d_width;
  point.d_y += leveltext_size.d_width;
  leaderflag_->setPosition(CEGUI::Absolute, point);
  size.d_width = size.d_height;
  leaderflag_->setSize(CEGUI::Absolute, size);

  //帮派权限图标标的位置
  size = namewindow_->getAbsoluteSize();
  point = namewindow_->getAbsolutePosition();
  point.d_x -= size.d_height;
  guildflag_->setPosition(CEGUI::Absolute, point);
  size.d_width = size.d_height;
  guildflag_->setSize(CEGUI::Absolute, size);

  //透明度设置
  countryflag_->setAlpha(alpha);
  guildflag_->setAlpha(alpha);
  leaderflag_->setAlpha(alpha);
  pkwindow_->setAlpha(alpha);
  salewindow_->setAlpha(alpha);
  namewindow_->setAlpha(alpha);
  titlewindow_->setAlpha(alpha);
  countrytitle_window_->setAlpha(alpha);
  guildtitle_window_->setAlpha(alpha);

  switch (infostate_) {
    case kPlayerInfoStateNormal:
      break;
    case kPlayerInfoStateDie: {
      namewindow_->setProperty("TextColor", 
          CEGUI::PropertyHelper::colourToString(
            CEGUI::colour( 0.5,0.5,0.5, alpha))); 
      break;
    }
    default:
      break;
  }
}

void Base::show(bool flag) {
  if (flag && !(namewindow_->getText().empty())) {
    window_->show();
    window_->requestRedraw();
    namewindow_->requestRedraw();
    if (show_hplevel_) {
      hplevel_window_->requestRedraw();
      hpwindow_->requestRedraw();
      if (!show_levelicon_) {
        leveltext_window_->requestRedraw();
      }
      else {
        levelicon_window_->requestRedraw();
      }
    }
    if (countrytitle_) countrytitle_window_->requestRedraw();
    if (guildtitle_) guildtitle_window_->requestRedraw();
    if (title_) titlewindow_->requestRedraw();
    guildflag_->requestRedraw();
    countryflag_->requestRedraw();
    pkwindow_->requestRedraw();
    if (!showstall_) salewindow_->hide();
  }
  else {
    window_->hide();
    countrytitle_window_->hide();
    guildtitle_window_->hide();
    titlewindow_->hide();
  }
  show_ = flag;
}

void Base::showattribute(bool flag) {
  show_hplevel_ = flag;
}

void Base::showtitle(bool flag, uint16_t type) {
  switch(type) {
    case 1: { //国家
      if (flag) {
        countrytitle_ = true;
      }
      else {
        countrytitle_ = false;
        countrytitle_window_->hide();
      }
      break;
    }
    case 2: { //帮会
      if (flag) {
        guildtitle_ = true;
      }
      else {
        guildtitle_ = false;
        guildtitle_window_->hide();
      }
      break;
    }
    case 3: { //玩法
      if (flag) {
        title_ = true;
      }
      else {
        title_ = false;
        titlewindow_->hide();
      }
      break;
    }
    default:
      break;
  }
}

void Base::debuginfo() {
  CEGUI::Point position = namewindow_->getAbsolutePosition();
  if (position.d_x != lastx_ || position.d_y != lasty_) {
    //debug print
  }
  lastx_ = position.d_x;
  lasty_ = position.d_y;
}

void Base::setname(const char* name) { //设置名字
  name_ = name;
  update_nameelement();
}

void Base::set_HPprogress(uint32_t now, uint32_t max) { //设置
  if (0 == hp || 0 == max) {
    hpprogross_ = 1.0f;
  }
  else {
    hpprogross_ = static_cast<float>(now / max);
  }
}

void Base::set_HPprogress(float percent) {
  hpprogross_ = percent;
}

void Base::setlevel(uint8_t level, uint8_t type) {
  if (1 == type) { //等级图标
    show_levelicon_ = true;
    return;
  } 
  //设置文字
  char buffer[64] = {0};
  snprintf(buffer, sizeof(buffer) - 1, "(%d)", level);
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(buffer, str);
  if (leveltext_window_ && !(str.empty()))
    leveltext_window_->setText(str);
}

void Base::set_paopao_text(const char* paopao) {
  if (!vgui_base::System::getself()->is_paopap_active()) return;
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(paopao, str);
  if (paopao_) {
    paopao_->show();
    paopao_->setText(str);
  }
}

void Base::set_countryflag(uint8_t flag) {
  switch (flag) {
    case 0: {
      (dynamic_cast<CEGUI::StaticImage*>(countryflag_))->setImage(
          (CEGUI::utf8*)"blood", (CEGUI::utf8*)"blood_xinyue");
      countryflag_->show();
      break;
    }
    case 1: {
      (dynamic_cast<CEGUI::StaticImage*>(countryflag_))->setImage(
          (CEGUI::utf8*)"blood", (CEGUI::utf8*)"blood_jinzhang");
      countryflag_->show();
      break;
    }
    case 2: {
      (dynamic_cast<CEGUI::StaticImage*>(countryflag_))->setImage(
          (CEGUI::utf8*)"blood", (CEGUI::utf8*)"blood_damo");
      countryflag_->show();
      break;
    }
    case 3: {
      (dynamic_cast<CEGUI::StaticImage*>(countryflag_))->setImage(
          (CEGUI::utf8*)"blood", (CEGUI::utf8*)"blood_xueyu");
      countryflag_->show();
      break;
    }
    default:
      countryflag_->hide();
      break;
  }
}

void Base::settitle(const char* name, uint8_t type) { //设置称号
  if (0 == strlen(name)) {
    switch (titletype_) {
      case kTitleTypeCountry: {
        if (countrytitle_window_) {
          countrytitle_window_->setText("");
          countrytitle_window_->hide();
          break;
        }
      }
      case kTitleTypeGuild: {
        if (guildtitle_window_) {
          guildtitle_window_->setText("");
          guildtitle_window_->hide();
          break;
        }
      }
      case kTitleTypeSelfAdd: {
        if (titlewindow_) {
          titlewindow_->setText("");
          titlewindow_->hide();
          break;
        }
      }
      default:
        return;
    } //switch
  }

  STRING colortitle;
  CEGUI::String32 str;
  colortitle = title;
  titletype_ = type;
  vgui_string::System::getself()->parsestring_runtime(colortitle.c_str(), str);

  switch (titletype_) {
    case kTitleTypeCountry: {
      if (countrytitle_window_) countrytitle_window_->setText(str);
      break;
    }
    case kTitleTypeGuild: {
      if (guildtitle_window_) {
        guildtitle_window_->setText(str);
        switch (guildposition_) { //帮会位置
          case kGuildPositionNone:
            break;
          case kGuildPositionExcellence: { //精英
            ((CEGUI::StaticImage*)guildflag_)->setImage(
              (CEGUI::utf8*)"common2", 
              (CEGUI::utf8*)"Captain_Icon");
            guildflag_->hide();
            break;
          }
         case kGuildPositionOfficeholder: { //官员
            ((CEGUI::StaticImage*)guildflag_)->setImage(
              (CEGUI::utf8*)"common2", 
              (CEGUI::utf8*)"Captain_Icon");
            guildflag_->hide();
            break;
          }
         case kGuildPositionExcellence: { //帮主
            ((CEGUI::StaticImage*)guildflag_)->setImage(
              (CEGUI::utf8*)"common2", 
              (CEGUI::utf8*)"Captain_Icon");
            guildflag_->hide();
            break;
          }
          default:
            break;
        }
      }
      break;
    }
    case kTitleTypeSelfAdd: {
      if (titlewindow_) titlewindow_->setText(str);
      break;
    }
    default:
      break;
  } //switch
}

void Base::set_leaderflag(bool flag, uint8_t type) {
  if (name_.empty()) {
    namewindow_->setText("");
    window_->hide();
    return;
  }
  if (0 == type) {
    ((CEGUI::StaticImage*)leaderflag_)->setImage(
      (CEGUI::utf8*)"UIIcons",
      (CEGUI::utf8*)"Confraternity_Class2");
  }
  else if (1 == type) {
    ((CEGUI::StaticImage*)leaderflag_)->setImage(
      (CEGUI::utf8*)"UIIcons",
      (CEGUI::utf8*)"Icon_Captain_1");
  }
  if (flag) {
    if (false == showstall_) leaderflag_->show();
  }
  else {
    leaderflag_->hide();
  }
}

void Base::set_pkflag(uint8_t type, uint8_t state, bool flag) {
  if (pkwindow_->isVisible() && !flag) {
    pkwindow_->hide();
    return;
  }
  //如果当前对象是任务NPC，且任务状态没有变化的话，直接返回，
  //避免SetAnimate重新初始化播放起始时间，导致动画始终播放第一张图片
  if (1 == type && missionstate_ == state) {
    return;
  }
  else {
    missionstate_ = state;
  }
  if (0 == type) {
    ((CEGUI::StaticImage*)pkwindow_)->setImage(
      (CEGUI::utf8*)"blood", 
      (CEGUI::utf8*)"blood_xueyu");
  }
  else {
    switch (state) {
      case 0: {
        ((CEGUI::FalagardAnimate*)pkwindow_)->SetAnimate(
          (CEGUI::utf8*)"questsign_accept");
        break;
      }
      case 1: {
        ((CEGUI::FalagardAnimate*)pkwindow_)->SetAnimate(
          (CEGUI::utf8*)"questsign_un");
        break;
      }
      case 2: {
        ((CEGUI::FalagardAnimate*)pkwindow_)->SetAnimate(
          (CEGUI::utf8*)"questsign_accomplish");
        break;
      }
      default:
        break;
    }
  }
  if (flag) {
    pkwindow_->show();
  }
  else {
    pkwindow_->hide();
  }
}

void Base::set_saletext(const char* text) {
  CEGUI::String32 str;
  vgui_string::System::mbcs_to_utf8(text, str);
  if (salewindow_ != NULL) salewindow_->setText(str);
}

void Base::set_salesign(bool sign) {
  if (sign) {
    showstall_ = true;
    if (salewindow_) salewindow_->show();
  }
  else {
    showstall_ = false;
    if (salewindow_) salewindow_->hide();
  }
}

void Base::set_objectid(int32_t id) {
  objectid_ = id;
}

bool Base::handle_salesign_clicked(const CEGUI::EventArgs& event) {
  g_gameinterface->stall_opensale(objectid_);
  return false;
}

void Base::update_nameelement() {
  if (name_.empty()) {
    namewindow_->>setText("");
    window_->hide();
    return;
  }
  CEGUI::String32 str;
  vgui_string::System::getself()->parsestring_runtime(name_, str);
  if (namewindow_ && !(str.empty())) {
    namewindow_->show();
    namewindow_->setText(str);
    window_->hide();
  }
}

void Base::setstate(uint8_t state) {
  infostate_ = state;
}

void Base::showstall(bool isself) {
  show_hplevel_ = false;
  countrytitle_ = false;
  guildtitle_ = false;
  title_ = false;
  show_levelicon_ = false;

  if (true == isself) {
    namewindow_->show();
  }
  else {
    namewindow_->hide();
  }
  hplevel_window_->hide();
  leveltext_window_->hide();
  levelicon_window_->hide();
  countrytitle_window_->hide();
  guildtitle_window_->hide();
  titlewindow_->hide();
  leaderflag_->hide();
  guildflag_->hide();
  pkwindow_->hide();
  countryflag_->hide();
  set_salesign(true);
}

bool Base::isshow() {
  return show_;  
}

CEGUI::Window* Base::get_mainwindow() {
  return window_;
}

void Base::setdistance(float distance) {
  distance_ = distance;
}

void Base::set_titletype(uint8_t type) {
  titletype_ = type;
}

void Base::set_guildpposition(uint8_t position) {
  guildposition_ = position;
}

} //namespace head_board

} //namespace vgui_creature
