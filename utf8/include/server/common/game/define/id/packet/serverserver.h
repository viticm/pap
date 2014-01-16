/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id serverserver.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 14:37:21
 * @uses 服务器之间通讯的包，公用
 */
#ifndef PAP_SERVER_COMMON_GAME_DEFINE_ID_PACKET_SERVERSERVER_H_
#define PAP_SERVER_COMMON_GAME_DEFINE_ID_PACKET_SERVERSERVER_H_

#include "common/game/define/macros.h" //must include this

namespace serverserver { //登陆服务器与验证服务器公用

typedef enum {
  kFirst = 0, //起始ID
  kConnect,
  kLast, /* the last packetid */
  kMax = 7,
 } packetid_enum;

}; //namespace serverserver

#endif //PAP_SERVER_COMMON_GAME_DEFINE_ID_PACKET_SERVERSERVER_H_
