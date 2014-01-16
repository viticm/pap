/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id packet.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 14:37:21
 * @uses 游戏服务器网络包ID的定义，彻底改变天龙与武侠的设计模式，不过这里需要
 *       包含游戏基本定义中的宏，单独包含进来即可，不用担心ID重复
 *       （看似有局限，其实可以任意扩展）
 */
#ifndef PAP_SERVER_COMMON_GAME_DEFINE_ID_PACKET_ALL_H_
#define PAP_SERVER_COMMON_GAME_DEFINE_ID_PACKET_ALL_H_

namespace packet {

#include "server/common/game/define/id/packet/billinglogin.h"
#include "server/common/game/define/id/packet/serverserver.h"

}; //namespace packet

#endif //PAP_SERVER_COMMON_GAME_DEFINE_ID_PACKET_ALL_H_
