#ifndef PAP_COMMON_GAME_DEFINE_H_
#define PAP_COMMON_GAME_DEFINE_H_

//-- global
#define INVALID_COUNTRY -1
#define INVALID_JOB -1
#define INVALID_SEX -1
#define INVALID_GUILD_ID -1
#define INVALID_RESOURCE -1
#define INVALID_RULERID -1
#define INVALID_PRICE 0
#define INVALID_ITEM_ID 0
#define INVALID_ITEM_POS -1
#define INVALID_TIME 0xFFFFFFFF
#define INVALID_PAI_TYPE 0
#define INVALID_SOUL_TYPE 0
#define BASE_BAG_POS 185
#define GUILD_LEVEL_MAX 5 //公会最大等级
#define CHARACTER_ABILITY_MAX 8 //角色最多的生活技能数量

typedef enum {
  kTimeZhi, //子
  kTimeChou, //丑
  kTimeYin, //寅
  kTimeMao, //卯
  kTimeChen, //辰
  kTimeSi, //巳
  kTimeWu, //午
  kTimeWei, //未
  kTimeShen, //申
  kTimeYou, //酉
  kTimeXu, //戌
  kTimeHai, //亥
} world_time_enum; //old china time

typedef enum {
  kGmExcuteLevelGm = 1,
  kGmExcuteLevelGmAdmin,
  kGmExcuteLevelAdmin,
  kGmExcuteLevelAll,
} gm_excute_level_enum; //GM命令模式

//global --

//-- normal

