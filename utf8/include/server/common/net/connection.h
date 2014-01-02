/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id connection.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-2 11:17:20
 * @uses server net connect information
 *       cn: 连接信息，其中ID为用户ID，即玩家ID，用于管理网络连接
 */

#ifndef PAP_SERVER_COMMON_NET_CONNECTION_H_
#define PAP_SERVER_COMMON_NET_CONNECTION_H_

#include "server/common/net/config.h"

namespace pap_server_common_net {

class Connection {

 public:
   Connection();
   ~Connection();


};

}; //namespace pap_common_net

#endif //PAP_SERVER_COMMON_NET_CONNECTION_H_
