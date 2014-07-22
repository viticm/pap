/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id character.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-22 19:26:00
 * @uses vengine database character struct module
 *       cn: 角色相关数据定义
 */
#ifndef VENGINE_DB_STRUCT_CHARACTER_H_
#define VENGINE_DB_STRUCT_CHARACTER_H_

namespace character {

//主角种族
const uint16_t kRaceId = 101; //数据表中的id
typedef struct {
  uint8_t id;
  int32_t modelid; //模型ID
  int32_t hair; //头发
  int32_t face; //脸
  int32_t shoulder; //肩
  int32_t body; //身体
  int32_t hand; //手
  int32_t foot; //脚
  uint32_t idleinterval; //休闲时间间隔
} race_t;

//主角头发模型
const uint16_t kHairId = 102;
typedef struct {
  uint16_t id;
  uint8_t race;
  const char* meshfile;
  const char* showname;
} hair_t;

//主角脸型
const uint16_t kFaceId = 103;
typedef struct {
  uint16_t id;
  uint8_t race;
  const char* meshfile;
  const char* showname;
} face_t;

//主角动作组
const uint16_t kActionSetId = 104;
const uint8_t kWeaponTypeMax = 14;
typedef struct {
  uint16_t id;
  const char* weaponset[kWeaponTypeMax]; //对应武器类型
  bool hideweapon; //是否隐藏武器
  uint32_t appoint_weaponid; //指定的武器ID
  const char* description; //描述
} actionset_t;

//主角特效
const uint16_t kEffectId = 105;
typedef struct {
  uint16_t id;
  uint16_t effect1;
  uint16_t effect2;
  const char* locator;
  int32_t soundid;
  const char* weaponlocator;
} effect_t;

//主角升级经验
const uint16_t kExpId = 106;
typedef struct {
  uint8_t id;
  uint32_t effectneed;
} exp_t;

//外形ID对应模型名称
const uint16_t kModelId = 107;
enum {
  kMountNumberMax = 20,
  kSoundNumberMax = 6, //数值根据地面的类型得出
};
typedef struct {
  uint16_t id;
  float fusetime; //动作融合时间
  const char* modelname; //模型文件
  int16_t soundid[kSoundNumberMax]; //不同地面跑步的声音
  const char* actionset_none; //不使用坐骑的动作文件
  const char* actionset_mount[kMountNumberMax]; //使用坐骑的动作文件
} model_t;

//头像
const uint16_t kHeadPortrait = 108;
typedef struct {
  uint16_t id;
  uint8_t race;
  const char* imagesetname;
} headportrait_t;

//坐骑表
const uint16_t kMountId = 109;
const uint8_t kMountEffectMax = 8;
typedef struct {
  const char* effectlocator; //特效绑定点
  const char* effectname; //特效名称
} mounteffect_t;

typedef struct {
  uint16_t id;
  float leaveground_height; //距离地面的距离，特殊坐骑用
  uint16_t modelid;
  int16_t character_actionindex; //人物骑乘时的动作组
  mounteffect_t effectinfo[kMountEffectMax]; //特效信息
} mount_t;

//称号表
const uint16_t kTitleInfoId = 110;
typedef struct {
  uint16_t id;
  uint8_t type;
  const char* color; //显示颜色
  bool defaultshow; //默认是否显示
  const char* man; //男性称号
  const char* woman; //女性称号
  const char* description; //描述
  int32_t timelimit; //时限
  int16_t effectid; //效果ID
  const char* reclaimcause; //回收原因
  int16_t groupid; //组合称号ID
} titleinfo_t;

//阵营
const uint16_t kCampDataId = 111;

//人物等级携带金钱上限
const uint16_t kLevelMoneyMaxId = 112;
typedef struct {
  uint8_t id;
  uint32_t moneymax;
  uint8_t level; //等级
} level_moneymax_t;

//改变发型消耗表
const uint16_t kHairStyleCostId = 113;
typedef struct {
  uint16_t id;
  int32_t itemid; //物品ID
  int32_t itemcount; //消耗物品数量
  uint8_t sex; //性别
} hairstyle_cost_t;

}; //namespace character

#endif //VENGINE_DB_STRUCT_CHARACTER_H_
