#include <boost/multi_index_container.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/key_extractors.hpp>

#include "OgreException.h"
#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include "OgreParticleSystemManager.h"
#include "OgreCamera.h"
#include "OgreVector2.h"
#include "OgreVector3.h"
#include "OgreRay.h"
#include "OgreOverlayManager.h"
#include "OgreRenderTarget.h"
#include "OgreOverlayElement.h"
#include "OgreLogmanager.h"
#include "OgreCommon.h"
#include "OgreParticleSystem.h"
#include "OgreMeshManager.h"
#include "OgreSkeletonManager.h"
#include "OgreMaterialManager.h"
#include "OgreSceneManager.h"
#include "OgreStringConverter.h"
#include "OgreGpuProgramManager.h"

#include "Core/FairySystem.h"
#include "Core/TerrainData.h"
#include "Core/FrameStatsListener.h"
#include "Core/FairyObjectProxy.h"
#include "Camera/Camera_CharSel.h"
#include "Camera/Camera_Scene.h"
#include "Core/FairySceneInfo.h"
#include "Core/Terrain.h"
#include "Core/FairyResourceSolverHelper.h"
#include "Core/utf.h"
#include "Core/FairyResources.h"
#include "PostFilter/FairyPostFilters.h"
#include "PostFilter/FairyPostFilterManager.h"
#include "Core/FairyExpatParser.h"
#include "Core/FairySceneInfo.h"
#include "Core/FairyEnviromentObject.h"
#include "Core/FairyStaticEntityObject.h"
#include "Core/FairyTerrainLiquidObject.h"
#include "Core/FairyEffectObject.h"
#include "Core/FairyTerrainLiquid.h"
#include "Core/FairyParticleSystemObject.h"
#include "Core/FairyLightObject.h"
#include "Core/FairyActorObject.h"
#include "Core/FairyModelObject.h"

#include "vengine/exceiption/base.h"
#include "vengine/base/util.h"
#include "vengine/capability/profile.h"
#include "vengine/capability/ax/trace.h"
#include "vengine/kernel/base.h"
#include "vengine/sound/system.h"
#include "vengine/game/worldsystem.h"
#include "vengine/game/eventsystem.h"
#include "vengine/game/eventdefine.h"
#include "vengine/db/system.h"
#include "vengine/variable/system.h"
#include "vengine/time/system.h"
#include "vengine/resource/provider.h"
#include "client/game/resource/loadlistener.h"
#include "client/game/stdafx.h" //Precompiled not use like this, i will fix it
#include "client/game/global.h"
#include "client/game/engine/interface.h"

namespace Ogre {

extern "C" void InstallD3D9Plugin();
extern "C" void InstallParticleFXPlugin();
extern "C" void InstallParticleFX2Plugin();
extern "C" void InstallOctreeScenePlugin();
extern "C" void InstallCgProgramManagerPlugin();

} //namespace Ogre

