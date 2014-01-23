#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ISOFTKEYBOARD_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ISOFTKEYBOARD_H_
#pragma once
namespace CEGUI
{
  class Window;
  class IFalagardSoftKeyBoard
  {
  public:
    virtual void SetActiveEditBox( String& windowName ) = 0;
  };

};
#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ISOFTKEYBOARD_H_
