/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id connection.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-8 19:32:36
 * @uses 游戏服务器连接的状态
 */
#ifndef PAP_SERVER_COMMON_GAME_DEFINE_STATUS_CONNECTION_H_
#define PAP_SERVER_COMMON_GAME_DEFINE_STATUS_CONNECTION_H_

namespace connection {

typedef enum {
  kBillingEmpty = 400,
  kBillingConnect,
  kWorldConnect,
  kWorldNormal,
} _enum;

}; //namespace connection

#endif //PAP_SERVER_COMMON_GAME_DEFINE_STATUS_CONNECTION_H_

