/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id skill.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 09:30:30
 * @uses vengine database skill struct module
 *       cn: 技能相关数据定义
 */
#ifndef VENGINE_DB_STRUCT_SKILL_H_
#define VENGINE_DB_STRUCT_SKILL_H_

namespace skill {

//心法数据定义
const uint16_t kXinFaId = 601;
typedef struct {
  uint16_t id;
  const char* name;
  uint8_t meipai_id;
  const char* description;
  const char* icon;
} xinfa_t;

//附加效果
const uint16_t kAddImpactId = 602;
typedef struct {
  uint16_t id;
  uint16_t paramnumber;
  const char* description;
  uint16_t addattribute_number;
  const char* addattribute[4]; //附加的效果数组
  int16_t spliceid;
  const char* icon;
} addimpact_t;

//子弹
const uint16_t kBulletId = 603; //预留
typedef struct {
  uint16_t id;
  uint8_t type; //0 瞬移到达 1移动到达
  uint16_t effectid; //特效ID
  float speed; //移动速度(m/s)
  uint16_t fly_soundid; //飞行音效
  uint16_t hit_effectid; //击中特效
  const char* description;
} bullet_t;

//buff附加
const uint16_t kBuffImpactId = 604;

//directly附加效果
const uint16_t kDirectlyId = 605;

//子弹数据
const uint16_t kBulletDataId = 606;

//技能
//const uint16_t kDataId = 607;

//法术OBJECT数据
const uint16_t kSpecialObjectId = 608;
typedef struct {
  uint16_t id;
  const char* name;
  uint8_t type; //类别（服务器用）
  const char* tooltip; //
  uint16_t logicid; //逻辑ID（服务器用）
  uint8_t stealthlevel; //隐形级别（服务器专用，陷阱专用）
  int16_t trapflags; //陷阱标记位集合（服务器专用，陷阱专用）
  int32_t activetimes; //可激活的次数（服务器专用）
  const char* effectnormal; //生存期持续特效
  const char* soundnormal; //生存期持续音效
  const char* effectactive; //激活特效
  const char* soundactice; //激活音效
  const char* effectdie; //死亡特效
  const char* sounddie; //死亡音效
  int32_t reserve1; //预留
  int32_t reserve2; //预留
  int32_t reserve3; //预留
  int32_t bulletid; //子弹ID
  int32_t durationtime; //持续时间（服务器专用）
  int32_t interval; //激活时间间隔
  float triggerradius; //触发半径（服务器专用，陷阱专用）
  float effectradius; //影响半径（服务器专用，陷阱专用）
  int32_t effectunit_number; //影响个体数目（服务器专用，陷阱专用）
  int32_t reserve4; //预留
  int32_t reserve5; //预留
  int32_t reserve6; //预留
  int32_t reserve7; //预留
  int32_t reserve8; //预留
  const char* paramdescription0; //参数描述1
  int32_t param0; //参数值1
  const char* paramdescription1; //参数描述2
  int32_t param1; //参数值2
  const char* paramdescription2; //参数描述3
  int32_t param2; //参数值3
  const char* paramdescription3; //参数描述4
  int32_t param3; //参数值4
  const char* paramdescription4; //参数描述5
  int32_t param4; //参数值5
  const char* paramdescription5; //参数描述6
  int32_t param5; //参数值6
  const char* paramdescription6; //参数描述7
  int32_t param6; //参数值7
  const char* paramdescription7; //参数描述8
  int32_t param7; //参数值8
  const char* paramdescription8; //参数描述9
  int32_t param8; //参数值9
  const char* paramdescription9; //参数描述10
  int32_t param9; //参数值10
  const char* paramdescription10; //参数描述11
  int32_t param10; //参数值11
  const char* paramdescription11; //参数描述12
  int32_t param11; //参数值12
  const char* paramdescription12; //参数描述13
  int32_t param12; //参数值13
  const char* paramdescription13; //参数描述14
  int32_t param13; //参数值14
  const char* paramdescription14; //参数描述15
  int32_t param14; //参数值15
  const char* paramdescription15; //参数描述16
  int32_t param15; //参数值16
  /**
  const char* paramdescription16; //参数描述17
  int32_t param16; //参数值17
  const char* paramdescription17; //参数描述18
  int32_t param17; //参数值18
  **/
  const char* description; //说明
} specialobject_t;

/** 生活技能 **/
const uint16_t kLifeAbilityGrowPointId = 901;
typedef struct {
  uint16_t id;
  const char* name;
  int32_t lifeability;
  const char* meshfile;
  const char* tips;
  int32_t needtime;
  const char* param[4];
  bool animationshow;
} lifeability_growpoint_t;

const uint16_t kLifeAbilityDefineId = 902;
typedef struct {
  uint16_t id;
  const char* name;
  uint8_t levelneed; //所需等级
  uint8_t levelmax; //最高等级
  const char* levelup_table; //升级需求和消耗表
  int32_t operationtime; //操作时间基数
  int32_t toolneed; //需要工具
  float platformdistance; //距离平台的有效距离
  int32_t operationanimation; //操作动作
  const char* icon;
  int32_t item_visuallocator; //动作挂接
  const char* explain; //详细解释
  bool popup; //是否弹出下级界面
  const char* processbar_name; //进度条名称
  uint8_t consume; //消耗活力或是精力，类型
  uint16_t beginsound; //开始播放的音乐
  uint16_t successsound; //成功播放的音乐
  uint16_t failedsound; //失败播放的音乐
  bool isloop; //是否循环
} lifeability_define_t;

//生活技能 升级信息 --所有生活技能消耗使用相同的结构
const uint16_t kCaiKuangLevelUpInfoId = 911; //采矿
const uint16_t kCaiYaoLevelUpInfoId = 912; //采药
const uint16_t kBuZhuoLevelUpInfoId = 913; //捕捉
const uint16_t kZhuZaoLevelUpInfoId = 914; //铸造
const uint16_t kFengRenLevelUpInfoId = 915; //缝纫
const uint16_t kGongYiLevelUpInfoId = 916; //工艺
const uint16_t kPendRenLevelUpInfoId = 917; //烹饪
typedef struct {
  uint8_t level;
  const char* name;
  uint32_t moneyneed;
  uint32_t expneed;
  uint32_t skillproficiency; //熟练度限制
  uint32_t skill_clientproficiency; //客户端显示的熟练度限制
  const char* npcname; //NPC显示名称
  uint32_t npc_moneyneed; //NPC经验需求
  uint32_t npc_expneed; //NPC经验需求
} lifeability_levelup_info_t;

//物品合成
const uint16_t kLifeAbilityItemMergeId = 903;
typedef struct {
  uint16_t id; //配方ID
  const char* name;
  uint32_t productid; //产品ID
  uint32_t productnumber; //产品数量
  uint16_t lifeability; //所需生活技能
  uint8_t lifeability_level; //所需生活技能等级
  int32_t stuffid1; //所需材料1
  int32_t stuffnumber1; //所需材料数量1
  int32_t stuffid2;
  int32_t stuffnumber2;
  int32_t stuffid3;
  int32_t stuffnumber3;
  int32_t stuffid4;
  int32_t stuffnumber4;
  int32_t stuffid5;
  int32_t stuffnumber5;
  int32_t vigorneed; //活力需求
  int32_t energyneed; //精力需求
  int32_t menpai_pointneed; //门派贡献度需求
  int32_t reserver1; //预留1
  int32_t cooldown_time; //冷却时间
  int32_t tooneed; //所需的工具
  int32_t cooldown_group; //冷却组
  int32_t proficiencyrequire; //熟练度需求
  int32_t proficiencyincrease; //增加的熟练度
  int32_t notcare; //预留
  int32_t timeneed; //配方时间
  int32_t scriptid; //脚本ID
  int32_t failitem; //失败后的替代品
  const char* explain; //详细描述
} lifeability_itemmerge_t;

//生活技能操作平台
const uint16_t kLifeAbilityPlatformId = 904;
typedef struct {
  uint16_t id;
  const char* name;
  uint8_t type;
  const char* meshfile;
  uint8_t checktype;
} lifeability_platform_t;

/** 心法 **/ //预留
//心法
const uint16_t kXinFaDefineId = 905;
typedef struct {
  uint16_t id;
  uint8_t meipai_id;
  const char* name;
  const char* description;
  const char* icon;
} xinfa_define_t;

//心法消费
typedef struct {
  uint32_t money; //金钱
  uint32_t experience; //经验
} _xinfa_studycost_t;
const uint16_t kXinFaStudyCostId = 906;
typedef struct {
  uint8_t studylevel; //学习等级
  _xinfa_studycost_t studycost[54]; //学习消耗
} xinfa_studycost_t;

//技能数据 --预留
const uint16_t kDataId = 907;
typedef struct {
  int32_t data;
  const char* description;
} datapair_t;

typedef struct {
  uint32_t id; //技能数据可能会有很多
  int32_t planid; //策划专用ID
  int32_t logicid; //逻辑ID
  const char* effectdescription; //效果的说明
  int32_t cooldowntime; //冷却时间
  int32_t juqi_time; //聚气时间
  int32_t conducttime; //引导时间
  //... 参考天龙八部--SkillData_V1.txt
} data_t;

//技能模板 --预留
const uint16_t kTemplateId = 908;
typedef struct {
  uint32_t id;
  //... 参考天龙八部--SkillTemplate_V1.txt
} template_t;

}; //namespace skill

#endif //VENGINE_DB_STRUCT_SKILL_H_
