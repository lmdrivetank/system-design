#pragma once
#include <afxtempl.h>
#include "orangeedit.h"

class COrangeListCtrl : public CListCtrl
{
    DECLARE_DYNAMIC(COrangeListCtrl)

public:
    COrangeListCtrl();
    virtual ~COrangeListCtrl();

protected:
    DECLARE_MESSAGE_MAP()
public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void AddRow(UINT nFlags, CPoint point);
protected:
    virtual void PreSubclassWindow();
    afx_msg LRESULT OnEndEdit(WPARAM wParam, LPARAM lParam);
    void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
private:
    int m_nItem;//主项
    int m_nSubItem;//子项
    COrangeEdit m_Edit_ctlItem;

    CFont m_FontItem;
    int m_nRowHeight;
public:
    void SetRowHeigt(int nHeight);
};

