/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-27 11:04:51
 * @uses vgui string system
 *       cn: 文本资源管理器
 */
#ifndef VGUI_STRING_SYSTEM_H_
#define VGUI_STRING_SYSTEM_H_

#include <set>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <CEGUISystem.h>
#include "vengine/config.h"
#include "vengine/ui/system.h"
#include "vgui/config.h"
#include "vgui/string/filter.h"

namespace vgui_string {

typedef struct {
  const char* code;
  CEGUI::utf32 utfcode;
} facecode_t;

class System {

 public:
   System();
   virtual ~System();
   static System* getself();

 public:
   typedef struct {
     STRING str;
     //过滤规则
     //0表示忽略，1表示含有就过滤，2表示完全匹配过滤
     uint8_t chat;
     uint8_t role; //创建人物时规则
     uint8_t name; //创建时规则
     uint8_t stall; //摆摊时规则
   } filterstring_t;

 public:
   //string parse
   void parsestring_prebuild(const STRING& in, STRING& out);
   void parsestring_runtime(const STRING& in, 
                            CEGUI::String32& out, 
                            const vengine_ui::filtertype_enum filtertype
                            = vengine_ui::kFilterTypeChat);
   STRING parsestring_varparam(const STRING& id, va_list va_pointer);
   void parsestring_nocolor(const STRING& in, 
                            STRING& out, 
                            bool control = false);
   STRING parsestring_no_varparam(const STRING& id);

   //物品传输系统
   void parsestring_reverseruntime(const CEGUI::String32& in, STRING& out);
   void parsestring_elementonly_runtime(const STRING& in, CEGUI::String32& out);

   //聊天模板字串的取得
   STRING get_talktemplate(const STRING& key, uint32_t index);
   STRING modify_chattemplate(const STRING& source, 
                              const STRING& talker, 
                              const STRING& target);
   STRING get_talkrand_helpmessage(); //聊天随机提示消息
   //utf<->mbcs
   static void mbcs_to_utf8(const STRING& in, STRING& out);
   static void utf8_to_mbcs(const STRING& strIn, STRING& out);
   STRING check_stringvalid(const char* string);

 public:
   void init(const char* string_datbasefile = "../config/dictionary.txt");
   //过滤字符串中的非法敏感字符
   bool check_stringfilter(
       const STRING& in, 
       const vengine_ui::filtertype_enum type = vengine_ui::kFilterTypeNone);
   bool check_stringcode(const STRING& in, STRING& out);
   //完全匹配过滤
   bool check_string_fullcompare(const STRING& in, 
                                 const STRING& filtertype = "all", 
                                 bool use_alltable = true);
   void replacestring_usefilter(
       const STRING& in, 
       STRING& out, 
       vengine_ui::filtertype_enum filtertype);

 //defines 
 public:
#ifdef __SGI_STL_PORT
   typedef std::hash_map<STRING, STRING> dictionarymap;
#else
   typedef stdext::hash_map<STRING, STRING> dictionarymap;
#endif
   typedef std::map<int32_t, CEGUI::utf32> codeconvert_map;
   typedef std::vector<filterstring_t> filter_map;
   typedef std::vector<STRING> talktemplate_vector;
   typedef std::map<STRING, talktemplate_vector> talktemplate_map;
   typedef std::set<STRING> fullmatch_template_set;
   typedef std::map<STRING, fullmatch_template_set> fullmatch_map;

 protected:
   std::pair<bool, dictionarymap::iterator> isvalid_dictionkey(
       const STRING& key);

 //variables
 protected:
   static System* self_;
   dictionarymap dictionarytable_;
   codeconvert_map codeconvert_table_;
   filter_map filtertable_;
   talktemplate_map talktemplate_table_;
   fullmatch_map fullmatch_table_;
   Filter filter_[vengine_ui::kFilterTypeMax];

 private:
   void parsestring_runtimenew(
       const STRING& in, 
       CEGUI::String32& out, 
       const vengine_ui::filtertype_enum filterType = 
       vengine_ui::kFilterTypeNone);
   void generate_talktemplate_table();
   void generate_fullmatch_table();

};

}; //namespace vgui_string

#endif //VGUI_STRING_SYSTEM_H_
