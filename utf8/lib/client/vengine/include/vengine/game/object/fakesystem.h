/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id fakesystem.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-25 11:31:05
 * @uses vengine game fake object system class
 *       cn: 在ui上显示的物体管理器接口
 *       1. 创建/销毁在ui上显示的obj对象
 *       2. 对于需要显示的fakeobject，每桢调用渲染层渲染到texture上，
 *          并更新到ui上
 *       3. 这些object自身的逻辑操作，例如更换服装、武器等操作，
 *          需要更上层逻辑处理 
 */
#ifndef VENGINE_GAME_OBJECT_FAKESYSTEM_H_
#define VENGINE_GAME_OBJECT_FAKESYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"

namespace vengine_game {

namespace object {

class Base; //引用

class VENGINE_API FakeSystem : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(FakeSystem);

 public:
   //创建/销毁在ui上显示的obj对象
   virtual void create(const char* classname,
                       const char* objectname,
                       const char* cameraname) = 0;
   virtual void destroy(const name) = 0;
   //UI需要显示某物体
   virtual void on_ui_hook(const char* windowname,
                           const char* objectname,
                           int32_t texturewidth,
                           int32_t textureheight,
                           const char* backgroundname) = 0;
   //UI不再需要显示某物体
   virtual void on_ui_unhook(const char* windowname) = 0;

   //UI显示/隐藏
   virtual void on_ui_shown(const char* windowname, float aspectratio) = 0;
   virtual void on_ui_hiden(const char* windowname) = 0;

   //模型旋转
   virtual void rotatestart(const char* objectname, float angle) = 0;
   virtual void rotateend(const char* objectname) = 0;
   virtual STRING get_objectname(const char* windowname) = 0;

};

}; //namespace object

}; //namespace vengine_game

#endif //VENGINE_GAME_OBJECT_FAKESYSTEM_H_
