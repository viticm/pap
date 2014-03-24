/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id ui.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 10:50:36
 * @uses vengine database character struct module
 *       cn: UI相关数据定义
 */
#ifndef VENGINE_DB_STRUCT_UI_H_
#define VENGINE_DB_STRUCT_UI_H_

namespace ui {

const uint16_t kLayoutDefineId = 801;
typedef struct {
  uint16_t id;
  const char* name;
  const char* layout;
  int32_t demise;
  const char* script;
  uint16_t opensound;
  uint16_t closesound;
  const char* help;
  const char* description;
} layoutdefine_t;

}; //namespace ui

#endif //VENGINE_DB_STRUCT_UI_H_
