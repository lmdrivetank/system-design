#include "pch.h"
#include "ListComboBox.h"
#include "EditListCtrl.h"  

// CListComboBox  

IMPLEMENT_DYNAMIC(CListComboBox, CComboBox)

CListComboBox::CListComboBox()
{

}

CListComboBox::~CListComboBox()
{
}


BEGIN_MESSAGE_MAP(CListComboBox, CComboBox)
    ON_WM_KILLFOCUS()
    ON_CONTROL_REFLECT(CBN_DROPDOWN, &CListComboBox::OnCbnDropdown)
END_MESSAGE_MAP()



// CListComboBox message handlers  

void CListComboBox::OnKillFocus(CWnd* pNewWnd)
{
    CComboBox::OnKillFocus(pNewWnd);
    //ShowWindow(SW_HIDE);  

    CEditListCtrl* temp = (CEditListCtrl*)GetParent();
    temp->DisposeEdit(); //调用父窗口的DisposeEdit()函数  
}

void CListComboBox::OnCbnDropdown()
{
    CClientDC dc(this);
    int nTotalHeight = 0;
    //获取字体信息  
    dc.SelectObject(GetFont());
    //获取当前item的个数  
    int nCount = GetCount();
    if (nCount <= 0) return;
    //获取字体的高度  
    CString strLable = _T("");
    GetLBText(GetCurSel(), strLable);
    int nHeight = dc.GetTextExtent(strLable).cy;

    //组合框高度  
    CRect rect;
    GetWindowRect(rect);
    int height = rect.Height();

    if (nCount > 30)
        nTotalHeight = 30 * nHeight + height;
    else
        nTotalHeight = nCount * nHeight + height;

    //设置下拉的高度  
    CRect rc;
    GetClientRect(&rc);
    SetWindowPos(NULL, 0, 0, rc.Width(), rc.Height() + nTotalHeight, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);
}