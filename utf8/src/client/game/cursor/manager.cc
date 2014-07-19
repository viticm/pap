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
  state_ = vengine_cursor::kTypeNormal;
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

void Manager::set(vengine_cursor::type_enum type) {
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
  //USE_PARAM(cmd);
  //... 以后再做
}

void Manager::init(void* handle) {
  HINSTANCE instance_handle = *(reinterpret_cast<HINSTANCE*>(handle));
  cursorhandles_[vengine_cursor::kTypeWinBase] = //系统标准的
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_ARROW));
  cursorhandles_[vengine_cursor::kTypeNormal] = //普通状态
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_NORMAL));
  cursorhandles_[vengine_cursor::kTypeAttack] = //攻击
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_ATTACK));
  cursorhandles_[vengine_cursor::kTypeAutoRun] = //自动寻路中
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_AUTORUN));
  cursorhandles_[vengine_cursor::kTypePickup] = //拾取物品
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_PICKUP));
  cursorhandles_[vengine_cursor::kTypeUnreachable] = //无法到达的区域
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_UNREACHABLE));
  cursorhandles_[vengine_cursor::kTypeMine] = //采矿
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_MINE));
  cursorhandles_[vengine_cursor::kTypeHerbs] = //采药
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_HERBS));
  cursorhandles_[vengine_cursor::kTypeSpeak] = //对话
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_SPEAK));
  cursorhandles_[vengine_cursor::kTypeInteract] = //齿轮
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_INTERACT));
  cursorhandles_[vengine_cursor::kTypeRepiar] = //修理
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_REPAIR));
  cursorhandles_[vengine_cursor::kTypeHover] = //鼠标挂接物品
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_HOVER));
  cursorhandles_[vengine_cursor::kTypeIdentify] = //鉴定
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_IDENFITY));
  cursorhandles_[vengine_cursor::kTypeRing] = //技能环
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_RING));
  cursorhandles_[vengine_cursor::kTypeDirection] = //方向技能
    ::LoadCursor(instance_handle, MAKEINTRESOURCE(IDC_CURSOR_DIRECTION));
}

void Manager::mousecommand_set(
       bool hover_inui, 
       const vengine_math::base::threefloat_vector_t position, 
       vengine_game::action::Item* activeskill) {
  USE_PARAM(hover_inui);
  //USE_PARAM(position);
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
