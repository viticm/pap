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
#include "vengine/db/struct/all.h"
#include "vengine/script/system.h"
#include "vengine/capability/profile.h"
#include "vengine/game/object/basesystem.h"
#include "vengine/game/eventdefine.h"
#include "vengine/variable/base.h"
#include "vengine/sound/system.h"

#include "vgui/script/base.h"
#include "vgui/luacontrol/window/base.h"
#include "vgui/string/system.h"
#include "vgui/base/system.h"

#include "vgui/window/manager.h"
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
      vgui_luacontrol::window::Base::destroy(controls_[i]);
      controls_[i] = NULL;
    }
  }
  controls_.clear();
  CEGUI::WindowManager::getSingleton().destroyWindow(window_);
  window_ = NULL;
}

uint8_t Item::get_demisetype() {
  return is_candemise_;
}

bool Item::is_candemise() {
  return is_candemise_ > 0;
}

bool Item::callbackproperty(CEGUI::Window* window, 
                            CEGUI::String& propname, 
                            CEGUI::String& propvalue, 
                            void* userdata) {
  if ("Text" == propname && !propvalue.empty()) {
    CEGUI::String32 str; //字符串转化
    STRING mbcs;
    vgui_string::System::utf8_to_mbcs(STRING(propvalue.c_str()), mbcs);
    vgui_string::System::getself()->parsestring_runtime(mbcs, str);
    propvalue = str.c_str();
  }
  return true;
}

void Item::pre_loadwindow() {
  //创建脚本运行环境
  scriptenvironment_ = g_scriptsystem->newenvironment(windowname_.c_str(),
                                                      script_filename_.c_str());
  //加载执行
  scriptenvironment_->executescript(script_filename_.c_str());
  //注册引用函数
  //注册"this"对象
  LuaPlus::LuaObject metatable_ui_windowitem = g_scriptsystem->
                                               get_luastate()->
                                               GetGlobals().
                                               GetByName("MetaTable_UIWindowItem");
  LuaPlus::LuaObject objectthis = g_scriptsystem->get_luastate()->BoxPointer(this);
  objectthis.SetMetaTable(metatable_ui_windowitem);
  scriptenvironment_->get_luaobject()->SetObject("this", objectthis);
  //执行其中的***_PreLoad函数
  char temp[MAX_PATH] = {0};
  snprintf(temp, sizeof(temp) - 1, "%s_PreLoad", windowname_.c_str());
  scriptenvironment_->executefunction(temp);
  layoutloaded_ = false;
}

void Item::loadwindow() {
  VENGINE_ASSERT(window_ == NULL);
  if (layoutloaded_) return;
  //加载布局文件
  window_ = CEGUI::WindowManager::getSingleton().loadWindowLayout(
      layout_filename_,
      "",
      "",
      callbackproperty);
  //初始状态：隐藏
  window_->hide();
  Manager::get_clientscreen()->addChildWindow(window_);
  //注册控件
  register_control_toscript(window_);
  //执行其中的***_OnLoad函数
  char temp[MAX_PATH];
  snprintf(temp, sizeof(temp) - 1, "%s_OnLoad", windowname_.c_str());
  scriptenvironment_->executefunction(temp);
  layoutloaded_ = true;
}

