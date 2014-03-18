#include "vengine/math/base.h"
#include <math.h>

namespace vengine_math {

namespace base {

inline float twofloat_vector_t::length() const {
  return sqrt(x * x + y * y);
}

float twofloat_vector_t::normalise(float aimlength) {
  float length = sqrt(x * x + y * y);
  //Will also work for zero-sized vectors, but will change nothing
  if (length > 1e-08) {
    float invlength = aimLength / length;
    x *= invlength;
    y *= invlength;
  }
  return length;
}

inline float threefloat_vector_t::length() const {
  return sqrt(x * x + y * y + z * z);
}

float threefloat_vector_t::normalise(float aimlength) {
  float length = sqrt(x * x + y * y + z * z);
  // Will also work for zero-sized vectors, but will change nothing
  if (length > 1e-08) {
    float invlength = aimlength / length;
    x *= invlength;
    y *= invlength;
    z *= invlength;
  }
  return length;
}

} //namespace base

} //namespace vengine_math
