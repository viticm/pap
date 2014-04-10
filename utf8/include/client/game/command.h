/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id command.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-12 11:15:08
 * @uses the base config macros and defines, also with system include
 */
#ifndef PAP_CLIENT_GAME_COMMAND_H_
#define PAP_CLIENT_GAME_COMMAND_H_

#include "common/base/type.h"

#define OBJECT_CMDPARAM_NUMBER_MAX 16
enum commandtype_enum {
  kCommandTypeInvalid = -1,
  kCommandTypeWorld,
  kCommandTypeObject,
  kCommandTypeAI,
  kCommandTypeDataPool,
  kCommandTypeUI,
  kCommandTypeMouse
};

enum runcommand_result_enum {
  kRunCommandResultSuccess = 0,
  kRunCommandResultError,
  kRunCommandResultSkip,
  kRunCommandResultWait
};

struct command_t {

 public:
   uint16_t id;
   union {  
     uint32_t dwordparam[OBJECT_CMDPARAM_NUMBER_MAX];
     uint32_t uint32param[OBJECT_CMDPARAM_NUMBER_MAX];
     float floatparam[OBJECT_CMDPARAM_NUMBER_MAX];
     int32_t int32param[OBJECT_CMDPARAM_NUMBER_MAX];
     bool boolparam[OBJECT_CMDPARAM_NUMBER_MAX];
     uint64_t uint64param[OBJECT_CMDPARAM_NUMBER_MAX];
     int64_t int64param[OBJECT_CMDPARAM_NUMBER_MAX];
     void* voidpointer_param[OBJECT_CMDPARAM_NUMBER_MAX];
     const void* constvoid_pointer_param[OBJECT_CMDPARAM_NUMBER_MAX];
   };
  
 public:
   command_t() {
     type = kCommandTypeInvalid;
   };
   commandtype_enum gettype() {
     return type;
   };
   void cleanup() {
     id = 0xFFFF;
     memset(dwordparam, 0, sizeof(dwordparam));
   };

 protected:
   commandtype_enum type;

};

struct objcetcommand_t : public command_t {
  objcetcommand_t() {
    type = kCommandTypeObject;
  };
};

struct aicommand_t : public command_t {
  aicommand_t() {
    type = kCommandTypeUI;
  };
};

struct datapool_command_t : public command_t {
  datapool_command_t() {
    type = kCommandTypeUI
  };
};

struct mousecommand_t : public command_t {
  enum type_enum {
    kTypeNull,
    kTypePlayerMoveTo,
    kTypePlayerSelect,
    kTypeSkillObject,
    kTypeSkillArea,
    kTypeSkillDirect,
    kTypeHitTripperObject,
    kTypeSpeak,
    kTypeContexMenu,
    kTypeRepiar,
    kTypeUseItem,
    kTypeCancleUseItem,
    kTypeUIUseIdentify,
    kTypeUICancleUseIdentify,
    kTypeAddFriend,
    kTypeExchange,
    kTypePlayerJump
  };
  mousecommand_t() {
    type = kCommandTypeMouse;
  };
  type_enum mousetype;
};

#endif //PAP_CLIENT_GAME_COMMAND_H_
