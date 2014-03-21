/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id entitynode.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-21 16:15:57
 * @uses vengine render entity node class
 *       cn: 渲染实体类
 */
#ifndef VENGINE_RENDER_ENTITYNODE_H_
#define VENGINE_RENDER_ENTITYNODE_H_

#include "vengine/config.h"
#include "vengine/math/base.h"

// Fairy
namespace Fairy {

class Skill;

}; //namespace Fairy


namespace vengine_render {

typedef bool (*function_on_animationend)(const char*, uint64_t); 
typedef bool (*function_on_animationendex)(const char*, uint64_t, int32_t);
typedef bool (*function_on_skillbreak_time)
  (const char*, uint64_t, uint16_t, uint16_t);
typedef bool (*function_on_skillhit_time)
  (const char*, uint64_t, uint16_t, uint16_t);

class EntityNode {

 public:
   typedef enum {
     kTypeDummy, //空物体,只有SceneNode，不会渲染,可以附加特效或者投影纹理
     kTypeMesh, //静态物体(.mesh)
     kTypeModel, //动态物体(.model)
     kTypeActor, //角色
   } type_enum;

   typedef enum {
     kWeaponBindPointTypeNone, //空
     kWeaponBindPointTypeRight, //右手
     kWeaponBindPointTypeLeft, //左手
     kWeaponBindPointTypeLeftShield, //左手盾 --取消此绑定点
   } weapon_bindpoint_type_eunm;

 public:
   virtual type_enum gettype() const = 0;
   virtual void destroy() = 0; //从渲染层销毁
   //附加数据
   virtual void setdata(uint32_t data) = 0;
   virtual uint32_t getdata() const = 0;
   //位置设置，游戏世界坐标
   virtual void setposition(
       const vengine_math::base::threefloat_vector_t& position) = 0;
   //设置旋转角度
   virtual void setdirection(
       const vengine_math::base::threefloat_vector_t& position) = 0;
   virtual void set_renderposition(
       const vengine_math::base::threefloat_vector_t& position) = 0;
   //直接设置Fairy属性
   virtual void set_fairyproperty(const char* name, const char* value) = 0;
   virtual void set_leftweapon_effect(const char* effectname, 
                                      char* locatorname, 
                                      uint32_t color) = 0;
   virtual void set_rightweapon_effect(const char* effectname, 
                                       const char* locatorname, 
                                       uint32_t color) = 0;
   
   virtual void clear_weaponeffect(weapon_bindpoint_type_eunm type) = 0;
   //改变武器的动作
   virtual void change_weaponaction(weapon_bindpoint_type_eunm type, 
                                    const char* actionname, 
                                    bool loop, 
                                    float fuseparam) = 0;
   //设置是否可见
   virtual void setvisible(bool flag) = 0;
   //设置是否能被鼠标选中
   virtual void set_rayquery(bool flag) = 0;
   virtual bool get_rayquery() const = 0;

 public:
   //置鼠标选中优先级，数字越大优先级越高
   typedef enum {
     kRayQueryLevelUnkown = 0,
     kRayQueryLevelItemBox = 1, //掉落包
     kRayQueryLevelPlayerDeadBody = 2, //死亡尸体
     kRayQueryLevelCreature = 3, //NPC & MONSTER
     kRayQueryLevelResource = 4, //资源
     kRayQueryLevelOtherPlayer = 5, //别的玩家
     kRayQueryLevelSelf = 6, //自己
     kRayQueryLevelPet = 7, //宠物
     kRayQueryLevelCreatureDeadBody = 8, //怪物尸体
     kRayQueryLevelPlatform = 9, //操作平台 
   } rayquery_level_enum;

 public:
   virtual void rayquery_setlevel(rayquery_level_enum level) = 0;
   virtual rayquery_level_enum rayquery_getlevel() const = 0;

 public:
   //附加特效
   virtual void attacheffect(const char* name) = 0;
   virtual void detacheffect() = 0;

   //新增附加特效
   virtual void addeffect(const char* name, const char* locatorname) = 0;
   virtual void removeeffect(uint32_t effect) = 0;
   virtual void remove_alleffect() = 0;
   virtual void add_areaeffect(const char* name) = 0;
   virtual void remove_areaeffect(const char* name) = 0;

