/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id eventdefine.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-25 15:59:14
 * @uses vegine game event define id enum
 *       cn: 时间处理定义相关
 */
#ifndef VENGINE_GAME_EVENTDEFINE_H_
#define VENGINE_GAME_EVENTDEFINE_H_

#include "vengine/config.h"

namespace vengine_game {

namespace event_id {

enum _enum {
  kApplicationInit, //-- 游戏主程序初始化
  kSceneCutover, //-- 场景切换

/** 用户登陆{ **/
  kGameLoginShowSystemInfoAndCloseNet, //-- 打开系统提示信息和关闭网络
  kGameLoginShowSystemInfo, //-- 打开系统提示信息
  kGameLoginCloseSystemInfo, //-- 关闭系统提示信息
  kGameLoginOpenSelectServer, //-- 打开选择服务器
  kGameLoginCloseSelectServer, //-- 关闭选择服务器
  kGameLoginOpenAccountInput, //-- 打开账号输入界面
  kGameLoginCloseAccountInput, //-- 关闭账号输入界面
  kGameLoginShowSystemInfoNoButton, //-- 显示系统信息无按钮
  kGameLoginShowSystemInfoYesOrNo, //-- 参数0, 提示的字符串
                                   //-- 参数1, 对话框的类型
                                   //-- 0 -- 是否退出游戏
                                   //-- 1 -- 是否删除角色
                                   //-- 2 -- 是否更换帐号
  kGameLoginSelectLoginServer, //-- 选择一个login server
                               //-- 参数0 区域索引 参数1 服务器索引
  kGameLoginCleanAccount, //-- 清空显示的账号
  kGameLoginSelectArea, //-- 选择大区

/** }用户登陆 **/

  kUIToggleSystemFrame, //-- 切换显示系统菜单
  kUICloseSecondMenu, //-- 关闭二级菜单
  kUIChatAdjustMoveCtl, //-- 通知聊天窗口调整大小

  kChatChangePrivateName, //-- 修改聊天中的密语对象
  kChatContexMenu, //-- 聊天相关的快捷菜单

  kSuperToolTip, //-- 提示框 arg0 - 显示/隐藏 1,0
                          // arg1 - 类型 "skill", "lifeability", "item", 
                          // "xinfa", "pet_skill"
                          // arg2, arg3 鼠标位置

  kNewDebugMessage, // -- 新的调试消息
  kNetClose, // --关闭网络

};

}; //namespace event_id

}; //namespace vengine_game

#endif //VENGINE_GAME_EVENTDEFINE_H_
