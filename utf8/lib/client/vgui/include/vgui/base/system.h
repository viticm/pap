/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-26 11:26:48
 * @uses vgui base system
 */
#ifndef VGUI_BASE_SYSTEM_H_
#define VGUI_BASE_SYSTEM_H_

#include <OgreRoot.h>
#include <imm.h>
#include "CEGUIString.h"
#include "vengine/ui/system.h"
#include "vgui/config.h"

/** ogre and cegui { **/

namespace Ogre {
class Root;
}; //namespace Ogre

namespace CEGUI {
class System;
class OgreCEGUIRenderer;
class FalagardActionButton;
class EventArgs;
class Window;
}; //namespace CEGUI

namespace vgui_script {
class Base;
}; //namespace vgui_script

/** }ogre and cegui **/

namespace vgui_window {
class Manager;
}; //namespace vgui_base

namespace vgui_icon {
class Manager;
}; //namespace vgui_icon

namespace vgui_string {
class System;
}; //namespace vgui_string

namespace vgui_creature {

namespace head_board {
class System;
}; //namespace head_board

}; //namespace vgui_creature

namespace vgui_base {

class System : public vengine_ui::System {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   System();
   virtual ~System();
   static System* getself();

 public: //implement from abstract class
   virtual void on_windowsize_change(uint32_t message,
                                     WPARAM wparam, 
                                     LPARAM lparam); //窗口大小改变事件
   virtual void injectinput(); //如果事件结果为true则获取了输入
   virtual bool messageprocess(HWND hwnd, 
                               uint32_t message, 
                               WPARAM wparam, 
                               LPARAM lparam); //文字输入消息
   virtual bool is_mousehover(); //鼠标是否在UI上空
   //鼠标是否在聊天板上空
   virtual bool is_mousehover_chatboard(int64_t x, int64_t y); 
   //获得聊天信息里的超链接信息
   virtual STRING get_chatboard_hyplink_content(int64_t x, int64_t y);
   //创建一个新的角色信息板
   virtual vengine_ui::CreatureHeadBoard* create_creature_headboard();
   //添加一个新的被击中信息框
   virtual void add_behit_board(bool _double, 
                                const char* info, 
                                float startx, 
                                float starty, 
                                uint8_t type, 
                                uint8_t movetype);
   virtual bool is_windowshow(const char* name, 
                              const char* childname = NULL);
   virtual bool close_allwindow();
   //通知UI创建一组UI显示模型
   virtual void fakeobject_show(const char* windowname, const char* name);
   //知UI销毁一组UI显示模型
   virtual void fakeobject_destroy(const char* windowname, 
                                   const char* name);
   
   //debugs
 public:
   virtual void debug_push_chatstring(const char* name, 
                                      const char* message);
   virtual void debug_save_fonttexture();

 public:
   virtual void change_dragflag(bool flag);
   virtual bool is_dragend();

 public:
   //逻辑层添加系统通知信息
   virtual STRING parsestring_varparam(const char* id, ...);
   virtual void parsestring_nocolor(const STRING& in, 
                                    STRING& out, 
                                    bool control = false);
   virtual STRING parsestring_nocolor_varparam(const char* id, ...);
   virtual STRING parsestring_no_varparam(const char* id);
   virtual STRING parsestring_nocolor_no_varparam(const char* id);

   //聊天模板字串的取得
   virtual STRING get_talktemplate(const STRING& key, uint16_t index);
   virtual STRING modify_chattemplate(const STRING& temp, 
                                      const STRING& talker, 
                                      const STRING& target);
   virtual STRING get_talkrand_helpmessage(); //聊天随机提示消息
   //查看当前获取输入的EditBox
   virtual bool is_IME_editbox_active(const char* windowname);
   virtual int32_t get_current_IMEstate(); //获取当前输入法状态
   virtual STRING get_IME_editbox_string(const char* name); //获得输入内容

   //传入一个物品信息
   virtual bool inject_iteminfo(
       vengine_game::ItemTransferSystem::element_t* element);

   virtual void on_pushescape();
   virtual bool is_paopao_active();
   virtual uint32_t lumination_ogrecolor(uint32_t ogrecolor, 
                                         int32_t lumination);
   virtual int32_t ogrecolor_lumination(uint32_t ogrecolor);

