#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IANIMATE_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IANIMATE_H_

namespace CEGUI
{

  class IFalagardAnimate
  {
  public:
    /*!
    \brief
      Recaculate all subwindow
    */
    virtual void  Play(bool bPlay) = 0;

    virtual void  SetAnimate( const String& strAnimate ) = 0;

  };

}
#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IANIMATE_H_
