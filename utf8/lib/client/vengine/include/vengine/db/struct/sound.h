/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id sound.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 09:20:26
 * @uses vengine database sound struct module
 *       cn: 声音相关数据定义
 */
#ifndef VENGINE_DB_STRUCT_SOUND_H_
#define VENGINE_DB_STRUCT_SOUND_H_

namespace sound {

const uint16_t kSoundInfoId = 401;
typedef struct {
  uint16_t id; //序号
  const char* file; //文件名
} soundinfo_t;

}; //namespace sound

#endif //VENGINE_DB_STRUCT_SOUND_H_
