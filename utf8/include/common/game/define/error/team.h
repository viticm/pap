/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id team.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:40:49
 * @uses 游戏队伍错误的定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_ERROR_TEAM_H_
#define PAP_COMMON_GAME_DEFINE_ERROR_TEAM_H_

namespace team {

typedef enum {
  kInviteTargetHasTeam = 0, //邀请对象已经属于某个组了
  kInviteTargetRefuse, //邀请对象拒绝邀请
  kInviterTeamFull, //邀请者队伍满
  kInviterLeaderRefuse, //邀请者的队长拒绝
  kDismissNotLeader, //解散的人不是队长
  kKickNotLeader, //踢人的不是队长
  kApplicantHasTeam, //申请人已经有队伍
  kByApplicantNotHasTeam, //被申请的人没有队伍
  kByApplicantTeamLeaderRefuse, //申请的队长拒绝申请人加入
  kByApplicantTeamFull, //被申请的队伍已满
  kByApplicantTeamLeaderGuidError, //被申请队伍的队长GUID发生了变化
  kAppointNewLeaderNotMember, //被委任的队长不是队伍成员
  kAppointOldLeaderNotMember, //委任的队长不是队伍成员
  kAppointNotInSameTeam, //委任不在同一队伍
  kAppointOldLeaderNotTeamLeader, //旧的队长已经不是队长了
  kByApplicantTeamLeaderCanNotAnser, //申请的队长无法答复
  kInviterNotInTeam, //邀请的人不在队伍中
  kApplicantWhenInTeam, //申请的人在已有队伍的情况下申请组队
  kTeamFull, //队伍满
  kInviteTargetRefuseSetting, //被邀请的人使用了拒绝邀请设置
  kTargetNotOnline, //目标不在线
} _enum;

typedef enum {
  kFollowTooFar, //过远
  kFollowIn, //已经进入组队跟随
  kFollowOnStall, //正在摆摊
  kFollowNotInState, //不在跟随状态
} follow_enum;

}; //namespace team

#endif //PAP_COMMON_GAME_DEFINE_ERROR_TEAM_H_
