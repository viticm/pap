/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id interface.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-14 16:03:48
 * @uses pap client game engine interface class
 *       cn: 前端引擎核心系统
 *       现阶段实现界面的渲染即可，后续加上物体、相机、场景等 --viticm
 */
#ifndef PAP_CLIENT_GAME_ENGINE_INTERFACE_H_
#define PAP_CLIENT_GAME_ENGINE_INTERFACE_H_

#include "vengine/game/eventsystem.h"
#include "vengine/render/system.h"

namespace Fairy { 
class System;
class TerrainGrid;
class PostFilterManager;
class EnviromentObject;
}; //namespace Fairy

namespace Ogre {
class RaySceneQuery;
}; //namespace Ogre

namespace engine {

enum objecttype_enum {
  kObjectTypeNone = -1,
  kObjectTypeStaticEntity = 1,
  kObjectTypePartice = 1 << 1, //2
  kObjectTypeTerrainGrid = 1 << 2, //4
  kObjectTypeEffect = 1 << 3, //8
  kObjectTypeBullet = 1 << 4, //16
  kObjectTypeLogicModel = 1 << 5, //32
  kObjectTypeAll = (1 << 6) - 1,
};

class Interface : public vengine_render::System {

VENGINE_KERNEL_DECLARE_DYNAMIC(Interface);

 public: //implement from abstract
   virtual void init(void*);
   virtual void release();
   //场景渲染
   virtual void renderframe();
   //渲染loading画面
   virtual void render_loadingframe(const char* loading);
   //响应WM_PAINT消息
   virtual void OnPaint();
   //窗口大小改变事件
   virtual void OnSizeChange(UINT message, 
                             WPARAM wparam, 
                             LPARAM lparam);
   //取得渲染窗口
   virtual HWND getwindow() const;
   //保存当前屏幕截图到文件中
   virtual void printscreen(const char* buffer, int32_t size);
 
 //debugs
 public: //implement from abstract 
   //加入debug信息
   virtual void debug_pushstring(const char* format, ...);
   //设置debug状态信息
   virtual void debug_setstring(const char* name, const char* value);
   //设置选中物体信息
   virtual void set_hitobjet_string(const char* str);
   //检查物体的透明度
   virtual void check_objecttransparent();
   virtual void set_showobject_bytype(const char* name);

 public: //implement from abstract 
   //将一种坐标转化为另一种坐标,转化成成功返回true
   //当源坐标非法的时候，返回false
   virtual bool axistrans(
       axistype_enum type,
       const vengine_math::base::threefloat_vector_t& source,
       axistype_enum targettype,
       const vengine_math::base::threefloat_vector_t& target);
   vengine_math::base::threefloat_vector_t getscale() const;
   virtual bool axis_checkvalid(
       axistype_enum type,
       const vengine_math::base::threefloat_vector_t& axis);

 //camera
 public: //implement from abstract
   //设置当前摄像机
   virtual void camera_setcurrent(cameratype_enum type);
   //设置偏移量
   virtual void camera_setoffset(cameraoffset_enum tag, 
                                 float paralleloffset, 
                                 float verticaloffset = 0.0f);
   //移动相机所看的位置到某一点,一般是玩家所在的位置(世界二维坐标系)
   virtual void camera_set_lookat(
       const vengine_math::base::threefloat_vector_t& position);
   //缩放相机视口 [0.0f, 1.0f]  0-最近距离 1-最远距离
   virtual void camera_setzoom(float zoom);
   virtual void camera_setzoom(bool up, int32_t multiple);
   virtual float camera_getzoom() const;
   //设置相机方向 (0, 2л)， 以z轴指向的方向为0度，逆时针为正方向
   virtual void camera_setdirection(float direction);
   virtual void camera_adddirection(float multiple);
   virtual float camera_getdirection() const;
   //取得屏幕射线
   virtual void camera_getwindow_to_viewpointray(
       int32_t x,
       int32_t y,
       vengine_math::base::floatray& ray);
   //震荡一次
   virtual void camera_vibrate_onetime();
   virtual void camera_vibrate_onetime(float range, 
                                       float steplength, 
                                       uint32_t times);
   //人物选择, 创建, 界面用到的摄像机接口.
   virtual void camera_set_eyeposition(
       const vengine_math::base::threefloat_vector_t& position);
   //设置观察点的位置
   virtual void camera_set_lookat_position(
       const vengine_math::base::threefloat_vector_t& position);

