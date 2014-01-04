/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id userdata.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-4 11:06:39
 * @uses 游戏服务器用户数据结果的所有定义
 */
#ifndef PAP_SERVER_COMMON_GAME_DEFINE_RESULT_USERDATA_H_
#define PAP_SERVER_COMMON_GAME_DEFINE_RESULT_USERDATA_H_

namespace userdata {

typedef enum {
  kNotFind = 0, //没有发现用户数据
  kHave, //拥有用户数据
  kCaching, //目标服务器的用户数据正在缓存
  kServerCrash, //用户Server已经Crash,可能还在缓存中,Server正在处理这块缓存
  kKeyError, //验证码错误
} _enum;

}; //namespace user_data

#endif //PAP_SERVER_COMMON_GAME_DEFINE_RESULT_USERDATA_H_
