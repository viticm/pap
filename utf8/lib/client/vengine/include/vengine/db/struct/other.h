/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id other.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 10:15:41
 * @uses vengine database item struct module
 *       cn: 其他的数据定义 id 2001+
 */
#ifndef VENGINE_DB_STRUCT_OTHER_H_
#define VENGINE_DB_STRUCT_OTHER_H_

namespace other {

//表情和颜色转换字符
const kCodeConvertId = 2001;
typedef struct {
  uint16_t id;
  const char* code; //字符串形式的十六进制数字
  const char* name; //介绍
} codeconvert_t;

}; //namespace other

#endif //VENGINE_DB_STRUCT_OTHER_H_
