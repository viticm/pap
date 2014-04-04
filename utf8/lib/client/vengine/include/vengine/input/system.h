/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 17:23:32
 * @uses vengine inpout system module
 */
#ifndef VENGINE_INPUT_SYSTEM_H_
#define VENGINE_INPUT_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

namespace vengine_input {

typedef enum { //for windows keycode
    kKeyCode_ESCAPE          =0x01,
    kKeyCode_1               =0x02,
    kKeyCode_2               =0x03,
    kKeyCode_3               =0x04,
    kKeyCode_4               =0x05,
    kKeyCode_5               =0x06,
    kKeyCode_6               =0x07,
    kKeyCode_7               =0x08,
    kKeyCode_8               =0x09,
    kKeyCode_9               =0x0A,
    kKeyCode_0               =0x0B,
    kKeyCode_MINUS           =0x0C,    /* - on main keyboard */
    kKeyCode_EQUALS          =0x0D,
    kKeyCode_BACK            =0x0E,    /* backspace */
    kKeyCode_TAB             =0x0F,
    kKeyCode_Q               =0x10,
    kKeyCode_W               =0x11,
    kKeyCode_E               =0x12,
    kKeyCode_R               =0x13,
    kKeyCode_T               =0x14,
    kKeyCode_Y               =0x15,
    kKeyCode_U               =0x16,
    kKeyCode_I               =0x17,
    kKeyCode_O               =0x18,
    kKeyCode_P               =0x19,
    kKeyCode_LBRACKET        =0x1A,
    kKeyCode_RBRACKET        =0x1B,
    kKeyCode_RETURN          =0x1C,    /* Enter on main keyboard */
    kKeyCode_LCONTROL        =0x1D,
    kKeyCode_A               =0x1E,
    kKeyCode_S               =0x1F,
    kKeyCode_D               =0x20,
    kKeyCode_F               =0x21,
    kKeyCode_G               =0x22,
    kKeyCode_H               =0x23,
    kKeyCode_J               =0x24,
    kKeyCode_K               =0x25,
    kKeyCode_L               =0x26,
    kKeyCode_SEMICOLON       =0x27,
    kKeyCode_APOSTROPHE      =0x28,
    kKeyCode_GRAVE           =0x29,    /* accent grave */
    kKeyCode_LSHIFT          =0x2A,
    kKeyCode_BACKSLASH       =0x2B,
    kKeyCode_Z               =0x2C,
    kKeyCode_X               =0x2D,
    kKeyCode_C               =0x2E,
    kKeyCode_V               =0x2F,
    kKeyCode_B               =0x30,
    kKeyCode_N               =0x31,
    kKeyCode_M               =0x32,
    kKeyCode_COMMA           =0x33,
    kKeyCode_PERIOD          =0x34,    /* . on main keyboard */
    kKeyCode_SLASH           =0x35,    /* '/' on main keyboard */
    kKeyCode_RSHIFT          =0x36,
    kKeyCode_MULTIPLY        =0x37,    /* * on numeric keypad */
    kKeyCode_LMENU           =0x38,    /* left Alt */
    kKeyCode_SPACE           =0x39,
    kKeyCode_CAPITAL         =0x3A,
    kKeyCode_F1              =0x3B,
    kKeyCode_F2              =0x3C,
    kKeyCode_F3              =0x3D,
    kKeyCode_F4              =0x3E,
    kKeyCode_F5              =0x3F,
    kKeyCode_F6              =0x40,
    kKeyCode_F7              =0x41,
    kKeyCode_F8              =0x42,
    kKeyCode_F9              =0x43,
    kKeyCode_F10             =0x44,
    kKeyCode_NUMLOCK         =0x45,
    kKeyCode_SCROLL          =0x46,    /* Scroll Lock */
    kKeyCode_NUMPAD7         =0x47,
    kKeyCode_NUMPAD8         =0x48,
    kKeyCode_NUMPAD9         =0x49,
    kKeyCode_SUBTRACT        =0x4A,    /* - on numeric keypad */
    kKeyCode_NUMPAD4         =0x4B,
    kKeyCode_NUMPAD5         =0x4C,
    kKeyCode_NUMPAD6         =0x4D,
    kKeyCode_ADD             =0x4E,    /* + on numeric keypad */
    kKeyCode_NUMPAD1         =0x4F,
    kKeyCode_NUMPAD2         =0x50,
    kKeyCode_NUMPAD3         =0x51,
    kKeyCode_NUMPAD0         =0x52,
    kKeyCode_DECIMAL         =0x53,    /* . on numeric keypad */
    kKeyCode_OEM_102         =0x56,    /* < > | on UK/Germany keyboards */
    kKeyCode_F11             =0x57,
    kKeyCode_F12             =0x58,
    kKeyCode_F13             =0x64,    /*                     (NEC PC98) */
    kKeyCode_F14             =0x65,    /*                     (NEC PC98) */
    kKeyCode_F15             =0x66,    /*                     (NEC PC98) */
    kKeyCode_KANA            =0x70,    /* (Japanese keyboard)            */
    kKeyCode_ABNT_C1         =0x73,    /* / ? on Portugese (Brazilian) keyboards */
    kKeyCode_CONVERT         =0x79,    /* (Japanese keyboard)            */
    kKeyCode_NOCONVERT       =0x7B,    /* (Japanese keyboard)            */
    kKeyCode_YEN             =0x7D,    /* (Japanese keyboard)            */
    kKeyCode_ABNT_C2         =0x7E,    /* Numpad . on Portugese (Brazilian) keyboards */
    kKeyCode_NUMPADEQUALS    =0x8D,    /* = on numeric keypad (NEC PC98) */
    kKeyCode_PREVTRACK       =0x90,    /* Previous Track (  kKeyCode_CIRCUMFLEX on Japanese keyboard) */
    kKeyCode_AT              =0x91,    /*                     (NEC PC98) */
    kKeyCode_COLON           =0x92,    /*                     (NEC PC98) */
    kKeyCode_UNDERLINE       =0x93,    /*                     (NEC PC98) */
    kKeyCode_KANJI           =0x94,    /* (Japanese keyboard)            */
    kKeyCode_STOP            =0x95,    /*                     (NEC PC98) */
    kKeyCode_AX              =0x96,    /*                     (Japan AX) */
    kKeyCode_UNLABELED       =0x97,    /*                        (J3100) */
    kKeyCode_NEXTTRACK       =0x99,    /* Next Track */
    kKeyCode_NUMPADENTER     =0x9C,    /* Enter on numeric keypad */
    kKeyCode_RCONTROL        =0x9D,
    kKeyCode_MUTE            =0xA0,    /* Mute */
    kKeyCode_CALCULATOR      =0xA1,    /* Calculator */
    kKeyCode_PLAYPAUSE       =0xA2,    /* Play / Pause */
    kKeyCode_MEDIASTOP       =0xA4,    /* Media Stop */
    kKeyCode_VOLUMEDOWN      =0xAE,    /* Volume - */
    kKeyCode_VOLUMEUP        =0xB0,    /* Volume + */
    kKeyCode_WEBHOME         =0xB2,    /* Web home */
    kKeyCode_NUMPADCOMMA     =0xB3,    /* , on numeric keypad (NEC PC98) */
    kKeyCode_DIVIDE          =0xB5,    /* / on numeric keypad */
    kKeyCode_SYSRQ           =0xB7,
    kKeyCode_RMENU           =0xB8,    /* right Alt */
    kKeyCode_PAUSE           =0xC5,    /* Pause */
    kKeyCode_HOME            =0xC7,    /* Home on arrow keypad */
    kKeyCode_UP              =0xC8,    /* UpArrow on arrow keypad */
    kKeyCode_PGUP            =0xC9,    /* PgUp on arrow keypad */
    kKeyCode_LEFT            =0xCB,    /* LeftArrow on arrow keypad */
    kKeyCode_RIGHT           =0xCD,    /* RightArrow on arrow keypad */
    kKeyCode_END             =0xCF,    /* End on arrow keypad */
    kKeyCode_DOWN            =0xD0,    /* DownArrow on arrow keypad */
    kKeyCode_PGDOWN          =0xD1,    /* PgDn on arrow keypad */
    kKeyCode_INSERT          =0xD2,    /* Insert on arrow keypad */
    kKeyCode_DELETE          =0xD3,    /* Delete on arrow keypad */
    kKeyCode_LWIN            =0xDB,    /* Left Windows key */
    kKeyCode_RWIN            =0xDC,    /* Right Windows key */
    kKeyCode_APPS            =0xDD,    /* AppMenu key */
    kKeyCode_POWER           =0xDE,    /* System Power */
    kKeyCode_SLEEP           =0xDF,    /* System Sleep */
    kKeyCode_WAKE            =0xE3,    /* System Wake */
    kKeyCode_WEBSEARCH       =0xE5,    /* Web Search */
    kKeyCode_WEBFAVORITES    =0xE6,    /* Web Favorites */
    kKeyCode_WEBREFRESH      =0xE7,    /* Web Refresh */
    kKeyCode_WEBSTOP         =0xE8,    /* Web Stop */
    kKeyCode_WEBFORWARD      =0xE9,    /* Web Forward */
    kKeyCode_WEBBACK         =0xEA,    /* Web Back */
    kKeyCode_MYCOMPUTER      =0xEB,    /* My Computer */
    kKeyCode_MAIL            =0xEC,    /* Mail */
    kKeyCode_MEDIASELECT     =0xED     /* Media Select */
} keycode_enum;

// 鼠标状态定义
const int32_t kMouse_LBCLICK  = 0x1;      //  00000000 00000001
const int32_t kMouse_LBCLICKED = 0x2;      //  00000000 00000010
const int32_t kMouse_LBDOWN = 0x4;      //  00000000 00000100
const int32_t kMouse_MBCLICK = 0x8;      //  00000000 00001000
const int32_t kMouse_MBCLICKED = 0x10;      //  00000000 00010000
const int32_t kMouse_MBDOWN = 0x20;      //  00000000 00100000
const int32_t kMouse_RBCLICK = 0x40;      //  00000000 01000000
const int32_t kMouse_RBCLICKED = 0x80;      //  00000000 10000000
const int32_t kMouse_RBDOWN = 0x100;    //  00000001 00000000 
const int32_t kMouse_LBDBLCLK = 0x200;    //  00000010 00000000
const int32_t kMouse_MBDBLCLK = 0x400;    //  00000100 00000000
const int32_t kMouse_RBDBLCLK = 0x800;    //  00001000 00000000
const int32_t kMouse_WHEELUP = 0x1000;    //  00010000 00000000
const int32_t kMouse_WHEELDOWN = 0x2000;    //  00100000 00000000

//外部输入事件定义
typedef enum {
  kEventId_KEY_DOWN,      
  kEventId_KEY_UP,      
  kEventId_MOUSE_MOVE,    
  kEventId_MOUSE_LDRAG_MOVE,
  kEventId_MOUSE_RDRAG_MOVE,  
  kEventId_MOUSE_LBDOWN,    
  kEventId_MOUSE_LBUP,    
  kEventId_MOUSE_LBCLICK,    
  kEventId_MOUSE_RBDOWN,    
  kEventId_MOUSE_RBUP,    
  kEventId_MOUSE_RBCLICK,    
  kEventId_MOUSE_MBDOWN,    
  kEventId_MOUSE_MBUP,    
  kEventId_MOUSE_MBCLICK,    
  kEventId_MOUSE_LDBCLICK,  
  kEventId_MOUSE_MDBCLICK,  
  kEventId_MOUSE_RDBCLICK,  
  kEventId_MOUSE_WHEEL_UP,
  kEventId_MOUSE_WHEEL_DOWN,
  kEventId_MOUSE_LBDOWNREPEAT,
} eventid_enum;

typedef struct {
  eventid_enum id;
  //键盘事件的键盘编号，如果是鼠标事件，此值无效
  keycode_enum keyindex;
  //是否已被处理
  bool processed;
} event_t;

typedef std::vector<event_t> eventqueue;

typedef enum {
  kCaptureStatusNone, //没有被捕获
  kCaptureStatusUI, //被UI捕获
  kCaptureStatusGame, //被Game捕获
} capturestatus_enum;

class VENGINE_API System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   //获得传输的队列
   virtual eventqueue& get_eventqueue() = 0;
   //查询队列中是否有某事件存在
   virtual bool is_eventexist(eventid_enum id) = 0;
   //捕获状态
   virtual capturestatus_enum getcapture() = 0;
   virtual void setcapture(capturestatus_enum type) = 0;
   //处理windows消息
   virtual bool messageprocess(HWND hwnd, 
                               uint32_t message, 
                               WPARAM wparam, 
                               LPARAM lparam) = 0;

 public:
   //某个键是否被按下
   virtual bool is_keydown(keycode_enum key) = 0;
   //某个键是否刚被按下
   virtual bool is_keypress(keycode_enum key) = 0;
   //某个键是否刚被抬起
   virtual bool is_keypressed(keycode_enum key) = 0;
   //判断某个系统键是否按下
   virtual bool is_ctrldown() = 0;
   virtual bool is_shiftdown() = 0;
   virtual bool is_altdown() = 0;

 public:
   //设置鼠标
   virtual void set_mouseposition(int32_t x, int32_t y) = 0;
   virtual POINT get_mousepostion() = 0;
   virtual POINT get_mouse_oldpostion() = 0;
   virtual RECT get_mouse_LB_dragrect() = 0;
   virtual RECT get_mouse_MB_dragrect() = 0;
   virtual RECT get_mouse_RB_dragrect() = 0;
   virtual uint32_t get_mouseflag() = 0;
   virtual uint32_t get_mouse_oldflag() = 0;
   virtual uint32_t get_L_putdown_time() = 0;

};

}; //namespace vengine_input

#endif //VENGINE_INPUT_SYSTEM_H_
