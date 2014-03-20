/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-19 16:52:24
 * @uses vengine cursor system module
 */
#ifndef VENGINE_CURSOR_SYSTEM_H_
#define VENGINE_CURSOR_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

namespace vengine_cursor {

typedef enum {
  kTypeWinBase = 0,
  kTypeNormal, //普通
  kTypeAutoRun, //自动行走中
  kTypePickup, //拾取物品
  kTypeUnreachable, //区域无法访问
  kTypeMine, //采矿
  kTypeHerbs, //采药
  kTypeTalk, //对话
  kTypeInteract, //齿轮
  kTypeRepiar, //修理
  kTypeHover, //鼠标激活（挂接物品）
  kTypeIdentify, //鉴定
  kTypeRing, //技能环
  kTypeDirection, //方向
  kTypeNumber
} type_enum; //指针类型定义

class VENGINE_API System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   virtual void set(type_enum type) = 0;
   virtual HCURSOR get() = 0;

   /* enter ui control model */
   virtual void enterui(HCURSOR hcursor) = 0;
   virtual void leaveui() = 0;

   /* 应WM_SETCURSOR */
   virtual void onset() = 0;
   /* 显示或隐藏 */
   virtual void show(bool flag) = 0;

};

}; //namespace vengine_cursor

#endif //VENGINE_CURSOR_SYSTEM_H_
