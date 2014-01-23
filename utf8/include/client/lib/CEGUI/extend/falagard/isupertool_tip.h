#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ISUPERTOOL_TIP_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ISUPERTOOL_TIP_H_

namespace CEGUI
{

  class IFalagardSuperTooltip
  {
  public:
    /*!
    \brief
      Recaculate all subwindow
    */
    virtual void      resizeSelf(void) = 0;

  };

}
#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ISUPERTOOL_TIP_H_
