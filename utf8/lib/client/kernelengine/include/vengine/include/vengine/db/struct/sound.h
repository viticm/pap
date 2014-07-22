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

const uint16_t kInfoId = 401;
struct info_t {
  uint16_t id; //序号
  const char* file; //文件名
};

//环境音效列表
const uint16_t kEnvironmentId = 402;
typedef struct {
  uint16_t id;
  uint16_t soundid;
  uint32_t xposition; //声音源X坐标
  uint32_t yposition; //声音源Y坐标
  uint32_t canhear_distancemax; //能听见的最大距离
  int32_t looptimes; //连播次数
  int32_t interval; //间隔
  int32_t loopinterval; //下一次连播的时间间隔
} environment_t;

}; //namespace sound

#endif //VENGINE_DB_STRUCT_SOUND_H_
