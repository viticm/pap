#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ISELFFIT_WINDOW_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ISELFFIT_WINDOW_H_

#pragma once

namespace CEGUI
{

  class IFalagardSelfFitWindow
  {
  public:
    virtual void      setCenter(const Point& pos) = 0;
  };

}
#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_ISELFFIT_WINDOW_H_
