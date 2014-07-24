/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-21 16:11:04
 * @uses vengine render system class
 *       cn: 渲染系统接口
 */
#ifndef VENGINE_RENDER_SYSTEM_H_
#define VENGINE_RENDER_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"
#include "vengine/math/base.h"
#include "vengine/render/entitynode.h"

namespace vengine_render {

class VENGINE_API System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(vengine_render_System);

 public:
   virtual void init(void*) = 0;
   virtual void release() = 0;
   //场景渲染
   virtual void renderframe() = 0;
   //渲染loading画面
   virtual void render_loadingframe(const char* loading) = 0;
   //响应WM_PAINT消息
   virtual void onpaint() = 0;
   //窗口大小改变事件
   virtual void on_windowsize_change(uint32_t message, 
                                     WPARAM wparam, 
                                     LPARAM lparam) = 0;
   //取得渲染窗口
   virtual HWND getwindow() const = 0;
   //保存当前屏幕截图到文件中
   virtual bool printscreen(char* buffer, int32_t size) = 0;
 
 //debugs
 public:
   //加入debug信息
   virtual void debug_pushstring(const char* format, ...) = 0;
   //设置debug状态信息
   virtual void debug_setstring(const char* name, const char* value) = 0;
   //设置选中物体信息
   virtual void set_hitobjet_string(const char* str) = 0;
   //检查物体的透明度
   virtual void check_objecttransparent() = 0;
   virtual void set_shoeobject_bytype(const char* name) = 0;

 public:
   typedef enum {
     kAxisTypeGame, //游戏世界坐标，以米为单位
     kAxisTypePlan, //戏世界坐标，以米为单位,不过不包括Y坐标
     kAxisTypeRender, //渲染系统中定点坐标，一般以厘米为单位
     kAxisTypeScreen, //屏幕上的像素坐标，例如鼠标位置,整数
   } axistype_enum;
   //将一种坐标转化为另一种坐标,转化成成功返回true
   //当源坐标非法的时候，返回false
   virtual bool axistrans(
       axistype_enum type,
       const vengine_math::base::threefloat_vector_t& source,
       axistype_enum targettype,
       vengine_math::base::threefloat_vector_t& target) = 0;
   virtual bool axis_checkvalid(
       axistype_enum type,
       const vengine_math::base::threefloat_vector_t& axis) = 0;

 //camera
 public:
   typedef enum {
     kCameraTypeCharacter, //主角
     kCameraTypeScene, //场景
   } cameratype_enum;
   typedef enum {
     kCameraOffsetLeft = 0,
     kCameraOffsetRight,
     kCameraOffsetNone
   } cameraoffset_enum;
   //设置当前摄像机
   virtual void camera_setcurrent(cameratype_enum type) = 0;
   //设置偏移量
   virtual void camera_setoffset(cameraoffset_enum tag, 
                                 float paralleloffset, 
                                 float verticaloffset = 0.0f) = 0;
   //移动相机所看的位置到某一点,一般是玩家所在的位置(世界二维坐标系)
   virtual void camera_set_lookat(
       const vengine_math::base::threefloat_vector_t& position) = 0;
   //缩放相机视口 [0.0f, 1.0f]  0-最近距离 1-最远距离
   virtual void camera_setzoom(float zoom) = 0;
   virtual void camera_setzoom(bool up, int32_t multiple) = 0;
   virtual float camera_getzoom() const = 0;
   //设置相机方向 (0, 2л)， 以z轴指向的方向为0度，逆时针为正方向
   virtual void camera_setdirection(float direction) = 0;
   virtual void camera_adddirection(float multiple) = 0;
   virtual float camera_getdirection() const = 0;
   //取得屏幕射线
   virtual void camera_getwindow_to_viewpointray(
       int32_t x,
       int32_t y,
       vengine_math::base::floatray& ray) = 0;
   //震荡一次
   virtual void camera_vibrate_onetime() = 0;
   virtual void camera_vibrate_onetime(float range, 
                                       float steplength, 
                                       uint32_t times) = 0;
   //人物选择, 创建, 界面用到的摄像机接口.
   virtual void camera_set_eyeposition(
       const vengine_math::base::threefloat_vector_t& position) = 0;
   //设置观察点的位置
   virtual void camera_set_lookat_position(
       const vengine_math::base::threefloat_vector_t& position) = 0;

 //scene
 public:
   //预加载场景
   virtual void scene_preload(const STRING& scenename) = 0;
   //加载场景
   virtual void scene_load(uint16_t id, const STRING& scenedefine) = 0;
   //卸载场景
   virtual void scene_unload() = 0;
   //显示地形网格
   //virtual void scene_show_girdswitch(int32_t size) = 0;
   //显示设置全局渲染效果
   virtual void scene_set_postfilter(const char* name,
                                     bool state = true) = 0;
   //设置lightmap
   virtual void scene_set_lightmap_quality(int32_t quality) = 0;
   //进入/退出死亡全局渲染效果
   virtual void scene_set_postfilter_death(bool enter) = 0;
   //设置环境特效(位置)
   virtual void scene_set_environmentinfo(
       const vengine_math::base::threefloat_vector_t& position) = 0;
   //设置材质32位/16位转化
   virtual void scene_enable_32bittextures(bool setting = true) = 0;
   //设置采样（高是各向异性3、中是三线性2、低是双线性1(远景清晰度)）
   virtual void scene_set_texturefiltering(uint8_t option) = 0;
   //设置静态物体动画
   virtual void scene_set_animationquality(uint8_t option) = 0;
   //设置全屏泛光效果
   virtual void scene_set_postfilter_enable(bool flag) = 0;
   //设置人物实时阴影
   virtual void scene_set_shadowtechnique(uint8_t flag) = 0;
   //显示地形网格切换
   virtual void scene_show_girdswitch(int32_t zonesize) = 0;
   
 //debugs
 public:
   //在某点增加一个粒子
   virtual void debug_addparticle(
       const char* name,
       const vengine_math::base::threefloat_vector_t& position) = 0;
   virtual void debug_set_fakecamera(uint8_t type, float value) = 0;
   //显示/隐藏
   virtual void debug_toggleshow_debugpanel() = 0;
   virtual void debug_toggleshow_boundingbox() = 0;

 public:
   //创建一个可渲染实体
   virtual EntityNode* new_entityobject(EntityNode::type_enum type) = 0;
   //寻找和鼠标接触的实体
   virtual EntityNode* find_hitfairy_object(int32_t x, int32_t y) = 0;

 //UI显示模型相关
 public:
   //创建一个fake渲染对象
   virtual void fakeobject_create(const char* name,
                                  EntityNode* node,
                                  EntityNode* parentnode,
                                  const char* cameraname,
                                  int32_t textuewidth,
                                  int32_t textueheight,
                                  const char* backgroundname) = 0;
   //销毁一个fake渲染对象
   virtual void fakeobject_destroy(const char* name) = 0;
   //隐藏/显示fake渲染对象
   virtual void fakeobject_show(const char* name,
                                bool visible,
                                float aspectratio) = 0;
   virtual bool fakeobject_setattach(EntityNode* node, 
                                     EntityNode* attachnode) = 0;

};

}; //namespace vengine_render

#endif //VENGINE_RENDER_SYSTEM_H_
