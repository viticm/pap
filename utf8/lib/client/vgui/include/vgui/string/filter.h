/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id filter.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-26 18:19:14
 * @uses vgui string filter module
 *       cn: 字符串过滤功能
 */
#ifndef VGUI_STRING_FILTER_H_
#define VGUI_STRING_FILTER_H_

#include <set>
#include "vengine/kernel/node.h"
#include "vgui/config.h"

namespace vgui_string {

class Filter {

 public:
   friend class System;

 public:
   Filter() {}
   ~Filter() {}

 public:
   void addinclude(const char* str);
   void add_fullmatch(const char* str);
   void clean();

   bool isinclude(const STRING& str); //是否包含了该字符串
   bool is_fullmatch(const STRING& str); //是否完全匹配该字符串

   //替换函数，将非法字符替换成'?'
   void replace_tosign(const STRING& in, STRING& out);
   //替换函数，将非法字符替换成'?'
   void replace_tosign_normal(const STRING& in, STRING& out);
   //替换函数，将非法字符替换成乱序的符号排列
   void replace_tosign_new(const STRING& in, STRING& out);
   bool is_include_or_fullmatch(const STRING& str);

 protected:
   typedef std::vector<STRING> includefilter;
   typedef std::set<STRING> fullmatch_filter;
   typedef struct {
     STRING str;
     bool replaced;
   } stringreplace_t;
   includefilter includefilter_;
   fullmatch_filter fullmatch_filter_;

};

}; //namespace vgui_string

#endif //VGUI_STRING_FILTER_H_
