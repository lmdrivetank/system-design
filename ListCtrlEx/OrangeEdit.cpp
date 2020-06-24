#include "pch.h"
//#include "stdafx.h"
#include "OrangeEdit.h"
//#include "WindowManager.h"

// COrangeEdit

IMPLEMENT_DYNAMIC(COrangeEdit, CEdit)

COrangeEdit::COrangeEdit()
{

}

COrangeEdit::~COrangeEdit()
{
}


BEGIN_MESSAGE_MAP(COrangeEdit, CEdit)
    ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// COrangeEdit 消息处理程序



void COrangeEdit::PreSubclassWindow()
{
    // TODO: 在此添加专用代码和/或调用基类
    CEdit::PreSubclassWindow();
}

void COrangeEdit::OnKillFocus(CWnd* pNewWnd)
{
    CEdit::OnKillFocus(pNewWnd);

    // TODO: 在此处添加消息处理程序代码
    CWnd* pParent = this->GetParent();

    ::SendMessage(pParent->GetSafeHwnd(), ORANGE_LVN_ENDEDIT, 0, 0);
}