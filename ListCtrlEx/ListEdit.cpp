#include "pch.h"
#include "ListEdit.h"
#include "EditListCtrl.h"  

// CListEdit  

IMPLEMENT_DYNAMIC(CListEdit, CEdit)

CListEdit::CListEdit()
{

}

CListEdit::~CListEdit()
{
}


BEGIN_MESSAGE_MAP(CListEdit, CEdit)
    ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CListEdit message handlers  



void CListEdit::OnKillFocus(CWnd* pNewWnd)
{
    CEdit::OnKillFocus(pNewWnd);

    //ShowWindow(SW_HIDE);  
    CEditListCtrl* temp = (CEditListCtrl*)GetParent();
    temp->DisposeEdit();

}

void CListEdit::PreSubclassWindow()
{
    // TODO: Add your specialized code here and/or call the base class  

    CEdit::PreSubclassWindow();
}