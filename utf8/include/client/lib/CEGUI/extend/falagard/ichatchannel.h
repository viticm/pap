#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IATANNEL_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IATANNEL_H_

namespace CEGUI
{
  class IFalagardChatChannel
  {
  public:
    /*!
    \brief
      Clear all channel in channel list.
    */
    virtual void      clearAllChannel(void) = 0;

    /*!
    \brief
      Add channel in channel list
    */
    virtual void      addChannel(const String& strType, const String& strIconName, const String& strName) = 0;

  };

}
#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IATANNEL_H_
