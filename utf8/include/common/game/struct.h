/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id struct.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-4 16:18:56
 * @uses server and clinet use structs
 *      cn: 这是整个游戏的核心结构，所有的服务器与客户端公用的类与结构都需放到此处
 */
#ifndef PAP_COMMON_GAME_STRUCT_H_
#define PAP_COMMON_GAME_STRUCT_H_

#include "common/game/config.h"

namespace pap_common_game {

namespace skill {

typedef enum {
} type_enum;

typedef enum {
} select_type_enum;

typedef enum {
} logic_target_enum;

typedef enum {
} behavior_type_enum;

typedef enum {
} action_type_enum;

struct filedb_data_t { //skill base data template(skill_data.txt)
};

struct filedb_xinfa_data_t { //心法的数据结构(xinfa.txt)
};

struct experience_t { //技能熟练度
};

struct own_data_t {
};

struct own_xinfa_data_t {
};

struct damage_info_t {
};

struct buff_impact_info_t {
};

struct callof_info_t {
};

class Cooldown {
};

template <int32_t size>
class CooldownList {
};

typedef enum { //技能未击中的类型枚举
} miss_flag_enum;

}; //namespace skill

namespace impact {

struct filedb_directly_t { //impact_directly.txt
}; //特效

struct filedb_buff_t { //impact_buff.txt
}; //buff

typedef enum {
  kDropBox = -3, //drop
  kDie = -2, //die
  kMiss = -1, //miss
  kPhysicsDamage, //物理伤害
  kMagicDamage, //内功伤害
  kColdDamage, //冰伤害
  kFireDamage, //火伤害
  kElectricityDamage, //电伤害
  kPoisonDamage, //毒伤害
  kCutIre, //减怒气
} direct_type_enum;

struct direct_t {
};

class Own {
};

}; //namespace impact



}; //namespace pap_common_game

#endif //PAP_COMMON_GAME_STRUCT_H_
