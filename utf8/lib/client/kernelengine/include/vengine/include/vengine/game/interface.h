/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id interface.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-25 14:45:06
 * @uses vengine game interface module
 *       cn: 整个游戏的外部控制接口类，
 *           所有的外部模块需要通过这个接口来控制游戏的数据和控制
 */
#ifndef VENGINE_GAME_INTERFACE_H_
#define VENGINE_GAME_INTERFACE_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"
#include "vengine/math/base.h"

//引用客户端的类 --不赞成使用过多这种引用
namespace object {

namespace logic {

class Base;

}; //namespace logic

}; //namespace object

namespace vengine_game {

//引用本模块中的类
namespace action {

class Item;

}; //namespace action

namespace object {

class Item;

}; //namespace action

class VENGINE_API Interface : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(vengine_game_Interface);

 public:
   //物体操作系列
   virtual void object_selectas_maintarget(int32_t objectid, 
                                           uint8_t type = 0) = 0;
   //显示右键菜单
   virtual void object_show_contextmenu(int32_t objectid,
                                        bool showself = false) = 0;

   /** 主角操作系列 **/
   //移动到场景中某个位置
   virtual void player_moveto(
       const vengine_math::base::twofloat_vector_t& aimposition) = 0;
   virtual void player_moveto(
       uint16_t sceneid,
       const vengine_math::base::twofloat_vector_t& aimposition) = 0;
   //使用技能(瞬发)
   virtual void player_useskill(uint32_t skillid) = 0;
   //使用技能(对某个object)
   virtual void player_useskill(uint32_t skillid, int32_t objectid) = 0;
   //使用技能(对某个范围)
   virtual void player_useskill(
       uint32_t skillid,
       const vengine_math::base::twofloat_vector_t& position) = 0;
   //使用技能(对某个队友(GUID))
   virtual void player_useskill(uint32_t skillid, const uint32_t& aim) = 0;
   virtual void player_useskill(
       uint32_t skillid,
       const vengine_math::base::twofloat_vector_t& position,
       const uint32_t& aim) = 0;
   //使用技能(对某个方向)
   virtual void player_useskill(uint32_t skillid, float& direct) = 0;
   //合成某配方
   virtual void player_use_lifeability(uint16_t prescriptionid, 
                                       uint32_t makecount) = 0;
   virtual void player_use_lifeability(uint16_t prescriptionid) = 0;
   //销毁身上的装备
   virtual void player_destroyequip(const object::Item* equip) = 0;
   //卸载身上的装备
   virtual void player_unequip(const object::Item* equip) = 0;
   //请求升级
   virtual void player_ask_levelup() = 0;
   //请求洗一级属性点
   virtual void player_ask_cleanbase_attributepoint() = 0;
   //谈话(对某个NPC)
   virtual void player_speak(int32_t objectid) = 0;
   //自动寻路
   virtual void set_auto_findpath_tonpc(uint16_t sceneid, 
                                        const char* npcname) = 0;
   //试图对某个TripperObj进行操作，如果距离过远，会走过去
   virtual void tripper_objectactive(uint32_t id) = 0;
   //试图捡起当前盒子里的第几项
   virtual void itembox_pick(object::Item* item) = 0;

 public:
   //使用包裹里的物品_通用
   virtual void packet_useitem(
       action::Item* item,
       uint16_t target_serverid,
       const vengine_math::base::twofloat_vector_t& position) = 0;
   //使用包裹里的物品_对象
   virtual void packet_useitem_totarget(uint16_t index, uint32_t targetid) = 0;
   //使用包裹里的物品_装备
   virtual void packet_useequip(uint16_t index) = 0;
   //使用包裹里的物品_宝石
   virtual void packet_usegem(uint16_t gemindex, uint16_t equipindex) = 0;
   virtual void packet_destroyitem(uint16_t index) = 0;
   //装备打孔
   virtual void packet_add_equiphole() = 0;
   virtual void packet_equipmount() = 0; //装备坐骑
   virtual void packet_callmount() = 0; //召唤坐骑
   virtual void packet_recallmount() = 0; //召回坐骑
   virtual void packet_destroymount() = 0; //销毁坐骑
   //装备绑定
   virtual void packet_equipbind() = 0;

 public:
   //给玩家身上的装备打孔
   virtual void humanequip_addhole() = 0;
   //玩家身上的装备绑定
   virtual void humanequip_bind() = 0;
   //合成装备
   virtual void equipmerge(uint32_t productid, int32_t* grad) = 0;
   //改造装备
   virtual void equiprework(int32_t* grad) = 0;
   //发送GM指令
   virtual void send_gmcommand(const char* cmd) = 0;
   virtual void send_chatcommand(int32_t channelid, 
                                 uint8_t chatype, 
                                 int32_t teamid, 
                                 const char* context, 
                                 const char* targetname) = 0;

   //场景
   virtual void scene_set_postfilter(const char* filtername) = 0;
   virtual void scene_set_lightmap_quality(int32_t quality) = 0;
   //设置当前激活技能
   virtual void skill_setactive(action::Item* Item) = 0;
   virtual action::Item* skill_getactive() = 0;
   //恢复到缺省技能操作，用于退出修理，鉴定，等特殊鼠标命令状态
   virtual void skill_cancelaction() = 0;

 public:
   virtual void booth_buyitem(action::Item* item) = 0; //物品购买
   virtual void booth_sellitem(action::Item* item) = 0; //物品卖出
   virtual void booth_close() = 0; //交易完成
   //修理
   virtual void booth_repair(bool all, 
                             uint16_t bagindex, 
                             bool is_inbag = true) = 0;

   //称号
   virtual void title_updatecurrent(uint8_t type, int16_t data) = 0;
   
   //摊位
   virtual void stall_opensale(uint32_t objectid) = 0;

};

}; //namespace vengine_game

#endif //VENGINE_GAME_INTERFACE_H_
