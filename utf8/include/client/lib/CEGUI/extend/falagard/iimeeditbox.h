#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IIMEEDITBOX_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IIMEEDITBOX_H_

#pragma once

namespace CEGUI
{

  class IFalagardIMEEditBox
  {
  public:
    /*!
      Add a item element info to edit box
    */
    virtual bool injectItemInfo(int nID, const String32& szDisplayName, int nLength) = 0;
    /*!
    \brief
      Subscribes ItemElementDelete Event.
    */
    virtual void  subscribeItemElementDeleteEvent(Event::Subscriber subscriber) = 0;

    /*!
    \brief
      set a string that include ItemElement info.
    */
    virtual void  setItemElementString(const String32& szInfoString) = 0;

    /*!
    \brief
      get a string that include ItemElement info.
    */
    virtual String32  getItemElementString() = 0;

    /*!
    \brief
      set blink text.
    */
    virtual void  setBlinkText (const String32& text) = 0;
  };
}
#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IIMEEDITBOX_H_
