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
  STRING itemstr = "_INFOID"; //物品对象字符串,替换为物品
  STRING messagestr = "_INFOMSG"; //消息对象字符串，将替换为消息
  uint8_t itemlength = iteminfo_str.size();
  uint8_t messagelength = messageinfo_str.size();

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
    if ('{' == operatorstr) { //ok, check magic #{} string.
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
      else if (messagelength == itemelement) {
        //get info message
        int32_t contentlength = atoi(
            sourcestrc.substr(e + 2 + messagestr, 3).c_str());
        STRING::size_type idend = e + 2 + messagestr + 3 + contentlength;
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

} //namespace vgui_string
