#pragma once
#include <afxwin.h>
#include "framework.h"

class COrangeEdit :
    public CEdit
{
    DECLARE_DYNAMIC(COrangeEdit)

public:
    COrangeEdit();
    virtual ~COrangeEdit();

protected:
    DECLARE_MESSAGE_MAP()
    virtual void PreSubclassWindow();
public:
    afx_msg void OnKillFocus(CWnd* pNewWnd);
};

