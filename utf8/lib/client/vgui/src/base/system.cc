#include <windows.h>

#include "vgui/stdafx.h"

#include "CEGUISystem.h"
#include "OgreCEGUIRenderer.h"
#include "CEGUISchemeManager.h"
#include "CEGUIWindowManager.h"
#include "CEGUIFontManager.h"
#include "CEGUIWindow.h"
#include "CEGUIScriptModule.h"
#include "CEGUIImageset.h"
#include "CEGUIAnimateManager.h"
#include "CEGUIEventArgs.h"
#include "elements/CEGUIStaticImage.h"
#include "CEGUIIme.h"
#include "CEGUIHyperLinkManager.h"
#include "CEGUIPropertyHelper.h"

#include "OgreCEGUITexture.h"
#include "OgreTexture.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgreTextureManager.h"
#include "OgreTimer.h"

#include "FalActionButton.h"
#include "FalIMEEditBox.h"
#include "FalChatHistory.h"
#include "FalChatBoard.h"
#include "FalMultiIMEEditBox.h"

#include "vengine/exception/base.h"
#include "vengine/kernel/base.h"
#include "vengine/script/system.h"
#include "vengine/input/system.h"
#include "vengine/render/system.h"
#include "vengine/game/action/system.h"
#include "vengine/time/system.h"
#include "vengine/capability/profile.h"
#include "vengine/capability/debuger.h"
#include "vengine/game/object/fakesystem.h"
#include "vengine/game/interface.h"
#include "vengine/game/worldsystem.h"
#include "vengine/ui/creature_headboard.h"
#include "vengine/db/system.h"
#include "vengine/variable/system.h"

#include "vgui/script/base.h"
#include "vgui/icon/manager.h"
#include "vgui/window/manager.h"
#include "vgui/string/system.h"
#include "vgui/creature/head/board/system.h"
#include "vgui/base/system.h"
//defines in last, remember
#include "vengine/game/eventdefine.h"
#include "vengine/db/struct/all.h"