void Item::register_control_toscript(CEGUI::Window* window) {
  //设置UserData,用于回朔调用
  window->setUserData(this);
  vgui_luacontrol::window::Base* tempcontrol = vgui_luacontrol::window::Base::create(window);
  LuaPlus::LuaObject objectthis = g_scriptsystem->get_luastate()->BoxPointer(tempcontrol);
  objectthis.SetMetaTable(*(tempcontrol->get_metatable()));
  CEGUI::String temp = window->getName();
  scriptenvironment_->get_luaobject()->SetObject(temp.c_str(), objectthis);
  controls_.push_back(tempcontrol);
  //对ActionButton特殊处理
  if (window->testClassName((CEGUI::utf8*)"FalagardActionButton")) {
    CEGUI::IFalagardActionButton* actionbutton = 
      dynamic_cast<CEGUI::IFalagardActionButton*>(
          dynamic_cast<CEGUI::FalagardActionButton*>(window));

    //DrawStarted
    actionbutton->subscribeDragDropStartedEvent(CEGUI::Event::Subscriber(
      &vgui_base::System::handle_action_dragdrop_started, 
          vgui_base::System::getself()));
    //MouseEnter
    actionbutton->subscribeMouseEnterEvent(CEGUI::Event::Subscriber(
          &vgui_base::System::handle_actionbutton_mouseenter, 
          vgui_base::System::getself()));
    //MouseLeave
    actionbutton->subscribeMouseLeaveEvent(CEGUI::Event::Subscriber(
          &vgui_base::System::handle_actionbutton_mouseleave, 
          vgui_base::System::getself()));
    //ParentHidden
    window->subscribeEvent(
        (CEGUI::utf8*)"ParentHidden", 
        CEGUI::Event::Subscriber(
          &vgui_base::System::handle_actionbutton_parenthidden, 
          vgui_base::System::getself()));
  } 
  else if(window->testClassName((CEGUI::utf8*)"FalagardMeshWindow")) {
    CEGUI::IFalagardMeshWindow* meshwindow = 
      dynamic_cast<CEGUI::IFalagardMeshWindow*>(
          dynamic_cast<CEGUI::FalagardMeshWindow*>(window));

    meshwindow->subscribeShownEvent(CEGUI::Event::Subscriber(
          &vgui_base::System::handle_meshwindow_shown, 
          vgui_base::System::getself()));
    meshwindow->subscribeHidenEvent(CEGUI::Event::Subscriber(
          &vgui_base::System::handle_meshwindow_hiden, 
          vgui_base::System::getself()));
  }
  else if (window->testClassName((CEGUI::utf8*)"FalagardComplexWindow")) {
    CEGUI::IFalagardComplexWindow* complexwindow = 
      dynamic_cast<CEGUI::IFalagardComplexWindow*>(
          dynamic_cast<CEGUI::FalagardComplexWindow*>(window));
    complexwindow->subscribInfoItemClickEvent(CEGUI::Event::Subscriber(
          &vgui_base::System::handle_chathistory_infoelement_click, 
          vgui_base::System::getself()));
    complexwindow->subscribInfoItemDeleteEvent(CEGUI::Event::Subscriber(
          &vgui_base::System::handle_elementdelete, 
          vgui_base::System::getself()));
  }
  else if(window->testClassName((CEGUI::utf8*)"FalagardChatHistory")) {
    CEGUI::IFalagardChatHistory* chathistory_window = 
      dynamic_cast<CEGUI::IFalagardChatHistory*>(
          dynamic_cast<CEGUI::FalagardChatHistory*>(window));
    chathistory_window->subscribInfoItemClickEvent(CEGUI::Event::Subscriber(
          &vgui_base::System::handle_chathistory_infoelement_click, 
          vgui_base::System::getself()));
    chathistory_window->subscribInfoItemDeleteEvent(CEGUI::Event::Subscriber(
          &vgui_base::System::handle_elementdelete, 
          vgui_base::System::getself()));
    chathistory_window->subscribInfoItemMoveInEvent(CEGUI::Event::Subscriber(
          &vgui_base::System::handle_chathistory_infoelement_movein, 
          vgui_base::System::getself()));
    chathistory_window->subscribInfoItemMoveOutEvent(CEGUI::Event::Subscriber(
          &vgui_base::System::handle_chathistory_infoelement_moveout, 
          vgui_base::System::getself()));
  }

  //register child
  for (uint32_t i = 0; 
       i < static_cast<uint32_t>(window->getChildCount()); 
       ++i) {
    register_control_toscript(window->getChildAtIdx(i));
  }
  return;
}

