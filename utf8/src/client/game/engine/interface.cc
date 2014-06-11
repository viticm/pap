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
#include "vengine/variable/system.h"
#include "vengine/time/system.h"
#include "vengine/resource/provider.h"
#include "client/game/resource/loadlistener.h"
#include "client/game/stdafx.h" //Precompiled not use like this, i will fix it
#include "client/game/globa.h"
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

} //namespace engine
