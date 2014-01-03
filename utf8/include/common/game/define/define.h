/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id define.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-17 15:58:56
 * @uses 游戏公用基础模块的基本定义文件
 */
#ifndef PAP_COMMON_GAME_DEFINE_H_
#define PAP_COMMON_GAME_DEFINE_H_

#include "common/game/config.h"



//global --

//-- normal

namespace pap_common_game {

namespace define {


//-- status
namespace status {

namespace share_memory {

typedef enum {
  kUseNever = 0, //从未使用过
  kUseServer = 1, //server 占用
  kUseServerHasClean = 2, //server 正常shutdown ，已经清除
  kUseWorld = 3, //world 占用
  kUseWorldHasClean = 3, //world 正常shutdown ，已经清除
} use_enum;

}; //namespace share_memory

}; //namespace status
//status --

//-- result
namespace result {



namespace user_data {

typedef enum {
  kNotFind = 0, //没有发现用户数据
  kHave, //拥有用户数据
  kCaching, //目标服务器的用户数据正在缓存
  kServerCrash, //用户Server已经Crash,可能还在缓存中,Server正在处理这块缓存
  kKeyError, //验证码错误
} _enum;

}; //namespace user_data

}; //namespace result
//result --

//-- value
namespace value { //值的定义


namespace relation {

typedef enum {
  kFriendOffset = 0, 
  kBlackOffset = 80,
} _enum;

}; //namespace relation

namespace combat {

typedef enum {
  kAcceptableDistanceErrorForHuman = 2,
  kAcceptableDistanceErrorForNpc = 1,
} acceptable_distance_error_enum;

}; //namespace combat


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

}; //namespace value
//value --

//-- index
namespace index {

namespace skill {

typedef enum {
  kPetInvalid = -1,
  kPetControlByPlayer,
  kPetControlByAI,
  kPetControlByMeiPai,
  kPetCount,
} pet_enum;

}; //namespace skill

}; //namespace index
//index --

}; //namespace define

}; //namespace pap_common_game

//normal --

#endif //PAP_COMMON_GAME_DEFINE_H_
