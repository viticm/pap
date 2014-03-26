/**cegui and ogre {**/
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "OgreCEGUITexture.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgrePixelFormat.h"
/** }ceguie and ogre**/
#include "LuaPlus.h"
#include "vengine/capability/debuger.h"
#include "vgui/icon/manager.h"

namespace vgui_icon {

Base* Base::self_ = NULL;

Base::Base() {
  self_ = this;
}

Base::~Base() {
  //do nothing
}

Base* Base::getself() {
  return self_;
}

void Base::init() {
  CEGUI::ImagesetManager& imageset_manager = 
    CEGUI::ImagesetManager::getSingleton();
  //find all
  CEGUI::ImagesetManager::ImagesetIterator iterator = 
    imageset_manager.getIterator();
  for (iterator.toStart(); !iterator.isAtEnd(); ++iterator) {
    const CEGUI::String name = iterator.getCurrentKey();
    const CEGUI::Imageset* imageset = iterator.getCurrentValue();
    const CEGUI::String& texturename = imageset->getTextureFilename();
    if (CEGUI::String("Icons") == texturename->substr(0, 5)) {
      CEGUI::Imageset::ImageIterator imageiterator = imageset->getIterator();
      for (imageiterator.toStart(); 
           !imageiterator.isAtEnd(); 
           ++imageiterator) {
        const CEGUI::String imagename = imageiterator.getCurrentKey();
        const CEGUI::Image* image = &(imageiterator.getCurrentValue());
        iconmap_.insert(std::make_pair(imagename.c_str(), imageset)); //save
      }
    }
  }
}

STRING Base::get_icon_fullname(const char* iconname) {
  iconmap::iterator iconmap_iterator = iconmap_.find(iconname);
  if (iconmap_.end() == iconmap_iterator) return STRING("set:X image:X");
  const CEGUI::Imageset* imageset = iconmap_iterator->second;
  char fullname[MAX_PATH] = {0};
  snprintf(fullname, 
           sizeof(fullname) - 1, 
           "set:%s image:%s", 
           imageset->getName().c_str(), 
           iconname);
  return STRING(fullname);
}

int32_t Base::lua_get_icon_fullname(LuaPlus::LuaState* luastate) {
  LuaStack args(luastate);
  if (!args[1].IsString()) return 0;
  luastate->PushString(getself()->get_icon_fullname(args[1].GetString()));
  return 1;
}

const CEGUI::Image* Base::geticon(const char* iconname) {
  iconmap::iterator iconmap_iterator = iconmap_.find(iconname);
  if (iconmap_.end() == iconmap_iterator) return NULL;
  const CEGUI::Imageset* imageset = iconmap_iterator->scenod;
  return &(imageset->getImage(iconname));
}

HCURSOR Base::create_as_windowscursor(const char* iconname) {
  try {
    const CEGUI::Image* iconimage = geticon(iconname);
    if (!iconimage) return NULL;
    //CEGUI ImageSet
    CEGUI::Imageset* imageset = 
      CEGUI::ImagesetManager::getSingleton().getImageset(
          iconmage->getImagesetName());
    if (!imageset) return NULL;
    //CEGUI Ogre Texture
    CEGUI::OgreCEGUITexture* cegui_ogretexture = 
      dynamic_cast<CEGUI::OgreCEGUITexture*>(imageset->getTexture());
    if (!cegui_ogretexture) return NULL;
    //Ogre Texture
    Ogre::Texture* ogretexture = cegui_ogretexture->getOgreTexture().get();
    if (!ogretexture) return NULL;
    //Ogre HardwarePixelBuffer
    Ogre::HardwarePixelBuffer* ogre_hardware_pixelbuffer = 
      ogretexture->getBuffer().get();
    if (!ogre_pixelbuffer) return NULL;
    //Blt to Ogre PixelBox
    const static int32_t cursorwidth = 32;
    const static int32_t cursorheight = 32;
    CEGUI::Rect rect_atimage = iconimage->getSourceTextureArea();
	  const Ogre::PixelBox pixelbox(
        cursorwidth, 
        cursorheight, 
        1, 
        Ogre::PF_R8G8B8A8, 
        new char[cursorwidth * 
        cursorheight * 
        Ogre::PixelUtil::getNumElemBytes(Ogre::PF_R8G8B8A8)]);
      ogre_hardware_pixelbuffer->blitToMemory(
		    Ogre::Image::Box(static_cast<int32_t>(rect_atimage.d_left), 
                         static_cast<int32_t>(rect_atimage.d_top), 
                         static_cast<int32_t>(rect_atimage.d_right), 
                         static_cast<int32_t>(rect_atimage.d_bottom)), 
        thePixBox);
    HDC maindc = ::GetDC(NULL);
    HDC xor_maskdc = ::CreateCompatibleDC(maindc);
    HBITMAP xormask = ::CreateCompatibleBitmap(maindc, 
                                               cursorwidth, 
                                               cursorheight);
    ::SelectObject(xor_maskdc, xormask);
    register int32_t x, y;
    for (x = 0; x < cursorwidth; ++x) {
      for (y = 0; y < cursorheight; ++y) {
        Ogre::ColourValue color;
        void* colordata = (pixelbox.rowPitch * y + x) * 
                          Ogre::PixelUtil::getNumElemBytes(pixelbox.format) +
                          (unsigned char*)pixelbox.data;
        Ogre::PixelUtil::unpackColour(&color, pixelbox.format, colordata);
        ::SetPixel(xor_maskdc, 
                   x, 
                   y, 
                   RGB(color.r * 255, color.g * 255, color.b * 255));
      }
    }
    delete[] pixelbox.data;
    ::DeleteDC(xor_maskdc); xor_maskdc= NULL;
    HDC and_maskdc = ::CreateCompatibleDC(maindc);
    HBITMAP andmask = ::CreateCompatibleBitmap(maindc, 
                                               cursorwidth, 
                                               cursorheight);
    ::SelectObject(and_maskdc, andmask);
    RECT rect;
    ::SetRect(&rect, 0, 0, cursorwidth, cursorheight);
    ::FillRect(and_maskdc, &rect, (HBRUSH)::GetStockObject(BLACK_BRUSH));
    ::DeleteDC(and_maskdc); and_maskdc = NULL;
    ICONINFO iconinfo = {0};
    iconinfo.fIcon = false;
    iconinfo.xHotspot = 0;
    iconinfo.yHotspot = 0;
    iconinfo.hbmMask = andmask;
    iconinfo.hbmColor = xormask;
    HCURSOR cursorhandle = ::CreateIconIndirect(&iconinfo);

    //release
    ::DeleteObject(andmask);
    ::DeleteObject(xormask);
    ::ReleaseDC(NULL, maindc);
    return cursorhandle;
  }
  catch(...) {
    return NULL;
  }
}

} //namespace vgui_icon