namespace vgui_base {

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(
  System,
  VENGINE_KERNEL_GETCLASS(vengine_ui::System));

System* System::self_ = NULL;

System::System() {
  self_ = this;
  buttonname_indragging_ = "";
  draggingcursor_ = NULL;
  is_dragend_ = false;
  active_paopao_ = true;
  is_ctrlinfo_enable_ = false;
}

System::~System() {
  //do nothing
}

System* System::getself() {
  return self_;
}

vgui_icon::Manager* System::get_iconmanager() {
  return iconmanager_;
}

void System::injectinput() {
  CEGUI::System& cegui_system = CEGUI::System::getSingleton();
  vengine_input::eventqueue& eventqueue = g_inputsystem->get_eventqueue();
  POINT point = g_inputsystem->get_mousepostion();
  uint32_t i;
  for (i = 0; i < static_cast<uint32_t>(eventqueue.size()); ++i) {
    vengine_input::event_t event = eventqueue[i];
    if (event.processed) continue; //已经处理过
    switch (event.id) {
      case vengine_input::kEventId_MOUSE_MOVE:
        break;
      case vengine_input::kEventId_MOUSE_LDRAG_MOVE:
        break;
      case vengine_input::kEventId_MOUSE_RDRAG_MOVE: {
        POINT point = g_inputsystem->get_mousepostion();
        if (cegui_system_->injectMousePosition(static_cast<float>(point.x),
                                               static_cast<float>(point.y))) {
          event.processed = true;
        }
        break;
      }
      case vengine_input::kEventId_MOUSE_LBDOWN: {
        //如果在拖动中,处理拖动结束
        if (!buttonname_indragging_.empty()) {
          CEGUI::FalagardActionButton* button_indragging = 
            (CEGUI::FalagardActionButton*)
            CEGUI::WindowManager::getSingleton().getWindow(
                buttonname_indragging_);
          if (button_indragging) {
            CEGUI::Window* window = cegui_system.getTargetWindow(CEGUI::Point(
                  static_cast<float>(point.x), static_cast<float>(point.y)));
            if (window) {
              on_dragend(window);
              event.processed = true;
            }
          }
          else {
            if (cegui_system.injectMouseButtonDown(CEGUI::LeftButton))
              event.processed = true;
          }
        }
        break;
      }
      case vengine_input::kEventId_MOUSE_LBUP: {
        if (CEGUI::Window::getCaptureWindow()) {
          if (cegui_system.injectMouseButtonUp(CEGUI::LeftButton)) {
            event.processed = true;
            //捕获本桢鼠标click事件
            for (uint32_t j = 0; 
                 j < static_cast<uint32_t>(eventqueue.size());
                 ++j) {
              if (vengine_input::kEventId_MOUSE_LBCLICK == eventqueue[j].id || 
                  vengine_input::kEventId_MOUSE_LBUP == eventqueue[j].id) {
                eventqueue[j].processed = true;
              }
            }
          }
        }
        if (!buttonname_indragging_.empty()) {
           CEGUI::FalagardActionButton* button_indragging = 
            (CEGUI::FalagardActionButton*)
            CEGUI::WindowManager::getSingleton().getWindow(
                buttonname_indragging_);
          if (button_indragging) {
            CEGUI::Window* window = cegui_system.getTargetWindow(CEGUI::Point(
                  static_cast<float>(point.x), static_cast<float>(point.y)));
            if (window && 
                window->testClassName((CEGUI::utf8*)"FalagardActionButton")) {
              on_dragend(window);
              event.processed = true;
            }
          }
        }
        break;
      }
      case vengine_input::kEventId_MOUSE_LBCLICK: {
        if (cegui_system.injectMouseButtonUp(CEGUI::LeftButton)) {
          event.processed = true;
          //捕获本桢鼠标click事件
          for (uint32_t j = 0; 
               j < static_cast<uint32_t>(eventqueue.size());
               ++j) {
            if (vengine_input::kEventId_MOUSE_LBCLICK == eventqueue[j].id || 
                vengine_input::kEventId_MOUSE_LBUP == eventqueue[j].id) {
              eventqueue[j].processed = true;
            }
          }
        }
        break;
      }
      case vengine_input::kEventId_MOUSE_RBDOWN: {
        if (cegui_system.injectMouseButtonDown(CEGUI::RightButton))
          event.processed = true;
        break;
      }
      case vengine_input::kEventId_MOUSE_RBCLICK: {
        if (cegui_system.injectMouseButtonUp(CEGUI::RightButton)) {
          event.processed = true;
          //捕获本桢鼠标click事件
          for (uint32_t j = 0; 
               j < static_cast<uint32_t>(eventqueue.size());
               ++j) {
            if (vengine_input::kEventId_MOUSE_RBCLICK == eventqueue[j].id || 
                vengine_input::kEventId_MOUSE_RBUP == eventqueue[j].id) {
              eventqueue[j].processed = true;
            }
          }
        }
        //右键点击，恢复到缺省技能操作，用于退出修理，鉴定，等特殊鼠标命令状态
        g_gameinterface->skill_cancelaction();
        break;
      }
      case vengine_input::kEventId_MOUSE_RBUP: {
        if (cegui_system.injectMouseButtonUp(CEGUI::RightButton))
          event.processed = true;
        break;
      }
      case vengine_input::kEventId_MOUSE_LBDOWNREPEAT:
        break;
      default:
        break;
    } //switch

    if (!event.processed) {
      //对于未加handle的keybord event，根据位置判断是否应该捕获
      if (vengine_input::kEventId_KEY_DOWN == event.id || 
          vengine_input::kEventId_KEY_UP == event.id) {
        
      }
      else { //对于未加handle的mouse event，根据位置判断是否应该捕获
        CEGUI::Window* window = cegui_system.getTargetWindow(CEGUI::Point(
              static_cast<float>(point.x), static_cast<float>(point.y)));
        if (vengine_input::kEventId_MOUSE_LBDOWN == event.id ||
            vengine_input::kEventId_MOUSE_LBUP == event.id ||
            vengine_input::kEventId_MOUSE_LBCLICK == event.id ||
            vengine_input::kEventId_MOUSE_LDBCLICK == event.id ||
            vengine_input::kEventId_MOUSE_LBDOWNREPEAT == event.id) {
          if (window && !window->getMouseLButtonHollow()) {
            event.processed = true;
            if (window->testClassName((CEGUI::utf8*)"FalagardChatBoard")) {
              event.processed = false;
            }
          }
        }
        else if (vengine_input::kEventId_MOUSE_RBDOWN == event.id ||
                 vengine_input::kEventId_MOUSE_RBUP == event.id ||
                 vengine_input::kEventId_MOUSE_RBCLICK == event.id ||
                 vengine_input::kEventId_MOUSE_RDBCLICK == event.id) {
          if (window && !window->getMouseRButtonHollow()) {
            event.processed = true;
          }
        }
        else if (window && window->getMouseHollow()) {
          event.processed = true;
        }
      }
    }
  } //for loop
}

bool System::messageprocess(HWND hwnd, 
                           uint32_t message, 
                           WPARAM wparam, 
                           LPARAM lparam) { //文字输入消息
  bool result = Ime::ImeMsgProc(message, 
                                static_cast<uint32_t>(wparam), 
                                static_cast<uint32_t>(lparam));
  return result;
}

bool System::is_mousehover() {
  if (buttonname_indragging_ != "") {
    CEGUI::FalagardActionButton* button_indragging = 
      (CEGUI::FalagardActionButton *)
      CEGUI::WindowManager::getSingleton().getWindow(buttonname_indragging_);
    if (button_indragging) return true;
  }
  POINT point = g_inputsystem->get_mousepostion();
  CEGUI::System& cegui_system = CEGUI::System::getSingleton();
  CEGUI::Window* window = cegui_system.getTargetWindow(
    CEGUI::Point(
    static_cast<float>(point.x), static_cast<float>(point.y)), 0);
  if (window && 
      !(window->getMouseHollow() || window->getMouseLButtonHollow())) {
    if (window->testClassName((CEGUI::utf8*)"FalagardChatBoard") && 
        get_chatboard_hyplink_content(point.x, point.y).empty()) {
      g_rendersystem->debug_setstring("UI", "-");
      return false;
    }
    g_rendersystem->debug_setstring("UI", window->getName().c_str());
    return true;
  }
  return false;
}

bool System::is_mousehover_chatboard(int64_t x, int64_t y) {
  CEGUI::System& cegui_system = CEGUI::System::getSingleton();
  CEGUI::Window* window = cegui_system.getTargetWindow(
      CEGUI::Point(
        static_cast<float>(x), 
        static_cast<float>(y)));
  //const char* name = window->getName().c_str();
  if (window && window->testClassName((CEGUI::utf8*)"FalagardChatBoard")) {
    return true;
  }
  else {
    return false;
  }
}

STRING System::get_chatboard_hyplink_content(int64_t x, int64_t y) {
  if (is_mousehover_chatboard(x, y)) {
    CEGUI::System& cegui_system = CEGUI::System::getSingleton();
    CEGUI::Window* window = cegui_system.getTargetWindow(
        CEGUI::Point(
          static_cast<float>(x), 
          static_cast<float>(y)));
    CEGUI::String32 str = 
      CEGUI::HyperLinkManager::getSingleton().getHyperLinkContex(
          window, 
          CEGUI::Point(
            static_cast<float>(x), 
            static_cast<float>(y)));
    STRING mbcs;
    vgui_string::System::utf8_to_mbcs(str.c_str(), mbcs);
    return mbcs;
  }
  return STRING("");
}

void System::init(void*) {
  //保存全局变量
  g_scriptsystem = dynamic_cast<vengine_script::System*>(
      g_kernel->getnode("bin\\script"));
  VENGINE_ASSERT(g_scriptsystem);
  g_game_eventsystem = dynamic_cast<vengine_game::EventSystem*>(
      g_kernel->getnode("bin\\event"));
  VENGINE_ASSERT(g_game_eventsystem);
  g_game_actionsystem = dynamic_cast<vengine_game::action::System*>(
      g_kernel->getnode("bin\\action"));
  VENGINE_ASSERT(g_game_actionsystem);
  g_inputsystem = dynamic_cast<vengine_input::System*>( 
      g_kernel->getnode("bin\\input"));
  VENGINE_ASSERT(g_inputsystem);
  g_rendersystem = dynamic_cast<vengine_render::System*>(
      g_kernel->getnode("bin\\gfx"));
  VENGINE_ASSERT(g_rendersystem);
  g_game_objectsystem = dynamic_cast<vengine_game::object::BaseSystem*>(
      g_kernel->getnode("bin\\objman"));
  VENGINE_ASSERT(g_game_objectsystem);
  g_cursorsystem = dynamic_cast<vengine_cursor::System*>(
      g_kernel->getnode("bin\\cursor"));
  VENGINE_ASSERT(g_cursorsystem);
  g_capability_debuger = dynamic_cast<vengine_capability::Debuger*>(
      g_kernel->getnode("bin\\debuger"));
  VENGINE_ASSERT(g_capability_debuger);
  g_game_worldsystem = dynamic_cast<vengine_game::WorldSystem*>(
      g_kernel->getnode("bin\\worldman"));
  VENGINE_ASSERT(g_game_worldsystem);
  g_timesystem = dynamic_cast<vengine_time::System*>(
      g_kernel->getnode("bin\\time"));
  VENGINE_ASSERT(g_timesystem);
  g_game_fake_objectsystem = dynamic_cast<vengine_game::object::FakeSystem*>(
      g_kernel->getnode("bin\\fake"));
  VENGINE_ASSERT(g_game_fake_objectsystem);
  g_variablesystem = dynamic_cast<vengine_variable::System*>( 
      g_kernel->getnode("bin\\var"));
  VENGINE_ASSERT(g_variablesystem);
  g_databasesystem = dynamic_cast<vengine_db::System*>(
      g_kernel->getnode("bin\\dbc"));
  VENGINE_ASSERT(g_databasesystem);
  g_soundsystem = dynamic_cast<vengine_sound::System*>(
      g_kernel->getnode("bin\\snd"));
  VENGINE_ASSERT(g_soundsystem);
  g_game_itemtransfer_system = dynamic_cast<vengine_game::ItemTransferSystem*>(
      g_kernel->getnode("bin\\transfer"));
  VENGINE_ASSERT(g_game_itemtransfer_system);
  g_mainwindow_handle = g_rendersystem->getwindow(); //渲染窗口
  
  //ogre init
  ogreroot_ = Ogre::Root::getSingletonPtr();
  VENGINE_ASSERT(ogreroot_);

  Ogre::RenderWindow* window = 
    (Ogre::RenderWindow*)ogreroot_->getRenderTarget("");
  script_ = new vgui_script::Base();
  cegui_render_ = new CEGUI::OgreCEGUIRenderer(
      (Ogre::RenderTarget*)window,
      Ogre::RENDER_QUEUE_OVERLAY, 
      false, 
      0, 
      ogreroot_->getSceneManager("FairyMainScene"));
  cegui_system_ = new CEGUI::System(cegui_render_, script_, (CEGUI::utf8*)"");
  //使用UI资源组
  cegui_system_->getResourceProvider()->setDefaultResourceGroup("General");

  //加载总控文件
  CEGUI::SchemeManager::getSingleton().loadScheme(
      "Schema\\WoWLookSkin.scheme.xml");
  cegui_system_->setTooltip("WoWLook/Tooltip");
  //挂接超连接管理器
  CEGUI::HyperLinkManager::getSingleton().subscribeEvent(
      "HyperLinkActive",
      CEGUI::Event::Subscriber(&System::handle_hyperlink_active, 
        getself()));
  CEGUI::HyperLinkManager::getSingleton().subscribeEvent(
      "HyperLinkLeftActive",
      CEGUI::Event::Subscriber(&System::handle_hyperlink_leftactive, 
        getself()));
  CEGUI::HyperLinkManager::getSingleton().subscribeEvent(
      "HyperLinkRightActive",
      CEGUI::Event::Subscriber(&System::handle_hyperlink_rightactive, 
        getself()));
  CEGUI::HyperLinkManager::getSingleton().subscribeEvent(
      "HyperLinkInactive",
      CEGUI::Event::Subscriber(&System::handle_hyperlink_inactive, 
        getself()));
  //初始化动画管理器
  new CEGUI::AnimateManager( "schema\\wowanimate.xml");
  
  //中文输入初始化
  Ime::InitializeImm((unsigned int)g_mainwindow_handle);
  
  //文本管理器
  stringsystem_ = new vgui_string::System();
  stringsystem_->init();

  //初始化图标管理器
  iconmanager_ = new vgui_icon::Manager();
  VENGINE_ASSERT(iconmanager_);
  iconmanager_->init();

  //初始化布局管理器
  windowmanager_ = new vgui_window::Manager();
  VENGINE_ASSERT(windowmanager_);
  windowmanager_->init();

  //初始化角色信息板管理器
  creature_headboard_system_ = new vgui_creature::head_board::System();
  VENGINE_ASSERT(creature_headboard_system_);
  creature_headboard_system_->init();

  //创建地图探灯
  const char* maplight_name = "MapLight_RenderTexture";
  CEGUI::Texture* rtt_maplight_texture =
    ((CEGUI::OgreCEGUIRenderer*)cegui_render_)->createTexture(
      (CEGUI::utf8*)maplight_name);
  VENGINE_ASSERT(maplight_name);
  //创建Imageset
  CEGUI::Imageset* rtt_imageset = 
    CEGUI::ImagesetManager::getSingleton().createImageset(
        maplight_name, 
        rtt_maplight_texture);
  rtt_imageset->disableAutoFree();
  rtt_imageset->defineImage(
      (CEGUI::utf8*)"View",
      CEGUI::Point(0.0f, 0.0f),
      CEGUI::Size(rtt_maplight_texture->getWidth(), 
                  rtt_maplight_texture->getHeight()),
      CEGUI::Point(0.0f,0.0f));
  buttonname_indragging_ = "";
  RECT rect;
  GetClientRect(g_mainwindow_handle, &rect);
  //聊天窗口
  g_game_eventsystem->push(vengine_game::event_id::kUIChatAdjustMoveCtl, 
                           rect.right - rect.left,
                           rect.bottom - rect.top);
}

void System::release() {
  if (creature_headboard_system_) creature_headboard_system_->release();
  SAFE_DELETE(creature_headboard_system_);
  SAFE_DELETE(iconmanager_);
  SAFE_DELETE(windowmanager_);
  SAFE_DELETE(stringsystem_);
  delete CEGUI::AnimateManager::getSingletonPtr();
  Ime::UninitializeImm();
  SAFE_DELETE(cegui_system_);
  SAFE_DELETE(cegui_render_);
  SAFE_DELETE(script_);
}

void System::tick() {
  static uint32_t lasttime = 0;
  uint32_t nowtime = g_timesystem->get_nowtime();
  if (0 == lasttime) {
    lasttime = nowtime;
    return;
  }
  
  if (CEGUI::System::getSingletonPtr()) {
     CEGUI::System::getSingleton().injectTimePulse(g_timesystem->get_difftime(
           lasttime, nowtime) / 1000.0f);
  }
  lasttime = nowtime;
  if (creature_headboard_system_) creature_headboard_system_->tick();
  static uint32_t last_freetime = g_timesystem->get_nowtime();
  if (g_timesystem->get_difftime(last_freetime, nowtime) > 6000) { 
    //每分钟释放一次
    CEGUI::ImagesetManager::getSingleton().FreeUnuseImageset();
    last_freetime = nowtime;
  }
}

void System::on_windowsize_change(uint32_t message, 
                                  WPARAM wparam, 
                                  LPARAM lparam) {
  //用户点击最大化或者最小化
  if (WM_SIZE == message) {
    cegui_render_->_notifySizeChanged();
  }
  else if (WM_EXITSIZEMOVE == message) { //用户拖动窗口边缘结束
    cegui_render_->_notifySizeChanged();
  }
  if (windowmanager_) windowmanager_->on_sizechange();
}

bool System::handle_action_dragdrop_started(const CEGUI::EventArgs& event) {
  const CEGUI::WindowEventArgs& eventwindow = 
    (const CEGUI::WindowEventArgs&)event;
  CEGUI::Window* window = eventwindow.window;
  if (!(window->testClassName((CEGUI::utf8*)"FalagardActionButton")))
    return false;
  on_dragbegin(dynamic_cast<CEGUI::FalagardActionButton*>(window));
  return false;
}

bool System::handle_actionbutton_mouseenter(const CEGUI::EventArgs& event) { 
  const CEGUI::WindowEventArgs& eventwindow =
    (const CEGUI::WindowEventArgs&)event;
  CEGUI::Window* window = eventwindow.window;
  if (!(window->testClassName((CEGUI::utf8*)"FalagardActionButton"))) 
    return false;
  //如果在拖拽中
  if (draggingcursor_) return false;
  //得到逻辑数据
  CEGUI::IFalagardActionButton* button = 
    dynamic_cast<CEGUI::IFalagardActionButton*>(
        dynamic_cast<CEGUI::FalagardActionButton*>(window));
  vengine_game::action::Item* actionitem = g_game_actionsystem->get(
      (int32_t)(int32_t*)button->getLogicItemData());
  if (actionitem) {
    if (vengine_game::action::kOperateTypeChatMood == actionitem->get_operatetype()) {
      STRING tip = actionitem->getname();
      CEGUI::String32 str;
      vgui_string::System::getself()->parsestring_runtime(tip, str);
      window->setTooltipText(str);
    }
    else {
      //调用逻辑接口
      CEGUI::Rect rect = window->getPixelRect();
      actionitem->notify_tooltips_show(static_cast<int32_t>(rect.d_left),
                                       static_cast<int32_t>(rect.d_top),
                                       static_cast<int32_t>(rect.d_right),
                                       static_cast<int32_t>(rect.d_bottom));
    }
  }
  return false;
}

bool System::handle_actionbutton_mouseleave(const CEGUI::EventArgs& event) {
  const CEGUI::WindowEventArgs& eventwindow =
    (const CEGUI::WindowEventArgs&)event;
  CEGUI::Window* window = eventwindow.window;
  if (!(window->testClassName((CEGUI::utf8*)"FalagardActionButton"))) 
    return false;
  //如果在拖拽中
  if (draggingcursor_) return false;
  //得到逻辑数据
  CEGUI::IFalagardActionButton* button = 
    dynamic_cast<CEGUI::IFalagardActionButton*>(
        dynamic_cast<CEGUI::FalagardActionButton*>(window));
  vengine_game::action::Item* actionitem = g_game_actionsystem->get(
      (int32_t)(int32_t*)button->getLogicItemData());
  if (actionitem) actionitem->notify_tooltips_hide();
  return false;
}

bool System::handle_actionbutton_parenthidden(const CEGUI::EventArgs& event) { 
  const CEGUI::WindowEventArgs& eventwindow =
    (const CEGUI::WindowEventArgs&)event;
  CEGUI::Window* window = eventwindow.window;
  if (!(window->testClassName((CEGUI::utf8*)"FalagardActionButton"))) 
    return false;
  //如果在拖拽中
  if (draggingcursor_) return false;
  //得到逻辑数据
  CEGUI::IFalagardActionButton* button = 
    dynamic_cast<CEGUI::IFalagardActionButton*>(
        dynamic_cast<CEGUI::FalagardActionButton*>(window));
  vengine_game::action::Item* actionitem = g_game_actionsystem->get(
      (int32_t)(int32_t*)button->getLogicItemData());
  if (actionitem) actionitem->notify_tooltips_hide();
  return false;
}

bool System::handle_meshwindow_shown(const CEGUI::EventArgs& event) {
  const CEGUI::WindowEventArgs& eventwindow =
    (const CEGUI::WindowEventArgs&)event;
  CEGUI::Window* window = eventwindow.window;
  if (!(window->testClassName((CEGUI::utf8*)"FalagardMeshWindow"))) 
    return false;
  CEGUI::Size size = window->getAbsoluteSize();
  g_game_fake_objectsystem->on_ui_shown(window->getName().c_str(), 
                                        size.d_width / size.d_height);
  return false;
}

bool System::handle_meshwindow_hiden(const CEGUI::EventArgs& event) {
  const CEGUI::WindowEventArgs& eventwindow = 
    (const CEGUI::WindowEventArgs&)event;
  CEGUI::Window* window = eventwindow.window;
  if (!(window->testClassName((CEGUI::utf8*)"FalagardMeshWindow")))
    return false;
  g_game_fake_objectsystem->on_ui_hiden(window->getName().c_str());
  return false;
}

void System::on_dragbegin(CEGUI::FalagardActionButton* draggingbutton) {
  CEGUI::IFalagardActionButton* button = 
    dynamic_cast<CEGUI::IFalagardActionButton*>(draggingbutton);
  vengine_game::action::Item* actionitem = g_game_actionsystem->get(
      (int32_t)(int32_t*)button->getLogicItemData());
  if (!actionitem) return;
  //ui捕获输入
  g_inputsystem->setcapture(vengine_input::kCaptureStatusUI);
  //将光标设为相应的image
  if (draggingcursor_) {
    ::DestroyIcon(draggingcursor_);
    draggingcursor_ = NULL;
  }
  draggingcursor_ = vgui_icon::Manager::getself()->create_as_windowscursor(
      actionitem->getname());
  if (draggingcursor_) g_cursorsystem->enterui(draggingcursor_);
  buttonname_indragging_ = 
    (dynamic_cast<CEGUI::Window*>(draggingbutton))->getName();
}

void System::on_dragend(CEGUI::Window* targetwindow) {
  //释放捕获
  g_inputsystem->setcapture(vengine_input::kCaptureStatusNone);
  //恢复光标
  if (draggingcursor_) {
    g_cursorsystem->leaveui();
    ::DestroyIcon(draggingcursor_);
    draggingcursor_ = NULL;
  }
  g_cursorsystem->set(vengine_cursor::kTypeNormal);
  //通知正在托拽的ActionButton
  if (buttonname_indragging_ != "") {
    CEGUI::FalagardActionButton* button_indragging = 
      (CEGUI::FalagardActionButton*)CEGUI::WindowManager::getSingleton().
      getWindow(buttonname_indragging_);
    CEGUI::IFalagardActionButton* button = 
      dynamic_cast<CEGUI::IFalagardActionButton*>(button_indragging);
    if (button_indragging) button->notifyDragingEnd();
    //判断是否被销毁
    bool bedestroy = targetwindow && targetwindow->getMouseHollow();
    //如果被拖入一个actionbutton上，取得该ActionButton的DragAcceptName
    CEGUI::IFalagardActionButton* targetbutton = NULL;
    if (targetwindow && 
        targetwindow->testClassName("FalagardActionButton")) {
      targetbutton = 
        dynamic_cast<CEGUI::IFalagardActionButton*>(
          dynamic_cast<CEGUI::FalagardActionButton*>(targetwindow));
      targetbutton->notifyDragDrop_Droped(button_indragging);
    }
    //通知逻辑系统
    vengine_game::action::Item* actionitem = g_game_actionsystem->get(
      (int32_t)(int32_t*)(button->getLogicItemData()));
    if (actionitem) {
      actionitem->notify_dragdrop_dragged(
        bedestroy, 
        targetbutton ? (targetbutton->getDragAcceptName()) : NULL, 
        (dynamic_cast<CEGUI::FalagardActionButton*>(button))
        ->getDragAcceptName());
    }
    buttonname_indragging_ = "";
    change_dragflag(true);
  }

  CEGUI::WindowManager::WindowIterator iterator = 
    CEGUI::WindowManager::getSingleton().getIterator();
  for (iterator.toStart(); !iterator.isAtEnd(); ++iterator) {
    CEGUI::Window* window = iterator.getCurrentValue();
    if (window && 
        window->isVisible() && 
        window->testClassName((CEGUI::utf8*)"FalagardActionButton")) {
      CEGUI::IFalagardActionButton* button =
        dynamic_cast<CEGUI::IFalagardActionButton*>(
            dynamic_cast<CEGUI::FalagardActionButton*>(window));
      button->notifyDragingEnd();
    }
  }
}

vengine_ui::CreatureHeadBoard* System::create_creature_headboard() {
  vengine_ui::CreatureHeadBoard* board;
  board = (vengine_ui::CreatureHeadBoard*)creature_headboard_system_->create();
  return board;
}
void System::add_behit_board(bool _double, 
                             const char* info, 
                             float startx, 
                             float starty, 
                             uint8_t type, 
                             uint8_t movetype) {
  creature_headboard_system_->add_new_behit(_double,
                                           info,
                                           startx,
                                           starty,
                                           type,
                                           movetype);
}
 
bool System::is_windowshow(const char* uiname, const char* childname) {
  bool result = windowmanager_->isshow(uiname, childname); //as easy
  return result;
}

void System::fakeobject_show(const char* windowname, const char* name) {
  //取得UI窗口
  CEGUI::Window* meshwindow = 
    CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)windowname);
  if (!meshwindow || 
      !(meshwindow->testClassName((CEGUI::utf8*)"FalagardMeshWindow"))) return;
  //按照固定的命名规则取得渲染纹理
  STRING imagename = name;
  imagename += vengine_game::object::kFakeRenderTexture;

  //取得纹理，该纹理应该在渲染层已经创建
  CEGUI::Texture* rtt_texture = 
    cegui_render_->createTexture((CEGUI::utf8*)imagename.c_str());
  VENGINE_ASSERT(rtt_texture);

  //创建UI用的Imageset
  CEGUI::Imageset* rtt_imageset =
    CEGUI::ImagesetManager::getSingleton().createImageset(imagename.c_str(), 
                                                          rtt_texture);
  rtt_imageset->disableAutoFree();
  rtt_imageset->defineImage(
      (CEGUI::utf8*)"View",
      CEGUI::Point(0.0f, 0.0f),
      CEGUI::Size(rtt_texture->getWidth(), rtt_texture->getHeight()),
      CEGUI::Point(0.0f,0.0f));

  //设置显示纹理
  (dynamic_cast<CEGUI::StaticImage*>(meshwindow))->setImage(
      &(rtt_imageset->getImage((CEGUI::utf8*)"View")));
}