namespace pap_common_game {

namespace define {

//-- attr
namespace attribute { //属性 --虽然是三级嵌套，但是书写起来很方便

namespace character { //角色

typedef enum {
  kShaoLin = 0, //少林
  kMingJiao = 1, //明教
  kGaiBang = 2, //丐帮
  kWuDang = 3, //武当
  kEMei = 4, //峨眉
  kXingXiu = 5, //星宿
  kTianLong = 6, //天龙
  kTianShan = 7, //天山
  kXiaoYao = 8, //逍遥
  kWuMenPai = 9, //无门派
  kMenPaiCount,
} meipai_enum; //门派，暂时与天龙一致

typedef enum {
  kInvalid = -1,
  kPower, //力量
  kAnima, //灵气
  kPhysique, //体质
  kIntellect, //智力
  kAgility, //敏捷
  kHP, //血量
  kMP, //魔法值
  kHPMax, //血量最大值
  kMPMax, //魔法最大值
  kHPRecoverSpeed, //血气回复速度 点/秒
  kMPRecoverSpeed, //魔法回复速度 点/秒
  kHit, //命中
  kMiss, //闪避
  kCrit, //会心
  kMoveSpeed, //移动速度
  kAttackSpeed, //攻击速度
  kPhysicalAttack, //物理攻击
  kPhysicalDefence, //物理防御
  kMagicAttack, //魔法攻击
  kMagicDefence, //魔法防御
  kColdAttack, //冰攻
  kColdDefence, //冰防
  kFireAttack, //火攻
  kFireDefence, //火防
  kElectricityAttack, //电攻
  kElectricityDefence, //电防
  kPoisonAttack, //毒攻
  kPoisonDefence, //毒防
  kRage, //怒气 
  kStrikePoint, //连技点
  kCount,
} _enum; //基本属性

typedef enum {
  kInfoBaseHP = 0, //初始生命
  kInfoPhysiqueAffectHP = 1, //体质对生命影响系数
  kInfoLevelAffectHP = 2, //等级对生命影响系数
  kInfoBaseHPRecover = 3, //初始生命回复
  kInfoPhysiqueAffectHPRecover = 4, //体质对生命回复影响系数
  kInfoLevelAffectHPRecover = 5, //等级对生命回复影响系数
  kInfoBaseMP = 6, //初始内力
  kInfoIntellectAffectMP = 7, //智力对内力影响系数
  kInfoLevelAffectMP = 8, //等级对内力影响系数
  kInfoBaseMPRecover = 9, //初始内力恢复
  kInfoIntellectAffectMPRecover =10, //智力对内力回复影响系数
  kInfoLevelAffectMPRecover = 11, //等级对内力回复影响系数
  kInfoBasePhysicalAttack = 12, //初始物理攻击 --外功攻击
  kInfoPowerAffectPhysicalAttack = 13, //力量对物理攻击的影响系数
  kInfoLevelAffectPhysicalAttack = 14, //等级对物理攻击的影响系数
  kInfoBaseMagicAttack = 15, //初始魔法伤害 --内功攻击
  kInfoAnimaAffectMagicAttack = 16, //灵力对魔法攻击的影响系数
  kInfoLevelAffectMagicAttack = 17, //等级对魔法攻击的影响系数
  kInfoBasePhysicalDefence = 18, //初始物理防御 --外功防御
  kInfoPhysiqueAffectPhysicalDefence = 19, //体质对物理防御的影响系数
  kInfoLevelAffectPhysicalDefence = 20, //等级对物理防御的影响系数
  kInfoBaseMagicDefence = 21, //初始魔法防御 --内功防御
  kInfoIntellectAffectMagicDefence = 22, //智力对魔法防御的影响系数
  kInfoLevelAffectMagicDefence = 23, //等级对魔法防御的影响系数
  kInfoBaseHit = 24, //初始命中
  kInfoAgilityAffectHit = 25, //敏捷对命中的影响系数
  kInfoLevelAffectHit = 26, //等级对命中的影响系数
  kInfoBaseMiss = 27, //初始闪避
  kInfoAgilityAffectMiss = 28, //敏捷对闪避的影响系数
  kInfoLevelAffectMiss = 29, //等级对闪避的影响系数
  kInfoBaseCrit = 30, //初始会心率 --暴击
  kInfoAgilityAffectCrit = 31, //敏捷对会心率的影响系数
  kInfoLevelAffectCrit = 32, //等级对会心率的影响系数
  kInfoAttackFluctuation = 33, //攻击浮动
  kInfoCount,
} info_enum;

typedef enum {
  kUpdateDataId = 0, //数据资源ID
  kUpdateName, //姓名
  kUpdateTitle, //称号
  kUpdateLevel, //等级
  kUpdateHPPercent, //血气百分比
  kUpdateMPPercent, //内力百分比
  kUpdateRage, //怒气
  kUpdateHideLevel, //隐形级别
  kUpdateSit, //是否为坐下状态
  kUpdateMoveSpeed, //移动速度
  kUpdateAttackSpeed, //攻击速度
  kUpdateCampId, //阵营ID
  kUpdateHeadPortraitId, //头像ID
  kUpdateModelId, //模型ID
  kUpdateMountId, //坐骑ID
  kUpdateAIType, //AI类型
  kUpdatePlayerData, //玩家数据
                     // 00|0000|0000|0000|0000
                     //     |     |    |    |
                     //    头发  脸型 头发 脸型
                     //    颜色  颜色 模型 模型
  kUpdateIsInStall, //是否在摆摊状态
  kUpdateStallName, //摊位名
  kUpdateOccupant, //占有者(是谁打的，死了算谁的)
  kUpdateOwner, //拥有者(是谁控制的)
  kIsNpc, //是否为NPC
  kUpdateCount,
} update_enum; //刷新属性

typedef enum {
  kDetialLevel = 0, //等级
  kDetialHP, //气血
  kDetialMP, //魔法值
  kDetialExp, //经验
  kDetialMoney, //金钱
  kDetialPower, //力量
  kDetialAnima, //灵气
  kDetialPhysique, //体质
  kDetialIntellect, //智力
  kDetialAgility, //敏捷
  kDetialPointRemain, //剩余点数
  kDetialPhysicalAttack, //物理攻击
  kDetialPhysicalDefence, //物理防御
  kDetialMagicAttack, //魔法攻击
  kDetialMagicDefence, //魔法防御
  kDetialHPMax, //血气最大值
  kDetialMPMax, //魔法最大值
  kDetialHPRecoverSpeed, //血气回复速度 点/秒
  kDetialMPRecoverSpeed, //魔法回复速度 点/秒
  kDetialHit, //命中
  kDetialMiss, //闪避
  kDetialCrit, //会心
  kDetialRage, //怒气
  kDetialStrikePoint, //连技点
  kDetialMoveSpeed, //移动速度
  kDetialAttackSpeed, //攻击速度
  kDetialColdAttack, //冰攻
  kDetialColdDefence, //冰防
  kDetialFireAttack, //火攻
  kDetialFireDefence, //火防
  kDetialElectricityAttack, //电攻
  kDetialElectricityDefence, //电防
  kDetialPoisonAttack, //毒攻
  kDetialPoisonDefence, //毒防
  kDetialMeiPai, //门派
  kDetialGuild, //帮会
  kDetialCamp, //阵营
  kDetialDataId, //数据ID
  kDetialHeadPortraitId, //头像ID
  kDetialModelId, //模型ID
  kDetialMountId, //坐骑ID
  kDetialCurrentPetGuid, //当前宠物的GUID
  kDetialMoveLimit, //是否限制移动
  kDetialSkillAction1, //技能限制的标记1
  kDetialSkillAction2, //技能限制的标记2
  kDetialHandleLimit, //是否限制一起操作
  kDetialYuanBao, //角色身上的元宝
  kDetialBankYuanBao, //银行中的元宝
  kDetialEnergy, //精力
  kDetialEnergyMax, //精力上限
  kDetialVigor, //活力
  kDetialVigorMax, //活力上限
  kDetialGoodAndEvilValue, //善恶值
  kDetialCount,
} detial_enum;

}; //namespace character

namespace pet { //宠物
}; //namespace pet

namespace monster { //怪物

typedef enum {
  kAiParamScanEnemyTime = 0, //扫描敌人的时间间隔，如果是-1，则不会主动攻击
  kAiParamRandMoveTime = 1, //随机移动的时间间隔，如果是-1，则不会随机移动
  kAiParamCanNotAttack = 2, //不能被攻击（无敌）
  kAiParamReturnDistance = 3, //离开出生地的距离大于此值时，放弃追赶敌人
  kAiParamScanEnemyDistance = 4, //扫描敌人的最大距离
  kAiParamScanTeammateDistance = 5, //扫描队友的最大距离
  kAiParamResetTargetDistance = 6, //如果当前的移动目标和敌人的位置之间的距离大于此数值,则需要重新设定移动目标
  kAiParamPatrolTime = 7, //巡逻的时间间隔
  kAiParamStrikeBack = 8, //是否会还击
  kAiParamUseLuaScript = 9, //是否有扩展脚本
  kAiParamCallOther = 10, //是否召唤其他怪物
  kAiParamCount,
} ai_param_enum;

}; //namespace monster

namespace team_member { //队伍成员

typedef enum {
  kInvalid = -1,
  kMeiPai, //门派
  kLevel, //等级
  kPosition, //位置
  kHP,
  kHPMax,
  kMP,
  kMPMax,
  kWeapon, //武器
  kCap, //帽子
  kArmor, //衣服
  kCuff, //护腕
  kBoot, //鞋子
  kBuff, 
  kDeadLink, //断线（与离线是不同概念）
  kDead, //死亡
  kFaceModel, //面部模型
  kHairModel, //头发模型
  kHairColor, //头发颜色
  kCount,
} _enum;

}; //namespace team_member

}; //namespace attr
//attr --

//-- item
namespace item {
}; //namespace item
//item --

//-- error
namespace error { //错误类型定义

namespace attack { //攻击

typedef enum {
  kNotLive = -1, //目标死了，攻击无效
  kNotSameScene = -2, //目标不在当前场景
  kNotInRange = -3, //超出范围
  kTargetInvalid = -4, //目标无效
  kNotHit = -5, //未命中
  kTargetDead = -6, //目标已死亡
  kBreak = -7, //攻击被打断
  kCanNotAttack = -8, //目标不能被攻击
} _enum;

namespace team {

typedef enum {
  kInviteTargetHasTeam = 0, //邀请对象已经属于某个组了
  kInviteTargetRefuse, //邀请对象拒绝邀请
  kInviterTeamFull, //邀请者队伍满
  kInviterLeaderRefuse, //邀请者的队长拒绝
  kDismissNotLeader, //解散的人不是队长
  kKickNotLeader, //踢人的不是队长
  kApplicantHasTeam, //申请人已经有队伍
  kByApplicantNotHasTeam, //被申请的人没有队伍
  kByApplicantTeamLeaderRefuse, //申请的队长拒绝申请人加入
  kByApplicantTeamFull, //被申请的队伍已满
  kByApplicantTeamLeaderGuidError, //被申请队伍的队长GUID发生了变化
  kAppointNewLeaderNotMember, //被委任的队长不是队伍成员
  kAppointOldLeaderNotMember, //委任的队长不是队伍成员
  kAppointNotInSameTeam, //委任不在同一队伍
  kAppointOldLeaderNotTeamLeader, //旧的队长已经不是队长了
  kByApplicantTeamLeaderCanNotAnser, //申请的队长无法答复
  kInviterNotInTeam, //邀请的人不在队伍中
  kApplicantWhenInTeam, //申请的人在已有队伍的情况下申请组队
  kTeamFull, //队伍满
  kInviteTargetRefuseSetting, //被邀请的人使用了拒绝邀请设置
  kTargetNotOnline, //目标不在线
} _enum;

typedef enum {
  kFollowTooFar, //过远
  kFollowIn, //已经进入组队跟随
  kFollowOnStall, //正在摆摊
  kFollowNotInState, //不在跟随状态
} follow_enum;

}; //namespace team

namespace channel {

typedef enum {
  kExist = 0, //已经有频道
  kFull, //频道满了
  kNotExist, //频道不存在
  kMemberFull, //频道用户已满
  kMemberExist, //用户已在该频道
  kMemberNotExist, //用户不在该频道
} _enum;

}; //namespace channel

}; //namespace attack

};
//error --

//-- type
namespace type {

namespace relation { //关系

typedef enum {
  kInvalid = -1,
  kEnemy = 0, //敌对
  kFriend = 1, //友好
  kCount,
} _enum;

typedef enum {
  kPlayerNone = 0, //空
  kPlayerFriend, //好友
  kPlayerBrother, //结拜
  kPlayerMarry, //结婚
  kPlayerBlack, //黑名单
  kPlayerTempFriend, //临时好友
  kPlayerStranger, //陌生人
  kPlayerProffer, //师傅关系
  kPlayerDisciple, //徒弟关系
  kPlayerCount,
} player_enum;

}; //namespace relation

namespace chat {

typedef enum {
  kInvalid = -1,
  kNormal, //普通说话消息
  kTeam, //队伍消息
  kScene, //场景消息
  kTell, //私聊消息
  kSystem, //系统消息
  kChannel, //频道消息
  kGuild, //帮会消息
  kMeiPai, //门派消息
  kClient, //客户端专用
  kCount,
} _enum;

typedef enum {
  kConsumeNone = -1, //不需要消耗
  kConsumeVigor = 0, //消耗活力
} consume_enum;

}; //namespace chat

namespace attack {

typedef enum {
  kPhysicalDamage, //物理伤害
  kMagicDamage, //魔法伤害
  kColdDamage, //冰伤害
  kFireDamage, //火伤害
  kElectricityDamage, //电伤害
  kPoisonDamage, //毒伤害
  kDamageCount,
} damage_enum; //伤害类型

}; //namespace attack

namespace monster {

typedef enum { //怪物AI基本类型
  kAiBaseInvalid = -1,
  kAiBaseScan = 0, //主动攻击
  kAiBaseNotScan = 1, //非主动攻击
  kAiBaseCanNotAttack =2, //不可攻击
} ai_base_enum;

}; //namespace monster

namespace skill {

typedef enum {
  kUserPlayer = 0,
  kUserMonster = 1,
  kUserPet = 2,
  kUserItem = 3,
} user_enum; //技能使用者分类

typedef enum {
  kPetInvalid = -1, 
  kPetPlayer = 0, //玩家触发
  kPetAI, //AI触发
  kPetPassive, //被动技能，增强属性
  kPetCount
} pet_enum; //宠物的技能操作类型

}; //namespace skill

namespace command { //指令分类

typedef enum {
  kGmNone = 0, //空指令
} gm_enum; //GM指令，后期考虑实现该功能

}; //namespace command

namespace mail {

typedef enum {
  kNormal = 0, //普通
  kSystem = 1, //系统
  kScript = 2, //脚本邮件，服务器端接收到此邮件后会调用一个脚本
  kSystemForPlayer = 3, //系统为玩家代发
} _enum;

typedef enum { //此定义必须与脚本ScriptGlobal.lua中的定义完全相同
  kScriptDivorce, //离婚
  kScriptBetrayProffer, //叛师
  kScriptFireDisciple, //开除徒弟
  kScriptUpdateAttribute, //更新离线玩家属性，上线时发送该脚本邮件
} script_enum;

typedef enum {
  kAttributeGuildId = 1, //帮会ID
  kAttributeMoney = 2, //金钱
} attribute_enum; //邮件可以更改的玩家属性

typedef enum {
  kAskLogin = 0, //用户刚登陆游戏时发送的邮件检查消息
  kAskSelf, //请求自己的邮件
} ask_enum;

}; //namespace mail

namespace setting {

typedef enum {
  kNone = 0, //
  kFlag, //游戏标记设置，如拒绝的配置
  kKey0, //0号快捷栏设置
  kKey1, //1号快捷栏设置
  kKey2, //2号快捷栏设置
  kKey3, //3号快捷栏设置
  kKey4, //4号快捷栏设置
  kKey5, //5号快捷栏设置
  kKey6, //6号快捷栏设置
  kKey7, //7号快捷栏设置
  kKey8, //8号快捷栏设置
  kKey9, //9号快捷栏设置
  kKey10, //右边0号快捷栏设置
  kKey11, //右边1号快捷栏设置
  kKey12, //右边2号快捷栏设置
  kKey13, //右边3号快捷栏设置
  kKey14, //右边4号快捷栏设置
  kKey15, //右边5号快捷栏设置
  kKey16, //右边6号快捷栏设置
  kKey17, //右边7号快捷栏设置
  kKey18, //右边8号快捷栏设置
  kKey19, //右边9号快捷栏设置
  kChatTab1Part1, //聊天自定义tab1设置第一部分 下同
  kChatTab1Part2,
  kChatTab2Part1,
  kChatTab2Part2,
  kChatTab3Part1,
  kChatTab3Part2,
  kChatTab4Part1,
  kChatTab4Part2,

} _enum;

typedef enum {
  kFlagRefuseAddFriend = 0, //拒绝添加好友
  kFlagRefuseReceiveMail = 1, //拒绝接收邮件
  kFlagRefuseReceiveStangerMail = 2, //拒绝陌生人邮件
  kFlagRefuseTeamInvite = 3, //拒绝组队邀请
  kFlagRefuseLookSpouseInfo = 16, //拒绝查看配偶资料
  kFlagRefuseTransaction = 17, //拒绝交易
  kFlagClosePopup = 18, //关闭当前泡泡框
  kFlagManualLevelUp = 19, //手动升级 --这个无效了
} flag_enum; //个人设置标记

}; //namespace setting

namespace human {

typedef enum {
  kDieInvalid = -1,
  kDieMatch, //切磋
  kDieMonsterKill, //被怪物杀死
  kDiePlayerKill, //被玩家杀死
  kDieCount,
} die_enum; //死亡类型

}; //namespace human


typedef enum {
  kSexInvalid = -1,
  kSexFemale, //雌 女
  kSexMale, //雄 男
  kSexCount,
} sex_enum;

namespace event { //事件类型

typedef enum {
  kTaskKillMonster = 0, //杀死怪物
  kTaskEnterArea, //进入事件区域
  kTaskItemChange, //物品变化
  kTaskPetChange, //宠物变化
} task_enum;

}; //namespace event 

namespace shop { //商店类型

typedef enum {
  kNpcAll = 1, //
  kNpcDefence, //防具
  kNpcAdorn, //饰品
  kNpcWeapon, //武器
  kNpcFood, //食物
  kNpcMetarial, //材料
  kNpcDrugs, //药品
} npc_enum;

}; //namespace shop

typedef enum {
  kCurrencyMoney = 0, //普通金钱
  kCurrencyGoodAndEvil, //善恶值
  kCurrencyProfferMoralPoint, //师德点
} currency_enum;

}; //namespace type
//type --

//-- group
namespace group {

namespace relation {

typedef enum {
  kFriendAll = 0, //全部好友
  kFriend1, //好友组1
  kFriend2, //好友组2
  kFriend3, //好友组3
  kFriend4, //好友组4
  kBlack, //黑名单
  kCount,
  kFriendTemp, //临时好友
} _enum;

}; //namespace relation

}; //namespace group
//group --

//-- status
namespace status {

namespace share_memory {

typedef enum {
  kUseNever = 0, //从未使用过
  kUseServer = 1, //server 占用
  kUseServerHasClean = 2, //server 正常shutdown ，已经清除
  kUseWorld = 3, //world 占用
  kUseWorldHasClean = 3, //world 正常shutdown ，已经清除
} use_enum;

}; //namespace share_memory

}; //namespace status
//status --

//-- id
namespace id {

namespace ability {

typedef enum {
  kGemCompound = CHARACTER_ABILITY_MAX + 1,
  kGemInlay
} gem_enum;

}; //namespace ability

namespace skill {

typedef enum {
  kSystemMeleeAttack, //近战
  kSystemPetCapture, //扑捉宠物
  kSystemPetCallUp, //召唤宠物
} system_enum;

}; //namespace skill

namespace impact { //效果

typedef enum {
  kSystemDamagesOfAttack = 0,
  kSystemNoType,
} system_enum;

}; //namespace impact

}; //namespace id
//id --

//-- size
namespace size {

typedef enum {
  kCooldownList = 255
} cooldown_list_enum;


}; //namespace size
//size --

//-- time
namespace time {

typedef enum {
  kCommonCooldown = 750,
} cooldown_enum; //冷却

}; //namespace time
//time --

//-- result
namespace result {

namespace team {

typedef enum {
  kMemberEnter, //成员加入
  kMemberLeave, //成员离队
  kLeaderLeave, //队长离队
  kDismiss, //解散
  kMemberKick, //成员被踢出
  kAppoint, //队长任命
  kRefresh, //请求队伍信息的重新刷新
  kStartChangeScene, //开始切换场景
  kEnterScene, //成员进入场景
  kChangeSceneRefreshServerInfo, //玩家跳转场景后，给服务器刷新队伍消息
  kMemberOffline, //成员离线
} _enum;

typedef enum { //队伍跟随
  kFollowMemberRefuse, //队员拒绝
  kFollowMemberEnter, //队员进入组队跟随
  kFollowMemberStop, //队员退出组队跟随
  kFollowNoticeFlag, //通知客户端进入组队跟随的标记
} follow_enum;

}; //namespace team

namespace channel {

typedef enum {
  kCreate, //创建
  kAddMember, //添加成员
  kDismiss, //解散
  kKickMember, //踢出成员
  kCount,
} _enum;
 
}; //namespace channel

namespace user_data {

typedef enum {
  kNotFind = 0, //没有发现用户数据
  kHave, //拥有用户数据
  kCaching, //目标服务器的用户数据正在缓存
  kServerCrash, //用户Server已经Crash,可能还在缓存中,Server正在处理这块缓存
  kKeyError, //验证码错误
} _enum;

}; //namespace user_data

}; //namespace result
//result --

//-- value
namespace value { //值的定义

namespace pk {

typedef enum {
  kValue1 = 1,
  kValue2 = 20,
  kValue3 = 40,
  kValue4 = 60,
  kValue5 = 80,
  kValueMax = 1000,
} _enum;

}; //namespace pk

namespace relation {

typedef enum {
  kFriendOffset = 0, 
  kBlackOffset = 80,
} _enum;

}; //namespace relation

namespace combat {

typedef enum {
  kAcceptableDistanceErrorForHuman = 2,
  kAcceptableDistanceErrorForNpc = 1,
} acceptable_distance_error_enum;

}; //namespace combat

}; //namespace value
//value --

//-- index
namespace index {

namespace skill {

typedef enum {
  kPetInvalid = -1,
  kPetControlByPlayer,
  kPetControlByAI,
  kPetControlByMeiPai,
  kPetCount,
} pet_enum;

}; //namespace skill

}; //namespace index
//index --

}; //namespace define

}; //namespace pap_common_game

//normal --

#endif //PAP_COMMON_GAME_DEFINE_H_
