/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id setting.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏设置的类型定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_TYPE_SETTING_H_
#define PAP_COMMON_GAME_DEFINE_TYPE_SETTING_H_

namespace setting {

typedef enum {
  kNone = 0, //
  kFlag, //游戏标记设置，如拒绝的配置
  kKey0, //0号快捷栏设置
  kKey1, //1号快捷栏设置
  kKey2, //2号快捷栏设置
  kKey3, //3号快捷栏设置
  kKey4, //4号快捷栏设置
  kKey5, //5号快捷栏设置
  kKey6, //6号快捷栏设置
  kKey7, //7号快捷栏设置
  kKey8, //8号快捷栏设置
  kKey9, //9号快捷栏设置
  kKey10, //右边0号快捷栏设置
  kKey11, //右边1号快捷栏设置
  kKey12, //右边2号快捷栏设置
  kKey13, //右边3号快捷栏设置
  kKey14, //右边4号快捷栏设置
  kKey15, //右边5号快捷栏设置
  kKey16, //右边6号快捷栏设置
  kKey17, //右边7号快捷栏设置
  kKey18, //右边8号快捷栏设置
  kKey19, //右边9号快捷栏设置
  kChatTab1Part1, //聊天自定义tab1设置第一部分 下同
  kChatTab1Part2,
  kChatTab2Part1,
  kChatTab2Part2,
  kChatTab3Part1,
  kChatTab3Part2,
  kChatTab4Part1,
  kChatTab4Part2,

} _enum;

typedef enum {
  kFlagRefuseAddFriend = 0, //拒绝添加好友
  kFlagRefuseReceiveMail = 1, //拒绝接收邮件
  kFlagRefuseReceiveStangerMail = 2, //拒绝陌生人邮件
  kFlagRefuseTeamInvite = 3, //拒绝组队邀请
  kFlagRefuseLookSpouseInfo = 16, //拒绝查看配偶资料
  kFlagRefuseTransaction = 17, //拒绝交易
  kFlagClosePopup = 18, //关闭当前泡泡框
  kFlagManualLevelUp = 19, //手动升级 --这个无效了
} flag_enum; //个人设置标记

}; //namespace setting

#endif //PAP_COMMON_GAME_DEFINE_TYPE_SETTING_H_
