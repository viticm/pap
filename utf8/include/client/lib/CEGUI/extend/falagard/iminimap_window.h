#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IMINIMAP_WINDOW_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IMINIMAP_WINDOW_H_
#pragma once

namespace CEGUI
{
  class IFalagardMinimapWindow
  {
  public:
    virtual void setMinimapData( int nType, float fX, float fY, String32& szName  ) = 0;
    virtual void clearFlagList() = 0;
    virtual void setMinimapCenter( const Point& pos ) = 0;
    virtual void setPlayerDirection( int nDir ) = 0; 
  };
};
#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IMINIMAP_WINDOW_H_
