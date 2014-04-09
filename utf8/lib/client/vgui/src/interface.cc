#include "vgui/stdafx.h"
#include "vengine/kernel/base.h"
#include "OgreRoot.h"
#include "vgui/interface.h"
#include "vgui/base/system.h"

//Magic Code
extern "C" uint32_t DllMagicCode = VENGINE_DLL_MAGIC_CODE | VENGINE_VERSION;

//插件初始化
extern "C" void __stdcall DllInit(vengine_kernel::Base* kernel) {
	VENGINE_ASSERT(kernel);
	g_kernel = kernel;
  kernel->registerclass(VENGINE_KERNEL_GETCLASS(vgui_base::System));
}

extern VOID instll_uisystem(vengine_kernel::Base* kernel) {
	VENGINE_ASSERT(kernel);
	g_kernel = kernel;
	kernel->registerclass(VENGINE_KERNEL_GETCLASS(vgui_base::System));
}

// 插件释放
extern "C" VOID __stdcall DllRelease(VOID) {
  //do nothing
}


//I put global variables init in here
HINSTANCE g_hInstance = NULL;
HWND g_mainwindow_handle = NULL;
vengine_kernel::Base* g_kernel = NULL;
vengine_script::System* g_scriptsystem = NULL;
vengine_game::EventSystem* g_game_eventsystem = NULL;
vengine_game::action::System* g_game_actionsystem = NULL;
vengine_input::System* g_inputsystem = NULL;
vengine_render::System* g_rendersystem = NULL;
vengine_game::object::BaseSystem* g_game_objectsystem = NULL;
vengine_game::WorldSystem* g_game_worldsystem = NULL;
vengine_cursor::System* g_cursorsystem = NULL;
vengine_capability::Debuger* g_capability_debuger = NULL;
vengine_time::System* g_timesystem = NULL;
vengine_game::object::FakeSystem* g_game_fake_objectsystem = NULL;
vengine_variable::System* g_variablesystem = NULL;
vengine_game::Interface* g_gameinterface = NULL;
vengine_db::System* g_databasesystem = NULL;
vengine_game::ItemTransferSystem* g_game_itemtransfer_system = NULL;
vengine_sound::System* g_soundsystem = NULL;
