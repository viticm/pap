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
    int32_t human_light_map = g_variablesystem->getfloat(kShadowTechniqueVar, 
                                                         &have);
    if (have) scene_set_shadowtechnique(human_light_map > 0 ? true : false);
    //加载全局泛光配置


  }
  catch(...) {

  }
}


} //namespace engine