namespace engine {

const char Interface::k32BitTexturesVar[] = "View_ColorQuality";
const char Interface::kDefaultTextureFilteringVar[] = "View_TextureFiltering";
const char Interface::kLightmapQualityVar[] = "View_LightmapQuality";
const char Interface::kAnimationQualityVar[] = "View_ObjectMove";
const char Interface::kPostFilterEnabledVar[] = "View_FullScreenLight";
const char Interface::kFSAAVar[] = "View_Fanhunjiao";
const char Interface::kShadowTechniqueVar[] = "View_HumanLightmap";
const char Interface::kVsyncVar[] = "View_Aplomb";

Interface* Interface::self_ = NULL;

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(
    Interface,
    VENGINE_KERNEL_GETCLASS(vengine_render::System));

Interface::Interface() {
  self_ = this;
  fairysystem_ = NULL;
  deathmode_ = false;
  deathmode_percent_ = 0;
  client_fullwidth_ = 0.0f;
  is_fullwidth_ = false;
  clientwidth_ = 0.0f;
  unitgame_toscene_ = 0.0f;
  ray_scenequery_ = NULL;
  postfilter_manager_ = NULL;
  environmentobject_ = NULL;
  terraingrid_ = NULL;
  deathmode_ = false;
  is_leftoffset_ = false;
  is_rightoffset_ = false;
  offsettag_ = kCameraOffsetNone;
  fairysystem_ = new Fairy::System();
}

Interface::~Interface() {
  release();
}

Interface* Interface::getself() {
  return self_;
}

void Interface::init(void* param) {
#if (_MSC_VER >= 1400)
  setlocale( LC_CTYPE, "" );
#endif
  VENGINE_ASSERT(param);
  HWND main_window = *((HWND*))param; //vc pointers can use like this
  g_mainwindow_handle = main_window;
  g_variablesystem = 
    dynamic_cast<vengine_variable::System*>(g_root_kernel.getnode("bin\\var"));
  VENGINE_ASSERT(g_variablesystem);
  g_eventsystem = dynamic_cast<vengine_game::EventSystem*>(
      g_root_kernel.getnode("bin\\event"));
  VENGINE_ASSERT(g_eventsystem);
  Ogre::SystemSetting::forcePixelShader(false);
  fairysystem_.init("Resources.cfg", "", "", "Engine.log"); //load resources
  
  g_debuger = dynamic_cast<vengine_capability::Debuger*>(
      g_root_kernel.getnode("bin\\debuger"));

  g_soundsystem = 
    dynamic_cast<vengine_sound::System*>(g_root_kernel.getnode("bin\\snd"));
  VENGINE_ASSERT(g_soundsystem);

  g_worldsystem = dynamic_cast<vengine_game::WorldSystem*>(
      g_root_kernel.getnode("bin\\worldman"));
  VENGINE_ASSERT(g_worldsystem);

  g_timesystem = 
    dynamic_cast<vengine_time::System*>(g_root_kernel.getnode("bin\\time"));
  VENGINE_ASSERT(g_timesystem);

  g_resourceprovider = dynamic_cast<vengine_resource::Provider*>(
      g_root_kernel.getnode("bin\\resprovider"));
  VENGINE_ASSERT(g_resourceprovider);

  g_databasesystem = 
    dynamic_cast<vengine_db::System*>(g_root_kernel.getnode("bin\\dbc"));
  VENGINE_ASSERT(g_databasesystem);

  STRING str = g_variablesystem->getstring("Gfx_API");
  Ogre::Root* ogre_root = &(Ogre::Root::getSingleton());

  //select render system
  if ("Direct3D" == str) {
#ifdef USEOGRELIB /* { */
    Ogre::InstallD3D9Plugin();
#else /* }{ */
    ogre_root->loadPlugin("RenderSystem_Direct3D9.dll");
    ogre_root->setRenderSystem(
        ogre_root->getRenderSystemByName("Direct3D9 Rendering Subsystem"));
#endif/* } */
  }
  else if ("OpenGL" == str) {
#ifdef USEOGRELIB /* { */
    
#else /* }{ */
    ogre_root->loadPlugin("RenderSystem_GL.dll");
    ogre_root->setRenderSystem(
        ogre_root->getRenderSystemByName("OpenGL Rendering Subsystem"));
#endif/* } */
  }
  else {
    VENGINE_SHOW("unkown render system!");
  }

#ifdef USEOGRELIB /* { */
  Ogre::InstallParticleFXPlugin();
  Ogre::InstallParticleFX2Plugin();
  Ogre::InstallOctreeScenePlugin();
  Ogre::InstallCgProgramManagerPlugin();
#else /* }{ */
  ogre_root->loadPlugin("Plugin_ParticleFX.dll");
  ogre_root->loadPlugin("Plugin_ParticleFX2.dll");
  ogre_root->loadPlugin("Plugin_OctreeSceneManager.dll");
  ogre_root->loadPlugin("Plugin_CgProgramManager.dll");
#endif/* } */
  resource::LoadListener resource_listener;
  try {
    //传入渲染窗口句柄
    Ogre::NameValuePairList view_setting;
    int32_t FSAA_value = g_variablesystem->getint32(kFSAAVar);
    int32_t vsync_value = g_variablesystem->getint32(kVsyncVar);
    switch (FSAA_value) {
      case 0: {
        view_setting["FSAA"] = Ogre::StringConverter::toString(0);
        break;
      }
      case 1: {
        view_setting["FSAA"] = Ogre::StringConverter::toString(1);
        break;
      }
      case 2: {
        view_setting["FSAA"] = Ogre::StringConverter::toString(2);
        break;
      }
      default: {
        view_setting["FSAA"] = Ogre::StringConverter::toString(0);
        break;
      }
    } //switch

    if (1 == vsync_value) {
      view_setting["vsync"] = "true";
    }
    else {
      view_setting["vsync"] = "false";
    }
    fairysystem_->setup(
        (Fairy::ulong)(uint32_t *)g_mainwindow_handle, &view_setting);
    //close ogre logo
    fairysystem_->getFrameStatsListener()->showLogoPanel(false);
    //状态板
    fairysystem_->getFrameStatsListener()->showStatPanel(false);
    //创建射线交集
    ray_scenequery_ = 
      fairysystem_->getSceneManager()->createRayQuery(Ogre::Ray());
    ray_scenequery_->setSortByDistance(true);

    {//camera

    }
    //初始化PostFilter系统
    postfilter_manager_ = fairysystem_->getPostFilterManager();

    //注册所有全局渲染器
    Fairy::registerAllPostFilterFactories(postfilter_manager_);
    postfilter_manager_->createPostFilter("Floodlighting", 
                                          fairysystem_->getViewport());
    postfilter_manager_->createPostFilter("Bloom", fairysystem_->getViewport());
    postfilter_manager_->createPostFilter("HeatVision", 
                                          fairysystem_->getViewport());
    postfilter_manager_->createPostFilter("Fade", fairysystem_->getViewport());
    postfilter_manager_->createPostFilter("MotionBlur", 
                                          fairysystem_->getViewport());
    //reinterpret_cast ???
    Fairy::LogicModel::SetPlaySoundFuncton(
        (OnPlaySound)(g_soundsystem->get_playfunction()));
    Fairy::LogicModel::SetStopSoundFunction(
        (OnStopSound)(g_soundsystem->get_stopfunction()));
    Fairy::BulletSystem::SetPlaySoundFuncton(
        (OnPlaySound)(g_soundsystem->get_playfunction()));
    Fairy::BulletSystem::SetStopSoundFunction(
        (OnStopSound)(g_soundsystem->get_stopfunction()));
    Fairy::LogicModel::SetGetHeightInWorldListener(
        (GetHeightInWorld)(g_worldsystem->get_terrainheight_function()));

    //init fake object --
    Ogre::ParticleSystem::setDefaultIterationInterval(0.033f);
    //系统设置接口挂接变量控制系统
    g_eventsystem->registerhandle("VARIABLE_CHANGED", on_variablechange_event);

    //恢复上次颜色设置
    g_eventsystem->push(vengine_game::eventdefine::kVariableChanged, 
                        k32BitTexturesVar, 
                        g_variablesystem->(k32BitTexturesVar).c_str());

    //加载人物阴影配置
    bool have = false;
    int32_t human_light_map = g_variablesystem->getint32(kShadowTechniqueVar, 
                                                         &have);
    if (have) scene_set_shadowtechnique(human_light_map);
    //加载全局泛光配置
    int32_t full_screen_light = g_variablesystem->getint32(
        kPostFilterEnabledVar,
        &have);
    if (have) scene_set_postfilter_enable(full_screen_light > 0 ? true : false);
    //初始化小地图探灯功能 --以后做
  }
  catch(const Ogre::Exception& e) {
    bool isthrow = true;
    if (e.getNumber() == Ogre::Exception::ERR_DUPLICATE_ITEM) {
      if ("ResourceManager::add" == e.getSource()) {
        if (Ogre::StringUtil::endsWith(listener._scriptName, 
                                       ".material", 
                                       true)) {
          char materialName[256] = {0}; 
          if (1 == sscanf(e.getDescription().c_str(), 
                          "Resource with the name %255s already exists.", 
                          materialName)) {
            Ogre::MaterialPtr material = 
              Ogre::MaterialManager::getSingleton().getByName(materialName);
            if (!material.isNull()) {
              char message[1024] = {0};
              Ogre::StringVectorPtr currentNames = 
                Fairy::findResourceFilenames(listener._groupName, 
                                             listener._scriptName);
              const Ogre::String& currentName = 
                currentNames.isNull() || currentNames->empty() ? 
                listener._scriptName : 
                currentNames->front();
              if (material->getOrigin().empty()) {
                _snprintf(message, 
                          sizeof(message) - 1,
                          "Predefined material \"%s\" duplicated in file"
                          " \"%s\", the application will exit.",
                          material->getName().c_str(), 
                          currentName.c_str());
              }
              else {
                Ogre::StringVectorPtr originNames = 
                  Fairy::findResourceFilenames(material->getGroup(), 
                                               material->getOrigin());
                const Ogre::String& originName = 
                  originNames.isNull() || 
                  originNames->empty() ? 
                  material->getOrigin() : 
                  originNames->front();
                if (currentName == originName) {
                  _snprintf(message, 
                            sizeof(message) - 1,
                            "The material \"%s\" occuring in the file \"%s\" "
                            "more than once, the application will exit.",
                            material->getName().c_str(),
                            currentName.c_str());
                }
                else {
                  _snprintf(message,
                            sizeof(message) - 1,
                            "Duplicate material \"%s\" in files \"%s\" "
                            "and \"%s\", the application will exit.",
                            material->getName().c_str(), 
                            currentName.c_str(), 
                            originName.c_str());
                }
              }
              VENGINE_SHOW("Ogre: %s", message);
            }
          }
        }
      }
    }
    throw;
  } //catch(const OgreException& e)
}

void Interface::release() {
  if (terraingrid_) {
    delete terraingrid_;
    terraingrid_ = NULL;
  }

  if (ray_scenequery_) {
    fairysystem_->getSceneManager()->destroyQuery(ray_scenequery_);
    ray_scenequery_ = NULL;
  }

  if (fairysystem_) {
    delete fairysystem_;
    fairysystem_ = NULL;
  }
}

void Interface::renderframe() {
  if (!Ogre::Root::getSingletonPtr()) {
    VENGINE_SHOW("Ogre::Root::getSingletonPtr() == NULL");
  }
  const uint16_t kRenderIntervalTimeMax = 2000;
  static uint32_t last_rendertime = 0;
  uint32_t nowtime = g_timesystem->get_nowtime();
  if (g_timesystem->get_difftime(last_rendertime, nowtime) 
      > kRenderIntervalTimeMax) {
    Ogre::Root::getSingleton().clearEventTimes();
    last_rendertime = nowtime;
    return;
  }
  last_rendertime = nowtime;
  //重置小地图探灯 --以后实现

  Ogre::Root::getSingleton().renderOneFrame();
}

void Interface::OnPaint() { //windows function
  renderframe();
}

void Interface::render_loadingframe(const char* loading) {
  renderframe();
}

void Interface::OnSizeChange(UINT message, WPARAM wParam, LPARAM lParam) {
  if (WM_SIZE == message) {
    fairysystem_->resizeWindow(LOWORD(lParam), HIWORD(lParam));
  }
  else if (WM_EXITSIZEMOVE == message) {
    RECT rect;
    GetClientRect(g_mainwindow_handle, &rect);
    fairysystem_->resizeWindow(rect.right - rect.left, rect.bottom - rect.top);
  }
}

HWND Interface::getwindow() const {
  return g_mainwindow_handle;
}

bool Interface::printscreen(const char* buffer, int32_t size) {
  const char* kScreenShortPath = "..\\ScreenShots";
  char filename[MAX_PATH] = {0};
  try {
    SYSTEMTIME nowtime;
    ::GetLocalTime(&nowtime);
    _snprintf(buffer, 
              sizeof(filename) - 1,
              "%04d_%02d_%02d_%02d_%02d_%02d.jpg",
              nowtime.wYear,
              nowtime.wMonth,
              nowtime.wDay,
              nowtime.wHour,
              nowtime.wMinute,
              nowtime.wSecond);
    ::CreateDirectory(kScreenShortPath, 0);
    //full path
    char full_filename[MAX_PATH] = {0};
    _snprintf(full_filename, 
              sizeof(full_filename) - 1, 
              "%s\\%s", 
              kScreenShortPath, 
              filename);
    fairysystem_->getRenderWindow()->writeContentsToFile(full_filename);
  }
  catch(...) {
    return false;
  }
  strncpy(buffer, full_filename, size);
  return true;
}

void Interface::debug_pushstring(const char* format, ...) {
  //do nothing
}

void Interface::debug_setstring(const char* name, const char* value) {
  //do nothing
}

void Interface::set_hitobjet_string(const char* str) {
  //do nothing  
}

void Interface::check_objecttransparent() {
  if (!fairysystem_) return;
  //以后实现
}

void Interface::set_showobject_bytype(const char* name) {
  static bool logic = true;
  static bool static_entity = true;
  static bool effect = true;
  static bool liquid = true;
  static bool pareticle = true;
  static uint64_t show_type = objecttype_enum::kObjectTypeAll;
  Ogre::String currentName = name;
  if ("lm" == currentName) show_type ^= (logic << 5);
  if ("se" == currentName) show_type ^= static_entity;
  if ("sl" == currentName) show_type ^= (liquid << 2);
  if ("ef" == currentName) show_type ^= (effect << 3);
  if ("ps" == currentName) show_type ^= (effect << 1);
  if ("all" == currentName) show_type = objecttype_enum::kObjectTypeAll;
  Fairy::LogicModelManager::LogicModelMap logicmap = 
    Fairy::LogicModelManager::getSingleton().getModelMap();
  Fairy::LogicModelManager::LogicModelMap::iterator iterator;
  for (iterator = logicmap.begin(); iterator != logicmap.end(); ++iterator) {
    Fairy::LogicModel* model = iterator->second;
    model->setVisible(show_type & objecttype_enum::kObjectTypeLogicModel);
  }
  //对象以后再做
}

bool Interface::axistrans(
       axistype_enum type,
       const vengine_math::base::threefloat_vector_t& source,
       axistype_enum targettype,
       const vengine_math::base::threefloat_vector_t& target) {
  register Fairy::TerrainData* terraindata = fairysystem_->getTerrainData();
  //资源未完全加载
  if (terraindata && 
      (0 == terraindata->getXSize() || 
      0 == terraindata->getYSize())) {
    terraindata = NULL;
  }
  vengine_math::base::threefloat_vector_t scale = getscale();
  //check position is valid
  target = source;
  if (!axis_checkvalid(type, source)) return false;
  if (type == targettype) return true;
  switch (type) {
    case axistype_enum::kAxisTypeGame: {
      if (axistype_enum::kAxisTypePlan == targettype) return true;
      if (axistype_enum::kAxisTypeRender == targettype) {
        if (terraindata) {
          target.x = 
            terraindata->mPosition.x + source.x * terraindata->mScale.x;
          target.y =
            terraindata->mPosition.y + source.y * terraindata->mScale.y;
          target.z = 
            terraindata->mPosition.z + source.z * terraindata->mScale.z;
        }
        else {
          target.x = source.x * scale.x;
          target.y = source.y * scale.y;
          target.z = source.z * scale.z;
        }
        return true;
      }
      else if (axistype_enum::kAxisTypeScreen == targettype) {
        if (!terraindata) return false;
        //相机以后再做

        return true;
      }
    }
    case axistype_enum::kAxisTypeScreen: {
      if (!terraindata) return false;
      Ogre::Vector3 render_position;
      bool result = fairysystem_->getTerrainIntersects(
          Fairy::Point((source.x, source.y), render_position));
      if (!result) return false;
      if (axistype_enum::kAxisTypeGame == targettype || 
          axistype_enum::kAxisTypePlan == targettype) {
        return axistrans(
            axistype_enum::kAxisTypeRender,
            vengine_math::base::threefloat_vector_t(
              render_position.x, render_position.y, render_position.z),
            render_position);
      }
      else if (axistype_enum::kAxisTypeRender == targettype) {
        target = vengine_math::base::threefloat_vector_t(
            render_position.x,
            render_position.y,
            render_position.z);
        return true;
      }
      break;
    }
    default:
      break;
  }
  return false;
}

vengine_math::base::threefloat_vector_t Interface::getscale() const {
  register Fairy::TerrainData* terraindata = fairysystem_->getTerrainData();
  if (terraindata && 
      terraindata->getXSize() > 0 && 
      terraindata->getYSize() > 0) {
    return vengine_math::base::threefloat_vector_t(terraindata->mScale.x,
                                                   terraindata->mScale.y,
                                                   terraindata->mScale.z);
  }
  return vengine_math::base::threefloat_vector_t(100.0f, 100.0f, 100.0f);
}

bool Interface::axis_checkvalid(
    axistype_enum type,
    const vengine_math::base::threefloat_vector_t& axis) {
  register Fairy::TerrainData* terraindata = fairysystem_->getTerrainData();
  bool result = false;
  if (terraindata && 
      (0 == terraindata->getXSize() || 0 == terraindata->getYSize())) {
    terraindata = 0;
  }
  switch (type) {
    case axistype_enum::kAxisTypeGame: {
      break;
    }
    case axistype_enum::kAxisTypePlan: {
      if (terraindata) {
        result = terraindata->isValidGrid(
            std::make_pair(static_cast<int32_t>(axis.x), 
              static_cast<int32_t>(axis.z)));
      }
      else {
        result = true;
      }
      break;
    }
    case axistype_enum::kAxisTypeRender: {
      if (terraindata) {
        result = terraindata->isValidCoord(axis.x, axis.z);
      }
      else {
        result = true;
      }
      break;
    }
    case axistype_enum::kAxisTypeScreen: {
      RECT rect;
      ::GetClientRect(g_mainwindow_handle, &rect);
      POINT point;
      point.x = static_cast<int32_t>(rect.x);
      point.y = static_cast<int32_t>(rect.y);
      result = ::PtInRect(&rect, point);
      break;
    }
    default:
      break;
  }
  return result;
}

//以下接口以后实现
void Interface::camera_setcurrent(cameratype_enum type) {

}

void Interface::camera_setoffset(cameraoffset_enum tag, 
                                 float paralleloffset, 
                                 float verticaloffset) {

}

void Interface::camera_set_lookat(
       const vengine_math::base::threefloat_vector_t& position) {

}

void Interface::camera_setzoom(float zoom) {

}

void Interface::camera_setzoom(bool up, int32_t multiple) {

}

float Interface::camera_getzoom() const {
  return 0.0f;
}

void Interface::camera_setdirection(float direction) {

}

void Interface::camera_adddirection(float multiple) {

}
  
void float Interface::camera_getdirection() const {
  return .0f;
}

void Interface::camera_getwindow_to_viewpointray(
       int32_t x,
       int32_t y,
       vengine_math::base::floatray& ray) {

}

void Interface::camera_vibrate_onetime() {

}

void Interface::camera_vibrate_onetime(float range, 
                                       float steplength, 
                                       uint32_t times) {

}

void Interface::camera_set_eyeposition(
       const vengine_math::base::threefloat_vector_t& position) {

}

void Interface::camera_set_lookat_position(
       const vengine_math::base::threefloat_vector_t& position) {

}

void Interface::scene_preload(const STRING& scenename) {

}

void Interface::scene_load(uint16_t id, const STRING& scenedefine) {

}

void Interface::scene_unload() {

}

void Interface::scene_set_postfilter(const char* name,
                                     bool state) {

}

void Interface::scene_set_lightmap_quality(int32_t quality) {

}
   
void Interface::scene_set_postfilter_death(bool enter) {

}

void Interface::scene_set_environmentinfo(
       const vengine_math::base::threefloat_vector_t& position) {

}

void Interface::scene_enable_32bittextures(bool setting) {

}

void Interface::scene_set_texturefiltering(uint8_t option) {

}

void Interface::scene_set_animationquality(uint8_t option) {

}

void Interface::scene_set_postfilter_enable(bool flag) {

}

void Interface::scene_set_shadowtechnique(uint8_t flag) {

}

void Interface::scene_show_girdswitch(int32_t zonesize) {

}

void Interface::debug_addparticle(
       const char* name,
       const vengine_math::base::threefloat_vector_t& position) {

}

void Interface::debug_set_fakecamera(uint8_t type, float value) {

}

void Interface::debug_toggleshow_debugpanel() {

}

void Interface::debug_toggleshow_boundingbox() {

}

EntityNode* Interface::new_entityobject(EntityNode::type_enum type) {
  return NULL;
}

EntityNode* Interface::find_hitfairy_object(int32_t x, int32_t y) {
  return NULL;
}

void Interface::fakeobject_create(const char* name,
                                  EntityNode* node,
                                  EntityNode* parentnode,
                                  const char* cameraname,
                                  int32_t textuewidth,
                                  int32_t textueheight,
                                  const char* backgroundname) {

}

void Interface::fakeobject_destroy(const char* name) {

}

void Interface::fakeobject_show(const char* name,
                                bool visible,
                                float aspectratio) {

}

bool Interface::fakeobject_setattach(EntityNode* node, 
                                     EntityNode* attachnode) {
  return true;
}


} //namespace engine
