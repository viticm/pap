#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IMEWINDOW_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IMEWINDOW_H_

namespace CEGUI
{

  class IFalagardMeshWindow
  {
  public:
    /*!
    \brief
      Subscribes Shown Event.
    */
    virtual void  subscribeShownEvent(Event::Subscriber subscriber) = 0;
    /*!
    \brief
      Subscribes Hiden Event.
    */
    virtual void  subscribeHidenEvent(Event::Subscriber subscriber) = 0;
  };

}
#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IMEWINDOW_H_
