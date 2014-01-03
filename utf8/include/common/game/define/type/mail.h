/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id mail.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏邮件类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_MAIL_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_MAIL_H_

namespace mail {

typedef enum {
  kNormal = 0, //普通
  kSystem = 1, //系统
  kScript = 2, //脚本邮件，服务器端接收到此邮件后会调用一个脚本
  kSystemForPlayer = 3, //系统为玩家代发
} _enum;

typedef enum { //此定义必须与脚本ScriptGlobal.lua中的定义完全相同
  kScriptDivorce, //离婚
  kScriptBetrayProffer, //叛师
  kScriptFireDisciple, //开除徒弟
  kScriptUpdateAttribute, //更新离线玩家属性，上线时发送该脚本邮件
} script_enum;

typedef enum {
  kAttributeGuildId = 1, //帮会ID
  kAttributeMoney = 2, //金钱
} attribute_enum; //邮件可以更改的玩家属性

typedef enum {
  kAskLogin = 0, //用户刚登陆游戏时发送的邮件检查消息
  kAskSelf, //请求自己的邮件
} ask_enum;

}; //namespace mail

#endif //PAP_COMMON_GAME_DEFINE_TYPE_MAIL_H_
