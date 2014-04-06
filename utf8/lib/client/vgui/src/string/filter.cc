#include "vengine/game/itemtransfer_system.h"
#include "vgui/string/filter.h"

namespace vgui_string {

void Filter::addinclude(const char* str) {
  if (str) includefilter_.push_back(str);
}

void Filter::add_fullmatch(const char* str) {
  if (str) fullmatch_filter_.insert(str);
}

void Filter::clean() {
  includefilter_.clear();
  fullmatch_filter_.clear();
}

bool Filter::isinclude(const STRING& str) {
  STRING::size_type totalsize = includefilter_.size();
  STRING::size_type i;
  for (i = 0; i < totalsize; ++i) {
    if (str.find(includefilter_[i]) != STRING::npos) return true;
  }
  return false;
}

bool Filter::is_fullmatch(const STRING& str) {
  if (fullmatch_filter_.find(str) != fullmatch_filter_.end()) return true;
  return false;
}

void Filter::replace_tosign(const STRING& in, STRING& out) {
  const char startkey = '#';
  const char contentend = '}';
  STRING iteminfo_str = "_INFOID"; //物品对象字符串,替换为物品
  STRING messageinfo_str = "_INFOMSG"; //消息对象字符串，将替换为消息
  uint8_t itemlength = static_cast<uint8_t>(iteminfo_str.size());
  uint8_t messagelength = static_cast<uint8_t>(messageinfo_str.size());

  std::vector<stringreplace_t> stringreplaces; //分割来源字符串
  STRING sourcestr = in;
  stringreplace_t stringreplace;
  STRING::size_type b = 0;
  STRING::size_type c = 0;
  STRING::size_type e = sourcestr.find_first_of(startkey);
  STRING::size_type length = sourcestr.size();
  for (;;) {
    if (STRING::npos == e) {
      //the last
      stringreplace.replaced = true;
      stringreplace.str = sourcestr.substr(c);
      stringreplaces.push_back(stringreplace);
      break;
    }
    STRING operatorstr = sourcestr.substr(e + 1, 1);
    if ("{" == operatorstr) { //ok, check magic #{} string.
      //item element is valid. ex: #{_INFOID123}
      STRING itemelement = sourcestr.substr(e + 2, itemlength);
      //info message is valid. ex: #{_INFOMSGxxxxxx}
      STRING messageinfo = sourcestr.substr(e + 2, messagelength);
      if (iteminfo_str == itemelement) {
        STRING::size_type idend = sourcestr.find(contentend, 
                                                 e + 2 + itemlength);
        if (e + 2 + itemlength >= length) {
          e += 2;
          goto lengthover;
        }
        STRING id = sourcestr.substr(e + 2 + itemlength, 
                                     idend - e - 2 - itemlength);
        int32_t itemid = atoi(id.c_str());
        if (g_game_itemtransfer_system->is_elementexist(itemid)) {
          //0. push normal replace str 
          stringreplace.replaced = true;
          stringreplace.str = sourcestr.substr(c, e - c);
          stringreplaces.push_back(stringreplace);
          //1. push no replace str
          stringreplace.replaced = false;
          stringreplace.str = sourcestr.substr(e, idend - e + 1);
          stringreplaces.push_back(stringreplace);
        }
        //step to new point.
        e = idend + 1;
        c = e;
      }
      else if (messageinfo_str == itemelement) {
        //get info message
        int32_t contentlength = atoi(
            sourcestr.substr(e + 2 + messagelength, 3).c_str());
        STRING::size_type idend = e + 2 + messagelength + 3 + contentlength;
        if (e + 2 + messagelength >= length) {
          e += 2;
          goto lengthover;
        }
        //ok, valid info message found.
        //0. push normal replace str
        stringreplace.replaced = true;
        stringreplace.str = sourcestr.substr(c, e - c);
        stringreplaces.push_back(stringreplace);
        //1. push no replace str
        stringreplace.replaced = false;
        stringreplace.str = sourcestr.substr(e, idend - e + 1);
        stringreplaces.push_back(stringreplace);
        //step to new point.
        e = idend + 1;
        c = e;
      }
      else {
        e += 2;
      }
    }
    else {
        e += 1;
    }
lengthover:
    if (e >= length) {
      if (c != e) {
        //push last replace str
        stringreplace.replaced = true;
        stringreplace.str = sourcestr.substr(c);
        stringreplaces.push_back(stringreplace);
      }
      break;
    }
    //save new begin point
    b = e;
    //find next keystart
    e = sourcestr.find(startkey, b);
  }

  //替换非法字符
  uint32_t i;
  for (i = 0; i < static_cast<uint32_t>(stringreplaces.size()); ++i) {
    if (true == stringreplaces[i].replaced) {
      STRING oldstr = stringreplaces[i].str;
      replace_tosign_normal(oldstr, stringreplaces[i].str);
    }
  }
  out.clear(); //输出
  for (i = 0; i < static_cast<uint32_t>(stringreplaces.size()); ++i) {
    out += stringreplaces[i].str;
  }
}

void Filter::replace_tosign_normal(const STRING& in, STRING& out) {
  static STRING sign = "?";
  static uint8_t ansistart = 0X20;
  static uint8_t ansiend = 0X80;
  out = in;
  STRING::size_type totalsize = includefilter_.size();
  STRING::size_type i;
  //包含替换
  for (i = 0; i < totalsize; ++i) {
    STRING::size_type position = in.find(includefilter_[i]);
    while (position != STRING::npos) {
      STRING replace = "";
      STRING::size_type length = includefilter_[i].size();
      //如果包含替换的是1个字节的ANSI字节，替换前，
      //需要确认前一个字节一定不是双字节字符集的前一个字节
      bool skip = false;
      if (1 == length && position > 0) {
        int8_t _char = in[position - 1];
        //不是标准ANSI英文字符
        if (!(_char >= ansistart 
              && _char <= ansiend || 
              '\r' == _char || 
              '\n' == _char || 
              '\t' == _char)) {
          skip = true;
        }
      }
      if (!skip) {
        for (STRING::size_type j = 0; j < length; ++j, replace += sign);
        out.replace(position, length, replace);
      }
      position = in.find(includefilter_[i], position + length);
    }
  } //include replace

  //完全匹配替换
  if (is_fullmatch(in)) {
    STRING::size_type length = in.size();
    out.clear();
    for (i = 0; i < length; ++i, out += sign);
  }
}

void Filter::replace_tosign_new(const STRING& in, STRING& out) {
  static STRING signs = "~$%^&(){}`-_+=?,.<>";
  out = in;
  //包含替换
  STRING::size_type i;
  STRING::size_type totalsize = includefilter_.size();
  for (i = 0; i < totalsize; ++i) {
    STRING::size_type position = in.find(includefilter_[i]);
    while (position != STRING::npos) {
      STRING replace = "";
      STRING::size_type length = includefilter_[i].size();
      for(STRING::size_type j = 0; j < length; ++j) {
        STRING::size_type randsize = rand() % int32_t(signs.size());
        replace += signs.at(randsize);
      }
      out.replace(position, length, replace);
      position = in.find(includefilter_[i], position + length);
    }
  }
  //完全匹配替换
  if (is_fullmatch(in)) {
    STRING::size_type length = in.size();
    out.clear();
    for (i = 0; i < length; ++i) {
      STRING::size_type randsize = rand() % int32_t(signs.size());
      out += signs.at(randsize);
    }
  }
}

} //namespace vgui_string
