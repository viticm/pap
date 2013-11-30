/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id define.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-26 9:41:11
 * @uses 游戏服务器基础模块的基本定义文件
 */
#ifndef PAP_SERVER_COMMON_BASE_DEFINE_H_
#define PAP_SERVER_COMMON_BASE_DEFINE_H_

#include "common/base/type.h"

#define OVER_MAX_SERVER 256
//odbc 连接名长度
#define DB_CONNECTION_NAME_LENGTH 128
//数据库名称长度
#define DB_DBNAME_LENGTH 128
//数据库用户名长度
#define DB_USER_NAME_LENGTH 32
//数据库密码长度
#define DB_PASSWORD_LENGTH 32
//DB 操作时间间隔
#define DB_OPERATION_TIME 500
//账号保存角色个数
#define DB_CHAR_NUMBER 5
//角色中非即时刷新属性同步到ShareMemory的时间间隔
#define DB_TO_SM_TIME 60000 //60秒
//数据库连接池默认连接个数
#define DB_CONNECTION_COUNT 40
#define SCENE_MAX 1024 //场景的最大数量
#define RICHES_CARD_MAX 10 //财富卡的最大数量

#endif //PAP_SERVER_COMMON_BASE_DEFINE_H_
