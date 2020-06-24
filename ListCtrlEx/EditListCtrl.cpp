#include "pch.h"
#include "EditListCtrl.h"
#include "resource.h"
// CEditListCtrl  

IMPLEMENT_DYNAMIC(CEditListCtrl, CListCtrl)

CEditListCtrl::CEditListCtrl()
{
    m_nRow = 0;
    m_nCol = 0;
}
CEditListCtrl::~CEditListCtrl()
{
}


BEGIN_MESSAGE_MAP(CEditListCtrl, CListCtrl)
    ON_WM_LBUTTONDBLCLK()
    ON_CBN_SELCHANGE(IDC_CELL_COMBOBOX, &CEditListCtrl::OnCbnSelchangeCbCellComboBox)
    ON_WM_HSCROLL()
    ON_WM_VSCROLL()
END_MESSAGE_MAP()



// CEditListCtrl message handlers  
void CEditListCtrl::DoDataExchange(CDataExchange* pDX)
{
    DDX_Control(pDX, IDC_EDIT_CELL, m_edit);
    DDX_Control(pDX, IDC_CELL_COMBOBOX, m_comboBox);
}
// ���༭��ɺ�ͬ������  
void CEditListCtrl::DisposeEdit(void)
{
    int nIndex = GetSelectionMark();
    //ͬ�����´�������  
    CString sLable;

    if( Te_LabelStyle_Edit == GetLabelStyle(m_nCol)) //edit�ؼ�  
    {
        m_edit.GetWindowText(sLable);
        SetItemText(m_nRow, m_nCol, sLable);

        m_edit.ShowWindow(SW_HIDE);
    }
    else if ((Te_LabelStyle_ComboBox == GetLabelStyle(m_nCol)) || (Te_LabelStyle_ComboBoxEx == GetLabelStyle(m_nCol)))
    {
        m_comboBox.ShowWindow(SW_HIDE);
        m_comboBox.GetWindowText(sLable);
        SetItemText(m_nRow, m_nCol, sLable);
    }

}

// ���õ�ǰ���ڵķ��  
void CEditListCtrl::SetStyle(void)
{
    LONG lStyle;
    lStyle = GetWindowLong(m_hWnd, GWL_STYLE);
    lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽ  
    lStyle |= LVS_REPORT; //listģʽ  
    lStyle |= LVS_SINGLESEL; //��ѡ  
    SetWindowLong(m_hWnd, GWL_STYLE, lStyle);

    //��չģʽ  
    DWORD dwStyle = GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ�����и���  
    dwStyle |= LVS_EX_GRIDLINES; //������  
    SetExtendedStyle(dwStyle); //������չ���  
}

void CEditListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default  
    CListCtrl::OnLButtonDblClk(nFlags, point);

    LVHITTESTINFO info;
    info.pt = point;
    info.flags = LVHT_ONITEMLABEL;

    if (SubItemHitTest(&info) < 0)
    {
        InsertItem(GetItemCount(), "new item");
        info.iItem = GetItemCount();
        info.iSubItem = 0;        
    }
    m_nRow = info.iItem;
    m_nCol = info.iSubItem;

    CRect rect;
    GetSubItemRect(m_nRow, m_nCol, LVIR_LABEL, rect);

    CString strValue;
    strValue = GetItemText(m_nRow, m_nCol);

    //Edit��Ԫ��  
    if ((Te_LabelStyle_Edit == GetLabelStyle(m_nCol)))
    {
        if (m_edit.m_hWnd == NULL)
        {
            m_edit.Create(WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN | ES_LEFT,
                CRect(0, 0, 0, 0), this, IDC_CELL_EDIT);
        }
        m_edit.MoveWindow(rect);
        m_edit.SetWindowText(strValue);
        m_edit.ShowWindow(SW_SHOW);
        m_edit.SetSel(0, -1);
        m_edit.SetFocus();
        UpdateWindow();
    }
    //ComboBox��Ԫ��  
    if ((Te_LabelStyle_ComboBox == GetLabelStyle(m_nCol)) || (Te_LabelStyle_ComboBoxEx == GetLabelStyle(m_nCol)))
    {
        if (m_comboBox.m_hWnd == NULL)
        {
            m_comboBox.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP | CBS_AUTOHSCROLL,
                CRect(0, 0, 0, 0), this, IDC_CELL_COMBOBOX);
        }
        m_comboBox.MoveWindow(rect);
        if (Te_LabelStyle_ComboBox == GetLabelStyle(m_nCol))
            UpdateComboBoxContext(m_nCol);
        else
            UpdateComboBoxContextEx(m_nRow, m_nCol);
        m_comboBox.ShowWindow(SW_SHOW);
        //TODO comboBox ��ʼ��  
        //��ǰcell��ֵ  
        CString strCellValue = GetItemText(m_nRow, m_nCol);
        int nIndex = m_comboBox.FindStringExact(0, strCellValue);
        if (CB_ERR == nIndex)
            m_comboBox.SetCurSel(0); //TODO ����Ϊ��ǰֵ��Item  
        else
            m_comboBox.SetCurSel(nIndex);

        m_comboBox.SetFocus();
        UpdateWindow();
    }
}


