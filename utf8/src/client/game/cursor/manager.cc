#include "vengine/game/action/system.h"
#include "vengine/time/system.h"
#include "vengine/base/util.h"
#include "client/game/global.h"
#include "client/game/event/system.h"
#include "client/game/cursor/manager.h"

namespace cursor {

VENGINE_KERNEL_IMPLEMENT_DYNAMIC(
    Manager, 
    VENGINE_KERNEL_GETCLASS(vengine_cursor::System));

Manager* Manager::self_ = NULL;

Manager::Manager() {
  self_ = this;
  show_ = true;
  state_ = kTypeNormal;
  uicursor_handle_ = NULL;
  current_mousecommand_left_.cleanup();
  current_mousecommand_right_.cleanup();
  current_mousecommand_left_.mousetype = mousecommand_t::kTypeNull;
  current_mousecommand_right_.mousetype = mousecommand_t::kTypeNull;
}

Manager::~Manager() {
  //do nothing
}

Manager* Manager::getself() {
  return self_;
}

void Manager::set(type_enum type) {
  state_ = type;
  ::PostMessage(g_mainwindow_handle, WM_SETCURSOR, 0, HTCLIENT);
}

int32_t Manager::getstate() {
  return state_;
}

HCURSOR Manager::get() {
  if (!show_) return NULL;
  return cursorhandles_[state_];
}

void Manager::onset() {
  if (show_) {
    if (uicursor_handle_) {
      ::SetCursor(uicursor_handle_);
    }
    else {
      ::SetCursor(get());
    }
  }
}

void Manager::show(bool flag) {
  if (show_ == flag) return;
  show_ = flag;
  ::ShowCursor(flag);
}

void Manager::mousecommand_active(mousecommand_t& cmd) {
  USE_PARAM(cmd);
  //... 以后再做
}

void Manager::init(void* handle) {
  HINSTANCE instance_handle = *(reinterpret_cast<HINSTANCE*>(handle));
  cursorhandles_[kTypeWinBase] = //系统标准的
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_ARROW));
  cursorhandles_[kTypeNormal] = //普通状态
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_NORMAL));
  cursorhandles_[kTypeAttack] = //攻击
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_ATTACK));
  cursorhandles_[kTypeAutoRun] = //自动寻路中
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_AUTORUN));
  cursorhandles_[kTypePickup] = //拾取物品
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_PICKUP));
  cursorhandles_[kTypeUnreachable] = //无法到达的区域
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_UNREACHABLE));
  cursorhandles_[kTypeMine] = //采矿
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_MINE));
  cursorhandles_[kTypeHerbs] = //采药
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_HERBS));
  cursorhandles_[kTypeSpeak] = //对话
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_SPEAK));
  cursorhandles_[kTypeInteract] = //齿轮
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_INTERACT));
  cursorhandles_[kTypeRepiar] = //修理
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_REPAIR));
  cursorhandles_[kTypeHover] = //鼠标挂接物品
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_HOVER));
  cursorhandles_[kTypeIdentify] = //鉴定
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_IDENFITY));
  cursorhandles_[kTypeRing] = //技能环
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_RING));
  cursorhandles_[kTypeDirection] = //方向技能
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_DIRECTION));
}

void Manager::mousecommand_set(
       bool hover_inui, 
       const vengine_math::base::threefloat_vector position, 
       vengine_game::action::Item* activeskill) {
  USE_PARAM(hover_inui);
  USE_PARAM(position);
  USE_PARAM(activeskill);
}

mousecommand_t& Manager::mousecommand_getleft() {
  return current_mousecommand_left_;
}

mousecommand_t& Manager::mousecommand_getright() {
  return current_mousecommand_right_;
}

void Manager::mousecommand_clear() {
  current_mousecommand_left_.mousetype = mousecommand_t::kTypeNull;
}

void Manager::enterui(HCURSOR handle) {
  uicursor_handle_ = handle;
}

void Manager::leaveui() {
  uicursor_handle_ = NULL;
}

} //namespace cursor