void Item::transtext(CEGUI::Window* window) {
  CEGUI::String32 str = window->getTextOriginal();
  if (!str.empty()) {
    STRING mbcs_totrans;
    vgui_string::System::utf8_to_mbcs(str.c_str(), mbcs_totrans);
    //经过special转化的string，已经是utf32格式
    CEGUI::String32 mbcs_transddone;
    vgui_string::System::getself()->parsestring_runtime(mbcs_totrans, 
                                                        mbcs_transddone);

    window->setText(mbcs_transddone);
  }
  //register child
  for (uint32_t i = 0; 
       i < static_cast<uint32_t>(window->getChildCount()); 
       ++i) {
    register_control_toscript(window->getChildAtIdx(i));
  }
}

bool Item::is_childwindow_show(const char* uiname) const {
  CEGUI::String name(uiname);
  try {
    CEGUI::Window* child = CEGUI::WindowManager::getSingleton().getWindow(name);
    if (child) return child->isVisible();
  }
  catch(...) {
    return false;
  }
  return false;
}

void Item::show(bool flag) {
  if (show_ == flag || !window_) return;
  if (flag) {
    g_soundsystem->play_UIsound(openwindow_soundid_);
    window_->show();
    //如果看不见,那么自动归位
    if (!window_->isCanVisible()) on_sizechange();
    window_->activate();
  }
  else {
    g_soundsystem->play_UIsound(closewindow_soundid_);
    window_->hide();
    on_windowhide();
  }
  //防止屏幕闪烁
  vgui_window::Manager::get_clientscreen()->requestRedraw();
  show_ = flag;
}

void Item::on_windowhide() {
  //do nothing
}

int32_t Item::lua_registerevent(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!(args[2].IsString())) return 0;
  if (layoutloaded_) {
    VENGINE_SHOW("%s must register event in \"***PreLoad\" function ",
                 windowname_.c_str());
  }
  STRING eventname = args[2].GetString();
  g_game_eventsystem->registerhandle(eventname, 
                                     on_gameevent, 
                                     (uint32_t)(uint32_t*)this);
  return 0;
}

int32_t Item::lua_show(LuaPlus::LuaState* luastate) {
  vgui_window::Manager::getself()->demise(this, true);
  show(true);
  return 0;
}

int32_t Item::lua_hide(LuaPlus::LuaState* luastate) {
  vgui_window::Manager::getself()->demise(this, false);
  show(false);
  return 0;
}

int32_t Item::lua_toggle(LuaPlus::LuaState* luastate) {
  if (show_) {
    window_->hide();
    show_ = false;
    luastate->PushInteger(0);
  }
  else {
    window_->show();
    show_ = true;
    luastate->PushInteger(1);
  }
  return 1;
}

int32_t Item::lua_isvisible(LuaPlus::LuaState* luastate) {
  luastate->PushBoolean(show_ == true);
  return 1;
}

int32_t Item::lua_trans_alltext(LuaPlus::LuaState* luastate) {
  transtext(window_);
  return 0;
}

int32_t Item::lua_careobject(LuaPlus::LuaState* luastate) {
  LuaPlus::LuaStack args(luastate);
  if (!(args[2].IsInteger())) {
    VENGINE_SHOW("lua: vgui_window::Item::lua_careobject:args[2] "
                 "is wrong param!");
  }
  
  if (!(args[3].IsInteger())) {
    VENGINE_SHOW("lua: vgui_window::Item::lua_careobject:args[3] "
                 "is wrong param!");
  }

  if (!(args[4].IsString())) {
    VENGINE_SHOW("lua: vgui_window::Item::lua_careobject:args[4] "
                 "is wrong param!");
  }
  int32_t objectid = args[2].GetInteger();
  bool care = 1 == args[2].GetInteger(); //是否关心
  STRING str = args[4].GetString(); //谁在关心
  g_game_objectsystem->care(objectid, care, str);
  return 0;
}