void System::fakeobject_destroy(const char* windowname, const char* name) {
  //取得UI窗口
  CEGUI::Window* meshwindow = 
    CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)windowname);
  if (!meshwindow || 
      !(meshwindow->testClassName((CEGUI::utf8*)"FalagardMeshWindow"))) return;
  //通知UI
  (dynamic_cast<CEGUI::StaticImage*>(meshwindow))->setImage(0);
  //销毁UI的Imageset
  STRING imagename = name;
  imagename += vengine_game::object::kFakeRenderTexture;
  CEGUI::ImagesetManager::getSingleton().destroyImageset(
      (CEGUI::utf8*)imagename.c_str());
}

void System::debug_save_fonttexture() {
  ::CreateDirectory("debugsave", NULL);

  CEGUI::FontManager* fontmanager = CEGUI::FontManager::getSingletonPtr();
  CEGUI::FontManager::FontIterator iterator = fontmanager->getIterator();
  for (iterator.toStart(); !iterator.isAtEnd(); ++iterator) {
    const CEGUI::String& name = iterator.getCurrentKey();
    CEGUI::FontBase* font = iterator.getCurrentValue();
    char fontout[MAX_PATH] = {0};
    strncpy(fontout, "debugsave", sizeof(fontout) - 1);
    ::PathAppend(fontout, name.c_str());
    ::CreateDirectory(fontout, NULL); //创建保存目录
    std::vector<CEGUI::Imageset*> imagesets;
    int32_t shouldlength = font->debug_GetFontImageset(imagesets);
    uint32_t i;
    for (i = 0; i < static_cast<uint32_t>(imagesets.size()); ++i) {
      const CEGUI::OgreCEGUITexture* texture = 
        (const CEGUI::OgreCEGUITexture*)imagesets[i]->getTexture();
      const Ogre::TexturePtr ogretexture = texture->getOgreTexture();
      const Ogre::HardwarePixelBufferSharedPtr pixelbuffer =
        ogretexture->getBuffer(0, 0);
      Ogre::Image imageout;
      imageout.load("_TEMP_.tga", "General");
      imageout.resize(static_cast<Ogre::ushort>(pixelbuffer->getWidth()), 
                      static_cast<Ogre::ushort>(pixelbuffer->getHeight()));
      pixelbuffer->blitToMemory(imageout.getPixelBox());
      char filename[MAX_PATH] = {0};
      strncpy(filename, fontout, sizeof(filename) - 1);
      ::PathAppend(filename, imagesets[i]->getName().c_str());
      strcat(filename, ".tga");
      imageout.save(filename);
    }
  }
}

