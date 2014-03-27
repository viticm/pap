#include "vengine/kernel/base.h"
#include "vengine/game/object/basesystem.h"
#include "vengine/exception/base.h"
#include "vengine/db/system.h"
#include "vengine/db/struct/all.h"
#include "Core/utf.h"
#include "vgui/string/encode.h"
#include "vgui/string/system.h"

namespace vgui_string {

struct auto_localeconvert_t {
  auto_localeconvert_t() {
    std::locale langLocale("");
    old = std::locale::global(langLocale);
  }
  ~auto_localeconvert_t() {
    std::locale::global(old);
  }
  std::locale old;
};

System* System::self_ = NULL;

System::System() {
  self_ = this;
}

System::~System() {

}

System* System::getself() {
  return self_;
}

void System::init(const char* string_datbasefile) {
  //字符串字典
  vengine_db::System* filedb_system = 
    dynamic_cast<vengine_db::System*>(g_kernel->getnode("bin\\dbc"));
  const vengine_db::File* stringdict = filedb_system->get(
      vengine_db::structs::other::kStringDictId);
  VENGINE_ASSERT(stringdict);
  typedef vengine_db::structs::other::stringdict_t stringdict_t; //function use
  int32_t i;
  for (i = 0; i < stringdict->get_record_number(); ++i) {
    const stringdict_t* line = 
      reinterpret_cast<stringdict_t*>(stringdict->search_line_equal(i));
    dictionarytable_[line->key] = line->string;
  }
  dictionarymap::iterator dictmap_iterator;
  //字符串字典id转化
  for (dictmap_iterator = dictionarytable_.begin(); 
       dictmap_iterator != dictionarytable_.end();
       ++dictmap_iterator) {
    STRING out;
    parsestring_prebuild(dictmap_iterator->second, out);
    dictmap_iterator->second = out;
  }
  //聊天模板创建
  generate_talktemplate_table();
  //表情映射
  //ui load
  const vengine_db::File* codeconvert = filedb_system->get(
      vengine_db::structs::other::kCodeConvertId);
  typedef vengine_db::structs::other::codeconvert_t codeconvert_t;
  for (i = 0; i < codeconvert->get_record_number(); ++i) {
    const codeconvert_t* line = 
      reinterpret_cast<codeconvert_t*>(codeconvert->search_line_equal(i));
    CEGUI::utf32 value = 0;
    sscanf(line->code, "%8X", &value);
    codeconvert_table_[line->id] = value;
  }
  //过滤词数组构造
  const vengine_db::File* talkfilter = filedb_system->get(
      vengine_db::structs::other::kTalkFilterId);
  typedef vengine_db::structs::other::talkfilter_t talkfilter_t;
  for (i = 0; i < talkfilter->get_record_number(); ++i) {
    const talkfilter_t* line = 
      reinterpret_cast<talkfilter_t*>(talkfilter->search_line_equal(i));
    filterstring_t filterstring;
    filterstring.str = line->str;
    filterstring.chat = line->chat;
    filterstring.role = line->role;
    filterstring.name = line->name;
    filterstring.stall = line->stall;
    filtertable_.push_back(filterstring);       
  }

  //生成完全过滤表
  generate_fullmatch_table();
}

std::pair<bool, System::dictionarymap::iterator> System::isvalid_dictionkey(
  const STRING& key) {
  dictionarymap::iterator dictmap_iterator = dictionarytable_.find(key);
  bool result = dictmap_iterator == dictionarytable_.end() ? false : true;
  return std::pair<result, dictmap_iterator>;
}

//转化：主要是从字典和系统级字符串中查找
void System::parsestring_prebuild(const STRING& in, STRING& out) {
  const char key_parsestart = '{';
  const char key_parsemiddle = '=';
  const char key_parseend = '}';
  STRING::size_type validstart = 0;
  out = "";
  for (;;) {
    if (validstart >= in.size()) break;
    STRING::size_type validend = in.find(key_parsestart, validstart);
    //最后一段正常值
    if (STRING::npos == validend) {
      out += in.substr(validstart);
      break;
    }
    //加入正常值
    if (validend != validstart) {
      out += in.substr(validstart, validend - validstart);
    }

    STRING::size_type keystart = validend + 1;
    STRING::size_type keymiddle = in.find(key_parsemiddle, keystart);
    STRING::size_type keyend = in.find(key_parseend, keystart);
    //合法的Key描述
    if (keyend != STRING::npos && 
        keymiddle != STRING::npos && 
        keyend > keymiddle) {
      STRING keyleft = in.substr(keystart, keymiddle - keystart);
      STRING keyright = in.substr(keymiddle + 1, keyend - keymiddle - 1);
      if ("ID" == keyleft) {
        std::pair<bool, dictionarymap::iterator> is_validkey =
          isvalid_dictionkey(keyright);
        //找到key
        if (is_validkey.first) {
          //加入从key转化过来的值
          out += is_validkey.second->second;
          validstart = keyend + 1;
          continue;
        }
      }
    }
    out += in.substr(validend, keyend - validend);
    validstart = keyend;
  } //loop end
}

//对MBCS码字符串进行合法检测，剔除非法字符，例如半个汉字
/*
|  可以在UT8环境下使用该方法
|  使用GBK标准
|
|  Windows95及后续版本中文版支持GBK。
|  GB2312的EUC编码范围是第一字节0xA1~0xFE(实际只用到0xF7)，第
|  二字节0xA1~0xFE。GBK对此进行扩展。第一字节为0x81~0xFE，第二
|  字节分两部分，一是0x40~0x7E，二是0x80~0xFE。其中和GB2312相
|  同的区域，字完全相同。扩展部分大概是按部件(部首)和笔顺(笔画)
|  从GB13000中取出再排列入GBK中。因此GBK并不是GB13000，虽然两者
|  字汇相同，但编码体系不同。一个是ISO2022系列不等长编码，一个
|  是等长编码，并且编码区域也不同。注意到GBK实际上不是国家标准。
|  在此之前有一个GB2312基本集，在它之上是一个技术更先进的GB13000。
|  GBK只是一种过渡和扩展规范。所以在Unicode里有GB2312->Unicode,
|  GB12345->Unicode的转换表格，而没有GBK->Unicode转换表格。只有
|  Microsoft制作的Code Page 936(CP936.TXT)可以算作GBK->Unicode
|  转换表格。但要注意这是一个商业公司制作的文件，而不是国家或
|  国际标准组织制作的，有可能与标准有不一致的地方。
|
*/
bool System::check_stringcode(const STRING& in, STRING out) {
  const uint8_t ansi_start = 0X20;
  const uint8_t ansi_end = 0X80;

  const uint8_t by1_gbk_start = 0X81;
  const uint8_t by1_gbk_end = 0XFE;

  const uint8_t by2_gbk_start1 = 0X40;
  const uint8_t by2_gbk_end1 = 0X7E;
  const uint8_t by2_gbk_start2 = 0X80;
  const uint8_t by2_gbk_end2 = 0XFE;

  const CHAR * const errorstr = "<ERROR>";

  //预先分配好内存
  int32_t sourcesize = static_cast<int32_t>(in.size());
  out.reserve(sourcesize + 1);
  out = "";
  int32_t i;
  for (i = 0; i < sourcesize;){
    uint8_t bychar = in[i];
    //标准ANSI英文字符
    if (bychar >= ansi_start && 
        bychar <= ansi_end || 
        '\r' == bychar || 
        '\n' == bychar || 
        '\t' == bychar) {
      out += bychar;
      i++; 
      continue;
    }
    //汉字第一个字节
    else if (bychar >= by1_gbk_start && bychar <= by1_gbk_end) {
      //半个汉字
      if (i + 1 == sroucesize) goto CHECKSTRING_ERROR;
      //取出第二个字节
      uint8_t bynext = in[++i];
      if (!(bynext >= by2_gbk_start1 && 
            bynext <= by2_gbk_end1 || 
            bynext >= by2_gbk_start2 && 
            bynext <= by2_gbk_end2)) {
        //非法的汉字
        goto CHECKSTRING_ERROR;
      }
      //加入完整的汉字
      char temp[8];
      temp[0] = bychar;
      temp[1] = bynext;
      temp[2] = 0;
      out += temp;
      ++i;
      continue;
    }
    else goto CHECKSTRING_ERROR;
  }
  return true;
CHECKSTRING_ERROR:
  out += errorstr;
  return false;
}

bool System::check_stringfilter(const STRING& in, 
                                const vengine_ui::filtertype_enum filtertype) {
  if (filtertype == vengine_ui::kFilterTypeNone) return true;
  vengine_ui::filterlevel_enum ruler = vengine_ui::kFilterLevelNoMatch;
  size_t i;
  for (i = 0; i < filtertable_.size(); ++i) {
    //判断过滤类型
    switch (filtertype) {
      case vengine_ui::kFilterTypeChat: {
        ruler = static_cast<vengine_ui::filterlevel_enum>(
            filtertable_[i].chat);
        break;
      }
      case vengine_ui::kFilterTypeRole: {
        ruler = static_cast<vengine_ui::filterlevel_enum>(
            filtertable_[i].role);
        break;
      }
      case vengine_ui::kFilterTypeName: {
        ruler = static_cast<vengine_ui::filterlevel_enum>(
            filtertable_[i].name);
        break;
      }
      case vengine_ui::kFilterTypeStall: {
        ruler = static_cast<vengine_ui::filterlevel_enum>(
            filtertable_[i].stall);
        break;
      }
      default: {
        break;
      }
    }
    //判断过滤等级
    switch (ruler) {
      case vengine_ui::kFilterLevelNoMatch: {
        break;
      }
      case vengine_ui::kFilterLevelPartMatch: {
        if (in.find(filtertable_[i].str) != STRING::npos) return false;
        break;
      }
      case vengine_ui::kFilterLevelNoMatch: {
        if (in== filtertable_[i].str ) return false;
        break;
      }
      default: {
        break;
      }
    }
  }
  return true;
}

bool System::check_string_fullcompare(const STRING& in
                                      const STRING& filtertype,
                                      bool use_alltable) {
  bool find = false;
  fullmatch_map::iterator iterator = fullmatch_table_.find("all");
  if (use_alltable && iterator != fullmatch_table_.end()) {
    fullmatch_template_set& templatestr = iterator->second;
    if (templatestr.find(in) != templatestr.end()) find = true;
  }
  iterator = fullmatch_table_.find(filtertype);
  if (!find && iterator != fullmatch_table_.end()) {
    fullmatch_template_set& templatestr = iterator->second;
    if (templatestr.find(in) != templatestr.end()) find = true;
  }
  return !find;
}

//运行时转化
//特殊表情符转化，把后面的字符转化成utf32，并且把string也转化成utf32
void System::parsestring_runtime(
    const STRING& in, 
    CEGUI::String32& out, 
    const vengine_ui::filtertype_enum filtertype) {
  parsestring_runtimenew(in, out, filtertype);
}

void System::parsestring_runtimenew(
    const STRING& in,
    CEGUI::String32& out,
    const vengine_ui::filtertype_enum filtertype) {
/**
*  #R 表示后面的字体为红色(red)
*  #G 表示后面的字体为绿色(green)
*  #B 表示后面的字体为蓝色(blue)
*  #K 表示后面的字体为黑色(black)
*  #Y 表示后面的字体为黄色(yellow)
*  #W 表示后面的字体为白色(white)
*  #b 表示后面的字体为闪烁(blink)
*  #c + 六个数字或者A-F字母 自定义颜色，例如：c008000=暗绿色
*  #e + 六个数字或者A-F字母 自定义颜色，例如：e008000=暗绿色,表示字体扩展边底色
*  #u + 文字 + #u 文字有下划线。
*  #n 所有文字状态恢复正常。
*  #r 文字换行。
*  ## 输出一个#号。
*  #aB 表示后面跟着一个超链接，这是超链接部分的开始
*  #aE 表示后面跟着一个超链接，这是超链接部分的结束
*  #{IDSTR}  查表替换字符串
*  #0~99    表情
*  #-01~-99  仅程序使用，不许玩家输入的动画
**/
  const char keyparse = '#';
  const char key_parseid_start = '{';
  const char key_parseid_end = '}';
  STRING::size_type validstart = 0;
  STRING out_mbcs = "";
  int32_t currentcolor = 0xFBFFFFFF;
  bool blink = false;
  
  //检查字符串的合法性
  STRING sourcestr;
  check_stringcode(in, sourcestr);
  //过滤聊天信息中的非法信息
  if (!check_stringfilter(sourcestr, filtertype)) 
    sourcestr = "#R请注意你的言辞！"
  for (;;) {
    if (validstart >= sourcestr.size()) break;
    STRING::size_type validend = strSource.find(keyparse, validstart);
    //最后一段正常值
    if (STRING::npos == validend) {
      out_mbcs = sourcestr.substr(validstart);
      STRING temp;
      mbcs_to_utf8(out_mbcs, temp);
      out += (CEGUI::String32)(reinterpret_cast<CEGUI::utf8*>(temp.c_str()));
      break;
    }
    //加入正常值
    if (validend != validstart) {
      out_mbcs = sourcestr.substr(validstart, validend - validstart);
      STRING temp;
      mbcs_to_utf8(out_mbcs, temp);
      out += (CEGUI::String32)(reinterpret_cast<CEGUI::utf8*>(temp.c_str()));
    }

    STRING::size_type keystart = validend + 1; //"#"后面那个字符的位置
    STRING::size_type keyend; //下一个非指令字符的位置
    if (keystart != STRING::npos) { //合法的key描述
      STRING keyoption = sourcestr.substr(keystart, 1);
      CEGUI::utf32 val = 0;
      if ("R" == keyoption) { //#R红色
        val = 0xFBFF0000;
        out += val;
        keyend = keystart + 1;
      }
      else if ("G" == keyoption) { //#G绿色
        val = 0xFB00FF00;
        out += val;
        keyend = keystart + 1;
      }
      else if ("B" == keyoption) { //#B蓝色
        val = 0xFB0000FF;
        out += val;
        keyend = keystart + 1;
      }
      else if ("K" == keyoption) { //#K黑色
        val = 0xFB000000;
        out += val;
        keyend = keystart + 1;
      }
      else if ("Y" == keyoption) { //#Y黄色
        val = 0xFBFFFF00;
        out += val;
        keyend = keystart + 1;
      }
      else if ("W" == keyoption) { //#Y白色
        val = 0xFBFFFFFF;
        out += val;
        keyend = keystart + 1;
      }
      else if ("b" == keyoption) { //#b闪烁
        val = 0xE0000000;
        out += val;
        keyend = keystart + 1;
      }
      else if ("c" == keyoption) { //#c自定义颜色
        STRING color = sourcestr.substr(keystart + 1, 6);
        CEGUI::utf32 val = 0;
        sscanf(color.c_str(), " %6X", &val);
        out += val;
        keyend = keystart + 1 + 6;
      }
      else if ("e" == keyoption) { //#e自定义扩展颜色
        STRING color = sourcestr.substr(keystart + 1, 6);
        CEGUI::utf32 val = 0;
        sscanf(color.c_str(), " %6X", &val); 
        val = 0xFC000000 | (val & 0x00FFFFFF );
        out += val;
        keyend = keystart + 1;
      }
      else if ("u" == keyoption) { //#u下划线
        keyend = keystart + 1;
      }
      else if ("n" == keyoption) { //#n回复状态
        keyend = keystart + 1;
      }
      else if ("r" == keyoption) { //#r回车换行
        out_mbcs = "\n";
        STRING temp;
        mbcs_to_utf8(out_mbcs, temp);
        out += (CEGUI::String32)(reinterpret_cast<CEGUI::utf8*>(temp.c_str()));
        keyend = keystart + 1;
      }
      else if ("#" == keyoption) { //##输出#
        out_mbcs = "#";
        STRING temp;
        mbcs_to_utf8(out_mbcs, temp);
        out += (CEGUI::String32)(reinterpret_cast<CEGUI::utf8*>(temp.c_str()));
        keyend = keystart + 1;
      }
      else if ("a" == keyoption) { //#a:HyperLink #aB{linktxt}showtxt#aE
        STRING rig = sourcestr.substr(keystart + 1, 1);
        if ("B" == rig) { //#aB
          val = 0xFD000000;
          out += val;
          keyend = keystart + 2;
        }
        else if ("E" = rig) { //#aE
          val = 0xFE000000;
          out += val; 
          keyend = keystart + 2;
        }
        else { //非法的超链接
          keyend = keystart + 2;
        }
      }
      else if (keyoption.c_str()[0] == key_parseid_start) {
        STRING::size_type idstart = keystart + 1;
        STRING::size_type idend = sourcestr.find(key_parseid_end, idstart);
        if (idend != STRING::npos) {
          idstr = sourcestr.substr(idstart, idend - idstart);
          if ("_ITEM" == idstr.substr(0, 5)) { //#{_ITEM10100005}
            STRING tableindex_str = idstr.substr(5, 8);
            int32_t tableindex = atoi(tableindex_str.c_str());
            out_mbcs = g_game_objectsystem->getitem(tableindex);
            STRING temp;
            mbcs_to_utf8(out_mbcs, temp);
            out += 
              (CEGUI::String32)(reinterpret_cast<CEGUI::utf8*>(temp.c_str())); 
          }
          if ("_TIME" == idstr.substr(0, 5)) { //#{_TIME0507211233}
                                               //0507211233 表示 
                                               //"2005年07月21日 12:33"
            STRING timestr = idstr.substr(5, 10);
            uint32_t time = atoi(timestr.c_str());
            uint16_t minute, hour, day, month, year;
            minute = time % 100;
            time /= 100;
            hour = time % 100;
            time /= 100;
            day = time % 100;
            time /= 100;
            month = time % 100;
            time /= 100;
            year = 2000 + time % 100;
            const char* format = "%d年%d月%d日 %02d:%02d";
            char date[32] = {0};
            snprintf(date, 
                     sizeof(date) - 1, 
                     format, 
                     year, 
                     month, 
                     day, 
                     hour, 
                     minute);
            out_mbcs = date;
            STRING temp;
            mbcs_to_utf8(out_mbcs, temp);
            out += 
              (CEGUI::String32)(reinterpret_cast<CEGUI::utf8*>(temp.c_str()));
          }

          if ("_INFOID" == idstr.substr(0, 7)) { //#{_INFOID123}
                                                 //123 表示 ItemTransferSystem
                                                 //中的ID号为123的element
            STRING infoid_str = idstr.substr(7, idend - idstart - 7); 
            int32_t infoid = atoi(infoid_str);
            out_mbcs = 
              g_game_itemtransfer_system->get_element_displayname(infoid);
            if (!out_mbcs.empty()) {
              //id
              CEGUI::utf32 idnumber = static_cast<uint32_t>(infoid);
              idnumber |= 0xE4000000;
              //display
              CEGUI::String32 temp;
              parsestring_runtime(out_mbcs, temp);
              //length
              CEGUI::utf32 idlength = 
                static_cast<uint32_t>(
                    g_game_itemtransfer_system->
                    get_elementcontents(infoid).length());
              idlength |= 0xE5000000;
              out += idnumber + temp + idlength + currentcolor;
            }
          }

          if ("_INFOUSR" == idstr.substr(0, 8)) { //#{_INFOUSRviticm}
            STRING userstr = idstr.substr(0, idend - idstart - 8);
            if (userstr == g_game_objectsystem->get_selfor_targetname()) {
              //就是自己
              STRING temp;
              mbcs_to_utf8(userstr, temp);
              out += 0xFBFFFFFF; //自己的名字显示为白色
              out += 
                (CEGUI::String32)(reinterpret_cast<CEGUI::utf8*>(temp.c_str()));
              out += currentcolor; //恢复成句子起始的颜色
            }
            else {
              vengine_game::ItemTransferSystem::element_t* element =
                g_game_itemtransfer_system->add_hyperlink(userstr, userstr);
              if (element) {
                char itemid[64] = {0};
                snprintf(itemid, 
                         sizeof(itemid) - 1, 
                         "#{_INFOID%d}", 
                         element->id);
                out_mbcs = itemid;
                CEGUI::String32 temp;
                parsestring_runtime(out_mbcs, temp);
                out += temp + currentcolor;
              }
            }
          }

          if ("_INFOMSG" == idstr.substr(0, 8)) { //#{_INFOMSG物品或珍兽说明}
            STRING contents = idstr.substr(8, idstr.size() - 8);
            STRING::size_type idend = idstr.find_first_of(key_parseid_end);
            STRING::size_type idstart = 
              idstr.find_first_of(key_parseid_start) + 1;
            STRING::size_type contentslength = idend - idstart - 8 - 3;
            vengine_game::ItemTransferSystem::element_t* element = 
              g_game_itemtransfer_system->convert_fromstring("", idstr);
            if (element) {
              char itemid[64] = {0};
              snprintf(itemid, sizeof(itemid) - 1, "#{_INFOID%d}", element->id);
              out_mbcs = itemid;
              CEGUI::String32 = temp;
              parsestring_runtime(out_mbcs, temp);
              out += temp + currentcolor;
            }
          }

          if ("_MONEY" == idstr.substr(0, 6)) { //#{_MONEY123456}
            uint32_t money;
            sscanf(idstr.c_str(), "_MONEY%d", &money);
            uint32_t goldcoin = money / 10000; //金币
            uint32_t silvercoin = (money % 10000) / 100; //银币
            uint32_t coppercoin = money % 100; //铜币
            char data[128] = {0};
            if (goldcoin != 0) {
              snprintf(data, sizeof(data) - 1, "%d#-02", goldcoin);
            }
            if (silvercoin != 0) {
              snprintf(data, sizeof(data) - 1, "%s%d#-03", data, silvercoin);
            }
            if (coppercoin != 0) {
              snprintf(data, sizeof(data) - 1, "%s%d#-04", data, coppercoin);
            }
            out_mbcs = data;
            CEGUI::String32 temp;
            parsestring_runtime(out_mbcs, temp);
            out += temp;
          }
          else { //不是特殊命令查表
            std::pair<bool, dictionarymap::iterator> is_validkey = 
              isvalid_dictionkey(idstr);
            //find it
            if (is_validkey.first) {
              //加入从key转化过来的值
              out_mbcs = is_validkey.second->second;
              CEGUI::String32 temp;
              //递归分析
              parsestring_runtimenew(out_mbcs, temp);
              out += temp;
            }
          }
          keyend = idend + 1;
        }
        else {
          //非法#{需要过滤掉
          keyend = keystart + 2;
        }
      }
      else if ("-" == keyoption) { //#-01~-99(必须是两位数值，一位数值算非法值) 
                                   //仅程序使用的表情符，
                                   //玩家输入的字符串不能使用
        STRING numberstr = sourcestr.substr(keystart + 1, 2);
        if (2 == numberstr.size() &&
            (numberstr.at(0) >= 48 && numberstr.at(0) < 57) &&
            (numberstr.at(1) >= 48 && numberstr.at(1) < 57)) {
          uint32_t number;
          sscanf(numberstr.c_str(), "%u", &number);
          if (number != 1) {
            CEGUI::utf32 val = number;
            val |= 0xE3000000;
            out += val;
            keyend = keystart + 3;
          }
          else { //-1是非法动画标识，必须从-2开始
            keyend = keystart + 1;
          }
        }
        else { //命令非法，忽略
          keyend = keystart + 1;
        }
      }
      else if (keyoption.c_str()[0] >= 48 && keyoption.c_str()[0] <= 57) {
      //#0~99 表情
        uint32_t digital = keyoption.c_str()[0] - 48;
        STRING digitalstr = sourcestr.substr(keystart + 1, 1);
        if (digitalstr.c_str()[0] >= 48  && digitalstr.c_str()[0] <= 57) {
          //两位整数
          digital = digital * 10 + (digitalstr.c_str()[0] - 48);
        }
        else { //一位整数
          keyend = keystart + 1;
        }
        CEGUI::utf32 val = digital;
        val |= 0xFA000000;
        out += val;
      }
      else { //命令非法，忽略#
        keyend = keystart;
      }
    }
    validstart = keyend;
  } //for loop

  if (blink) {
    CEGUI::utf32 val = 0xE1000000;
    out += val;
  }
}

STRING System::parsestring_varparam(const STRING& id, va_list va_pointer) {
  const kSelfMessageLengthMax = 1024;
  STRING out = "";
  std::pair<bool, dictionarymap::iterator> is_validkey = 
    isvalid_dictionkey(id);
  if (is_validkey.first) {
    if (va_pointer) {
      STRING format = is_validkey.second->second;
      char result[kSelfMessageLengthMax] = {0};
      //格式化字符串
      vsnprintf(result, 
                sizeof(kSelfMessageLengthMax) - 1, 
                format.c_str(), 
                va_pointer);
      out = result;
    }
  }
  return out;
}

STRING System::parsestring_no_varparam(const STRING& id) {
  STRINT out;
  std::pair<bool, dictionarymap::iterator> is_validkey =
    isvalid_dictionkey(id);
  if (is_validkey.first) out = is_validkey.second->second;
  return out;
}

void System::parsestring_nocolor(const STRING& in,
                                 const STRING& out,
                                 bool control) {
  const char keystart = '#';
  out.clear();
  STRING::size_type start = 0;
  STRING::size_type end = in.find_first_of(keystart);
  STRING::size_type length = in.size();
  for (;;) {
    if (STRING::npos == end) {
      //copy last
      out += in.substr(start);
    }
    //copy normal
    out += in.substr(start, end - start);
    //get option
    STRING option = in.substr(end + 1, 1);
    //skip colors
    if ("R" == option ||
        "G" == option ||
        "B" == option ||
        "K" == option ||
        "Y" == option ||
        "W" == option) {
      end += 2;
    }
    else if ("c" == option || "e" == option) {
      end += 8;
    }
    else if (control && 
             ("b" == option || 
              "u" == option || 
              "r" == option || 
              "n" == option)) {
      end += 2;
    }
    else { //not color means
      out += in.at(end); //same as out += keystart
      end += 1;
    }
    if (end >= length) break;
    start = end; //new start position
    end = in.find(keystart, start);
  } //for loop
}

STRING System::get_talktemplate(const STRING& key, uint32_t index) {
  STRING out = "";
  if (!key.empty()) {
    talktemplate_map::iterator iterator = talktemplate_table_.find(key);
    if (iterator != talktemplate_table_.end() &&
        index < (iterator->second).size()) {
      out = (iterator->second)[index];
    }
  }
  return out;
}

STRING System::get_talkrand_helpmessage() {
  talktemplate_map::iterator iterator = talktemplate_table_.find(
      vengine_ui::kHelpStringKey);
  if (iterator != talktemplate_table_.end()) {
    uint32_t index = 
      abs(rand() % static_cast<int32_t>((iterator->second).size()));
    return (iterator->second)[index];
  }
  return "";
}

void System::mbcs_to_utf8(const STRING& in, STRING& out) {
  auto_localeconvert_t auto_localeconvert; //设置语言环境
  out = utf::mbcs_to_utf8(in);
}

void System::utf8_to_mbcs(const STRING&in, STRING& out) {
  auto_localeconvert_t auto_localeconvert; //设置语言环境
  out = utf::utf8_to_mbcs(in);
}

void System::generate_fullmatch_table() {
  vengine_db::System* filedb_system = dynamic_cast<vengine_db::System*>(
      g_kernel->getnode("bin\\dbc"));
  VENGINE_ASSERT(filedb_system);
  const vengine_db::File* fullmatch_filter = filedb_system->get(
      vengine_db::structs::other::kFullMatchFilterId);
  VENGINE_ASSERT(fullmatch_filter);
  int32_t i;
  typedef vengine_db::structs::other::fullmatch_filter_t fullmatch_filter_t;
  for (i = 0; i < fullmatch_filter->get_record_number(); ++i) {
    const fullmatch_filter_t* line = 
      reinterpret_cast<fullmatch_filter_t*>(
          fullmatch_filter->search_line_equal(i));
    fullmatch_map::iterator iterator = fullmatch_table_.find(line->type);
    //创建新的类型
    if (iterator == fullmatch_table_.end()) {
      fullmatch_template_set talktemplate;
      fullmatch_table_.insert(std::make_pair(line->type, talktemplate));
      iterator = fullmatch_table_.find(line->type);
    }
    //添加字串
    fullmatch_template_set& strset = iterator->second;
    strset->insert(line->text);
  } //for loop
}

void System::generate_talktemplate_table() {
  dictionarymap::iterator iterator = dictionarytable_.begin();
  talktemplate_map talktemplate;
  STRING talkkey;
  for (;iterator != dictionarytable_.end(); ++iterator) {
    //聊天快捷模板发现
    if ("TALK_" == (iterator->first).substr(0, 5)) {
      talkkey = (iterator->first).substr(5, 
                                        (iterator->first).find("_", 6) - 
                                        (iterator->first).find("_") - 1);
      talktemplate_map::iterator template_iterator = 
        talktemplate_table_.find(talkkey);
      if (template_iterator == talktemplate_table_.end()) {
        INT idmax = (vengine_ui::kHelpStringKey == talkkey) ? 
                     vengine_ui::kHelpStringMax : 
                     vengine_ui::kTalkTemplateMax;
        int32_t id;
        for (id = 0; id < idmax; ++id) {
          char number[4] = {0};
          snprintf(number, 4, "%03d", id + 1);
          STRING findstr = "TALK_" + talkkey + "_" + number;
          dictionarymap::iterator _iterator dictionarytable_.find(talkkey);
          if (_iterator != dictionarytable_.end()) {
            talktemplate.push_back(_iterator->second);
            dictionarytable_.erase(_iterator);
          }
          else {
            if (vengine_ui::kTalkTemplateMax == idmax) {
              talktemplate.push_back("");
            }
          }
        } //for loop

        talktemplate_table_.insert(std::make_pair(talkkey, talktemplate));
        talkkey.clear();
        iterator = dictionarytable_.begin();
      }
      else {
        dictionarytable_.erase(++iterator); //模板书写错误，移除
      }
    }
  } //for loop
}

STRING modify_chattemplate(const STRING& source, 
                           const STRING& talker, 
                           const STRING& target) {
  const char keystart = '$';
  STRING::size_type start = 0;
  STRING::size_type end = source.find_first_of(keystart); //not true end,
                                                          //as vector iterator
  STRING::size_type length = source.size();
  STRING out;
  out.clear();
  for (;;) {
    if (STRING::npos == end) {
      //copy last
      out += source.substr(start);
      break;
    }
    //copy normal
    out += source.substr(start, end - start);
    //get option
    STRING option = source.substr(end + 1, 1);
    
    //replace talker
    if ("N" == option) {
      out += talker;
      end += 2;
    }
    else if ("n" == option) {
      out += target;
      end += 2;
    }
    else {
      //ignore wrong '$'
      end += 1;
    }
    if (end >= length) break;
    //save new begin point 
    start = end;
    //find next keystart
    end = source.find(keystart, start);
  } //for loop
  return out;
}

void System::parsestring_reverseruntime(const CEGUI::String32& in, 
                                        STRING& out) {
  /**
   *
   * 0xE4000000 item element标识物品信息开始
   * 0xE5000000 item element标识物品信息结束
   * 
   * example: 0xE4id0xE5length
   * length always empty, because we don't need this message.
   *
   * */
  static CEGUI::String32 infostart = (CEGUI::utf8*)"#{_INFOID";
  static CEGUI::String32 infoend = (CEGUI::utf8*)"}";
  CEGUI::String32 temp;
  temp.erase();
  size_t i;
  for (i = 0; i < in.size(); ++i) {
    CEGUI::utf32 code = in[i];
    CEGUI::utf32 type = (in[i] >> 24) & 0xFF;
    if (0xE4 == type) {
      temp += infostart;
      char id[16] = {0};
      snprintf(id, 15, "%d", code & 0x00FFFFFF);
      temp += (CEGUI::utf8*)id;
    }
    else if (0xE5 == type) {
      temp += infoend;
    }
    else {
      temp += in[i];
    }
  } //for loop
  utf8_to_mbcs(temp.c_str(), out);
}

void parsestring_elementonly_runtime(const STRING& in, CEGUI::String32& out) {
  const char keyparse = '#';
  const char key_parsestart = '{';
  const char key_parseid_end = '}';
  STRING::size_type validstart = 0;
  STRING out_mbcs = "";
  //检查字符串合法性
  STRING sourcestr;
  check_stringcode(in, sourcestr);
  for (;;) {
    if (validstart > sourcestr.size()) break;
    STRING::size_type validend = sourcestr.find(keyparse, validstart);
    //最后一段正常值
    if (STRING::npos == validend) {
      out_mbcs = sourcestr.substr(validstart);
      STRING temp;
      mbcs_to_utf8(out_mbcs, temp);
      out += (CEGUI::String32)(
          reinterpret_cast<CEGUI::utf8*>(temp.c_str());
      break;
    }
    STRING::size_type keystart = validend + 1; //"#"后面那个字符的位置
    STRING::size_type keyend; //下一个非指令字符的位置

    //合法的Key描述
    if (keystart != STRING::npos) {
      STRING keyoption = sourcestr.substr(keystart, 1);
      CEGUI::utf32 val = 0;
      if (keyoption.c_str()[0] == key_parseid_start) {
        STRING::size_type idstart = keystart + 1;
        STRING::size_type idend = sourcestr.find(key_parseid_end, idstart);
        if (idend != STRING::npos) {
          STRING idstr = sourcestr.substr(idstart, idend - idstart);
          if ("_INFOID" == idstr.substr(0, 7)) { //#{_INFOID123}
                                                 //例如：123 表示 
                                                 //ItemTransferSystem中的ID号
                                                 //为123的Element
            STRING infoid_str = idstr.substr(7, idend - idstart - 7);
            int32_t infoid = atoi(infoid_str.c_str());
            out_mbcs = 
              g_game_itemtransfer_system->get_element_displayname(infoid);
            if (!out_mbcs.empty()) {
              
            }
          }
        }
      }
    }

  } //for loop
}

} //namespace vgui_string
