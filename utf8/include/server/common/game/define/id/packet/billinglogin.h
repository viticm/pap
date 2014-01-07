/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id billinglogin.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 14:37:21
 * @uses 验证（消费服务器）与登录服务器之间用到的包ID
 */
#ifndef PAP_SERVER_COMMON_GAME_DEFINE_ID_PACKET_ALL_H_
#define PAP_SERVER_COMMON_GAME_DEFINE_ID_PACKET_ALL_H_

#include "common/game/define/macros.h" //must include this

namespace billinglogin { //登陆服务器与验证服务器公用

typedef enum {
  kFirst = BILLINGLOGIN_PACKETID_MIN, //起始ID
  kLast, /* the last packetid */
  kMax = BILLINGLOGIN_PACKETID_MAX,
 } packetid_enum;

}; //namespace billinglogin

namespace billing_tologin { //验证服务器发送给登陆服务器

typedef enum {
  kFirst = BILLING_TOLOGIN_PACKETID_MIN,
  kResultAuth, /*begin {*/
  kLast, /* the last packetid */
  kMax = BILLING_TOLOGIN_PACKETID_MAX, /*end }*/
} packetid_enum;

}; //namespace billing_tologin

namespace login_tobilling { //登陆服务器发送给验证服务器

typedef enum {
  /*begin {*/
  kAskAuth = LOGIN_TOBILLING_PACKETID_MIN, 
  kLast, /* the last packetid */
  kMax = LOGIN_TOBILLING_PACKETID_MAX,
  /*end }*/
} packetid_enum;

}; //namespace login_tobilling

#endif //PAP_SERVER_COMMON_GAME_DEFINE_ID_PACKET_ALL_H_