void WINAPI Item::on_gameevent(const vengine_game::event_t* event,
                               uint32_t ownerdata) {
  //分发
  Item* windowitem = (Item*)(uint32_t*)ownerdata;
  if (!windowitem) return;
  if (!windowitem->layoutloaded_) windowitem->loadwindow();
  uint32_t i;
  for (i = 0; i < static_cast<uint32_t>(event->args.size()); ++i) {
    char temp[MAX_PATH];
    snprintf(temp, sizeof(temp) - 1, "arg%d", i);
    g_scriptsystem->get_luastate()->GetGlobals().SetString(
        temp, 
        event->args[i].c_str());
  }
  //调用脚本
  char functionname[MAX_PATH];
  snprintf(functionname, 
           sizeof(functionname) - 1, 
           "%s_OnEvent", 
           windowitem->windowname_.c_str());
  char functionparam[MAX_PATH];
  snprintf(functionparam,
           sizeof(functionparam) - 1,
           "\"%s\"",
           event->eventdefine->event);
  windowitem->scriptenvironment_->executefunction(functionname, functionparam);
}

void Item::handle_uievent(const char* eventhandle, CEGUI::Window* window) {
  g_scriptsystem->get_luastate()->GetGlobals().SetString(
      "arg0", 
      window->getName().c_str());
  scriptenvironment_->executestring(eventhandle);
}

void Item::moveto(CEGUI::Point& position) {
  window_->setPosition(position);
}

void Item::positionself() {
  if (window_) {
    CEGUI::MouseCursor& cursor = CEGUI::MouseCursor::getSingleton();
    CEGUI::Rect screen(CEGUI::System::getSingleton().getRenderer()->getRect());
    CEGUI::Rect tipRect(window_->getUnclippedPixelRect());
    const CEGUI::Image* mouseImage = cursor.getImage();

    CEGUI::Point mousePos(cursor.getPosition());
    CEGUI::Size mouseSz(0,0);

    if (mouseImage) {
        mouseSz = mouseImage->getSize();
    }

    CEGUI::Point tmpPos(mousePos.d_x - tipRect.getWidth() - 5, 
                        mousePos.d_y - tipRect.getHeight() - 5);
    tipRect.setPosition(tmpPos);

    // if tooltip would be off the right of the screen,
    // reposition to the other side of the mouse cursor.
    if (tipRect.d_right < 0) {
        tmpPos.d_x = mousePos.d_x + mouseSz.d_width + 5;
    }

    // if tooltip would be off the bottom of the screen,
    // reposition to the other side of the mouse cursor.
    if (tipRect.d_bottom < 0) {
        tmpPos.d_y = mousePos.d_y + mouseSz.d_height + 5;
    }
    // set final position of tooltip window.
    window_->setPosition(CEGUI::Absolute, tmpPos);
  }
}

void Item::on_sizechange() {
  //如果看不到了,那么重置为默认位置
  if (window_ && !window_->isCanVisible() && !defaultposition_.empty()) {
    float x = 100.0f, y = 100.0f;
    sscanf(defaultposition_.c_str(), "%f %f", &x, &y);
    window_->setPosition(CEGUI::Absolute, CEGUI::Point(x, y));
  }
}

void Item::reloadscript() {
  //清空已注册事件
  registered_eventname_list::iterator iterator = eventname_list_.begin();
  for (; iterator != eventname_list_.end(); ++iterator) {
    g_game_eventsystem->unregisterhandle(*iterator, 
                                         on_gameevent, 
                                         (DWORD)(DWORD_PTR)this);
  }
  layoutloaded_ = false;
  eventname_list_.clear();
  vengine_script::Environment* scriptenvironment = 
    g_scriptsystem->getenvironment(windowname_.c_str());
  if (scriptenvironment) {
    scriptenvironment_->executescript(script_filename_.c_str());
    //执行preload
    char temp[MAX_PATH] = {0};
    snprintf(temp, sizeof(temp) - 1, "%s_PreLoad", windowname_.c_str());
    scriptenvironment_->executefunction(temp);
  }
  //设置重新加载状态
  if (window_) {
    CEGUI::WindowManager::getSingleton().destroyWindow(window_);
    window_ = NULL;
  }
}

bool Item::is_windowshow() const {
  return show_;
}

const char* Item::get_windowname() const {
  return windowname_.c_str();
}

void Item::set_openclose_sound(uint16_t open, uint16_t close) {
  openwindow_soundid_ = open;
  closewindow_soundid_ = close;
};

}; //namespace vgui_window