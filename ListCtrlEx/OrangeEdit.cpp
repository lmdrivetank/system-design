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



// COrangeEdit ��Ϣ�������



void COrangeEdit::PreSubclassWindow()
{
    // TODO: �ڴ����ר�ô����/����û���
    CEdit::PreSubclassWindow();
}

void COrangeEdit::OnKillFocus(CWnd* pNewWnd)
{
    CEdit::OnKillFocus(pNewWnd);

    // TODO: �ڴ˴������Ϣ����������
    CWnd* pParent = this->GetParent();

    ::SendMessage(pParent->GetSafeHwnd(), ORANGE_LVN_ENDEDIT, 0, 0);
}