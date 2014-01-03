/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id team.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 队伍操作结果所有定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_RESULT_TEAM_H_
#define PAP_COMMON_GAME_DEFINE_RESULT_TEAM_H_

namespace team {

typedef enum {
  kMemberEnter, //成员加入
  kMemberLeave, //成员离队
  kLeaderLeave, //队长离队
  kDismiss, //解散
  kMemberKick, //成员被踢出
  kAppoint, //队长任命
  kRefresh, //请求队伍信息的重新刷新
  kStartChangeScene, //开始切换场景
  kEnterScene, //成员进入场景
  kChangeSceneRefreshServerInfo, //玩家跳转场景后，给服务器刷新队伍消息
  kMemberOffline, //成员离线
} _enum;

typedef enum { //队伍跟随
  kFollowMemberRefuse, //队员拒绝
  kFollowMemberEnter, //队员进入组队跟随
  kFollowMemberStop, //队员退出组队跟随
  kFollowNoticeFlag, //通知客户端进入组队跟随的标记
} follow_enum;

}; //namespace team

#endif //PAP_COMMON_GAME_DEFINE_RESULT_TEAM_H_
