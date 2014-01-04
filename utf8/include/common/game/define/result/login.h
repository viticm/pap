/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id login.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 登陆操作结果所有定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_RESULT_LOGIN_H_
#define PAP_COMMON_GAME_DEFINE_RESULT_LOGIN_H_

namespace login {

typedef enum {
  kSuccess, //成功
  kAuthFail, //验证失败
  kBadVersion, //版本错误
  kPointNotEnough, //点数不足，请充值 --点卡模式
  kServiceStop, //暂时停止服务
  kOtherOnline, //在其他游戏世界在线
  kUnknownError, //未知错误
  kForbit, //账号停权
  kUserOnline, //角色在线，直接踢出
  kNeedRegister, //passport 中存在,需要注册
  kRegisterSuccess, //passport 注册成功
  kRegisterAlreadyExist, //passport 账号存在
  kRegisterFail, //passport 注册失败
  kPassportNeedActive, //passport 需要激活
  kRegisterNeedWeb, //必须通过网站注册
  kCheckMibaoStatus, //提醒用户检查密保的使用状态
  kMibaoCheckError, //密保检查不通过
  kWrongIpAddress, //错误的IP地址
  kLockByMobile, //已被手机锁定
  kFagiugeLoginOne, //防沉迷用户只允许登陆一个账户，身份证通过则无此限制
  kMacError, //MAC 地址不对
  kNotAcceptNewLicense, //没有接受新的许可协议
  kMustWait, //必须等待登陆，默认20秒
  kNoticeSafeSign, //提醒用户去网站填写实名和绑定密保卡
  kOnlySuccess, //此状态不重新设置LoginPlayer的安全标识
  kSafeSignSuccess, //安全状态确认成功
} _enum;
 
}; //namespace login

#endif //PAP_COMMON_GAME_DEFINE_RESULT_LOGIN_H_
