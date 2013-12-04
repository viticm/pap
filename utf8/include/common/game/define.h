#ifndef PAP_COMMON_GAME_DEFINE_H_
#define PAP_COMMON_GAME_DEFINE_H_

//-- global
#define INVALID_COUNTRY -1
#define INVALID_JOB -1
#define INVALID_SEX -1
#define INVALID_GUILD_ID -1
#define INVALID_RESOURCE -1
#define INVALID_RULERID -1
#define INVALID_PRICE 0
#define INVALID_ITEM_ID 0
#define INVALID_ITEM_POS -1
#define INVALID_TIME 0xFFFFFFFF
#define INVALID_PAI_TYPE 0
#define INVALID_SOUL_TYPE 0
#define BASE_BAG_POS 185
#define GUILD_LEVEL_MAX 5 //公会最大等级

typedef enum {
  kTimeZhi, //子
  kTimeChou, //丑
  kTimeYin, //寅
  kTimeMao, //卯
  kTimeChen, //辰
  kTimeSi, //巳
  kTimeWu, //午
  kTimeWei, //未
  kTimeShen, //申
  kTimeYou, //酉
  kTimeXu, //戌
  kTimeHai, //亥
} world_time_enum; //old china time

//global --

//-- normal

namespace pap_common_game {

namespace define {

//-- attr
namespace attr { //属性 --虽然是三级嵌套，但是书写起来很方便

namespace character { //角色
}; //namespace character

namespace pet { //宠物
}; //namespace pet


}; //namespace attr
//attr --

//-- item
namespace item {
}; //namespace item
//item --

}; //namespace define

}; //namespace pap_common_game

//normal --

#endif //PAP_COMMON_GAME_DEFINE_H_
