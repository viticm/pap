/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id scene.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-25 12:01:16
 * @uses vengine game scene class
 */
#ifndef VENGINE_GAME_SCENE_H_
#define VENGINE_GAME_SCENE_H_

#include "vengine/config.h"
#include "vengine/math/base.h"

/** 引用数据表结构 **/
namespace vengine_db {

namespace structs {

namespace scene {

struct define_t;

}; //namespace scene

}; //namespace structs

}; //namespace vengine_db

namespace vengine_game {

class Scene {

public:
  //取得场景定义
  virtual const vengine_db::structs::scene::define_t* getdefine() const = 0;
  //场景位置是否合法
  virtual bool is_validposition(
      const vengine_math::base::twofloat_vector_t& position) = 0;
  //根据逻辑坐标取得地形高度，考虑行走面，如果传入坐标非法，返回false
  virtual bool get_mapheight(
      const vengine_math::base::twofloat_vector_t& position,
      float& height) = 0;

};

}; //namespace vengine_game

#endif //VENGINE_GAME_SCENE_H_
