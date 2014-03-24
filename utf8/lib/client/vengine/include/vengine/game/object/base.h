/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id base.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 19:45:21
 * @uses vengine game object base class
 */
#ifndef VENGINE_GAME_OBJECT_BASE_H_
#define VENGINE_GAME_OBJECT_BASE_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"
#include "vengine/render/entitynode.h"
#include "vengine/cursor/system.h"

//引用公用类物品结构
namespace pap_common_game {

namespace structs {

namespace item {

struct base_t;

}; //namespace item

}; //namespace structs

}; //namespace pap_common_game

//引用公用类的定义
namespace pap_common_game {

namespace define {

namespace type {

namespace item {

enum _enum;

}; //namespace item

}; //namespace define

}; //namespace define

}; //namespace pap_common_game


namespace vengine_game {

namespace object {

typedef enum {
  kStatusNone = 0x0,
  kStatusVisiable = 0x1, //是否可见
  //已经不再玩家的视野范围,如果该值维持一定时间,则会被删除
  kStatusOutVisualField = 0x2,
  kStatusRayQuery = 0x3, //鼠标是否能选中
} status_enum;

const uint8_t kExtraParamMax = 3;

class VENGINE_API Base : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_LOGICAL(false); //声明该对象没有逻辑功能
VENGINE_KERNEL_DECLARE_DYNAMIC(Base);

 public:
   //根据初始化物体，并同步到渲染层
   virtual void init(void*) = 0;
   //得到物体的ID
   virtual int32_t getid() const = 0; //客户端
   virtual int32_t get_serverid() const = 0; //与服务器同步的ID
   //设置某项基本状态为enable
   virtual void enable(uint8_t flag) = 0;
   //设置某项基本状态为disable
   virtual void disable(uint8_t flag) = 0;
   virtual bool isenable(uint8_t flag) = 0;
   virtual bool isdisable(uint8_t flag) = 0;
   //是否能够被作为主目标选择
   virtual bool can_beselect() const = 0;
   //获得渲染层指针
   virtual vengine_render::EntityNode* get_renderinterface() = 0;

 public:
   typedef enum {
     kTripperObjectTypeNone, //非tripper物体
     kTripperObjectTypeTransPort, //转送点
     kTripperObjectTypeItemBox, //掉落箱子
     kTripperObjectTypeResource, //生活技能中的矿物资源
     kTripperObjectTypePlatform, //生活技能中的合成所需要的平台
   } tripperobject_type_enum;
   //物体类型
   virtual tripperobject_type_enum tripper_gettype() const = 0;
   //能否鼠标操作
   virtual bool tripper_canoperate() const = 0;
   //获得鼠标类型
   virtual vengine_cursor::type_enum tripper_getcursor_type() const = 0;
   //进入激活状态
   virtual void tripper_enteractive() = 0;

};

}; //namespace object

}; //namespace vengine_game

#endif //VENGINE_GAME_OBJECT_BASE_H_
