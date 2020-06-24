#pragma once
#include <afxwin.h>
class CListComboBox :
    public CComboBox
{
    DECLARE_DYNAMIC(CListComboBox)

public:
    CListComboBox();
    virtual ~CListComboBox();

protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnCbnDropdown();
};

