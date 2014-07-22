/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id itemtransfer_system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-21 14:52:12
 * @uses vengine game item transfer system
 *       cn: 物品信息传输系统，将物品信息转换为聊天内容
 */
#ifndef VENGINE_GAME_ITEMTRANSFER_SYSTEM_H_
#define VENGINE_GAME_ITEMTRANSFER_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

namespace vengine_game {

namespace object { //object
  class Item;
};

typedef enum {
  kElementTypeInvalid = -1, //无效
  kElementTypeItemInfo, //普通物品信息
  kElementTypeHyperLink, //超链接
  kElementTypeChannel, //频道切换
  kElementTypePet, //珍兽
  kElementTypeBoss, //boss
} elementtype_enum;

typedef enum {
  kElementActionRClick, //右键点击
  kElementActionLClick, //左键点击
  kElementActionMoveIn, //鼠标移进
  kElementActionMoveOut, //鼠标移出
} elementaction_enum;

class VENGINE_API ItemTransferSystem : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(ItemTransferSystem);

 public:
   struct element_t {
     int32_t id;
     int32_t type; //类型
     int32_t objectid; //对象ID
     STRING display; //显示名称
     STRING originaldisplay; //原始未更改过的字符串
     STRING contents; //用于传入的字符串
     int32_t usecount; //用于计数，如果这个值到0则删除这个element
     element_t() : type(kElementTypeInvalid) {};
     virtual ~element_t() {};
     bool istype(int32_t _type) { return type == _type; }
     virtual STRING get_displaycolor() = 0;
     virtual STRING get_display_prefixtext() = 0;
   };

 public:
   //将一个物品转换为字符串
   virtual element_t* convet_fromitem(object::Item* item) = 0;
   //将一个珍兽转换为字符串
   virtual element_t* convert_frompet(int32_t index) = 0;
   //将字符串转换为物品
   virtual element_t* convert_fromstring(const STRING& display, 
                                        const STRING& contents) = 0;
   //添加一个超链接
   virtual element_t* add_hyperlink(const STRING& name,
                                    const STRING& content,
                                    int32_t chatype = -1) = 0;
   //添加频道
   virtual element_t* addchannel(int32_t type, const STRING& content) = 0;
   //销毁一个数据结构
   virtual void removeelement(int32_t id) = 0;
   //处理element
   virtual void doelement(int32_t id, 
                          int32_t action, 
                          int32_t messageid = -1) = 0;
   //判断element是否存在
   virtual bool is_elementexist(int32_t id) = 0;
   //获得element类型
   virtual int32_t get_elementtype(int32_t id) = 0;
   //获得element显示的名称
   virtual STRING get_element_displayname(int32_t id) = 0;
   //获得element的原始名称
   virtual STRING get_element_original_displayname(int32_t id) = 0;
   //获得element的内容
   virtual STRING get_elementcontents(int32_t id) = 0;
   //增加element的使用计数
   virtual void add_element_usecount(int32_t id) = 0;
   //获得当前选中的element对象
   virtual element_t* get_currentelement() = 0;
   virtual void reset() = 0;
};

}; //namespace vengine_game

#endif //VENGINE_GAME_ITEMTRANSFER_SYSTEM_H_
