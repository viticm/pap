/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-31 17:34:43
 * @uses server and client net model base config file
 */
#ifndef PAP_COMMON_NET_CONFIG_H_
#define PAP_COMMON_NET_CONFIG_H_

#include "common/base/type.h"

namespace pap_common_net {

namespace packet {

class Base;
class Factory;
class FactoryManager;

}; //namespace packet

namespace socket {

class Base;
class InputStream;
class OutputStream;

}; //namespace socket

}; //namespace pap_common_net


//server connection
namespace pap_server_common_net {

namespace connection {

class Base;

}; //namespace connection

}; //namespace pap_server_common_net

#endif //PAP_COMMON_NET_CONFIG_H_
