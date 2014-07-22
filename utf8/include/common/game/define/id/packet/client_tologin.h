/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id client_tologin.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-4-14 13:59:57
 * @uses 客户端发送到登陆服务器的网络包ID定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_ID_PACKET_CLIENT_TOLOGIN_H_
#define PAP_COMMON_GAME_DEFINE_ID_PACKET_CLIENT_TOLOGIN_H_

#include "common/game/define/macros.h" //must include this

namespace client_tologin {

enum packetid_enum {
  kFirst = CLIENT_TOLOGIN_PACKETID_MIN,
  kConnect,
  kAskLogin,
  kLast,
  kMax = CLIENT_TOLOGIN_PACKETID_MAX,
};

}; //namespace client_toserver

#endif //PAP_COMMON_GAME_DEFINE_ID_PACKET_CLIENT_TOLOGIN_H_
