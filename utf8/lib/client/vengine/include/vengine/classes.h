/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2014 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com/viticm.ti@gmail.com>
 * @date 2014-4-8 10:30:41
 * @uses vengine all class in here for exports
 *       cn: 这里集成了引擎最基本的类定义，供外部调用
 */
#ifndef VENGINE_CLASSES_H_
#define VENGINE_CLASSES_H_

#include "vengine/config.h"

namespace vengine_kernel {
class Base;
class Node;
}; //namespace vengine_kernel

namespace input {
class System;
}; //namespace input

namespace vengine_game {
class WorldSystem;
class Interface;
class EventSystem;
class ItemTransferSystem;

namespace object {
class Base;
class BaseSystem;
class FakeSystem;
}; //namespace object

namespace data_pool {
class Base;
class Ui;
}; //namespace data_pool

namespace action {
class Reference;
class Item;
class System;
}; //namespace action;

}; //namespace vengine_game

namespace vengine_render {
class EntityNode;
class System;
}; //namespace vengine_render

namespace vengine_time {
class System;
}; //namespace vengine_time

namespace vengine_sound {
class Buffer;
class Source;
class System;
}; //namespace vengine_sound

namespace vengine_db {
class System;
class File;
}; //namespace vengine_db

namespace vengine_variable {
class Base;
}; //namespace vengine_variable

namespace vengine_capability {
class Debuger;
}; //namespace vengine_capability

namespace vengine_ui {
class System;
}; //namespace vengine_ui

namespace vengine_cursor {
class CreatureHeadBoard;
class System;
}; //namespace vengine_cursor

namespace vengine_script {
class System;
}; //namespace vengine_script

namespace vengine_helper {
class System;
}; //namespace vengine_helper

namespace vengine_resource {
class Provider;
}; //namespace vengine_resource

#endif //VENGINE_CLASSES_H_
