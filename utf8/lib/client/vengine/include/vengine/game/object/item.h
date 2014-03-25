/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id item.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-25 09:38:02
 * @uses vengine game item object class
 */
#ifndef VENGINE_GAME_OBJECT_ITEM_H_
#define VENGINE_GAME_OBJECT_ITEM_H_

#include "vengine/config.h"

//引用公用类物品结构
namespace pap_common_game {

namespace structs {

namespace item {

struct base_t;

}; //namespace item

}; //namespace structs

}; //namespace pap_common_game

//引用公用类的定义
namespace pap_common_game {

namespace define {

namespace type {

namespace item {

enum class_enum;

}; //namespace item

}; //namespace type

}; //namespace define

}; //namespace pap_common_game

namespace vengine_game {

namespace object {

class VENGINE_API Item  {

 public:
   //从服务器传来的数据标示(用于和服务器通讯)
   union guid_union {
     //合并后的ID
     uint64_t unionid;
     //服务器传来的数据
     struct id_fromserver {
       uint16_t serverid; //服务端程序号：(例)5
       uint16_t worldid; //世界号: (例)101
       uint32_t serial; //物品序列号：(例)123429
     } idorg;
   } id_;
   //物品规则
   typedef enum {
     kRuleCanDrop, //是否可丢弃
     kRuleCanOverlay, //是否可以重叠
     kRuleCanPutShortcutBar, //是否可以放入快捷栏
     kRuleCanSale, //是否可以出售
     kRuleCanExchange, //是否可以交易
     kRulePickBind, //是否拾取就绑定
     kRuleSole, //是否唯一的
     kRuleNeedCheck, //是否需要鉴定
     kRuleVirtualItem, //是否为虚拟的物品
     kRuleStoreBank, //是否可以放入银行
     kRuleWearOut, //是否消耗
   } rule_enum;

   //物品归属
   typedef enum {
     kOwnerUnkown,
     kOwnerSelfEquip, //身上的装备
     kOwnerSelfPacket, //背包中的
     kOwnerSelfBank, //银行中
     kOwnerSelfMount, //坐骑上
     kOwnerOtherPlayerEquip, //其他玩家装备上
     kOwnerBooth, //商人的货架
     kOwnerSelfExchangeBox, //自己的交易盒子
     kOwnerOtherExchangeBox, //别人的交易盒子
     kOwnerMissionBox, //任务递交盒
     kOwnerSelfStallBox, //自己的摊位盒子
     kOwnerOtherStallBox, //别人的摊位盒子
     kOwnerQuestVirtual, //任务的虚拟物品，只作显示
     kOwnerSelfPlayerShop, //自己的商店
     kOwnerOtherPlayerShop, //别人的商店
     kOwnerDrop, //掉落
     kOwnerTransfer, //用于传输，显示用
     kOwnerMall, //商城
   } owner_enum;

 public:
   //客户端ID
   virtual int32_t getid() const = 0;
   virtual void set_guid(uint16_t worldid, 
                         uint16_t serverid, 
                         uint32_t serial) = 0;
   virtual uint16_t get_guid(uint16_t& worldid, 
                             uint16_t& serverid,
                             uint32_t& serial) const = 0;
   virtual pap_common_game::define::item::class_enum getclass() const = 0;
   virtual int32_t get_tabletype() const = 0;
   virtual const char* getname() const = 0;
   virtual const char* getdescription() const = 0;
   virtual const char* geticon() const = 0;
   //物品的详细编号，不是client用的index
   virtual int32_t get_particularid() const = 0;
   //详细解释(可能需要服务器)
   virtual const char* get_extradescription() = 0;
   //设置详细解释
   virtual void set_extrainfo(pap_common_game::structs::item::base_t* item) = 0;
   virtual void set_extrainfo(const char* info) = 0;
   virtual const char* get_extrainfo() const = 0;
   //归属
   virtual void setowner(owner_enum owner) = 0;
   virtual owner_enum getowner() const = 0;
   //设置所在索引
   virtual void set_positionindex(int32_t index) = 0;
   virtual int32_t get_postitionindex() const = 0;
   virtual const char* get_drop_visualid() const = 0;
   virtual const char* get_drop_visualcolor() const = 0;
   virtual uint8_t getlevel_oftable() const = 0;
   virtual void setnumber(uint32_t number) = 0;
   virtual uint32_t getnumber() const = 0;
   //最大数量,暂时用于有限商品的显示
   virtual void set_maxnumber(uint32_t number) = 0;
   virtual uint32_t get_maxnumber() const = 0;
   //获取叠放数量
   virtual int32_t get_laynumber() const = 0;
   //在资源表中的位置
   virtual int32_t getid_oftable() const = 0;
   //查询逻辑属性,一般用于脚本调用
   virtual STRING get_attributevalue(const char* valuename) const = 0;
   //克隆详细信息
   virtual void clone(const Item* srouceitem) = 0;
   //得到是否锁定(用于UI锁定)
   virtual void setlock(bool lock) = 0;
   virtual bool getlock() const = 0;
   //物品规则验证
   virtual bool rule(int32_t type) = 0;
   virtual STRING rule_failmessage(int32_t type) = 0;
   //物品的二级密码保护
   virtual void setprotect(bool protect) = 0;
   virtual bool getprotect() const = 0;

 public:
   //得到玩家使用这个物品需要的等级
   virtual uint8_t get_needlevel() const = 0;
   //获得物品的耐久
   virtual int32_t getdurability() const = 0;
   //获得物品的最大耐久
   virtual int32_t get_durabilitymax() const = 0;
   //获得物品的可修理次数
   virtual int32_t get_repaircount() const = 0;
   //获得物品的绑定信息
   virtual uint8_t get_bindinfo() const = 0;
   //获得物品的二级绑定信息
   virtual uint8_t get_secondlevel_bindinfo() const = 0;
   //获得绑定加成信息
   virtual const char* get_bindadd_info() const = 0;
   virtual uint32_t get_baseprice() const = 0;
   //得到卖给NPC的价格
   virtual uint32_t getprice() const = 0;
   //获得限定职业
   virtual uint8_t getprofession() const = 0;
   //检查物品是否唯一
   virtual bool checksole() const = 0;
   //得到物品的制作人
   virtual const char* getproducer() const = 0;
   //得到白色属性
   virtual const char* get_basewhite_attributeinfo() const = 0;
   //得到物品使用的目标类型
   virtual uint8_t get_targettype() const = 0;
   //获得物品描述
   virtual const char* get_typedescription() const = 0;
   //得到物品的第一个额外参数信息
   virtual int32_t get_extraparam1() const = 0;
   //得到物品的第二个额外参数信息
   virtual int32_t get_extraparam2() const = 0;
   //得到物品的第三个额外参数信息
   virtual int32_t get_extraparam3() const = 0;

};

}; //namespace object

}; //namespace vengine_game

#endif //VENGINE_GAME_OBJECT_ITEM_H_
