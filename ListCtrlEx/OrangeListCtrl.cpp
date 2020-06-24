#include "pch.h"
#include "OrangeListCtrl.h"

// OrangeListCtrl.cpp : 实现文件
//


// COrangeListCtrl

IMPLEMENT_DYNAMIC(COrangeListCtrl, CListCtrl)

COrangeListCtrl::COrangeListCtrl()
{
    m_nRowHeight = 0;
}

COrangeListCtrl::~COrangeListCtrl()
{
}


BEGIN_MESSAGE_MAP(COrangeListCtrl, CListCtrl)
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_MESSAGE(ORANGE_LVN_ENDEDIT, OnEndEdit)
    ON_WM_MEASUREITEM()
    ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()



// COrangeListCtrl 消息处理程序



void COrangeListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

    // TODO:  添加您的代码以绘制指定项
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    LVITEM lvi = { 0 };
    lvi.mask = LVIF_STATE;
    lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED;
    lvi.iItem = lpDrawItemStruct->itemID;
    BOOL bGet = GetItem(&lvi);

    BOOL bHighlight = ((lvi.state & LVIS_DROPHILITED) || ((lvi.state & LVIS_SELECTED) && ((GetFocus() == this) || (GetStyle() & LVS_SHOWSELALWAYS))));

    CRect rcBack = lpDrawItemStruct->rcItem;

    if (bHighlight) //高亮显示
    {
        pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
        pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
        pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
    }
    else
    {

        pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
        pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_WINDOW)));


    }
    //绘制文本
    CString strText = _T("");
    CRect rcItem;
    if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
    {
        for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
        {
            if (!GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem))
                continue;
            strText = GetItemText(lpDrawItemStruct->itemID, i);

            pDC->DrawText(strText, strText.GetLength(), &rcItem, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_BOTTOM);
        }
    }

}

void COrangeListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CListCtrl::OnLButtonDown(nFlags, point);
    CRect rcCtrl;
    LVHITTESTINFO lvhti;
    lvhti.pt = point;
    m_nItem = SubItemHitTest(&lvhti);
    if (m_nItem == -1)
    {
        AddRow(nFlags, point);
        return;
    }
    m_nSubItem = lvhti.iSubItem;
    GetSubItemRect(m_nItem, m_nSubItem, LVIR_LABEL, rcCtrl);
    if (m_Edit_ctlItem.m_hWnd == NULL)
    {
        m_Edit_ctlItem.Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN | WS_BORDER, CRect(0, 0, 0, 0), this, 99);
        m_Edit_ctlItem.ShowWindow(SW_HIDE);

        m_FontItem.CreateStockObject(DEFAULT_GUI_FONT);
        m_Edit_ctlItem.SetFont(&m_FontItem);
        m_FontItem.DeleteObject();

    }
    CString strItem = GetItemText(m_nItem, m_nSubItem);
    m_Edit_ctlItem.MoveWindow(&rcCtrl);
    m_Edit_ctlItem.ShowWindow(SW_SHOW);
    m_Edit_ctlItem.SetWindowText(strItem);
    m_Edit_ctlItem.SetFocus();
    m_Edit_ctlItem.SetSel(-1);
}
void COrangeListCtrl::AddRow(UINT nFlags, CPoint point)
{
    int column_cnt = GetHeaderCtrl()->GetItemCount();
    int item_cnt = GetItemCount();

    for (int i = 0; i < column_cnt; i++)
    {
        InsertItem(item_cnt, "");
        SetItemText(item_cnt, 1, "");
        SetItemText(item_cnt, 2, "");
    }

}
void COrangeListCtrl::PreSubclassWindow()
{
    // TODO: 在此添加专用代码和/或调用基类
    ModifyStyle(0, LVS_OWNERDRAWFIXED);
    CListCtrl::PreSubclassWindow();

}

LRESULT COrangeListCtrl::OnEndEdit(WPARAM wParam, LPARAM lParam)

{

    CString strText;
    m_Edit_ctlItem.GetWindowText(strText);
    SetItemText(m_nItem, m_nSubItem, strText);
    m_Edit_ctlItem.ShowWindow(SW_HIDE);


    return 0;

}

void COrangeListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    if (m_nRowHeight > 0)
    {
        lpMeasureItemStruct->itemHeight = m_nRowHeight;
    }
}
void COrangeListCtrl::SetRowHeigt(int nHeight)
{
    m_nRowHeight = nHeight;

    CRect rcWin;
    GetWindowRect(&rcWin);
    WINDOWPOS wp;
    wp.hwnd = m_hWnd;
    wp.cx = rcWin.Width();
    wp.cy = rcWin.Height();
    wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
    SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

void COrangeListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}