void System::change_dragflag(bool flag) {
  is_dragend_ = flag;
}

bool System::is_dragend() {
  return is_dragend_;
}

STRING System::parsestring_varparam(const char* id, ...) {
  STRING str = "";
  if (stringsystem_) {
    va_list vapointer;
    va_start(vapointer, id);
    str = stringsystem_->parsestring_varparam(id, vapointer);
    va_end(vapointer);
  }
  return str;
}

void System::parsestring_nocolor(const STRING& in, STRING& out, bool control) { 
  if (stringsystem_) stringsystem_->parsestring_nocolor(in, out, control);
}

STRING System::parsestring_nocolor_varparam(const char* id, ...) { 
  STRING str = "";
  if (stringsystem_) {
    va_list vapointer;
    va_start(vapointer, id);
    STRING str_hascolor = stringsystem_->parsestring_varparam(id, vapointer);
    va_end(vapointer);
    stringsystem_->parsestring_nocolor(str_hascolor, str);
  }
  return str;
}

STRING System::parsestring_no_varparam(const char* id) {
  STRING str;
  if (stringsystem_) str = stringsystem_->parsestring_no_varparam(id);
  return str;
}

STRING System::parsestring_nocolor_no_varparam(const char* id) {
  STRING str;
  if (stringsystem_) {
    STRING str_hascolor = stringsystem_->parsestring_no_varparam(id);
    stringsystem_->parsestring_nocolor(str_hascolor, str);
  }
  return str;
}

