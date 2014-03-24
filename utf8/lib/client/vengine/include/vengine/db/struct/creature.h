/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id creature.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-23 16:30:49
 * @uses vengine database creature struct module
 *       cn: 生物（怪物）相关数据定义
 */
#ifndef VENGINE_DB_STRUCT_CREATURE_H_
#define VENGINE_DB_STRUCT_CREATURE_H_

namespace creature {

const uint8_t kMonsterEffectMax = 4;
struct monstereffect_t {
  const char* effect;
  const char* bind;
  mounteffect_t() {
    effect = NULL;
    bind = NULL;
  };
};

const uint16_t kAttributeId = 201;
typedef struct {
  int32_t id; //怪物编号
  const char* name; //怪物名称
  uint8_t level; //怪物等级，(0 -  255)
  int32_t info1[3]; // 刷新周期 最小伤血百分比 础经验获得
  int32_t attackrate_near; //近程攻击获得
  int32_t attackrate_far; //远程攻击获得
  int32_t attackrate_magicnear; //近程外功攻击
  int32_t attackrate_magicfar; //远程外功攻击
  int32_t defencenear; //近程防御
  int32_t defencefar; //远程防御
  int32_t defence_magicnear; //近程外功防御
  int32_t defence_magicfar; //远程外功防御
  uint32_t HPmax; //血量上限
  uint32_t MPmax; //真气上限
  uint32_t HPrestore; //血量回复
  uint32_t MPrestore; //真气回复
  int32_t hit; //命中
  int32_t miss; //闪避
  int32_t critrate; //暴击，会心
  int32_t toughness; //韧性
  int32_t attackgold; //属性攻击（金）
  int32_t attackwood; //属性攻击（木）
  int32_t attackwater; //属性攻击（水）
  int32_t attackfire; //属性攻击（火）
  int32_t attacksoil; //属性攻击（土）
  int32_t defencegold; //属性防御（金）
  int32_t defencewood; //属性防御（木）
  int32_t defencewater; //属性防御（水）
  int32_t defencefire; //属性防御（火）
  int32_t defencesoil; //属性防御（土）
  int32_t scriptid; //调用脚本ID
  uint32_t modelid; //模型ID
  const char* headportrait; //头像ICON
  bool canswerve; //是否可以随玩家转向
  bool is_displayname; //是否显示头顶名称
  float nameboard_height; //名字板高度
  float ringselect_size; //选中环大小
  float shadowsize; //阴影大小
  int32_t attacktime[2]; //攻击动作时间 攻击冷却时间
  int32_t idletime; //休闲间隔时间
  int32_t speed; //移动速度
  int32_t walkspeed; //步行速度
  int32_t attackspeed; //攻击速度
  const char* armid; //武器调用ID
  int32_t info2[4]; //马调用ID 基础AI 扩展AI 阵营
  bool cannot_beattack; //是否不可攻击
  bool canhandle; //是否可以交互
  int32_t friendliness; //友好值
  uint8_t bossflag; //boss标记
  int32_t snappy_immunityid; //瞬间免疫ID
  int32_t duration_immunityid; //持续免疫ID
  int32_t drop[4]; //掉落分配半径(米) 掉落最大有效组 掉落物品组 掉落概率
  mounteffect_t mounteffect[kMountEffectMax]; //绑在怪物身上的特效
  const char* horse_dropid; //马掉落id
  int32_t dripid; //掉落ID
  int32_t type; //NPC类型
  const char* type_name; //NPC类型名
  const char* filtername; //NPC名称拼音索引
  int32_t critical_hitdamage; //暴击伤害
  int32_t rage; //怒气
  bool is_playanimation; //是否有搁挡或者闪避动作
} attribute_t;

const uint16_t kPetAttributeExtendId = 202;
typedef struct {
  uint32_t type; //宠物编号
  uint8_t takelevel; //携带等级
  const char* name; //名称
  int8_t camp; //阵营
  int32_t reserve1; //保留
  int32_t reserve2; //保留
  uint8_t foodtype; //食物类型
  uint8_t learnskill_number; //学会的技能数量
  int32_t positiveskill; //主动技能
  int32_t passiveskill[4]; //被动技能
  uint32_t life; //标准寿命
  uint32_t powerpreception; //力量资质
  uint32_t physiquepreception; //体力资质
  uint32_t animapreception; //灵气资质
  uint32_t agilitypreception; //身法资质
  uint32_t intellectpreception; //智力资质
  uint16_t growrate[5]; //成长率
  int32_t cowardicerate; //胆小几率
  int32_t warinessrate; //谨慎几率
  int32_t loyalismrate; //忠诚几率
  int32_t canninessrate; //精明几率
  int32_t valourrate; //勇猛几率
} petattribute_extend_t;

//声音定义表
const uint16_t kSoundId = 203;
typedef struct {
  int32_t id;
  int32_t underattack;
  int32_t attack;
  int32_t death;
} sound_t;

//怪物泡泡
const uint16_t kMonsterPaoPaoId = 204;
typedef struct {
  uint16_t id;
  const char* text; //头顶文字
} monster_paopao_t;

//宠物升级经验表
const uint16_t kPetLevelUpId = 205;
typedef struct {
  uint8_t id;
  uint32_t experience; //经验
} pet_levelup_t;

//坐骑基础数据表
const uint16_t kMountBaseDataId = 206;
typedef struct {
  uint16_t id; //坐骑ID
  const char* name; //坐骑名称
  uint8_t level; //坐骑等级
  uint8_t requirement_level; //携带等级
  const char* childid; //还童ID
  const char* matingid; //交配ID
  bool canmating; //是否可以交配
  bool isaberrance; //是否变异
  uint8_t daishu; //繁殖代数
  int32_t attach; //坐骑的归属
  int32_t survivaltime; //无主坐骑存活时间
  uint32_t powermin; //初始最小力量
  uint32_t powermax; //初始最大力量
  uint32_t agilitymin; //初始最小敏捷
  uint32_t agilitymax; //初始最大敏捷
  uint32_t intellectmin; //初始最小智力
  uint32_t intellectmax; //初始最大智力
  uint32_t physiquemin; //初始最小体质
  uint32_t physiquemax; //初始最大体质
  uint32_t power_zizhi_min; //初始最小力量资质
  uint32_t power_zizhi_max; //初始最大力量资质
  uint32_t agility_zizhi_min; //初始最小敏捷资质
  uint32_t agility_zizhi_max; //初始最大敏捷资质
  uint32_t intellect_zizhi_min; //初始最小智力资质
  uint32_t intellect_zizhi_max; //初始最大智力资质
  uint32_t physique_zizhi_min; //初始最小体质资质
  uint32_t physique_zizhi_max; //初始最大体质资质
  uint16_t savvymin; //初始最小悟性
  uint16_t savvymax; //初始最大悟性
  uint16_t basicmin; //初始最小根骨
  uint16_t basicmax; //初始最大根骨
  uint16_t growrate_min; //初始最小成长率
  uint16_t growrate_max; //初始最大成长率
  int32_t speed; //移动速度
  uint16_t modelid; //模型ID
  uint16_t modelid_show; //对应表现ID
  uint8_t skillnumber; //技能数量
  const char* skill[6]; //技能数据
  int32_t savvyskill; //坐骑领悟技能ID
} mount_basedata_t;

}; //namespace creature

#endif //VENGINE_DB_STRUCT_CREATURE_H_
