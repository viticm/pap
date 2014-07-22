/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id struct.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-22 18:52:54
 * @uses vengine database struct defines
 *       cn: 客户端所有文件数据结构定义，包含该文件则包含了所有定义
 *           注意本文件没有自己的模块命名空间
 */
#ifndef VENGINE_DB_STRUCT_ALL_H_
#define VENGINE_DB_STRUCT_ALL_H_

#include "vengine/config.h"

namespace vengine_db {

namespace structs {

#include "vengine/db/struct/character.h"
#include "vengine/db/struct/creature.h" 
#include "vengine/db/struct/effect.h" 
#include "vengine/db/struct/item.h"
#include "vengine/db/struct/other.h"
#include "vengine/db/struct/scene.h"
#include "vengine/db/struct/skill.h"
#include "vengine/db/struct/sound.h"
#include "vengine/db/struct/ui.h"

}; //namespace structs

}; //namespace vengine_db

#endif //VENGINE_DB_STRUCT_ALL_H_
