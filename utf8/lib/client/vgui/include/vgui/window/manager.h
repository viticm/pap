/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id manager.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-3-11 10:12:52
 * @uses vgui window manager
 */
#ifndef VGUI_WINDOW_MANAGER_H_
#define VGUI_WINDOW_MANAGER_H_

#include "CEGUIVector.h"

#include "vengine/config.h"
#include "vengine/game/eventsystem.h"

#include "vgui/config.h"
#include "vgui/window/item.h"

namespace CEGUI {
class Window;
}; //namespace CEGUI


namespace vgui_window {

class Manager {

 public:
   Manager();
   virtual ~Manager();

 public:
   //static Manager* self_;
   static CEGUI::Window* background_sheet_; //窗口底板

 public:
   static CEGUI::Window* get_clientscreen();
   static Manager* getself();

 public:
   void init();
   void hideall(); //关闭所有窗口
   //某组ui是否处于打开中
   bool isshow(const char* uiname, const char* childname = NULL);
   Item* finditem(const STRING& name);
   void open(const STRING& name);
   void close(const STRING& name);
   void toggle(const STRING& name);
   bool reloadscript(const char* uiname);
   void demise(Item* item, bool show);
   void demisetest(Item* item, bool show);
   bool closeall();
   void on_sizechange();
   void onescape();

 protected:
   static Manager* self_;
   typedef std::list<Item*> itemlist;
   typedef std::vector<Item*> itemvector;
   //窗口的列表
   itemlist itemlist_;

};

}; //namespace vgui

#endif //VGUI_WINDOW_MANAGER_H_

