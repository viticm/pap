#include "client/game/global.h"

vengine_capability::Debuger* g_debuger = NULL;
vengine_variable::System* g_variablesystem = NULL;
vengine_sound::System* g_soundsystem = NULL;
vengine_game::WorldSystem* g_worldsystem = NULL;
vengine_game::EventSystem* g_eventsystem = NULL;
vengine_resource::Provider* g_resourceprovider = NULL;
vengine_db::System* g_dbsystem = NULL;
vengine_kernel::Base* g_kernel = NULL;
HWND g_mainwindow_handle = NULL;
HINSTANCE g_instance_handle = NULL;
const char kVersionInfo[] = "0.0.1";
const char kGameTitle[] = "前世-今生";
bool g_debugmode = false;
