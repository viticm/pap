/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id sharememory.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 11:26:25
 * @uses 游戏服务器共享内存相关类型的所有定义
 */
#ifndef PAP_SERVER_COMMON_GAME_DEFINE_TYPE_SHAREMEMORY_H_
#define PAP_SERVER_COMMON_GAME_DEFINE_TYPE_SHAREMEMORY_H_

namespace sharememory {

typedef enum {
  kKeyInvalid = -1,
  kKeyHuman = 1,
  kKeyGuild = 2,
  kKeyMail = 3,
  kKeyPlayerShop = 4,
  kKeyGlobalData = 5,
  kKeyCommisionShop = 6,
  kKeyItemSerial = 7,
  kKeyUserData = 8,
} key_enum;

}; //namespace sharememory

#endif //PAP_SERVER_COMMON_GAME_DEFINE_TYPE_ALL_H_