   //过滤字符串中的非法敏感字符
   virtual bool check_stringfilter(
       const STRING& in, 
       const vengine_ui::filtertype_enum type = vengine_ui::kFilterTypeNone);
   virtual bool check_stringcode(const STRING& in, STRING& out);
   //完全匹配过滤
   virtual bool check_string_fullcompare(const STRING& in, 
                                         const STRING& filtertype = "all", 
                                         bool use_alltable = true);
   virtual STRING get_debugstring();

   //取当前的鼠标下面的窗口
   virtual void openwindow(const STRING& name);
   virtual void closewindow(const STRING& name);
   virtual void togglewindow(const STRING& name);

   virtual bool has_inputfocus();

   //加聊天信息（提高显示聊天信息的效率）
   virtual bool add_chathistory_message(int32_t id,
                                        const char* windowname, 
                                        const char* message, 
                                        int32_t type = -1, 
                                        uint32_t disappeartime = 0);
   virtual void replacestring_usefilter(
       const STRING& in, 
       STRING& out, 
       vengine_ui::filtertype_enum filtertype = vengine_ui::kFilterTypeChat);
   virtual STRING check_stringvalid(const char* string);
   virtual bool reload_windowscript(const STRING& windowname);
   virtual void uirender_toggleshow();

 public:
   virtual void init(void*);
   virtual void release();
   virtual void tick();

 public:
   virtual bool is_ctrlinfo_enable();
   virtual void set_ctrlinfo_enable(bool enable);
 
 public: //action buttons
   vgui_icon::Manager* get_iconmanager();
   //捕获拖动开始
   bool handle_action_dragdrop_started(const CEGUI::EventArgs& event);
   //鼠标进入，显示super tooltip
   bool handle_actionbutton_mouseenter(const CEGUI::EventArgs& event);
   //鼠标离开，隐藏super tooltip
   bool handle_actionbutton_mouseleave(const CEGUI::EventArgs& event);
   //父窗口关闭
   bool handle_actionbutton_parenthidden(const CEGUI::EventArgs& event);
   //mesh window开始显示
   bool handle_meshwindow_shown(const CEGUI::EventArgs& event);
   //mesh window隐藏
   bool handle_meshwindow_hiden(const CEGUI::EventArgs& event);

 public: //超链接
   bool handle_hyperlink_active(const CEGUI::EventArgs &event);
   bool handle_hyperlink_leftactive(const CEGUI::EventArgs &event);
   bool handle_hyperlink_rightactive(const CEGUI::EventArgs &event);
   bool handle_hyperlink_inactive(const CEGUI::EventArgs &event);

 public:
   //删除itemelement的通知相关
   bool handle_elementdelete(const CEGUI::EventArgs &event);
   //chat history 点击infoelement的通知
   bool handle_chathistory_infoelement_click(const CEGUI::EventArgs& event);
   //chat history 鼠标在infoelement的通知
   bool handle_chathistory_infoelement_movein(const CEGUI::EventArgs& event);
   bool handle_chathistory_infoelement_moveout(const CEGUI::EventArgs& event);
   //click sound 对应按钮点击后播放声音
   bool handle_pushbutton_clicksound(const CEGUI::EventArgs& event);

 protected:
   Ogre::Root* ogreroot_;
   CEGUI::System* cegui_system_;
   CEGUI::OgreCEGUIRenderer* cegui_render_;
   vgui_script::Base* script_;
   vgui_window::Manager* windowmanager_;
   vgui_icon::Manager* iconmanager_;
   vgui_string::System* stringsystem_;
   vgui_creature::head_board::System* creature_headboard_system_;
   CEGUI::String buttonname_indragging_; 
   bool is_dragend_;
   HCURSOR draggingcursor_;
   bool active_paopao_;
   bool is_ctrlinfo_enable_; //是否激活按住Ctrl键激活系统设置中所见所得功能
                             //是否用快捷键的设置，在游戏性设置部分
   
 protected:
   static System* self_;

 protected:
   void on_dragbegin(CEGUI::FalagardActionButton* dranggingbutton_);
   //拖动结束，targetbutton为目标button如果为空，则表示拖动到空白
   void on_dragend(CEGUI::Window* targetwindow);

};

}; //namespace vgui_base

#endif //VGUI_BASE_SYSTEM_H_
