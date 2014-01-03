/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id character.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏角色属性的基本定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_ATTRIBUTE_CHARACTER_H_
#define PAP_COMMON_GAME_DEFINE_ATTRIBUTE_CHARACTER_H_

namespace character { //这个对应的便是文件名，最后一层命名空间

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

#endif //PAP_COMMON_GAME_DEFINE_ATTRIBUTE_CHARACTER_H_
