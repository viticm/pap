/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id global.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-8 16:35:03
 * @uses client game global sets
 */
#ifndef CLIENT_GAME_GLOBAL_H_
#define CLIENT_GAME_GLOBAL_H_

#include "vengine/classes.h"
#include "vengine/kernel/base.h"

extern vengine_capability::Debuger* g_debuger;
extern vengine_variable::System* g_variablesystem;
extern vengine_sound::System* g_soundsystem;
extern vengine_game::WorldSystem* g_worldsystem;
extern vengine_game::EventSystem* g_eventsystem;
extern vengine_resource::Provider* g_resourceprovider;
extern vengine_db::System* g_dbsystem;
extern vengine_kernel::Base* g_kernel;
extern HWND g_mainwindow_handle;
extern HINSTANCE g_hinstance;
extern const char versioninfo[];
extern const char gametitle[];
extern bool g_debugmode; //是否为调试模式

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if (p) { delete (p); (p) = NULL; }
#endif

#endif //CLIENT_GAME_GLOBAL_H_