void CEditListCtrl::OnCbnSelchangeCbCellComboBox()
{
    //ͬ�����´�������  

    if (1 == m_nCol) //combobox�ؼ�  
    {
        CString szLable;
        int nindex = m_comboBox.GetCurSel();
        m_comboBox.GetLBText(nindex, szLable);

        SetItemText(m_nRow, m_nCol, szLable);
        m_comboBox.ShowWindow(SW_HIDE);
    }
}

//����ʧЧ��Ϣ  
void CEditListCtrl::SendInvalidateMsg()
{
    //Edit��Ԫ��  
    if ((0 == m_nCol))
    {

        if (NULL == m_edit.m_hWnd) return;
        BOOL bShow = m_edit.IsWindowVisible();
        if (bShow)
            ::SendMessage(m_edit.m_hWnd, WM_KILLFOCUS, (WPARAM)0, (LPARAM)0);

    }
    else if ((1 == m_nCol)) //combobox  
    {
        if (NULL == m_comboBox.m_hWnd) return;

        BOOL bShow = m_comboBox.IsWindowVisible();
        if (bShow)
            ::SendMessage(m_comboBox.m_hWnd, WM_KILLFOCUS, (WPARAM)0, (LPARAM)0);
    }
}

void CEditListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    SendInvalidateMsg();

    CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CEditListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    SendInvalidateMsg();

    CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

Te_LabelStyle CEditListCtrl::GetLabelStyle(unsigned int col)
{
    Te_LabelStyle result = m_style_map[col];

    return result;
}

void CEditListCtrl::SetLabelStyle(unsigned int col, Te_LabelStyle style)
{
    m_style_map[col] = style;
}

void CEditListCtrl::SetComboBoxContext(unsigned int col, CStringArray& context)
{
    mbuff_combo[col].RemoveAll();
    for (int i = 0; i < context.GetCount(); i++)
    {
        mbuff_combo[col].Add(context[i]);
    }
}

void CEditListCtrl::UpdateComboBoxContextEx(unsigned int row, unsigned int col)
{
    if (m_comboBox.m_hWnd == NULL)
    {
        m_comboBox.Create(WS_CHILD | WS_VISIBLE | CBS_SORT | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP | CBS_AUTOHSCROLL,
            CRect(0, 0, 0, 0), this, IDC_CELL_COMBOBOX);
    }
    m_comboBox.ResetContent();
    int id = m_map[row][col];
    for (int i = 0; i < mbuff_combo_ex[id].GetCount(); i++)
    {
        CString str = mbuff_combo_ex[id][i];
        m_comboBox.AddString(str);
    }
}

void CEditListCtrl::SetComboBoxContextEx(unsigned int id, CStringArray& context)
{
    mbuff_combo_ex[id].RemoveAll();
    for (int i = 0; i < context.GetCount(); i++)
    {
        mbuff_combo_ex[id].Add(context[i]);
    }
}

void CEditListCtrl::SetMapEx(unsigned int id, unsigned int row, unsigned int col)
{
    m_map[row][col] = id;
}

void CEditListCtrl::UpdateComboBoxContext(unsigned int col)
{
    if (m_comboBox.m_hWnd == NULL)
    {
        m_comboBox.Create(WS_CHILD | WS_VISIBLE | CBS_SORT | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP | CBS_AUTOHSCROLL,
            CRect(0, 0, 0, 0), this, IDC_CELL_COMBOBOX);
    }
    m_comboBox.ResetContent();
    for (int i = 0; i < mbuff_combo[col].GetCount(); i++)
    {
        m_comboBox.AddString(mbuff_combo[col][i]);
    }
}
