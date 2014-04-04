/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-21 12:05:53
 * @uses vengine ui system module
 */
#ifndef VENGINE_UI_SYSTEM_H_
#define VENGINE_UI_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/game/itemtransfer_system.h"
#include "vengine/ui/creature_headboard.h"

namespace vengine_ui {

typedef enum {
  kTalkTemplateNobody,
  kTalkTemplateOther,
  kTalkTemplateSelf,
  kTalkTemplateMax
} talktemplate_enum;

typedef enum {
  kFilterTypeNone, //无类型
  kFilterTypeChat, //聊天
  kFilterTypeRole, //角色创建
  kFilterTypeName, //命名
  kFilterTypeStall, //摆摊
  kFilterTypeMax
} filtertype_enum;

typedef enum {
  kFilterLevelNoMatch, //忽略
  kFilterLevelPartMatch, //部分匹配
  kFilterLevelFullMatch, //完全匹配
  kFilterLevelMax
} filterlevel_enum;

//static
const uint16_t kHelpStringMax = 200;
const char* kHelpStringKey = "help"; //this if have problem 
                                     //then change it to macros

//interface for ui system
class VENGINE_API System : public vengine_kernel::Node{ 

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   virtual void on_windowsize_change(uint32_t message,
                                     WPARAM wparam, 
                                     LPARAM lparam) = 0; //窗口大小改变事件
   virtual void injectinput() = 0; //如果事件结果为true则获取了输入
   virtual bool messageprocess(HWND hwnd, 
                               uint32_t message, 
                               WPARAM wparam, 
                               LPARAM lparam) = 0; //文字输入消息
   virtual bool is_mousehover() = 0; //鼠标是否在UI上空
   //鼠标是否在聊天板上空
   virtual bool is_mousehover_chatboard(int64_t x, int64_t y) = 0; 
   //获得聊天信息里的超链接信息
   virtual STRING get_chatboard_hyplink_content(int64_t x, int64_t y) = 0;
   //创建一个新的角色信息板
   virtual CreatureHeadBoard* create_creature_headboard() = 0;
   //添加一个新的被击中信息框
   virtual void add_behit_board(bool _double, 
                                const char* info, 
                                float startx, 
                                float starty, 
                                uint8_t type = 0, 
                                uint8_t movetype = 0) = 0;
   virtual bool is_windowshow(const char* name, 
                              const char* childname = NULL) = 0;
   virtual bool close_allwindow() = 0;
   //通知UI创建一组UI显示模型
   virtual void fakeobject_show(const char* windowname, const char* name) = 0;
   //知UI销毁一组UI显示模型
   virtual void fakeobject_destroy(const char* windowname, 
                                   const char* name) = 0;
   
   //debugs
 public:
   virtual void debug_push_chatstring(const char* name, 
                                      const char* message) = 0;
   virtual void debug_save_fonttexture() = 0;

 public:
   virtual void change_dragflag(bool flag) = 0;
   virtual bool is_dragend() = 0;

 public:
   //逻辑层添加系统通知信息
   virtual STRING parsestring_varparam(const char* id, ...) = 0;
   virtual void parsestring_nocolor(const STRING& in, 
                                    STRING& out, 
                                    bool control = false) = 0;
   virtual STRING parsestring_nocolor_varparam(const char* id, ...) = 0;
   virtual STRING parsestring_no_varparam(const char* id) = 0;
   virtual STRING parsestring_nocolor_no_varparam(const char* id) = 0;

   //聊天模板字串的取得
   virtual STRING get_talktemplate(const STRING& key, uint16_t index) = 0;
   virtual STRING modify_chattemplate(const STRING& temp, 
                                      const STRING& talker, 
                                      const STRING& target) = 0;
   virtual STRING get_talkrand_helpmessage() = 0; //聊天随机提示消息
   //查看当前获取输入的EditBox
   virtual bool is_IME_editbox_active(const char* windowname) = 0;
   virtual int32_t get_current_IMEstate() = 0; //获取当前输入法状态
   virtual STRING get_IME_editbox_string(const char* name) = 0; //获得输入内容

   //传入一个物品信息
   virtual bool inject_iteminfo(
       vengine_game::ItemTransferSystem::element_t* element) = 0;

   virtual void on_pushescape() = 0;
   virtual bool is_paopao_active() = 0;
   virtual uint32_t lumination_ogrecolor(uint32_t ogrecolor, 
                                         int32_t lumination) = 0;
   virtual int32_t ogrecolor_lumination(uint32_t ogrecolor) = 0;

   //过滤字符串中的非法敏感字符
   virtual bool check_stringfilter(
       const STRING& in, 
       const filtertype_enum type = kFilterTypeNone) = 0;
   virtual bool check_stringcode(const STRING& in, STRING& out) = 0;
   //完全匹配过滤
   virtual bool check_string_fullcompare(const STRING& in, 
                                         const STRING& filtertype = "all", 
                                         bool use_alltable = true) = 0;
   virtual STRING get_debugstring() = 0;

   //取当前的鼠标下面的窗口
   virtual void openwindow(const STRING& name) = 0;
   virtual void closewindow(const STRING& name) = 0;
   virtual void togglewindow(const STRING& name) =0;

   virtual bool has_inputfocus() = 0;

   //加聊天信息（提高显示聊天信息的效率）
   virtual bool add_chathistory_message(int32_t id,
                                        const char* windowname, 
                                        const char* message, 
                                        int32_t type = -1, 
                                        uint32_t disappeartime = 0) = 0;
   virtual void replacestring_usefilter(
       const STRING& in, 
       STRING& out, 
       filtertype_enum filtertype = kFilterTypeChat) = 0;
   virtual STRING check_stringvalid(const char* string) = 0;
   virtual bool reload_windowscript(const STRING& windowname) = 0;
   virtual void uirender_toggleshow() = 0;
};


}; //namespace vengine_ui

#endif //VENGINE_UI_SYSTEM_H_
