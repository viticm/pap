#include "server/common/db/data/sql_template.h"

//-- table t_global
const char* kLoadGlobal = 
    "SELECT * FROM `t_global`";
const char* kDeleteGlobal = 
    "DELETE FROM `t_global` WHERE `poolid` = %d";
const char* kUpdateGlobal =
    "CALL save_global(%d, %d)";
const char* kAddGlobal = 
    "CALL save_global(%d, %d)";
const char* kSaveGlobal = 
    "CALL save_global(%d, %d)";
//table t_global --
