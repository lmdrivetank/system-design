
// DSL4EmbedDlg.h: 头文件
//

#pragma once
#include "code_generate.h"
// CDSL4EmbedDlg 对话框
class CDSL4EmbedDlg : public CDialogEx
{
// 构造
public:
	CDSL4EmbedDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DSL4EMBED_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	code_generate cg;
	CString module_name;
	CString state_name;
	CEditListCtrl mlc_module;
	CEditListCtrl mlc_state;
	CEditListCtrl mlc_businessException;
	CEditListCtrl mlc_dependCooperate;
	CEditListCtrl mlc_branch;
	CEditListCtrl mlc_stateJump;
	CEditListCtrl mlc_task;
	afx_msg void OnNMClickListModule(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickListState(NMHDR* pNMHDR, LRESULT* pResult);
	void Save2Xml();
	void Sync2UI(CString state);
	afx_msg void OnLvnEndlabeleditListState(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnEndlabeleditListModule(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMKillfocusListState(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMKillfocusListModule(NMHDR* pNMHDR, LRESULT* pResult);
	void OnOK();
	afx_msg void OnBnClickedButton_GenerateCode();
	CComboBox mcb_finish_dest;
	CComboBox mcb_exception_dest;
	CComboBox mcb_state_begin_task;
	CComboBox mcb_cfbl;
	CComboBox mcb_coop_style;

	
};
