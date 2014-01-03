/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id relation.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 关系分组定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_GROUP_RELATION_H_
#define PAP_COMMON_GAME_DEFINE_GROUP_RELATION_H_

namespace relation {

typedef enum {
  kFriendAll = 0, //全部好友
  kFriend1, //好友组1
  kFriend2, //好友组2
  kFriend3, //好友组3
  kFriend4, //好友组4
  kBlack, //黑名单
  kCount,
  kFriendTemp, //临时好友
} _enum;

}; //namespace relation

#endif //PAP_COMMON_GAME_DEFINE_GROUP_RELATION_H_
