/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id scene.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-24 10:15:41
 * @uses vengine database item struct module
 *       cn: 场景相关数据定义
 */
#ifndef VENGINE_DB_STRUCT_SCENE_H_
#define VENGINE_DB_STRUCT_SCENE_H_

namespace scene {

const uint16_t kDefineId = 701;
typedef struct {
  static const uint8_t kSceneServerIdColumn = 1;
  uint16_t localid;
  uint16_t serverid;
  uint8_t citylevel;
  int32_t xsize;
  int32_t ysize;
  const char* name;
  const char* pov_file;
  const char* regionfile;
  const char* minimap; //小地图
  uint16_t background_soundid; //背景音乐
  int32_t silenttime;
  const char* map; //大地图
  int32_t worldmap_xposition; //场景图标所在得位置
  int32_t worldmap_yposition;
  int32_t name_worldmap_xposition; //场景名字所在得位置
  int32_t name_worldmap_yposition;
  const char* type; //场景得图标等级
  const char* cityname_normal_imageset; //场景正常名字所用得图片资源
  const char* cityname_normalimage; //场景正常名字所用得图片资源
  const char* cityname_hover_imageset; //场景高亮名字所用得图片资源 
  const char* cityname_hoverimage; //场景高亮名字所用得图片资源
  const char* info;
  const char* blurshine_amount;
  float cameraangle; //摄像机偏移
} define_t;

//城市建筑定义
const uint16_t kCityBuildingId = 702;
typedef struct {
  uint16_t id;
  uint16_t cityid;
  uint16_t buildingid;
  const char* gfxposition; //位置（gfx）
  uint8_t initlevel; //初始等级
  const char* gfxorientation; //旋转四元素（gfx）
} citybuilding_t;

//可跳转的地图信息定义
const uint16_t kWorldPositionId = 703;
typedef struct {
  uint16_t id;
  uint16_t scendid;
  const char* scenename;
  int32_t xposition; //传送点位置
  int32_t yposition;
  uint8_t scenetype; //场景类型
  uint8_t maplevel; //地图等级
  uint8_t enterlevel; //进入等级
  const char* pinyin_index; //拼音索引
} worldposition_t;

//场景地图上的任务NPC信息定义
const uint16_t kNpcDefineId = 704;
typedef struct {
  int32_t id;
  uint16_t sceneid;
  const char* name; //名字
  const char* UI_name; //显示头顶名字
  int32_t xposition; //坐标
  int32_t yposition;
  bool istalk; //是否讲话
  const char* type_name; //类型
  const char* pinyin_index;
} npcdefine_t;

//传送点定义
const uint16_t kDeliverPositionId = 705;
typedef struct {
  uint16_t id;
  uint16_t scendid; //场景ID
  const char* scenename;
  int32_t xposition;
  int32_t yposition;
  uint16_t target_sceneid; //目标场景
  const char* target_scenename; //目标场景名
} deliverposition_t;

}; //namespace scene

#endif //VENGINE_DB_STRUCT_SCENE_H_
