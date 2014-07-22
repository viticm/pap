/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id effect.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 09:23:50
 * @uses vengine database effect struct module
 *       cn: 特效相关数据定义
 */
#ifndef VENGINE_DB_STRUCT_EFFECT_H_
#define VENGINE_DB_STRUCT_EFFECT_H_

namespace effect {

//特效定义
const uint16_t kDefineId = 501;
typedef struct {
  uint16_t id;
  const char* type;
  const char* param[6];
} define_t;

}; //namespace effect

#endif //VENGINE_DB_STRUCT_EFFECT_H_
