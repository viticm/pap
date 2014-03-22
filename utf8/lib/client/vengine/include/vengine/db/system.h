/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id system.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-3-22 18:27:52
 * @uses vengine file database module
 */
#ifndef VENGINE_DB_SYSTEM_H_
#define VENGINE_DB_SYSTEM_H_

#include "vengine/config.h"
#include "vengine/kernel/node.h"
#include "vengine/db/file.h"

namespace vengine_db {

class VENGINE_API System : public vengine_kernel::Node {

VENGINE_KERNEL_DECLARE_DYNAMIC(System);

 public:
   virtual void open() = 0; //打开所有数据
   virtual void close() = 0; //关闭所有数据
   virtual const File* get(int32_t id) const = 0;

}; 

}; //namespace vengine_db

#endif //VENGINE_DB_SYSTEM_H_
