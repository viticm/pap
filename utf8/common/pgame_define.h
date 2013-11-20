#ifndef PAP_COMMON_PGAME_DEFINE_H_
#define PAP_COMMON_PGAME_DEFINE_H_

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

//数据库名称长度
#define  DATABASE_STR_LENGTH 128
//数据库用户名长度
#define  DB_USER_STR_LENGTH 32
//数据库密码长度
#define  DB_PASSWORD_STR_LENGTH 32
//DB 操作时间间隔
#define  DB_OPERATION_TIME 500
//账号保存角色个数
#define  DB_CHAR_NUMBER 5
//角色中非即时刷新属性同步到ShareMemory的时间间隔
#define  DB_2_SM_TIME  60000 //60秒
//数据库连接池默认连接个数
#define  DB_CONNECTION_COUNT   40

#endif //PAP_COMMON_PGAME_DEFINE_H_
