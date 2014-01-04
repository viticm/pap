/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id all.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 11:44:33
 * @uses 游戏所有常见结构
 */
#ifndef PAP_COMMON_GAME_STRUCTS_SKILL_H_
#define PAP_COMMON_GAME_STRUCTS_SKILL_H_

#include "server/common/game/config.h"

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

#endif //PAP_COMMON_GAME_STRUCTS_SKILL_H_
