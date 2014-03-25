/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id basesystem.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-25 11:01:41
 * @uses vengine game base object system class
 */
#ifndef VENGINE_GAME_OBJECT_BASESYSTEM_H_
#define VENGINE_GAME_OBJECT_BASESYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"
#include "vengine/math/base.h"
#include "vengine/game/object/base.h"
#include "vengine/game/object/item.h"

namespace vengine_game {

namespace object {

class VENGINE_API BaseSystem : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(BaseSystem);

 public:
   typedef enum {
     kDestroyMainTargetTypeObject, //销毁的对象
     kDestroyMainTargetTypeMouseRightClick, //鼠标右键销毁
   } destroy_maintarget_type_enum;

 public:
   //产生新物体,并加入数据链
   virtual Base* create(const char* classname, 
                        int32_t id_fromserver, 
                        Base* parent = NULL) = 0;
   //销毁物体,并从数据链上拆除
   virtual void destroy(Base* object) = 0;
   //跟据ID得到某物体
   virtual Base* find(int32_t id) = 0;
   //获取一个SERVER OBJ对象的指针 
   virtual Base* findserver(int32_t id) = 0;
   //跟据索引来获取对象
   virtual const std::vector<int32_t>& get_npc_objectid() = 0;
   //获得物品
   virtual Item* getitem(int32_t id) = 0;
   //根据屏幕坐标计算选中得物体
   virtual Base* get_mouseover(
       int32_t x, 
       int32_t y, 
       vengine_math::base::threefloat_vector_t& mouse_hitplan) = 0;
   //设置主目标对象，如果id非法，取消选中物体
   virtual void set_maintarget(
       int32_t id, 
       destroy_maintarget_type_enum destroytype = kDestroyMainTargetTypeObject) 
     = 0;
   //取得当前选中物体
   virtual Base* get_maintarget() const = 0;
   //关心某物体的指定事件 id-物体ID bCare-关心或者取消关心
   virtual void care(int32_t id, bool care, STRING szSign) = 0;
   //从本地资源表中读取物品名字
   virtual void get_local_itemname(uint32_t id_oftable) = 0;
   virtual void init_actoravatar() = 0;
   virtual void destroy_actoravatar() = 0;
   virtual const char* get_selfor_targetname(bool target = false) = 0;
};

}; //namespace object

}; //namespace vengine_game

#endif //VENGINE_GAME_OBJECT_BASESYSTEM_H_
