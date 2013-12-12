/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id define.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-4 16:18:56
 * @uses server game base define file
 *      cn: 这个是基本定义文件，定义了游戏中需要的宏以及枚举
 */
#ifndef PAP_SERVER_COMMON_GAME_CONFIG_H_
#define PAP_SERVER_COMMON_GAME_CONFIG_H_

#include "server/common/game/config.h"

namespace pap_server_common_game {

namespace define {
//-- type
namespace type {

namespace share_memory {

typedef enum {
  kKeyInvalid = -1,
  kKeyHuman = 1,
  kKeyGuild = 2,
  kKeyMail = 3,
  kKeyPlayerShop = 4,
  kKeyGlobalData = 5,
  kKeyCommisionShop = 6,
  kKeyItemSerial = 7,
  kKeyUserData = 8,
} key_enum;

}; //namespace share_memory

namespace server { //服务器类型

typedef enum {
  kGame = 0, //游戏服务器（主服务器）
  kLogin = 1, //登陆服务器
  kShareMemory = 2, //共享内存服务器
  kWorld = 3, //世界服务器
  kBilling = 4, //验证服务器（包括元宝等的充值以及与游戏后台交互）
  kCount,
} _enum;

}; //namespace server


}; //namespace type
//type --

}; //namespace define

}; //namespace pap_server_common_game

#endif //PAP_SERVER_COMMON_GAME_CONFIG_H_
