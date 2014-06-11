/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id client_toserver.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-4-8 16:07:17
 * @uses 客户端发送到服务器的网络包ID定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_ID_PACKET_CLIENT_TOSERVER_H_
#define PAP_COMMON_GAME_DEFINE_ID_PACKET_CLIENT_TOSERVER_H_

#include "common/game/define/macros.h" //must include this

namespace client_toserver {

enum packetid_enum {
  kFirst = CLIENT_TOSERVER_PACKETID_MIN,
  kHeartBeat,
  kLast,
  kMax = CLIENT_TOSERVER_PACKETID_MAX,
};

}; //namespace client_toserver

#endif //PAP_COMMON_GAME_DEFINE_ID_PACKET_CLIENT_TOSERVER_H_
