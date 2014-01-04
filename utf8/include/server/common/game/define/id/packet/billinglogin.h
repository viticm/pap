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

static const uint8_t kBillingLoginNumber = 10; //公用ID个数

namespace billinglogin { //登陆服务器与验证服务器公用

typedef enum {
  kMax = BILLINGLOGIN_PACKETID_MIN + kBillingLoginNumber;
 } packetid_enum;

}; //namespace billinglogin

namespace billing_tologin { //验证服务器发送给登陆服务器

typedef enum {
  kResultAuth = BILLINGLOGIN_PACKETID_MIN + kBillingLoginNumber, /*begin {*/
  kMax = (BILLINGLOGIN_PACKETID_MAX + kBillingLoginNumber) / 2, /*end }*/
} packetid_enum;

}; //namespace billing_tologin

namespace login_tobilling { //登陆服务器发送给验证服务器

typedef enum {
  /*begin {*/
  kAskAuth = (BILLINGLOGIN_PACKETID_MAX + kBillingLoginNumber) / 2, 
  kMax = BILLINGLOGIN_PACKETID_MAX, 
  /*end }*/
} packetid_enum;

}; //namespace login_tobilling

#endif //PAP_SERVER_COMMON_GAME_DEFINE_ID_PACKET_ALL_H_
