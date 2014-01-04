/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id mibao.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 10:43:21
 * @uses 密保相关常用大小长度的定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_SIZE_MIBAO_H_
#define PAP_COMMON_GAME_DEFINE_SIZE_MIBAO_H_

namespace mibao { //密保相关

typedef enum {
  kUnitNameLength = 2, //密保单元键名的长度
  kUnitValueLength = 2, //密保单元键值的长度
  kUnitNumber = 3, //密保卡一组有效数据的密保单元个数
  // 7 * 7
  kTableRowMax = 7, //密保使用的表的最大行数
  kTableColumnMax = 7, //密保使用的表的最大列数
} _enum;

}; //namespace mibao

#endif //PAP_COMMON_GAME_DEFINE_SIZE_MIBAO_H_
