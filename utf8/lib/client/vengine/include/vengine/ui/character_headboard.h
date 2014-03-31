/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id character_headboard.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-21 11:14:52
 * @uses vengine ui character headboard module
 */
#ifndef VENGINE_UI_CHARACTER_HEADBOARD_H_
#define VENGINE_UI_CHARACTER_HEADBOARD_H_

#include "vengine/config.h"
#include "vengine/math/base.h"

namespace vengine_ui {

//角色头顶信息
class VENGINE_API CharacterHeadBoard {

 public:
   virtual void destroy() = 0;
   virtual void setposition(float x, float y) = 0; //设置坐标（像素）
   virtual void show(bool flag) = 0; //显示/隐藏
   virtual void showattribute(bool flag) = 0; //显示属性，等级/血量/称号
   virtual void showtitle(bool flag, uint16_t type) = 0; //显示称号
   virtual void settitle(const char* name, uint8_t type) = 0; //设置称号
   virtual void setname(const char* name) = 0; //设置名称
   virtual void set_HPProgress(uint32_t now, uint32_t max) = 0; //设置血量
   virtual void set_HPProgress(float percent) = 0; //血量百分比
   virtual void setlevel(uint8_t level, uint8_t type) = 0; //设置等级
   virtual void set_countryflag(uint8_t flag) = 0; //国家标记--以后变为阵营
   virtual void set_leaderflag(bool flag, uint8_t type) = 0; //队长标记
   //设置PK|任务标记
   virtual void set_pkflag(uint8_t type, uint8_t state, bool flag) = 0;
   virtual void set_saletext(const char* text) = 0; //摆摊文字
   virtual void set_salesign(bool sign) = 0; //设置是否显示摆摊信息
   virtual void set_objectid(int32_t id) = 0; //设置对象ID
   virtual void setstate(uint8_t state) = 0; //玩家状态，正常|死亡
   virtual void setdistance(float distance) = 0; //设置信息与主角的距离
   virtual void set_paopao_text(const char* text) = 0; //聊天泡泡
   virtual vengine_math::base::twofloat_vector_t getposition() = 0; //屏幕位置
   virtual bool isshow() = 0; //是否显示
   virtual void showstall(bool isself) = 0; //显示摆摊信息

};

}; //namespace vengine_ui

#endif //VENGINE_UI_CHARACTER_HEADBOARD_H_