bool System::close_allwindow() {
  vgui_window::Manager::getself()->closeall();
  return true;
}

bool System::handle_hyperlink_active(const CEGUI::EventArgs& event) {
  return true;
}

bool System::handle_hyperlink_leftactive(const CEGUI::EventArgs& event) { 
  const CEGUI::HyperLinkEventArgs& hyperlink = 
    (const CEGUI::HyperLinkEventArgs&)event;
  STRING windowname, link;
  vgui_string::System::utf8_to_mbcs(hyperlink.windowName.c_str(), windowname);
  vgui_string::System::utf8_to_mbcs(hyperlink.hyperLinkName.c_str(), link);
  if (CEGUI::WindowManager::getSingleton().isWindowPresent(
        hyperlink.windowName)) {
    CEGUI::Window* window = 
      CEGUI::WindowManager::getSingleton().getWindow(hyperlink.windowName);
    if (window->testClassName((CEGUI::utf8*)"FalagardChatBoard")) {
      g_game_eventsystem->push(
          vengine_game::event_id::kChatChangePrivateName, link.c_str());        
    }
    else { //如果不是就说明是特殊链接
      if (!link.empty()) {
        int32_t x, y;
        uint16_t sceneid;
        char name[128] = {0};
        char npcname[128] = {0};
        sscanf(link.c_str(),
               "%d,%d,%d,%[^,],%[^,]", 
               &x, 
               &y, 
               &sceneid, 
               name, 
               npcname);
        if (g_game_worldsystem && 
            g_game_worldsystem->get_activescene() && 
            g_game_worldsystem->get_activescene()->getdefine()) {
          uint16_t current_sceneid = 
            g_game_worldsystem->get_activescene()->getdefine()->localid;
          //判断是否是可以对话的功能任务NPC，如果是则设置自动寻路的标记值
          if (strlen(npcname) > 0) {
            g_gameinterface->set_auto_findpath_tonpc(sceneid, npcname);
          }
          else {
            g_gameinterface->set_auto_findpath_tonpc(-1, "");
          }
          g_gameinterface->player_moveto(
              sceneid,
              vengine_math::base::twofloat_vector_t(static_cast<float>(x), 
                                                    static_cast<float>(y))); //移动过去
        }
      }
    }
  }
  return true;
}

