#ifndef PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IINFOLIST_H_
#define PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IINFOLIST_H_
#pragma once

namespace CEGUI
{
  class IFalagardInfoList
  {
  public:
    virtual void AddInfo(const String32& strInfo) = 0;
    virtual void RemoveAllInfo() = 0;
  };
}
#endif //PAP_CLIENT_LIB_CEGUI_EXTEND_FALAGARD_IINFOLIST_H_
