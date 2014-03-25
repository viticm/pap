/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id worldsystem.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-25 11:52:01
 * @uses vengine game world system class
 */
#ifndef VENGINE_GAME_WORLDSYSTEM_H_
#define VENGINE_GAME_WORLDSYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"
#include "vengine/render/system.h"
#include "vengine/sound/system.h"
#include "vengine/game/scene.h"
#include "vengine/game/object/basesystem.h"

namespace vengine_game {

struct mapposition_define_t {
  vengine_math::base::threefloat_vector_t position;
  uint16_t sceneid;
  char name[128];
  uint16_t serverid;
  char optimizename[128]; //优化名称
  bool optimize;
  mapposition_define_t() {
    optimize = false;
    memset(optimizename, 0, sizeof(optimizename));
  }
  void setname(const char* name);
  void set_positionname(const char* name);
  //去掉对UTF8的设置
};

//对外提供的地形高度查询接口(使用渲染系统坐标，考虑地形和行走面)
typedef bool (__stdcall* function_get_terrainheight)
  (float x, float z, float& y);

typedef enum {
  kMiniMapTypeAnimy = 0, //敌人
  kMiniMapTypeTeam, //队友
  kMiniMapTypeFamily, //家族
  kMiniMapTypeGuild, //帮会
  kMiniMapTypeHomeland, //国家的
  kMiniMapTypeNotHomeland, //非本国的
  kMiniMapTypeGrowPoint, //生长点
  kMiniMapTypeActive, //激活方向点
  kMiniMapTypeScenePosition, //场景传送点
  kMiniMapTypeFlash, //闪光点
  kMiniMapTypeNpcNormal, //普通NPC
  kMiniMapTypeNpcMissionComplete, //任务NPC，完成
  kMiniMapTypeNpcMissionNotComplete, //任务NPC，未完成
  kMiniMapTypeNpcMissionCanAccept, //任务NPC，可接
  kMiniMapTypeSelf, //自己
  kMiniMapTypePet, //宠物
  kMiniMapTypeNumber
} minimap_type_enum;

class VENGINE_API WorldSystem : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(WorldSystem);

 public:
   typedef enum {
     kStationNotEnterScene, //没有进入任何场景
     kStationEnteringScene, //正在进入一个场景
     kStationEnterScene, //成功进入场景
     kStationAskChangeScene, //要求切换到一个新的场景(已经发送了请求切换场景的消息)
   } station_enum;

 public:
   //进入某个场景
   virtual bool enterscene(uint16_t sceneid, 
                           int16_t citylevel, 
                           int32_t resourceid) = 0;
   virtual Scene* get_activescene() = 0;
   //取得当前状态
   virtual station_enum getstation() const = 0;
   //对外提供的地形高度查询接口(使用渲染系统坐标，考虑地形和行走面)
   virtual function_get_terrainheight get_terrainheight_function() = 0;
   //获得当前场景的ID
   virtual uint16_t get_active_sceneid() const = 0;
   virtual std::list<mapposition_define_t>* 
     get_objectlist_bytype(uint8_t type) = 0;
   virtual void set_minimap_searchrange(int32_t range) = 0;
   virtual void update_minimap_data() = 0;
   virtual void minimap_needfresh() = 0;
   virtual vengine_math::base::threefloat_vector_t get_selfposition() = 0;
   virtual int32_t get_selfdirect() = 0;
   virtual const char* get_scenename(uint16_t sceneid) = 0;

};

}; //namespace vengine_game

#endif //VENGINE_GAME_WORLDSYSTEM_H_