bool System::handle_hyperlink_rightactive(const CEGUI::EventArgs& event) {
  const CEGUI::HyperLinkEventArgs& hyperlink = 
    (const CEGUI::HyperLinkEventArgs&)event;
  STRING windowname, link;
  vgui_string::System::utf8_to_mbcs(hyperlink.windowName.c_str(), windowname);
  vgui_string::System::utf8_to_mbcs(hyperlink.hyperLinkName.c_str(), link);
  if (CEGUI::WindowManager::getSingleton().isWindowPresent(
        hyperlink.windowName)) {
    CEGUI::Window* window = 
      CEGUI::WindowManager::getSingleton().getWindow(hyperlink.windowName);
    if (window->testClassName((CEGUI::utf8*)"FalagardChatBoard")) {
      g_game_eventsystem->push(
          vengine_game::event_id::kChatContexMenu, link.c_str());        
    }
  }
  return true;
}

bool System::handle_hyperlink_inactive(const CEGUI::EventArgs& event) {
  STRING str = "HelpWindow";
  const CEGUI::HyperLinkEventArgs& hyperlink =
    (const CEGUI::HyperLinkEventArgs&)event;
  STRING str1, str2;
  vgui_string::System::utf8_to_mbcs(hyperlink.hyperLinkName.c_str(), str2);
  vgui_string::System::utf8_to_mbcs(hyperlink.windowName.c_str(), str1);
  if ("HelpWindow" == hyperlink.windowName) {
    return true;
  }
  else {
    return false;
  }
}

