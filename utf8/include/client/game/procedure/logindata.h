/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id logindata.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-8 13:34:30
 * @uses client game logindata defines
 */
#ifndef CLIENT_GAME_PROCEDURE_LOGINDATA_H_
#define CLIENT_GAME_PROCEDURE_LOGINDATA_H_

namespace procedure {

const uint8_t kLoginServerInAreaCount = 6;
enum loginserver_status_enum {
  kLoginServerStatusFull = 0, //爆满
  kLoginServerStatusBusy, //拥挤
  kLoginServerStatusNormal, //正常
  kLoginServerStatusIdle, //空闲
  kLoginServerStatusStop, //维护
};

enum netprovide_enum { //网络供应商
  kNetProvideCNII = 0, //电信
  kNetProvideCNC, //联通
  kNetProvideOther, //其他
};

//登陆服务器信息结构体
struct loginserver_info_t {
  loginserver_info_t() {
    memset(this, 0, sizeof(loginserver_info_t));
  };
  char name[128]; //服务器名
  char ip[64]; //IP
  loginserver_status_enum status; //状态
  uint8_t recommendlevel; //推荐等级
  bool isnew; //是否为新服务器
  uint8_t areaid; //区域ID（大区）
  char tooltip[128]; //描述
};

const uint8_t area_haveserver_max = 6; //每个大区拥有的服务器最大值
//大区信息结构体
struct areainfo_t {
  areainfo_t() {
    memset(this, 0, sizeof(areainfo_t));
  };
  char name[128];
  netprovide_enum provide;
  loginserver_info_t[area_haveserver_max];
};

//typedef areainfo_t* areainfo_pointer;

struct loginserver_position_t {
  int32_t areaindex;
  int32_t serverindex;
};

//typedef loginserver_position_t* loginserver_position_pointer;

typedef std::vector<loginserver_position_t> loginserver_position_vector;

struct provideinfo_t {
  loginserver_position_vector idle_loginserver_vector;
  loginserver_position_vector normal_loginserver_vector;
  loginserver_position_vector busy_loginserver_vector;
  loginserver_position_vector full_loginserver_vector;
};

}; //namespace procedure

#endif //CLIENT_GAME_PROCEDURE_LOGINDATA_H_
