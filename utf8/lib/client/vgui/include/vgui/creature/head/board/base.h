/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-30 11:30:08
 * @uses vgui creature head board base class
 *       cn: 生物（角色）头顶板信息
 */
#ifndef VGUI_CREATURE_HEAD_BOARD_BASE_H_
#define VGUI_CREATURE_HEAD_BOARD_BASE_H_

#include "vengine/ui/character_headboard.h"
#include "vgui/config.h"
#include "vgui/string/system.h"

namespace CEGUI {
class Window;
}; //namespace CEGUI

namespace vgui_creature {

namespace head_board {

typedef enum {
  kPlayerInfoStateNormal,
  kPlayerInfoStateDie
} playerinfo_state_enum;

class Base : public vengine_ui::CharacterHeadBoard {

 public:
   typedef enum {
     kTitleTypeDimness,
     kTitleTypeCountry,
     kTitleTypeGuild,
     kTitleTypeSelfAdd,
     kTitleTypeMenPai,
     kTitleTypeProfession,
     kTitleTypeMood,
     kTitleTypePlayerShop,
     kTitleTypeMax
   } titletype_enum; //称号类型 
   
   typedef enum {
     kGuildPositionNone,
     kGuildPositionExcellence, //精英
     kGuildPositionOfficeholder, //官员
     kGuildPositionChairman, //帮主
   } guild_position_enum;

 public: //--implement abstract class
   virtual void destroy();
   virtual void setposition(float x, float y); //设置坐标（像素）
   virtual void show(bool flag); //显示/隐藏
   virtual void showattribute(bool flag); //显示属性，等级/血量/称号
   virtual void showtitle(bool flag, uint16_t type) ; //显示称号
   virtual void settitle(const char* name, uint8_t type); //设置称号
   virtual void setname(const char* name); //设置名称
   virtual void set_HPprogress(uint32_t now, uint32_t max); //设置血量
   virtual void set_HPprogress(float percent); //血量百分比
   virtual void setlevel(uint8_t level, uint8_t type); //设置等级
   virtual void set_countryflag(uint8_t flag) ; //国家标记--以后变为阵营
   virtual void set_leaderflag(bool flag, uint8_t type); //队长标记
   //设置PK|任务标记
   virtual void set_pkflag(uint8_t type, uint8_t state, bool flag);
   virtual void set_saletext(const char* text); //摆摊文字
   virtual void set_salesign(bool sign); //设置是否显示摆摊信息
   virtual void set_objectid(int32_t id); //设置对象ID
   virtual void setstate(uint8_t state); //玩家状态，正常|死亡
   virtual void setdistance(float distance); //设置信息与主角的距离
   virtual void set_paopao_text(const char* text); //聊天泡泡
   virtual vengine_math::base::twofloat_vector_t getposition(); //屏幕位置
   virtual bool isshow(); //是否显示
   virtual void showstall(bool isself); //显示摆摊信息
 public:
   CEGUI::Window* get_mainwindow();
   void set_titletype(uint8_t type);
   void set_guildpposition(uint8_t position);

 protected:
   //必须显示
   CEGUI::Window* window_; //窗口指针
   CEGUI::Window* namewindow_; //名字指针

   //人物状态
   CEGUI::Window* hpwindow_; //血条
   CEGUI::Window* leveltext_window_; //等级
   CEGUI::Window* levelicon_window_; //等级
   CEGUI::Window* hplevel_window_; //血条等级背景

   //称号
   CEGUI::Window* countrytitle_window_; //国家称号
   CEGUI::Window* guildtitle_window_; //帮会称号
   CEGUI::Window* titlewindow_; //称号指针

   //图标
   CEGUI::Window* countryflag_; //国家
   CEGUI::Window* leaderflag_; //队长
   CEGUI::Window* pkwindow_; //PK

   //其他
   CEGUI::Window* salewindow_; //摆摊头顶的牌子
   CEGUI::Window* paopao_; //聊天泡泡
   CEGUI::Window* guildflag_; //帮会权限标志

   bool show_; //是否显示所有的信息
   bool show_hplevel_; //是否显示血条和等级
   bool show_levelicon_; //是否显示等级为图标
   bool leaderflag_; //队长标记
   bool teamflag_; //队长标记
   bool countrytitle_; //国家称号
   bool guildtitle_; //帮会称号
   bool title_; //玩法称号

   float hpprogross_; //血条比例

   bool showstall_; //是否显示摆摊
   int32_t objectid_; //对应的逻辑对象的ID
   
   STRING name_; //名字
   uint8_t titletype_; //称号类型
   uint8_t guildposition_; //帮会权限

   uint8_t infostate_;
   float distance_;
   float lastx_, lasty_;
   int32_t debugindex_;
   uint8_t missionstate_;

 protected:
   //捕获 "摆摊" 按钮按下通知
   bool handle_stallsign_clicked(const CEGUI::EventArgs& event);
   void update_nameelement(); //更新名称（考虑队长标志）
   void reset(); //从缓冲池取出后重置数据
   void debuginfo();

 private:
   friend class System;
   Base(int32_t index);
   virtual ~Base();

};

}; //namespace head_board

}; //namespace vgui_creature

#endif //VGUI_CREATURE_HEAD_BOARD_BASE_H_
