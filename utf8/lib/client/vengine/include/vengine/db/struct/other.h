/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id other.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 10:15:41
 * @uses vengine database item struct module
 *       cn: 其他的数据定义 id 2001+
 */
#ifndef VENGINE_DB_STRUCT_OTHER_H_
#define VENGINE_DB_STRUCT_OTHER_H_

namespace other {

//表情和颜色转换字符
const uint16_t kCodeConvertId = 2001;
typedef struct {
  uint16_t id;
  const char* code; //字符串形式的十六进制数字
  const char* name; //介绍
} codeconvert_t;

//任务类型
const uint16_t kMissionKindId = 2002;
typedef struct {
  uint16_t index; //种类索引
  const char* name; //种类名称
} missionkind_t;

//任务数据
const uint16_t kMissionInfoId = 2003;
typedef struct {
  uint32_t index;
  const char* npc_name;
  const char* defaultstr;
  int32_t scriptid;
  const char* eventlist[5];
} missioninfo_t;

//表情和颜色转换字符
const uint16_t kStringDictId = 2004; //字符串字典
typedef struct {
  uint32_t id;
  const char* key;
  const char* string;
} stringdict_t;

//聊天过滤词汇表
const uint16_t kTalkFilterId = 2005;
typedef struct {
  uint32_t id;
  const char* str; //过滤词汇（即：不能说的词汇）
  //过滤过则
  //0表示忽略，1表示含有就过滤，2表示完全匹配过滤
  uint8_t chat; //聊天时
  uint8_t role; //创建角色时，即命名
  uint8_t name; //命名
  uint8_t stall; //摆摊 --这几种基本一样
} talkfilter_t;

//聊天动作命令表
const uint16_t kTalkActorId = 2006;
typedef struct {
  uint16_t id;
  const char* command;
  const char* target_nobody; //没有目标时的字符串
  const char* target_self; //目标为自己时的字符串
  int32_t status; //维持状态标识
  const char* target_other; //目标为别人时的字符串
  const char* actorstart; //（起始）收到聊天信息时需要做的动作命令串
  const char* actorcontinue; //（持续）
  const char* actorend; //（结束）
  const char* icon;
  const char* tooltip; //提示
} talkactor_t;

//聊天限制配置表
const uint16_t kTalkConfigId = 2007;
typedef struct {
  uint16_t id;
  const char* channelname; //频道名称
  int32_t timeinterval; //时间间隔
  const char* channelheader; //频道前导字符
  int32_t needtype1; //消耗类型1
  int32_t needvalue1; //消耗数值1
  int32_t needtype2; //消耗类型2
  int32_t needvalue2; //消耗数值2
  int32_t needtype3; //消耗类型3
  int32_t needvalue3; //消耗数值3
  uint8_t needlevel; //等级限制
} talkconfig_t;

//字体颜色配置表
const uint16_t kSystemColor = 2008;
typedef struct {
  const static uint8_t name_playerself = 1; //主角自己的名字
  const static uint8_t name_playerother = 2; //其他玩家的名字
  const static uint8_t name_npc_peace = 3; //NPC 和平名字
  const static uint8_t name_npc_autoattack = 4; //主动攻击NPC
  const static uint8_t name_npc_notauto_attack = 5; //非主动攻击NPC
  const static uint8_t name_npc_cannot_attack = 6; //不可攻击的NPC
  const static uint8_t title_normal = 100; //普通称号
  const static uint8_t title_faction = 101; //工会
  const static uint8_t title_mood = 102; //玩家自定义心情
  const static uint8_t title_playershop; //玩家商店

  const static uint16_t ui_debug_listbox = 1000; //调试框

  const static uint8_t name_leveldiff1 = 201; //级别差>=20 (深红)
  const static uint8_t name_leveldiff2 = 202; //级别差[5,20] (红)
  const static uint8_t name_leveldiff3 = 203; //级别差(-5,5) (黄)
  const static uint8_t name_leveldiff4 = 204; //级别差(-20,-5）(绿)
  const static uint8_t name_leveldiff5 = 205; //级别差<=-20 (灰)
  
  uint16_t id;
  const char* fontcolor; //字体颜色
  const char* description; //描述
  const char* extendcolor; //扩展颜色
} systemcolor_t;

//全匹配过滤表，用在创建帮会、起名字之类的地方，避免使用系统词组
const uint16_t kFullMatchFilterId = 2009;
typedef struct {
  uint32_t id;
  const char* text; //完全屏蔽词
  const char* type; //用在什么地方，例如：all,guild,team
} fullmatch_filter_t;

//每日提醒相关
const uint8_t kNpcDialogLengthMax = 70;
const uint8_t kSceneNameMax = 10;
const uint8_t kMissionNameLengthMax = 24;
const uint8_t kMissionTextLengthMax = 24;
const uint8_t kCountryNumberMax = 4; //国家数量--以后改为阵营
const uint8_t kGuildFamilySize = 99; //工会和家族最大数量
const uint8_t kShowLevelMax = 100;
const uint16_t kDayTipsNumberMax = 256; 
const uint8_t kMonthWeekMax = 7; //每月最多的周数
const uint8_t kWeekDayMax = 7; //每周7天
//任务的有效时间片
typedef struct {
  tm start;
  tm end;
} valid_timeslice_t;

//每日提醒功能属性
const uint16_t kDayTipsId = 2010;
typedef struct {
  uint16_t index;
  bool used; //是否已初始化
  int32_t dayrecommend; //日推荐
  int32_t monthrecommend; //月推荐
  bool showall; //是否全部可见
  //可见等级  读表中0表示所有等级段
  //代码中遇0时，会将数组所有元素置1,代码中就没有0了
  //此后0表示不可见，1表示可见。
  uint8_t showlevel[kShowLevelMax];
  //可见国家, 0表示所有国家
  uint8_t showcountry[kCountryNumberMax];
  //可见工会，0表示所有工会
  uint8_t showguild[kGuildFamilySize];
  //可见家族，0表示所有家族
  uint8_t showfamily[kGuildFamilySize];
  uint8_t missiontype; //任务类型 0表示循环任务，1表示定时玩法
  char missionname[kMissionNameLengthMax]; //任务名称
  //任务有效月份 0表示不限月，否则表示可做该任务的月份
  uint8_t mission_validmonth[13]; //[0]废弃，其他表示[1-12]月份
  uint8_t mission_withweek_orday; //任务以月还是以星期做，0表示星期
  //mission_withweek_orday=1时的任务有效日期,0表示不限时。
  //要注意每个月不是都在31天
  uint8_t mission_validday[32]; //[0]无效
  //任务以周为单位来做
  //第一个字段表示第几周，为0表示不限周 
  //第二个字段表示周几，为0表示不限
  uint8_t mission_validweek[kMonthWeekMax][kWeekDayMax];
  //任务开始到结束的时间,为0表示不限时
  valid_timeslice_t valid_timeslice;
  int32_t missionposition; //表示读取此任务次数的相关变量及脚本位置
  int32_t missioncount; //每日可做次数 
  char missiontext[kMissionTextLengthMax]; //任务描述
  uint16_t sceneid; //对象所在场景ID
  char scenename[kSceneNameMax]; //场景名
  int32_t xposition;
  int32_t yposition;
  //活动参数保存在任务参数数组的序号，
  //对应ScriptGlobal.lua里MissionData中各个数据的定义
  int32_t donecount_index; //活动完成次数下标
  int32_t donecircle_index; //活动完成环数下标
  int32_t lastdone_timeindex; //活动最后一次完成时间下标
  int32_t lastabandon_timeindex; //活动最后一次放弃时间下标
} daytips_t;

//排行榜表
const uint16_t kRankListId = 2011;
typedef struct {
  uint8_t id;
  const char* name; //排行榜名
  const char* type; //所属分类
  float refresh; //刷新时间间隔
  uint16_t number; //排名数量
} ranklist_t;

//任务管理表
const uint16_t kQuestLogId = 2012;
typedef struct {
  uint32_t scriptid;
  int32_t missionid;
  const char* name; //任务名称
  uint16_t sceneid; //接受任务的场景ID
  const char* npc_name; //接任务NPC名称
  const char* npc_commit_name; //交任务的NPC名称
  int32_t npc_xposition; //NPC X坐标
  int32_t npc_yposition; //NPC Y坐标
  uint8_t levelmin; //接受最低等级
  uint8_t levelmax; //接受最高等级

  int32_t prevmission[5]; //前置任务
} questlog_t;

//模型配置表格 
const uint16_t kModelParameterId = 2013;
typedef struct {
  int32_t id;
  const char* modelname;
  float height;
  float distance;
} model_parameter_t;

//搜侠录数据
const uint16_t kSouXiaLuDataId = 2014;
typedef struct {
  uint32_t id;
  const char* name;
  uint8_t needlevel; //使用等级
  //类型 0.搜侠录道具， 1.搜侠录记忆棒， 2.拆卸道具， 3.炼化道具， 4.缝合道具
  uint8_t type;
  uint16_t allpage_number; //所有页的总数
  uint16_t skillpage_number; //技能页的上限
  uint16_t armpage_number; //武器页的上限
  uint16_t petpage_number; //宠物页的上限
  uint16_t mountpage_number; //坐骑页的上限

  //搜侠录记忆棒
  //1,2,3,4 分别表示技能，武器配方，神兽召唤，坐骑召唤
  uint8_t memorystick_type; //记忆棒类型
  const char* memorystick_skillid; //储存的技能标号
  const char* memorystick_armid; //存储的武器编号
  const char* memorystick_petid; //储存的宠物编号
  const char* memorystick_mountid; //储存的坐骑编号

  //拆卸道具数据
  uint8_t striplevel; //搜侠录拆卸道具的品质 
  int32_t stripskill; //拆卸功能，表示保留几个技能页
  int32_t strip_skillodds; //拆卸技能页的成功概率
  int32_t striparm; //拆卸功能，表示保留几个武器配方页
  int32_t strip_armodds; //拆卸武器配方页的成功概率
  int32_t strippet; //拆卸功能，表示保留几个神兽召唤技能页
  int32_t strip_petodds; //拆卸神兽召唤技能页的成功概率
  int32_t stripmount; //拆卸功能，表示保留几个坐骑召唤技能页
  int32_t strip_mountodds; //拆卸坐骑召唤技能页的成功概率

  //搜侠录炼化道具数据 
  uint8_t smeltlevel; //搜侠录炼化道具的品质
                      //（0-4，分别表示低级，初级，中级，高级，特殊炼化道具）
  int32_t smeltskill; //炼化功能，表示保留几个技能页
  int32_t smelt_skillodds; //炼化技能页的成功概率
  int32_t smeltarm; //炼化功能，表示保留几个武器配方页
  int32_t smelt_armodds; //炼化武器配方页的成功概率
  int32_t smeltpet; //炼化功能，表示保留几个神兽召唤技能页
  int32_t smelt_petodds; //炼化神兽召唤页的成功概率
  int32_t smeltmount; //炼化功能，表示保留几个坐骑召唤技能页
  int32_t smelt_mountodds; //炼化坐骑召唤技能页的成功概率

  int32_t sutrueodds; //搜侠录缝合道具的成功概率
  int32_t conjurenumber; //表示对应（神兽/坐骑）召唤技能使用的次数
} souxialu_data_t;

//登陆服务器数据
const uint16_t kLoginServerDataId = 2015;
typedef struct {
  uint16_t id;
  const char* areaname; //大区
  const char* servername; //服务器名
  const char* tip; //提示
  uint8_t provider; //0网通，1电信
  uint16_t server_areaid;
  //服务器荷载：0为爆满，1为繁忙，2为良好，3为极佳，4为维护，10为备用服务器 
  uint8_t serserstatus;
  bool isrecommend; //是否为推荐
  bool is_newserver; //是否为新服
  const char* serverid; //登陆服务器的ip:port
} loginserver_data_t;

/** 搜侠召唤技能所要转换的召唤兽的ID **/
const uint16_t kSouXiaLuImpactModelId = 2016;
typedef struct {
  uint16_t id; //效果ID
  uint32_t modelid; //召唤兽ID
} souxialu_impactmodel_t;

//商城
const uint16_t kMallId = 2017;
typedef struct {
  uint16_t id;
  uint32_t itemid;
  const char* description;
  uint32_t price; //价格
  bool isnew; //是否为新品
  bool ishot; //是否为热卖商品
  bool is_cutprice; //是否为打折商品
  int32_t cutprice_rate; //打折比例
  bool is_petshop; //是否为宠物商店
  bool is_equipshop; //是否为装备商店
  bool is_drugshop; //是否为药店
  bool is_specialshop; //是否为异术商店
  bool is_solligateshop; //是否为综合商店
} mall_t;

}; //namespace other

#endif //VENGINE_DB_STRUCT_OTHER_H_
