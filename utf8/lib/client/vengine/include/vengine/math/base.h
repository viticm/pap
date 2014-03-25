/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id math.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-12 11:15:08
 * @uses the base config macros and defines, also with system include
 */
#ifndef VENGINE_MATH_BASE_H_
#define VENGINE_MATH_BASE_H_

#include "vengine/config.h"

namespace vengine_math {

namespace base {

struct VENGINE_API twofloat_vector_t {
 public:
   inline twofloat_vector_t& operator = (const twofloat_vector_t& vector) {
     x = vector.x;
     y = vector.y;
     return *this;
   }

   inline bool operator == (const twofloat_vector_t& vector) const {
     return (x == vector.x && y == vector.y);
   }

   inline bool operator != (const twofloat_vector_t& vector) const {
     return ( x != vector.x || y != vector.y );
   }

   inline twofloat_vector_t operator + 
     (const twofloat_vector_t& vector) const {
     twofloat_vector_t sum;
     sum.x = x + vector.x;
     sum.y = y + vector.y;
     return sum;
   }

   inline twofloat_vector_t operator - 
     (const twofloat_vector_t& vector) const {
     twofloat_vector_t diff;
     diff.x = x - vector.x;
     diff.y = y - vector.y;
     return diff;
   }

   inline twofloat_vector_t operator * (float scalar ) const {
     twofloat_vector_t prod;
     prod.x = scalar * x;
     prod.y = scalar * y;
     return prod;
   }

   inline friend twofloat_vector_t operator * 
     (float scalar, const twofloat_vector_t& vector) {
     twofloat_vector_t prod;
     prod.x = scalar * vector.x;
     prod.y = scalar * vector.y;
     return prod;
   }

   inline float length() const;
   float normalise(float aimlength = 1.0f);
 public:
   twofloat_vector_t() : x(0.0f), y(0.0f) {}
   twofloat_vector_t(float _x, float _y) : x(_x), y(_y) {}
 public:
   float x; 
   float y;
};

//tow int32_t vector struct
struct VENGINE_API twoint_vector_t {
 public:
   twoint_vector_t() : x(0), y(0) {}
   twoint_vector_t(int32_t _x, int32_t _y) : x(_x), y(_y) {}
 public:
   int32_t x; 
   int32_t y;
};

struct VENGINE_API threefloat_vector_t {
 public:
   inline threefloat_vector_t& operator = 
     (const threefloat_vector_t& vector) {
     x = vector.x;
     y = vector.y;
     z = vector.z;            
     return *this;
   }

   inline bool operator == ( const threefloat_vector_t& vector) const {
     return (x == vector.x && y == vector.y && z == vector.z);
   }

   inline bool operator != ( const threefloat_vector_t& vector ) const {
     return (x != vector.x || y != vector.y || z != vector.z);
   }

   inline threefloat_vector_t operator + 
     (const threefloat_vector_t& vector) const {
     threefloat_vector_t sum;
     sum.x = x + vector.x;
     sum.y = y + vector.y;
     sum.z = z + vector.z;
     return sum;
   }

   inline threefloat_vector_t operator - 
     (const threefloat_vector_t& vector) const {
     threefloat_vector_t diff;
     diff.x = x - vector.x;
     diff.y = y - vector.y;
     diff.z = z - vector.z;
     return diff;
   }

   inline threefloat_vector_t operator * (const float& mult) const {
     threefloat_vector_t vector;
     vector.x = x * mult;
     vector.y = y * mult;
     vector.z = z * mult;
     return vector;
   }

   inline float length() const;

   float normalise(float aimlength = 1.0f);

 public:
   threefloat_vector_t() : x(0.0f), y(0.0f), z(0.0f) {}
   threefloat_vector_t(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
 public:
   float x; 
   float y; 
   float z;
};

struct VENGINE_API threeint_vector_t {
 public:
   threeint_vector_t() : x(0), y(0), z(0) {}
   threeint_vector_t(int32_t _x, int32_t _y, int32_t _z) : 
     x(_x), y(_y), z(_z) {}
 public:
   int32_t x; 
   int32_t y; 
   int32_t z;
};


struct VENGINE_API floatray {
 public:
   threefloat_vector_t origin;
   threefloat_vector_t direction;
};

}; //namespace base

}; //namespace vengine_math

#endif //VENGINE_MATH_BASE_H_