bool System::handle_elementdelete(const CEGUI::EventArgs& event) {
  const CEGUI::ItemElementEventArgs& item = 
    (const CEGUI::ItemElementEventArgs&)event;
  CEGUI::Window* window = item.window;
  int32_t itemid = item.itemID;
  g_game_itemtransfer_system->removeelement(itemid);
  return false;
}

bool System::handle_chathistory_infoelement_click(
    const CEGUI::EventArgs& event) {
  const CEGUI::ItemElementEventArgs& item = 
    (const CEGUI::ItemElementEventArgs&)event;
  CEGUI::Window* window = item.window;
  int32_t messageid = item.msgID;
  int32_t itemid = item.itemID;
  if (CEGUI::RightButton == item.button) {
    g_game_itemtransfer_system->doelement(itemid, 
                                          vengine_game::kElementActionRClick, 
                                          messageid);
  }
  else if (CEGUI::LeftButton == item.button) {
    if (is_ctrlinfo_enable() && !(::GetKeyState(VK_LCONTROL)&0xFF00))
      return false;
    g_game_itemtransfer_system->doelement(itemid,
                                          vengine_game::kElementActionLClick);
  }
  return false; //always flase why ? viticm
}

bool System::handle_chathistory_infoelement_movein(
    const CEGUI::EventArgs& event) {
  const CEGUI::ItemElementEventArgs& item = 
    (const CEGUI::ItemElementEventArgs&)event;
  CEGUI::Window* window = item.window;
  int32_t itemid = item.itemID;
  g_game_itemtransfer_system->doelement(itemid,
                                        vengine_game::kElementActionMoveIn);
  return false;
}

bool System::handle_chathistory_infoelement_moveout(
    const CEGUI::EventArgs& event) {
  const CEGUI::ItemElementEventArgs& item = 
    (const CEGUI::ItemElementEventArgs&)event;
  CEGUI::Window* window = item.window;
  int32_t itemid = item.itemID;
  g_game_itemtransfer_system->doelement(itemid,
                                        vengine_game::kElementActionMoveOut);
  return false;
}

bool System::handle_pushbutton_clicksound(const CEGUI::EventArgs& event) {
  const CEGUI::WindowEventArgs& eventwindow = 
    (const CEGUI::WindowEventArgs&)event;
  CEGUI::Window* window = eventwindow.window;
  if (window) {
    int32_t soundid = CEGUI::PropertyHelper::stringToInt(
        window->getProperty((CEGUI::utf8*)"ClickSound"));
    g_soundsystem->play_UIsound(soundid);
  }
  return false;
}

bool System::is_IME_editbox_active(const char* windowname) {
  if(Ime::GetActiveIMEEditBox()) {
    CEGUI::Window* window = Ime::GetActiveIMEEditBox();
    if( 0 == strcmp(window->getName().c_str(), windowname)) return true;
  }
  return false;
}

int32_t System::get_current_IMEstate() {
  return Ime::GetState();
}

//将一个物品信息传入
bool System::inject_iteminfo(
    vengine_game::ItemTransferSystem::element_t* element) {
  bool result = false;;
  //是否有激活的IME窗口
  CEGUI::Window* window = Ime::GetActiveIMEEditBox();
  if (!window) return result;
  //必须是单行编辑器
  if (window->testClassName("FalagardIMEEditBox")) {
    CEGUI::String32 str;
    vgui_string::System::getself()->parsestring_runtime(element->display, str);
    result = (dynamic_cast<CEGUI::IFalagardIMEEditBox*>(
          dynamic_cast<CEGUI::FalagardIMEEditBox*>(window)))->injectItemInfo(
            element->id,
            str,
            static_cast<int32_t>(element->contents.length()));
  }
  else if (window->testClassName("FalagardMultiIMEEditBox")) {
    CEGUI::String32 str;
    vgui_string::System::getself()->parsestring_runtime(element->display, str);
    result = (dynamic_cast<CEGUI::FalagardMultiIMEEditBox*>(window))
      ->injectItemInfo(element->id,
                       str,
                       static_cast<int32_t>(element->contents.length()));
  }
  return result;
}

STRING System::get_talktemplate(const STRING& key, uint16_t index) {
  STRING result = "";
  if (stringsystem_) {
    result = stringsystem_->get_talktemplate(key, index);
  }
  return result;
}

STRING System::modify_chattemplate(const STRING& source, 
                                   const STRING& talker, 
                                   const STRING& target) {
  STRING result = "";
  if (stringsystem_) {
    result = stringsystem_->modify_chattemplate(source, talker, target);
  }
  return result;
}

STRING System::get_talkrand_helpmessage() {
  STRING result = "";
  if (stringsystem_) {
    result = stringsystem_->get_talkrand_helpmessage();
  }
  return result;
}

void System::on_pushescape() {
  vgui_window::Manager::getself()->onescape();
}

bool System::check_stringfilter(
    const STRING& in, 
    const vengine_ui::filtertype_enum type) {
  bool result = false;
  if (stringsystem_) result = stringsystem_->check_stringfilter(in, type);
  return result;
}

bool System::check_stringcode(const STRING& in, STRING& out) {
  bool result = false;
  if (stringsystem_) result = stringsystem_->check_stringcode(in, out);
  return result;
}

bool System::check_string_fullcompare(const STRING& in, 
                                      const STRING& out,
                                      bool use_alltable) { 
  bool result = false;
  if (stringsystem_) result = stringsystem_->check_string_fullcompare(in, out);
  return result;
}