 //scene
 public: //implement from abstract 
   //预加载场景
   virtual void scene_preload(const STRING& scenename);
   //加载场景
   virtual void scene_load(uint16_t id, const STRING& scenedefine);
   //卸载场景
   virtual void scene_unload();
   //显示地形网格
   //virtual void scene_show_girdswitch(int32_t size) = 0;
   //显示设置全局渲染效果
   virtual void scene_set_postfilter(const char* name,
                                     bool state = true);
   //设置lightmap
   virtual void scene_set_lightmap_quality(int32_t quality);
   //进入/退出死亡全局渲染效果
   virtual void scene_set_postfilter_death(bool enter);
   //设置环境特效(位置)
   virtual void scene_set_environmentinfo(
       const vengine_math::base::threefloat_vector_t& position);
   //设置材质32位/16位转化
   virtual void scene_enable_32bittextures(bool setting = true);
   //设置采样（高是各向异性3、中是三线性2、低是双线性1(远景清晰度)）
   virtual void scene_set_texturefiltering(uint8_t option);
   //设置静态物体动画
   virtual void scene_set_animationquality(uint8_t option);
   //设置全屏泛光效果
   virtual void scene_set_postfilter_enable(bool flag);
   //设置人物实时阴影
   virtual void scene_set_shadowtechnique(uint8_t flag);
   //显示地形网格切换
   virtual void scene_show_girdswitch(int32_t zonesize);
   
 //debugs
 public: //implement from abstract 
   //在某点增加一个粒子
   virtual void debug_addparticle(
       const char* name,
       const vengine_math::base::threefloat_vector_t& position);
   virtual void debug_set_fakecamera(uint8_t type, float value);
   //显示/隐藏
   virtual void debug_toggleshow_debugpanel();
   virtual void debug_toggleshow_boundingbox();

 public: //implement from abstract 
   //创建一个可渲染实体
   virtual EntityNode* new_entityobject(EntityNode::type_enum type);
   //寻找和鼠标接触的实体
   virtual EntityNode* find_hitfairy_object(int32_t x, int32_t y);

 //UI显示模型相关
 public: //implement from abstract 
   //创建一个fake渲染对象
   virtual void fakeobject_create(const char* name,
                                  EntityNode* node,
                                  EntityNode* parentnode,
                                  const char* cameraname,
                                  int32_t textuewidth,
                                  int32_t textueheight,
                                  const char* backgroundname);
   //销毁一个fake渲染对象
   virtual void fakeobject_destroy(const char* name);
   //隐藏/显示fake渲染对象
   virtual void fakeobject_show(const char* name,
                                bool visible,
                                float aspectratio);
   virtual bool fakeobject_setattach(EntityNode* node, 
                                     EntityNode* attachnode);

 public:
   static const char k32BitTexturesVar[]; //颜色质量，比特数(16/32位)
   static const char kDefaultTextureFilteringVar[]; //采样(高/中/低)
   static const char kLightmapQualityVar[]; //地形阴影(高/低/无)
   static const char kAnimationQualityVar[]; //静态物体对象(开/关)
   static const char kPostFilterEnabledVar[]; //全屏泛光效果(开/关)
   static const char kFSAAVar[]; //反混角(1/2/4)
   static const char kShadowTechniqueVar[]; //人物阴影(开/关)
   static const char kVsyncVar[]; //垂直同步(开/关)

 public: //extends
   static Interface* getself();

 protected:
   static Interface* self_;
   Fairy::System* fairysystem_;
   //相机 --以后做

   //客户区宽度
   float client_fullwidth_;
   bool is_fullwidth_;
   float clientwidth_;

   //保存客户区单个尺寸对应的游戏单位（M）
   float unitgame_toscene_;
   cameraoffset_enum offsettag_;
   bool is_leftoffset_;
   bool is_rightoffset_;
   //鼠标射线和场景交集
   Ogre::RaySceneQuery* ray_scenequery_;
   Fairy::PostFilterManager* postfilter_manager_; //PostFilter系统(全局渲染器)
   Fairy::EnviromentObject* environmentobject_; //环境特效
   Fairy::TerrainGrid* terraingrid_; //地形网格
   bool deathmode_; //死亡特效
   int32_t deathmode_percent_; //[0, 100]

};

}; //namespace engine

#endif //PAP_CLIENT_GAME_ENGINE_INTERFACE_H_