 public:
   typedef enum {
     kProjectionTextureTypeSelectRing, //选择环
     kProjectionTextureTypeShadowPoint, //阴影点
     kProjectionTextureTypeReachable, //可以到达的地点
     kProjectionTextureTypeUnreachable, //不可到达的地点
     kProjectionTextureTypeSkillRange, //技能作用范围
     kProjectionTextureTypeBloodStain1, //血迹1
     kProjectionTextureTypeBloodStain2, //血迹2
     kProjectionTextureTypeBloodStain3, //血迹3
     kProjectionTextureTypeBloodStaint, //血迹4
     kProjectionTextureTypeSelfDefineEffect, //自定义纹理类型
   } projectiontexture_type_enum;

 public:
   virtual void attach_projectiontexture(projectiontexture_type_enum type, 
                                         bool show,
                                         float ringrange = 100.0f,
                                         float height = 1.7f) = 0;
   virtual void attach_projectiontexture(const char* effectname, 
                                         bool show, 
                                         float ringrange,
                                         float height) = 0;
   virtual void attachobject(EntityNode* object, const char* locator) {};
   virtual void attachobject(EntityNode* object) {};

 public:
   //设置静态物体类
   virtual void staticobject_set_meshfile(const char* filename) = 0;

   //角色类
   virtual void actor_setfile(const char* file) = 0; //设置模型文件
   //设置角色对象属性
   virtual void actor_set_objectproperty(const char* name, 
                                         const char* value) = 0; 
   virtual void actor_set_objectproperty(const char* name,
                                         STRING& value) = 0;
   //得任务模型上的某关键点位置
   virtual void actor_getlocator(
       const char* name,
       vengine_math::base::threefloat_vector_t& position) = 0;
   //取得"头顶状态点"在屏幕上的位置,如果返回false，表示在屏幕之外,或者没有该点
   virtual bool actor_get_infoboard_position(
       vengine_math::base::twofloat_vector_t& position, 
       const vengine_math::base::threefloat_vector_t *objectposition = NULL,
       const float obligeheight = -1) = 0;
   //进入招式 flag true 调用招式|false 调用动作
   virtual bool actor_enterskill(bool flag,
                                 const char* name,
                                 bool loop,
                                 float fuseparam = 0.3,
                                 int32_t flagex = 3,
                                 int32_t objecttype = 0,
                                 int32_t logictag = 0) = 0;
   virtual void actor_set_haircolor(uint32_t color) = 0;
   virtual Fairy::Skill* get_currentskill() {return NULL;}
   virtual void stop_currentaction() {}
   //切换动画的播放速度
   virtual void actor_change_actionrate(float rate) = 0;
   //在做动作的同时播放其他动作
   virtual void actor_playanimation(const char* name, 
                                    float starttime = 0.0f, 
                                    float weight = 1.0f) = 0;
   //设置缺省动作
   virtual void actor_set_defaultanimation(const char* name) = 0;
   //设置UI可见的标记
   virtual void actor_set_UI_visibleflag() = 0;
   //设置透明度
   virtual void actor_settransparent(float transparent, float time) = 0;
   //设置连线特效的目标点
   virtual void actor_set_effectextra_transforminfos(
       uint32_t effect,
       vengine_math::base::threefloat_vector_t& position) = 0;
   //置是否处于鼠标Hover状态 
   virtual void actor_set_mousehover(bool flag) = 0;
   //设置角色动画结束通知
   virtual void actor_setanimation_eventend(
       function_on_animationendex function,
       uint64_t param,
       int32_t) {}
   //设置角色动画打击点通知
   virtual void actor_setanimation_eventshake(
       function_on_animationend function,
       uint64_t param) {}

   //设置角色动画可以结束通知
   virtual void actor_setanimation_can_eventbreak(
       function_on_skillbreak_time function,
       uint64_t param) {}
   //设置角色动画打击点通知
   virtual void actor_setanimation_eventhit(
       function_on_skillhit_time function,
       uint64_t param) {}

 public:
   virtual int32_t get_terrainsound_type() { return -1; }
   virtual void set_scalefactor(float, float, float) {}

};

}; //vengine_render

#endif //VENGINE_RENDER_ENTITYNODE_H_
