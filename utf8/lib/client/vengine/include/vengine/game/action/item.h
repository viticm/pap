/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id item.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 18:06:13
 * @uses vengine game action item class
 */
#ifndef VENGINE_GAME_ACTION_ITEM_H_
#define VENGINE_GAME_ACTION_ITEM_H_

#include "vengine/config.h"

namespace vengine_game {

namespace action {

typedef enum {
  kOperateTypeEmpty, //空
  kOperateTypeSkill, //战斗技能
  kOperateTypeItem, //物品
  kOperateTypeXinfa, //心法
  kOperateTypePetSkill, //宠物技能
  kOperateTypeEquip, //装备
  kOperateTypeChatMood, //聊天动作
  kOperateTypeMouseCommandRepair, //鼠标指令--修理
  kOperateTypeMouseCommandIdentify, //鼠标指令--鉴定
  kOperateTypeMouseCommandAddFriend, //鼠标指令--增加好友
  kOperateTypeChangeSet, //一键换装
  kOperateTypeMouseCommandExchange, //交易
} operatetype_enum;

class Reference;

class VENGINE_API Item {

 public:
   virtual int32_t getid() const = 0;
   virtual const char* getname() const = 0;
   virtual const char* geticon() const = 0;
   virtual void seticon(STRING& name) = 0;
   virtual vois set_checkstate(bool check) = 0;
   //添加引用
   virtual void addreference(Reference* reference, 
                             bool is_menu_toolbar = false) = 0;
   //移除引用
   virtual void removereference(Reference* reference) = 0;
   virtual operatetype_enum get_operatetype() const = 0;
   virtual const char* get_typestring() = 0;
   //对于战斗技能, 是技能表中的ID (DBC_SKILL_DATA)
   //对于生活技能，是生活技能表中的ID(DBC_LIFEABILITY_DEFINE)
   //对于物品，是物品表中的ID
   //对于心法，是心法表中的ID
   virtual int32_t get_defineid() const = 0;
   virtual int32_t getnumber() const = 0;
   //得到内部数据
   virtual void* get_internaldata() const = 0;
   //得到解释
   virtual const char* getdescription() const = 0;
   virtual int32_t get_cooldownid() const = 0;
   //得到所在容器的索引
   virtual int32_t get_positionindex() const = 0;
   //激活动作
   virtual void doaction() = 0;
   //激活子动作
   virtual void do_subaction() = 0;
   virtual bool isvalid() const = 0; //是否有效
   virtual bool isenable() const = 0; //是否激活
   virtual void enable() = 0;
   virtual void disable() = 0;
   virtual bool cooldown_isover() const = 0; //检查冷清是否结束
   //拖动结束
   virtual void notify_dragdrop_dragged(bool destory, 
                                        const char* targetname, 
                                        const char* sourcename) = 0;
   //显示tooltips
   virtual void notify_tooltips_show(int32_t left, 
                                     int32_t top, 
                                     int32_t right, 
                                     int32_t bottom) = 0;
   //隐藏tooltips
   virtual void notify_tooltips_hide() = 0;
   //查询逻辑属性
   virtual STRING get_attributevalue(const char* name) = 0;
};

}; //namespace action

}; //namespace vengine_game

#endif //VENGINE_GAME_ACTION_ITEM_H_
