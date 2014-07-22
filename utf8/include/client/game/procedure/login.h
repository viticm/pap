/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id login.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-8 14:02:13
 * @uses client procedure of login
 */
#ifndef PAP_CLIENT_GAME_PROCEDURE_LOGIN_H_
#define PAP_CLIENT_GAME_PROCEDURE_LOGIN_H_

#include "client/game/procedure/logindata.h"
#include "client/game/procedure/base.h"

namespace procedure {

const uint8_t kProvideCount = 3; // 网络供应商数量

class Login : public Base {

 public:
   Login();
   virtual ~Login();

 public:
   enum status_enum {
     kStatusDebug = 0, //调试
     kStatusSelectServer, //选择服务器阶段
     kStatusDisconnect, //尚未登陆，断开的状态
     kStatusConnecting, //连接中
     kStatusConnectSuccess, //连接成功
     kStatusConnectFailed, //连接失败
     kStatusBeginRequesting, //发送密码之前状态
     kStatusRequesting, //发送密码到服务器等待验证
     kStatusSuccess, //账号验证成功
     kStatusFailed, //账号验证失败
     kStatusQueue, //正在排队
     kStatusFirstLogin, //首次登陆
     kStatusChangeScene, //切换场景的重新登陆
   };
   char serverip_[64];
   uint16_t serverport_;
   areainfo_t areainfo_;
   int32_t areacount_;
   enum loadconfig_enum {
     kLoadConfigSuccess = 0, //成功
     kLoadConfigNoFile, //找不到配置文件
     kLoadConfigNoArea, //找不到区域
     kLoadConfigOtherError, //其他错误
   };
   int32_t currentselect_areaid_;
   int32_t currentselect_serverid_;
   int32_t autoarea_index_[kProvideCount];
   int32_t autoserver_index_[kProvideCount];
   int32_t pre_findidle_; //前一次找到网络状态空闲的索引
   int32_t pre_findnormal_; //前一次找到网络状态正常的索引
   int32_t pre_findbusy_; //前一次找到网络状态拥挤的索引
   int32_t pre_findfull_; //前一次找到网络状态爆满的索引
   provideinfo_t provide_[3]; //三种网络供应商
   STRING username_;
   STRING password_;  

 public:   
   int32_t auto_selectserver(int32_t provide);
   int32_t build_autoselect_table() {} //构造自动选择login server需要的数据表
   int32_t open_accountinput(); //打开账号输入界面
   int32_t open_selectcharacter(); //打开选择角色界面
   int32_t change_to_selectcharacter(); //切换到选择角色界面
   int32_t send_connectmessage() {}; //发送同步消息
   int32_t checkaccount(const char* username, const char* password);
   int32_t send_checnaccount_message();

 public:
   status_enum getstatus() { return status_; }
   void setstatus(status_enum status) { status_ = status; }
   void set_relogin(bool flag);
   void firstlogin();
   void changescene();
   void set_serverip(const char* ip);
   void set_serverport(uint16_t port);
   virtual void processinput() {}; //处理输入
   int32_t load_serverinfo(STRING configfile = "../patch/serverlist.txt") {};
   int32_t read_areainfo(); //读取区域信息
   int32_t read_serverinfo(); //读取服务器信息
   void init_areainfo(); //初始化区域信息
   int32_t get_areacount(); //获取区域数量
   const char* get_areaname(int32_t index);
   areainfo_t* get_areainfo(int32_t index);
   uint16_t get_area_servercount(int32_t index) { return 1; };
   loginserver_info_t* get_area_serverinfo(int32_t areaindex, 
                                           int32_t serverindex);
   int32_t connect_toserver(int32_t areaindex, int32_t serverindex);
   int32_t connect_toserver();
   int32_t get_gameversion();
   int32_t selectserver(int32_t areaindex, int32_t serverindex) { return 0; }
   void get_lastarea_andserver_index(int32_t area, 
                                     int32_t server, 
                                     STRING& name) {};
   void get_last_serverid();
   void select_oldserver();

 protected:
   status_enum status_;
   bool relogin_;
   vengine_sound::Source* soundsource_;
   int32_t prevarea_;
   int32_t prevserver_;

 protected:
   virtual void init();
   virtual void tick();
   virtual void render() {};
   virtual void release() {};

};

}; //namespace procedure

#endif //PAP_CLIENT_GAME_PROCEDURE_LOGIN_H_
