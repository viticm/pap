/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id item.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-23 18:11:47
 * @uses vengine database item struct module
 *       cn: 物品相关数据定义
 */
#ifndef VENGINE_DB_STRUCT_ITEM_H_
#define VENGINE_DB_STRUCT_ITEM_H_

namespace item {

const uint8_t kMonsterEffectNumberMax = 4;
const uint8_t kEquipEffectNumberMax = 16;
typedef struct {
  const char* effect; //特效ID
  const char* bindpoint; //绑定点
} equipeffect_t;

const uint16_t kVisualCharacterId = 301;
typedef struct {
  int32_t id;
  int32_t entityindex[38]; //8个门派*2个方向*2个性别 +无门派*2 + 高模*2
} visualcharacter_t;

const uint8_t kEquipLocatorEffectNumberMax = 8;
const uint16_t kEquipLocatorId = 302;
typedef struct {
  int32_t id;
  const char* description;
  const char* meshfile;
  const char* matfile;
  equipeffect_t effect[kEquipLocatorEffectNumberMax]; //绑定点和特效
} equiplocator_t;

//挂接类物品显示定义
const uint16_t kItemLocatorId = 303;
typedef struct {
  int32_t id;
  const char* objectfile_right; //右手武器名
  const char* matname_right; //右手武器材质名
  const char* objectfile_left; //左手武器名
  const char* matname_left; //左手武器材质名
  const char* objectshield_file; //左手盾武器名
  const char* matname_shield; //左手盾材质名
  uint8_t weapontype; //武器类型
  bool weaponactor; //表示该武器是否有动作
  const char* actorfile; //动作文件
  const char* effectname[30]; //30种宝石效果
} itemlocator_t;

//怪武器
const uint16_t kItemMonsterLocatorId = 304;
typedef struct {
  int32_t id;
  const char* objectfile_right; //右手武器名
  const char* matname_right; //右手武器材质名
  equipeffect_t righteffect[kMonsterEffectNumberMax]; //手武器特效
  
  const char* objectfile_left; //左手武器名
  const char* matname_left; //左手武器材质名
  equipeffect_t lefteffect[kMonsterEffectNumberMax]; //手武器特效

  const char* objectshield_file; //左手盾名
  const char* matname_shield; //左手盾材质名
  equipeffect_t leftshield_effect[kEquipLocatorEffectNumberMax]; //武器特效
  uint8_t weapontype; //武器类型
  bool weaponactor; //表示该武器是否有动作
  const char* actorfile; //动作文件
} item_monsterlocator_t;

const uint8_t kEquipEffectAttributeNumberMax = 16;
//装备对人物属性的影响
typedef struct {
  int32_t attributeid; //属性ID
  int32_t effectnumber; //影响个数
} equip_effectattribute_t;

//附加技能最大个数
const uint8_t kEquipAddEffectSkillNumberMax = 4;
//影响技能最大个数
const uint8_t kEquipEffectSkillNumberMax = 4;

typedef struct {
  int32_t skillid; //技能ID
  int32_t skilllevel; //影响技能的等级
} equipeffect_skill_t

const uint16_t kEquipId = 305;
typedef struct {
  uint32_t id; //装备ID
  uint8_t baseclass; //基本类别
  uint8_t type; //类别
  int32_t index; //物品号
  uint8_t equippoint; //装备点
  int32_t rule; //适应规则
  int16_t setid; //套装ID
  const char* levelrequire; //等级需求
  uint32_t baseprice; //基础价格
  uint16_t durablemax; //最大耐久度
  uint8_t star; //星星
  uint8_t holenumber_nature; //基础孔数
  uint8_t holenumber_max; //最大孔数
  uint8_t professionalrequire; //职业需求
  uint8_t paixing; //装备牌型
  uint32_t score; //装备分数
  uint32_t baseattack_near; //基础近程攻击
  uint32_t baseattack_far; //基础远程攻击
  uint32_t baseattack_magic; //基础魔法攻击
  uint32_t basedefence_near; //基础近程防御
  uint32_t basedefence_far; //基础远程防御
  uint32_t basedefence_magic; //基础魔法防御
  //对人物属性的影响 
  equip_effectattribute_t effectattribute[kEquipEffectAttributeNumberMax];
  //装备对技能的影响
  equipeffect_skill_t addeffect_skill[kEquipAddEffectSkillNumberMax]; //附加
  equipeffect_skill_t effectskill[kEquipEffectSkillNumberMax]; //影响
} equip_t;

//药物
const uint16_t kCureId = 306;
typedef struct {
  uint32_t id;
  uint8_t baseclass;
  uint8_t type;
  int32_t index;
  const char* icon; //图标
  const char* name; //名称
  const char* description; //描述
  uint8_t level; //等级
  uint32_t baseprice; //基础价格
  uint32_t saleprice; //出售价格
  int32_t rule; //适应规则
  uint32_t pilecount; //堆叠数量
  int32_t scriptid; //脚本ID
  int32_t skillneed[2]; //技能需求等级
  uint32_t holdmax; //最大持有数量
  int32_t targettype; //针对对象类型
  bool broadcast; //是否广播
  const char* typedescription; //类型描述
  const char* drop_modelid; //掉落时的外形ID --这个考虑取消 viticm
  const char* dropeffect; //掉落模型附属特效 --考虑取消
  int16_t dropsound; //掉落声音
  const char* drop_displaycolor; //掉落显示颜色
} cure_t;

//任务物品表
const uint16_t kTaskId = 307;
typedef struct {
  uint32_t id;
  uint8_t baseclass;
  uint8_t type;
  int32_t index;
  const char* icon; //图标
  const char* name; //名称
  const char* description; //描述
  uint8_t level; //等级
  uint32_t baseprice; //基础价格
  uint32_t saleprice; //出售价格
  int32_t rule; //适应规则
  uint32_t pilecount; //堆叠数量
  int32_t scriptid; //脚本ID
  int32_t skillneed[2]; //技能需求等级
  uint32_t holdmax; //最大持有数量
  int32_t targettype; //针对对象类型
  bool broadcast; //是否广播
  const char* typedescription; //类型描述
} task_t;

//扩展背包物品表
const uint16_t kExtendBagId = 308;
typedef struct {
  uint32_t id;
  uint8_t baseclass;
  uint8_t type;
  int32_t index;
  const char* icon; //图标
  const char* name; //名称
  const char* description; //描述
  int32_t rule; //适应规则
  uint8_t level; //等级
  uint32_t baseprice; //基础价格
  uint32_t saleprice; //出售价格
  int32_t validtime; //有效时间
  int32_t valid_girdnumber; //有效格子数
  const char* drop_modelid; //掉落时的外形ID --这个考虑取消 viticm
  const char* dropeffect; //掉落模型附属特效 --考虑取消
  int16_t dropsound; //掉落声音
  const char* drop_displaycolor; //掉落显示颜色
} extendbag_t;

//魂珠物品表
const uint16_t kSoulBeadId = 309;
typedef struct {
  uint32_t id;
  uint8_t baseclass;
  uint8_t type;
  int32_t index;
  const char* icon; //图标
  const char* name; //名称
  const char* description; //描述
  int32_t rule; //适应规则
  int32_t validtime; //有效时间
  int32_t impactid; //效果ID
  bool broadcast; //是否广播
  const char* typedescription; //类型描述
  int32_t selectobject_type; //选择的对象类型
  const char* drop_modelid; //掉落时的外形ID --这个考虑取消 viticm
  const char* dropeffect; //掉落模型附属特效 --考虑取消
  int16_t dropsound; //掉落声音
  const char* drop_displaycolor; //掉落显示颜色
} soulbead_t;

/** 宝石 **/
const uint8_t kEquipGemAttributeNumberMax = 4; //宝石属性最大个数
const uint8_t kEquipGemNeedNumberMax = 4; //宝石需求的最大个数

typedef struct {
  int32_t attribute; //强化属性
  int32_t number; //强化数值
} equipgem_attribute_t;

typedef struct {
  int8_t gem; //需求宝石
  int8_t number; //需求数量
} equipgem_need_t;

//宝石定义表
const uint16_t kGemId = 310;
typedef struct {
  uint32_t id;
  uint8_t baseclass; //基础类别
  uint8_t type; //类型
  int32_t index; //编号
  const char* icon; //图标
  int32_t rule; //适应规则
  const char* position; //镶嵌位置
  const char* name;
  const char* description;
  uint32_t baseprice; //基础价格
  uint32_t saleprice; //出售价格
  bool broadcast; //是否广播
  equipgem_attribute_t attribute[kEquipGemAttributeNumberMax]; //附加属性
  equipgem_need_t need[kEquipGemNeedNumberMax]; //需求其他宝石的信息
  const char* color; //附加属性的颜色
  const char* typedescription; //类型描述
  const char* effectcolor; //特效颜色值
  int32_t effectindex; //特效索引
} gem_t;

//地图定义表
const uint16_t kMapId = 311;
typedef struct {
  uint32_t id;
  uint8_t baseclass;
  uint8_t type;
  const char* icon;
  int32_t index;
  const char* name;
  const char* description;
  uint8_t levelrequire;
  int32_t rule;
} map_t;

//套装组合后附加属性 
const uint16_t kSetAttributeId = 312;
typedef struct {
  uint16_t id;
  int32_t attribute[66];
} setattribute_t;

//高级装备外形表
const uint16_t kEquipVisualId = 313;
typedef struct {
  uint32_t id; //如 10010001
  uint16_t modelid; //模型id，可以在模型表里找到对应的具体模型
  const char* name;
  const char* description;
  const char* icon;
  const char* type;
  const char* drop_modelid; //掉落时模型 --考虑去掉
  const char* dropeffect; //掉落附属特效
  int16_t dropsound; //掉落声音
  const char* drop_displaycolor; //显示名称颜色
  equipeffect_t effect[kEquipEffectNumberMax]; //特效
} equipvisual_t;

//装备属性组表
const uint16_t kAttributeGroupId = 314;
typedef struct {
  uint16_t id; //属性组ID
  const char* name; //组名字
  int32_t probability; //属性组几率
  //影响属性id 共16项 对应到装备表的16项 
  int16_t attributeid[kEquipEffectAttributeNumberMax];
} attributegroup_t;

const uint8_t kEquipLevelNumberMax = 100;
const uint16_t kAttributeLevelId = 315;
//装备属性等级表（普通装备才会用到）
typedef struct {
  uint16_t id; //属性ID
  const char* name; //属性名称
  int32_t level[kEquipLevelNumberMax]; //装备影响属性
} attributelevel_t;

//装备打孔
const uint16_t kEquipHoleInfoId = 316;
typedef struct {
  uint8_t number; //孔的数目
  int32_t itemneed; //需要打孔的道具
  uint32_t moneyneed; //需要的金钱
  int16_t successratio; //成功几率
} equiphole_info_t;

//装备绑定
const uint16_t kEquipBindingInfoId = 317;
typedef struct {
  uint8_t level; //绑定等级
  int32_t gemneed; //宝石需求
  int32_t strengthen_percent; //强化比例
} equipbinding_info_t;

//装备打星
const uint16_t kEquipAddStar = 318;
typedef struct {
  uint8_t star; //星数
  int32_t lowlevel_gemid;
  int32_t highlevel_gemid;
  int32_t otherlevel_gemid;
  int32_t probability_onegem; //一颗宝石成功几率
  int32_t probability_twogem; //两颗宝石成功几率
  int32_t probability_threegem; //三颗宝石成功几率
  int32_t probability_fourgem; //四颗宝石成功几率
  uint32_t punishment; //失败惩罚
  uint32_t needmoney; //所需金钱
  int32_t strengthen_percent; //强化比例
} equip_addstar_t;

//装备特修表
const uint16_t kEquipSpecialRepairId = 319;
typedef struct {
  int32_t needitem; //所需物品
  uint16_t recoverdurable; //恢复耐久
} equip_specialrepair_t;

const uint8_t kEquipProductMatNumberMax = 4;
//mat -> material
typedef struct {
  int32_t mat; //材料类
  int32_t matnumber; //料数量
  uint8_t mat_lowestlevel; //材料最低等级
  int32_t matloss; //拆解损耗比例
} equip_productmat_t;

const uint8_t kEquipReformMatNumberMax = 4;
typedef struct {
  int32_t workmat; //改造1材料
  int32_t workmat_number; //改造1数量
  int32_t workmat_lowestlevel; //改造1材料最低等级
} equip_reformmat_t;

const uint8_t kEquipSpiritReformMatNumberMax = 3;

//物品制造
const uint16_t kEquipProductInfoId = 320;
typedef struct {
  uint16_t formulaid; //配方号
  uint32_t productid; //产品ID
  const char* formulaname; //配方名
  uint32_t productnumber; //产品数量
  equip_productmat_t productmat[kEquipProductMatNumberMax]; //生产材料
  equip_reformmat_t reformmat[kEquipReformMatNumberMax]; //改造材料（附加）
} equip_productinfo_t;

//材料等级
const uint16_t kEquipMatLevelInfoId = 321;
typedef struct {
  uint8_t level;
  int32_t value; //材料分值
} equip_matlevel_info_t;

//装备牌
const uint16_t kEquipCardInfoId = 322;
typedef struct {
  uint32_t id; //牌id
  const char* name;
  int32_t attributeid;
  int32_t attributevalue;
  int32_t rate;
} equip_cardinfo_t;

//牌组
const uint16_t kEquipCardGroupId = 323;
typedef struct {
  uint8_t id;
  const char* name;
  uint32_t needcard[3]; //需求的三张牌
  int32_t attributeid; //强化属性
  int32_t attributevalue; //强化数值
  const char* effect; //特效
} equip_cardgroup_info_t;

//整套牌 用于激活
const uint8_t kEquipCardActiveAttributeNumber = 3;
typedef struct {
  int32_t id; //强化属性
  int32_t value; //强化数值
} equip_cardattribute_t;

const uint16_t kEquipCardAllId = 324;
typedef struct {
  int16_t groupid; //组合ID
  const char* groupname; //组合名字
  int32_t needgroup[5]; //需求组合数组
  equip_cardattribute_t attribute[kEquipCardActiveAttributeNumber]; //强化属性
  const char* effect; //特效
} equip_cardall_t;

//换牌表格
const uint16_t kEquipCardTargetId = 325;
typedef struct {
  uint16_t id;
  const char* name;
  uint16_t targeid;
} equip_cardtarget_t;

//装备套装表
const uint16_t kEquipSetInfoId = 326;
const uint8_t kEquipSetAttributeNumber = 4;
typedef struct {
  uint16_t id;
  uint16_t number;
  uint8_t activenumber; //激活属性需要的套装数目
} equipset_attribute_t;

typedef struct {
  uint16_t id; //套装ID
  const char* name; //套装名
  uint8_t number; //数量
  const char* setid; //套装包含的系列id
  equipset_attribute_t attribute[kEquipSetAttributeNumber]; //套装属性
} equipset_info_t;



}; //namespace item

#endif //VENGINE_DB_STRUCT_ITEM_H_
