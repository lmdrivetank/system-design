#pragma once
#include <afxcmn.h>
#include "ListEdit.h"  
#include "ListComboBox.h"  
#include <vector> 

#define  IDC_CELL_EDIT      0xffe0  
#define  IDC_CELL_COMBOBOX  0xffe1  

typedef enum
{
    Te_LabelStyle_Edit = 0,
    Te_LabelStyle_ComboBox = 1,
    Te_LabelStyle_ComboBoxEx = 2,
} Te_LabelStyle;

class CEditListCtrl :
    public CListCtrl
{
    DECLARE_DYNAMIC(CEditListCtrl)

public:
    CEditListCtrl();
    virtual ~CEditListCtrl();

protected:
    DECLARE_MESSAGE_MAP()

private:
    CListEdit m_edit;
    CListComboBox m_comboBox;
    int m_nRow; //行  
    int m_nCol; //列  
    Te_LabelStyle m_style_map[32];
    CStringArray mbuff_combo[32];
    CStringArray mbuff_combo_ex[64];
    int m_map[32][32];
public:

    void DoDataExchange(CDataExchange* pDX);

    // 当编辑完成后同步数据  
    void DisposeEdit(void);

    //发送失效消息  
    void SendInvalidateMsg();

    // 设置当前窗口的风格  
    void SetStyle(void);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnCbnSelchangeCbCellComboBox();

    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    Te_LabelStyle GetLabelStyle(unsigned int col);
    void SetLabelStyle(unsigned int col, Te_LabelStyle style);

    void UpdateComboBoxContext(unsigned int col);
    void SetComboBoxContext(unsigned int col, CStringArray& context);

    void UpdateComboBoxContextEx(unsigned int row, unsigned int col);
    void SetComboBoxContextEx(unsigned int id, CStringArray& context);
    void SetMapEx(unsigned int id, unsigned int row, unsigned int col);
};

