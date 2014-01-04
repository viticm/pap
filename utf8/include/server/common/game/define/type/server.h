/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id server.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 11:26:25
 * @uses 游戏服务器服务器相关类型的定义
 */
#ifndef PAP_SERVER_COMMON_GAME_DEFINE_TYPE_SERVER_H_
#define PAP_SERVER_COMMON_GAME_DEFINE_TYPE_SERVER_H_

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

#endif //PAP_SERVER_COMMON_GAME_DEFINE_TYPE_SERVER_H_
