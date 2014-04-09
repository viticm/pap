/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id util.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-18 15:33:08
 * @uses vengine base util functions
 */
#ifndef VENGINE_BASE_UTIL_H_
#define VENGINE_BASE_UTIL_H_

#include "vengine/config.h"
#include "vengine/math/base.h"

#define PI (3.1415926535)
#define FLOATMIN (1.0E-9)

namespace vengine_base {

namespace util {

VENGINE_API void savelog(const char* format , ...);


 
//将字符串按照关键字分割
VENGINE_API int32_t convertstring_tovector(const char* str, 
                                           std::vector<STRING>& save, 
                                           const char* key = "\\/", 
                                           bool one_ofkey = true, 
                                           bool ignoreempty = true);


//取得两点间的距离
VENGINE_API float getdistance(
    const vengine_math::base::twofloat_vector_t& position1, 
    const vengine_math::base::twofloat_vector_t& position2);
VENGINE_API float getdistance(
    const vengine_math::base::threefloat_vector_t& position1, 
    const vengine_math::base::threefloat_vector_t& position2);

//取得两点间的距离平方
VENGINE_API float get_squaredistance(
    const vengine_math::base::twofloat_vector_t& position1, 
    const vengine_math::base::twofloat_vector_t& position2);

VENGINE_API float get_squaredistance(
    const vengine_math::base::threefloat_vector_t& position1, 
    const vengine_math::base::threefloat_vector_t& position2);

template<class T, class U, class V>  
  inline void clamp(T &v, const U &min, const V &max) {
  v = (v < min) ? min : v;
  v = (v > max) ? max : v;
}


//求两个向量的点积
inline float get_dotproduct(
    const vengine_math::base::twofloat_vector_t& vector1, 
    const vengine_math::base::twofloat_vector_t& vector2) {
  return vector1.x * vector2.x + vector1.y * vector2.y;
}

/*
|
|  取得从Pos1到Pos2的矢量相对于Y轴的旋转角度, 以z轴为0度
|   
|              ->x
|                  o pos1
|          |       |\
|       z  v       |  \
|                  |    \
|                  |      \
|                  |        o pos2
|
|  Return [0 ~ 2pi)
*/

VENGINE_API float get_Yangle(
    const vengine_math::base::twofloat_vector_t& position1, 
    const vengine_math::base::twofloat_vector_t& position2);

/*
|
|  取得从Pos1与Pos2之间的中心点
|        
|             ->x
|                    o pos2
|          |       /    
|       z  v      o <- This point!    
|               /    
|              o 
|             pos1        
|
*/
VENGINE_API vengine_math::base::threefloat_vector_t getcenter(
    const vengine_math::base::threefloat_vector_t& position1, 
    const vengine_math::base::threefloat_vector_t& position2);


/*
|
|  取得v1相对于从Pos1与Pos2之间直线的镜像点
|        
|             ->x
|                       o pos2
|        |  v1        /    
|     z  v    \     / 
|                \/     
|               /  \
|              o      \ 
|             pos1      v2  <- This point!    
|
*/
VENGINE_API vengine_math::base::twofloat_vector_t getreflect(
    const vengine_math::base::twofloat_vector_t& position1, 
    const vengine_math::base::twofloat_vector_t& position2, 
    const vengine_math::base::twofloat_vector_t& vector1);

//从内存中读取一行文本(相当于fgets)
VENGINE_API const char* getline_frommemory(char* buffer, 
                                           int32_t size, 
                                           const char* memory, 
                                           const char* deadend);

VENGINE_API bool sheckstring_valid(const char* str);

/*
|  使目标点根据方向轴旋转，返回旋转后的坐标。
|
|  position    要旋转的目标点坐标
|  axis  以原点为起点的矢量方向轴
|  angle  旋转的角度
|  
|  注：axis会被单位化，变以原点为起始点的矢量方向。如果想根据任意轴做旋转，
|    需要先将目标点做相应的平移，调用该函数旋转后，再平移回去即可。
|
*/
VENGINE_API vengine_math::base::threefloat_vector_t rotateangle(
    const vengine_math::base::threefloat_vector_t& position, 
    const vengine_math::base::threefloat_vector_t& axis, 
    float angle);


/*
|  hermite曲线差值算法。曲线被划分为150段，返回所需段数的2D坐标位置
|
|  x1,y1,x2,y2      曲线端点，最好数值限制在1000以内，否侧运算时会超出运算范围
|  xr1,yr1,xr2,yr2    曲线两参考向量, 最好限制在1000以内  
|  currentiter      当前段数，值限定在150以内。
*/ 
//win32 POINT
POINT hermitecurve(int32_t x1, 
                   int32_t y1, 
                   int32_t x2, 
                   int32_t y2, 
                   int32_t xr1, 
                   int32_t yr1, 
                   int32_t xr2, 
                   int32_t yr2, 
                   int32_t currentiter);

//同 hermitecurve
POINT beziercurve(int32_t x1, 
                  int32_t y1, 
                  int32_t x2, 
                  int32_t y2, 
                  int32_t xr1, 
                  int32_t yr1, 
                  int32_t xr2, 
                  int32_t yr2, 
                  int32_t currentiter);



}; //namespace util

}; //namespace vengine_base

#endif //VENGINE_BASE_UTIL_H_
