/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id macros.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:26:46
 * @uses 游戏中基本的宏定义（宏无命名空间的限制，所以不要放在命名空间中）
 *       可以单独包含该文件使用宏定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_MACROS_H_
#define PAP_COMMON_GAME_DEFINE_MACROS_H_

#define COUNTRY_INVALID -1
#define JOB_INVALID -1
#define SEX_INVALID -1
#define GUILDID_INVALID -1
#define RESOURCE_INVALID -1
#define RULERID_INVALID -1
#define PRICE_INVALID 0
#define ITEMID_INVALID 0
#define ITEMPOS_INVALID -1
#define TIME_INVALID 0xFFFFFFFF
#define MENPAITYPE_INVALID 0
#define SOULTYPE_INVALID 0
#define BASE_BAGPOS 185
#define GUILDLEVEL_MAX 5 //公会最大等级
#define CHARACTER_ABILITYMAX 8 //角色最多的生活技能数量

#define SERVRENAME_MAX 32

/* account{ */
#define ACCOUNTLENGTH_MAX 50
#define MD5SIZE_MAX 32
/* account} */

/*pakcetid {*/  //网络包ID的范围定义
#define PACKETID_INVALID -1
#define BILLINGLOGIN_PACKETID_MIN 1
#define BILLINGLOGIN_PACKETID_MAX 125
#define LOGINCLIENT_PACKETID_MIN 126
#define LOGINCLIENT_PACKETID_MAX 254
#define LOGINWORLD_PACKETID_MIN 255
#define LOGINWORLD_PACKETID_MAX 300
#define WORLDSERVER_PACKETID_MIN 301
#define WORLDSERVER_PACKETID_MAX 512
#define CLIENTSERVER_PACKETID_MIN 513
#define CLIENTSERVER_PACKETID_MAX 10000 //保证客户端与服务器之间的包范围足够大
/*packetid }*/

#endif //PAP_COMMON_GAME_DEFINE_MACROS_H_
