/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-11 10:12:52
 * @uses vgui base config and global set
 */
#ifndef VGUI_CONFIG_H_
#define VGUI_CONFIG_H_

#include <stdint.h> 

/*macros {*/

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if (p) { delete (p); (p) = NULL; }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) if (p) { (p)->Release(); delete (p); (p) = NULL; }
#endif
/* }macros*/

/*class {*/ //from vengine

namespace vengine_kernel {
class Base;
}; //namespace vengine_kernel

namespace vengine_script {
class System;
}; //namespace vengine_script

namespace vengine_game {
class EventSystem;
class WorldSystem;
class Interface;
class ItemTransferSystem;

namespace action {
class System;
}; //namespace action

namespace object {
class BaseSystem;
class FakeSystem;
}; //namespace object

}; //namespace vengine_game

namespace vengine_input {
class System;
}; //namespace vengine_input

namespace vengine_render {
class System;
}; //namespace vengine_render

namespace vengine_cursor {
class System;
}; //namespace vengine_cursor

namespace vengine_capability {
class Debuger;
}; //namespace vengine_capability

namespace vengine_time {
class System;
}; //namespace vengine_time

namespace vengine_variable {
class System;
}; //namespace vengine_variable

namespace vengine_db {
class System;
}; //namespace vengine_db

namespace vengine_sound {
class System;
}; //namespace vengine_sound

/* }class*/

/*global variable {*/
extern HINSTANCE g_hInstance;
extern HWND g_mainwindow_handle;
extern vengine_kernel::Base* g_kernel;
extern vengine_script::Sytem* g_scriptsystem;
extern vengine_game::EventSystem* g_game_eventsystem;
extern vengine_input::System* g_inputsystem;
extern vengine_render::System* g_rendersystem;
extern vengine_game::object::BaseSystem* g_game_objectsystem;
extern vengine_game::WorldSystem* g_game_worldsystem;
extern vengine_cursor::System* g_cursorsystem;
extern vengine_capability::Debuger* g_capability_debuger;
extern vengine_time::System* g_timesystem;
extern vengine_game::object::FakeSystem* g_game_fake_objectsystem;
extern vengine_variable::System* g_variablesystem;
extern vengine_game::Interface* g_gameinterface;
extern vengine_db::System* g_databasesystem;
extern vengine_game::ItemTransferSystem* g_game_itemtransfer_system;
extern vengine_sound::System* g_soundsystem;
/*} global variable*/

#endif //VGUI_CONFIG_H_
