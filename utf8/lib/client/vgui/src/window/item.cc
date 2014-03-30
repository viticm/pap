#include "CEGUIWindow.h"
#include "CEGUIWindowManager.h"

#include "FalActionButton.h"
#include "FalSuperTooltip.h"
#include "FalagardMeshWindow.h"
#include "FalagardComplexWindow.h"
#include "FalChatHistory.h"

#include "LuaPlus.h"

#include "vengine/kernel/base.h"
#include "vengine/db/system.h"
#include "vengine/db/structs/all.h"
#include "vengine/script/system.h"
#include "vengine/capability/profile.h"
#include "vengine/game/object/basesystem.h"
#include "vengine/game/eventdefine.h"
#include "vengine/variable/system.h"
#include "vengine/sound/system.h"

#include "vgui/script/base.h"
#include "vgui/luacontrol/all.h"
#include "vgui/string/system.h"
#include "vgui/base/system.h"

#include "vgui/window/item.h"

namespace vgui_window {

Item::Item(const vengine_db::structs::ui::layoutdefine_t* layoutdefine) {
  VENGINE_ASSERT(layoutdefine);
  id_ = layoutdefine->id;
  windowname_ = layoutdefine->name;
  layout_filename_ = layoutdefine->layout;
  script_filename_ = layoutdefine->script;
  is_candemise_ = layoutdefine->demise;
  defaultposition_ = layoutdefine->defaultposition;
  window_ = NULL;
  show_ = false;
  layoutloaded_ = false;
}

Item::~Item() {
  //释放lua环境
  g_scriptsystem->destroyenvironment(scriptenvironment_);
  scriptenvironment_ = NULL;
  //释放lua实例
  uint32_t i;
  for (i = 0; i < static_cast<uint32_t>(controls_.size()); ++i) {
    if (controls_[i]) {
      luacontrol::Window::destroycontrol(controls_[i]);
      controls_[i] = NULL;
    }
  }
  controls_.clear();
  CEGUI::WindowManager::getSingleton().destroyWindow(window_);
  window_ = NULL;
}

}; //namespace vgui_window