int32_t System::ogrecolor_lumination(uint32_t ogrecolor) {
  int32_t result;
  CEGUI::colour cegui_color;
  float color_a, color_r, color_g, color_b;
  color_a = static_cast<float>(COLOR_A(ogrecolor)) / 255.0f;
  color_r = static_cast<float>(COLOR_R(ogrecolor)) / 255.0f;
  color_g = static_cast<float>(COLOR_G(ogrecolor)) / 255.0f;
  color_b = static_cast<float>(COLOR_B(ogrecolor)) / 255.0f;
  cegui_color.setAlpha(color_a);
  cegui_color.setRed(color_r);
  cegui_color.setGreen(color_g);
  cegui_color.setBlue(color_b);
  result = static_cast<int32_t>(cegui_color.getLumination() * 240);
  return result;
}

uint32_t System::lumination_ogrecolor(uint32_t ogrecolor, int32_t lumination) {
  uint32_t result;
  CEGUI::colour cegui_color;
  float color_a, color_r, color_g, color_b, _lumination;
  color_a = static_cast<float>(COLOR_A(ogrecolor)) / 255.0f;
  color_r = static_cast<float>(COLOR_R(ogrecolor)) / 255.0f;
  color_g = static_cast<float>(COLOR_G(ogrecolor)) / 255.0f;
  color_b = static_cast<float>(COLOR_B(ogrecolor)) / 255.0f;
  _lumination = lumination / 240.0f;
  cegui_color.setAlpha(color_a);
  cegui_color.setRed(color_r);
  cegui_color.setGreen(color_g);
  cegui_color.setBlue(color_b);
  if (cegui_color.getLumination() != lumination) {
    cegui_color.setHSL(cegui_color.getHue(), 
                       cegui_color.getSaturation(), 
                       _lumination);
  }
  int32_t _color_a, _color_r, _color_g, _color_b;
  _color_a = static_cast<int32_t>(cegui_color.getAlpha() * 0xFF);
  _color_r = static_cast<int32_t>(cegui_color.getRed() * 0xFF);
  _color_g = static_cast<int32_t>(cegui_color.getGreen() * 0xFF);
  _color_b = static_cast<int32_t>(cegui_color.getBlue() * 0xFF);
  result = MAKE_COLOR(_color_r, _color_g, _color_b, _color_a);
  return result;
}

STRING System::get_debugstring() {
  if (cegui_system_) {
    CEGUI::Window* window = cegui_system_->getWindowContainingMouse();
    if (window) {
      STRING description = "UI: ";
      description += window->getName().c_str();
      description += "\ntype: ";
      description += window->getType().c_str();
      description += "\nparent: ";
      if (window->getParent()) {
        description += window->getParent()->getName().c_str();
      }
      else {
        description += "none";
      }
      return description;
    }
  }
  return STRING("");
}

void System::openwindow(const STRING& name) {
  vgui_window::Manager::getself()->open(name);
}

void System::closewindow(const STRING& name) {
  vgui_window::Manager::getself()->close(name);
}

void System::togglewindow(const STRING& name) {
  vgui_window::Manager::getself()->toggle(name);
}

bool System::has_inputfocus() {
  bool result = false;
  result = Ime::HasInputFocus();
  return result;
}

STRING System::get_IME_editbox_string(const char* windowname) {
  STRING result = "";
  if (Ime::GetActiveIMEEditBox()) {
    CEGUI::Window* window = Ime::GetActiveIMEEditBox();
    if (0 == strcmp(window->getName().c_str(), windowname)) {
      CEGUI::IFalagardIMEEditBox* findwindow = 
        dynamic_cast<CEGUI::IFalagardIMEEditBox*>(
            dynamic_cast<CEGUI::FalagardIMEEditBox*>(window));
      CEGUI::String32 text = findwindow->getItemElementString();
      vgui_string::System::getself()->parsestring_reverseruntime(text, result);
    }
  }
  return result;
}

bool System::add_chathistory_message(int32_t id,
                                     const char* windowname, 
                                     const char* message, 
                                     int32_t type, 
                                     uint32_t disappeartime) {
  bool result = false;
  if (!windowname || !message || !stringsystem_) return result;
  CEGUI::Window* window = 
    CEGUI::WindowManager::getSingleton().getWindow(windowname);
  if (window->testClassName((CEGUI::utf8*)"FalagardChatHistory")) {
    STRING mbcs = message;
    CEGUI::String32 str;
    stringsystem_->parsestring_runtime(mbcs, str);
    CEGUI::Window* child = (dynamic_cast<CEGUI::IFalagardChatHistory*>(
          dynamic_cast<CEGUI::FalagardChatHistory*>(window)))
      ->insertChatString(id, str, type);
    if (child && disappeartime > 0) {
      char killtimer[16] = {0};
      snprintf(killtimer, 
               sizeof(killtimer) - 1, 
               " %f", 
               static_cast<float>(disappeartime));
      child->setProperty("KillTimer", killtimer);
    }
    result = true;
  }
  return result;
}

void System::replacestring_usefilter(
    const STRING& in, 
    STRING& out, 
    vengine_ui::filtertype_enum filtertype) {
  if (stringsystem_) 
    stringsystem_->replacestring_usefilter(in, out, filtertype);
}

STRING System::check_stringvalid(const char* str) {
  STRING result = "";
  if (stringsystem_) result = stringsystem_->check_stringvalid(str);
  return result;
}

bool System::reload_windowscript(const STRING& windowname) {
  bool result = false;
  if (windowmanager_) result = windowmanager_->reloadscript(windowname.c_str());
  return result;
}

void System::uirender_toggleshow() {
  if (cegui_render_)
    cegui_render_->setRenderDisable(!(cegui_render_->isRenderDisable()));
}

bool System::is_ctrlinfo_enable() {
  return is_ctrlinfo_enable_;
}

void System::set_ctrlinfo_enable(bool enable) {
  is_ctrlinfo_enable_ = enable;
}

bool System::is_paopao_active() {
  return active_paopao_;
}

void System::debug_push_chatstring(const char* name, 
                           const char* message) {
  USE_PARAM(name);
  USE_PARAM(message);
}

} //namespace vgui_base
