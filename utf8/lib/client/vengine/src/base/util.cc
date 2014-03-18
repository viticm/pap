#include <stdio.h>
#include "vengine/exception/base.h"
#include "vengine/base/util.h"

namespace vengine_base {

namespace util {

void savelog(const char* format, ...) {
  FILE* fp = fopen(""VENGINE_MODULENAME".log", "a");
  if (!fp) fp = fopen(""VENGINE_MODULENAME".log", "w");
  if (!fp) return;
  char temp[1024] = {0};
  va_list vapointer;
  va_start(vapointer, format);
  vsnprintf(temp, sizeof(temp) - 1, format, vapointer);
  va_end(vapointer);
  //for windows, if also work in linux please see server timemanager
  SYSTEMTIME nowtime;
  ::GetLocalTime(&nowtime);
  fprintf(fp, 
          "[%02d_%02d:%02d:%02d]: %s"LF"", 
          nowtime.wDay, 
          nowtime.wHour, 
          nowtime.wMinute, 
          nowtime.wSecond, 
          temp);
  fclose(fp);
}

//see commmon/file/database.h have it
int32_t convertstring_tovector(const char* str, 
                               std::vector<STRING>& save, 
                               const char* key, 
                               bool one_ofkey, 
                               bool ignoreempty) {
  int32_t result = 0;
  save.clear();
  if (!str || NULL == str[0]) return result;
  STRING sourcestr = str;
  //find first split pointer
  STRING::size_type left = 0;
  STRING::size_type right;
  if (one_ofkey) {
    right = sourcestr.find_first_of(key);
  }
  else {
    right = sourcestr.find(key);
  }
  if (right == STRING::npos) {
    right = sourcestr.length();
  }
  for (;;) {
    STRING item = sourcestr.substr(left, right - left);
    if (item.length() > 0 || !ignoreempty) {
      save.push_back(item);
    }
    if (right == sourcestr.length()) break;
    
    left = right + (one_ofkey ? 1 : strlen(key));
    if (one_ofkey) {
      STRING temp = sourcestr.substr(left);
      right = temp.find_first_of(key);
      if (right != STRING::npos) right += left;
    }
    else {
      right = sourcestr.find(key, left);
    }
    if (STRING::npos == right) right = sourcestr.length();
  }
  result = static_cast<int32_t>(save.length());
  return result;
}
//取得两点间的距离
float getdistance(
    const vengine_math::base::twofloat_vector_t& position1, 
    const vengine_math::base::twofloat_vector_t& position2) {
  float result = .0f;
  result = sqrtf((position1.x - position2.x) * (position1.x - position2.x) + 
           (position1.y - position2.y) * (position1.y - position2.y));
  return result;
}

float getdistance(
    const vengine_math::base::threefloat_vector_t& position1, 
    const vengine_math::base::threefloat_vector_t& position2) {
  float result = .0f;
  result = sqrtf((position1.x - position2.x) * (position1.x - position2.x) + 
           (position1.y - position2.y) * (position1.y - position2.y) + 
           (position1.z - position2.z) * (position1.z - position2.z));
  return result;
}

//取得两点间的距离平方
float get_squaredistance(
    const vengine_math::base::twofloat_vector_t& position1, 
    const vengine_math::base::twofloat_vector_t& position2) {
  float result = .0f;
  result = (position1.x - position2.x) * (position1.x - position2.x) + 
           (position1.y - position2.y) * (position1.y - position2.y);
  return result;
}

float get_squaredistance(
    const vengine_math::base::threefloat_vector_t& position1, 
    const vengine_math::base::threefloat_vector_t& position2) {
  float result = .0f;
  result = (position1.x - position2.x) * (position1.x - position2.x) + 
           (position1.y - position2.y) * (position1.y - position2.y) +
           (position1.z - position2.z) * (position1.z - position2.z);
  return result;
}

float get_Yangle(const vengine_math::base::twofloat_vector_t& position1, 
                 const vengine_math::base::twofloat_vector_t& position2) {
  double distance = static_cast<double>(getdistance(position1, position2));
  float result = .0f
  if (distance <= 0.0f) return result;
  double _acos = (position2.y - position1.y) / distance;
  if (_acos > 1.0) _acos = 0.0;
  if (_acos < -1.0) _acos = PI;
  if (_acos > -FLOATMIN && _acos < FLOATMIN) {
    if (position2.x > position1.x) {
      result = static_cast<float>(PI / 2.0);
      return result;
    }
    else {
      result = -static_cast<float>(PI / 2.0);
      return result;
    }
  }
  _acos = ::acos(_acos);
  //[0~180]
  if (position2.x >= position1.x) {
    result = static_cast<float>(_acos);
  }
  else {
    result = static_cast<float>(2 * PI - _acos);
  }
  return result;
}

vengine_math::base::threefloat_vector_t getcenter(
    const vengine_math::base::threefloat_vector_t& position1, 
    const vengine_math::base::threefloat_vector_t& position2) {
  vengine_math::base::threefloat_vector_t result;
  result.x = (position1.x + position2.x) / 2.0f;
  result.y = (position1.y + position2.y) / 2.0f;
  result.z = (position1.z + position2.z) / 2.0f;
  return result;
}

vengine_math::base::twofloat_vector_t getreflect(
    const vengine_math::base::twofloat_vector_t& position1, 
    const vengine_math::base::twofloat_vector_t& position2, 
    const vengine_math::base::twofloat_vector_t& vector1) {
   //position1 -> position2
  vengine_math::base::twofloat_vector_t normal = position2 - position1;
  normal.normalise();
  //position1 -> vector1
  vengine_math::base::twofloat_vector_t line1 = vector1 - position1;
  // position1 -> vector2
  vengine_math::base::twofloat_vector_t line2 = 
    2 * get_dotproduct(line1, normal)* normal - line1;
  //return vector2
  return line2 + position1;
} 

const char* getline_frommemory(char* buffer, 
                               int32_t size, 
                               const char* memory, 
                               const char* deadend) {
  //search next lf
  register const char* _memory = memory;
  if (_memory > deadend || 0 == *_memory) return NULL;
  while (_memory < deadend && 
         _memory - memory + 1 < size &&
         *_memory != 0 && 
         *_memory != '\r' && 
         *_memory != '\n') 
    *(++buffer) = *(++_memory);
  *buffer = 0;
  while (_memory < deadend && 
         *_memory != 0 && 
         ('\r' == *_memory || '\n' == *_memory)) _memory++;
  return _memory;
}

bool sheckstring_valid(const char* str) {
  const char* invalid = " #\\/`~!@~$%^&*()-_+=|{}[];:'\"<>,.?";
  const char* hz_blank = "　"; //中文空格
  if (NULL == str) return false;
  STRING sourcestr(str);
  if (sourcestr.empty()) return false;
  //查找是否有非法ascii字符
  STRING::size_type invalidposition = sourcestr.find_first_of(invalid);
  if (invalidposition == STRING::npos) {
    invalidposition = sourcestr.find(hz_blank);
  }
  return STRING::npos == invalidposition;
}

vengine_math::base::threefloat_vector_t rotateangle(
    const vengine_math::base::threefloat_vector_t& position, 
    const vengine_math::base::threefloat_vector_t& axis, 
    float angle) {
  const vengine_math::base::threefloat_vector_t vector = position;  
  vengine_math::base::threefloat_vector_t unitaxis  = axis;
  unitaxis.normalise();
  const float halfangle = angle / float(2);
  const float s = sin(halfangle);
  const float c = cos(halfangle);
  const float x = unitaxis.x * s;
  const float y = unitaxis.y * s;
  const float z = unitaxis.z * s;
  const float w = c;
  const float xx = x * x;
  const float xy = y * x;
  const float xz = z * x;
  const float yy = y * y;
  const float yz = z * y;
  const float zz = z * z;
  const float wx = w * x;
  const float wy = w * y;
  const float wz = w * z;
  const float M[3][3] = {
    { 
      float(1 )- float(2) * (yy + zz), 
      float(2) * ( xy - wz), 
      float(2) * ( xz + wy)
    },
    { 
      float(2) * ( xy + wz), 
      float(1) - float(2) * (xx + zz),
      float(2) * (yz - wx)
    },
    {
      float(2) * (xz - wy),
      float(2) * (yz + wx),
      float(1) - float(2) * (xx + yy)
    },
  };

  return vengine_math::base::threefloat_vector_t( 
    vector.x * M[0][0] + vector.y * M[0][1] + vector.z * M[0][2],
    vector.x * M[1][0] + vector.y * M[1][1] + vector.z * M[1][2],
    vector.x * M[2][0] + vector.y * M[2][1] + vector.z * M[2][2]);
}

POINT hermitecurve(int32_t x1, 
                   int32_t y1, 
                   int32_t x2, 
                   int32_t y2, 
                   int32_t xr1, 
                   int32_t yr1, 
                   int32_t xr2, 
                   int32_t yr2, 
                   int32_t currentiter) {
  const int32_t iterative  = 150; //曲线仿真的线数(控制在150以内， 否则算法出错) 
  const int32_t iterative2 = iterative * iterative;  
  const int32_t iterative3 = iterative2 * iterative;

  if (currentiter > iterative) currentiter = iterative;

  int32_t oldx = x1,
      oldy  = y1,
      m1    = iterative3,
      m2    = 0,
      m3    = 0,
      m4    = 0,
      k1    = 0,
      k2    = 0;
  POINT point;
  
  for (int32_t i = 0; i < 150; ++i) {
    k1 = (i << 1) + 1;
    k2 = (k1 + i) * i + k1;  
    m4 += (k2 -= (k1 *= iterative));   
    m3 += (k1 = k2 - k1) + iterative2;   
    m2 -= (k2 += k1);
    m1 += k2;

    point.x = static_cast<int32_t>(((
            x1 * m1 + x2 * m2 + xr1 * m3 + xr2 * m4) / iterative3));
    point.y = static_cast<int32_t>(((
            y1 * m1 + y2 * m2 + yr1 * m3 + yr2 * m4) / iterative3));    
    if (i >= currentiter) return point;
  }
  return point;   
}

POINT beziercurve(int x1, 
                  int y1, 
                  int x2, 
                  int y2, 
                  int xr1, 
                  int yr1, 
                  int xr2, 
                  int yr2, 
                  int currentiter) {
	POINT result =  hermitecurve(x1, 
                               y1, 
                               x2, 
                               y2, 
                               3 * (xr1 - x1), 
                               3 * (yr1 - y1), 
                               3 * (x2 - xr2), 
                               3 * (y2 - yr2), 
                               currentiter);
  return result;
}

} //namespace util

} //namespace vengine_base
