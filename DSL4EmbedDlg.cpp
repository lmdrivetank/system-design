
// DSL4EmbedDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DSL4Embed.h"
#include "DSL4EmbedDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDSL4EmbedDlg 对话框



CDSL4EmbedDlg::CDSL4EmbedDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DSL4EMBED_DIALOG, pParent)
	, module_name(_T(""))
	, state_name(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}

void CDSL4EmbedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_Module, mlc_module);
	DDX_Control(pDX, IDC_LIST_State, mlc_state);
	DDX_Control(pDX, IDC_LIST_BusinessException, mlc_businessException);
	DDX_Control(pDX, IDC_LIST_DependCooperate, mlc_dependCooperate);
	DDX_Control(pDX, IDC_LIST_Branch, mlc_branch);
	DDX_Control(pDX, IDC_LIST_StateJump, mlc_stateJump);
	DDX_Control(pDX, IDC_LIST_Task, mlc_task);
	DDX_Control(pDX, IDC_COMBO_CooperateFallbackLevel, mcb_cfbl);
	DDX_Control(pDX, IDC_COMBO_CooperateStyle, mcb_coop_style);
	DDX_Control(pDX, IDC_COMBO_FinishDest, mcb_finish_dest);
	DDX_Control(pDX, IDC_COMBO_ExceptDest, mcb_exception_dest);
	DDX_Control(pDX, IDC_COMBO_StateBeginTask, mcb_state_begin_task);
}

BEGIN_MESSAGE_MAP(CDSL4EmbedDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LIST_Module, &CDSL4EmbedDlg::OnNMClickListModule)
	ON_NOTIFY(NM_CLICK, IDC_LIST_State, &CDSL4EmbedDlg::OnNMClickListState)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST_State, &CDSL4EmbedDlg::OnNMKillfocusListState)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST_Module, &CDSL4EmbedDlg::OnNMKillfocusListModule)
	ON_BN_CLICKED(IDC_BUTTON1, &CDSL4EmbedDlg::OnBnClickedButton_GenerateCode)
END_MESSAGE_MAP()


// CDSL4EmbedDlg 消息处理程序

BOOL CDSL4EmbedDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CStringArray fbl_array;
	fbl_array.RemoveAll();
	fbl_array.Add("None");
	fbl_array.Add("A");
	fbl_array.Add("B");
	fbl_array.Add("C");
	fbl_array.Add("D");
	fbl_array.Add("E");

	CStringArray rslt_array;
	rslt_array.RemoveAll();
	rslt_array.Add("Succ");
	rslt_array.Add("Fail");

	CStringArray brtype_array;
	brtype_array.RemoveAll();
	brtype_array.Add("Switch");
	brtype_array.Add("ParallelWith");
	brtype_array.Add("ParallelOr");

	CStringArray brloc_array;
	brloc_array.RemoveAll();
	brloc_array.Add("Begin");
	brloc_array.Add("End");
	brloc_array.Add("First");
	brloc_array.Add("Mid");
	
	mlc_module.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL);
	mlc_module.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	mlc_module.InsertColumn(0, "module_name");
	mlc_module.SetLabelStyle(0, Te_LabelStyle_Edit);
	mlc_module.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
		
	mlc_state.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL);
	mlc_state.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	mlc_state.InsertColumn(0, "state_name");
	mlc_state.SetLabelStyle(0, Te_LabelStyle_Edit);
	mlc_state.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	
	mlc_businessException.ModifyStyle(0, LVS_REPORT);
	mlc_businessException.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	mlc_businessException.InsertColumn(0, "function   ");
	mlc_businessException.InsertColumn(1, "level      ");
	mlc_businessException.InsertColumn(2, "result     ");
	mlc_businessException.SetLabelStyle(0, Te_LabelStyle_Edit);
	mlc_businessException.SetLabelStyle(1, Te_LabelStyle_ComboBox);
	mlc_businessException.SetLabelStyle(2, Te_LabelStyle_ComboBox);
	mlc_businessException.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	mlc_businessException.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	mlc_businessException.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	mlc_businessException.SetComboBoxContext(1, fbl_array);
	mlc_businessException.SetComboBoxContext(2, rslt_array);
	
	mlc_dependCooperate.ModifyStyle(0, LVS_REPORT);
	mlc_dependCooperate.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	mlc_dependCooperate.InsertColumn(0, "step");
	mlc_dependCooperate.InsertColumn(1, "depend_module     ");
	mlc_dependCooperate.InsertColumn(2, "depend_state_mid  ");
	mlc_dependCooperate.InsertColumn(3, "depend_state_dst  ");
	mlc_dependCooperate.SetLabelStyle(0, Te_LabelStyle_Edit);
	mlc_dependCooperate.SetLabelStyle(1, Te_LabelStyle_ComboBox);
	mlc_dependCooperate.SetLabelStyle(2, Te_LabelStyle_ComboBoxEx);
	mlc_dependCooperate.SetLabelStyle(3, Te_LabelStyle_ComboBoxEx);
	mlc_dependCooperate.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	mlc_dependCooperate.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	mlc_dependCooperate.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	mlc_dependCooperate.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);

	mlc_branch.ModifyStyle(0, LVS_REPORT);
	mlc_branch.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	mlc_branch.InsertColumn(0, "br-id  ");
	mlc_branch.InsertColumn(1, "br_type   ");
	mlc_branch.InsertColumn(2, "limit");
	mlc_branch.SetLabelStyle(0, Te_LabelStyle_Edit);
	mlc_branch.SetLabelStyle(1, Te_LabelStyle_ComboBox);
	mlc_branch.SetLabelStyle(2, Te_LabelStyle_Edit);
	mlc_branch.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	mlc_branch.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	mlc_branch.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	mlc_branch.SetComboBoxContext(1, brtype_array);

	mlc_task.ModifyStyle(0, LVS_REPORT);
	mlc_task.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	mlc_task.InsertColumn(0, "task-id");
	mlc_task.InsertColumn(1, "br-id  ");
	mlc_task.InsertColumn(2, "br-loc");
	mlc_task.InsertColumn(3, "order_next");
	mlc_task.InsertColumn(4, "parallel_next");
	mlc_task.InsertColumn(5, "ConditonResult   ");
	mlc_task.InsertColumn(6, "WorkCondition    ");
	mlc_task.InsertColumn(7, "WorkPerformance  ");
	mlc_task.SetLabelStyle(0, Te_LabelStyle_Edit);
	mlc_task.SetLabelStyle(1, Te_LabelStyle_Edit);
	mlc_task.SetLabelStyle(2, Te_LabelStyle_ComboBox);
	mlc_task.SetLabelStyle(3, Te_LabelStyle_Edit);
	mlc_task.SetLabelStyle(4, Te_LabelStyle_Edit);
	mlc_task.SetLabelStyle(5, Te_LabelStyle_ComboBox);
	mlc_task.SetLabelStyle(6, Te_LabelStyle_Edit);
	mlc_task.SetLabelStyle(7, Te_LabelStyle_Edit);
	mlc_task.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	mlc_task.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	mlc_task.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	mlc_task.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	mlc_task.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	mlc_task.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);
	mlc_task.SetColumnWidth(6, LVSCW_AUTOSIZE_USEHEADER);
	mlc_task.SetColumnWidth(7, LVSCW_AUTOSIZE_USEHEADER);
	mlc_task.SetComboBoxContext(2, brloc_array);
	mlc_task.SetComboBoxContext(5, rslt_array);

	mcb_cfbl.AddString("None");
	mcb_cfbl.AddString("A");
	mcb_cfbl.AddString("B");
	mcb_cfbl.AddString("C");
	mcb_cfbl.AddString("D");
	mcb_cfbl.AddString("E");

	mcb_coop_style.AddString("Negotiating");
	mcb_coop_style.AddString("Steady");

	CStringArray module_list;
	cg.GetModuleList(module_list);
	for (int i = 0; i < module_list.GetCount(); i++)
	{
		mlc_module.InsertItem(i, module_list[i]);
	}
	UpdateData(FALSE);

	NM_LISTVIEW EditCtrl;
	LRESULT result;
	EditCtrl.iItem = 0;
	EditCtrl.iSubItem = 0;
	OnNMClickListModule((NMHDR*)&EditCtrl, &result);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDSL4EmbedDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDSL4EmbedDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDSL4EmbedDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDSL4EmbedDlg::OnNMClickListModule(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	NM_LISTVIEW* pEditCtrl = (NM_LISTVIEW*)pNMHDR;
	if (pEditCtrl->iItem == -1)//点击到非工作区
		return;
	
	CString name = mlc_module.GetItemText(pEditCtrl->iItem, 0);
	if (name != module_name)
	{
		if (module_name != "")
			Save2Xml();			

		module_name = name;
		state_name = mlc_state.GetItemText(0, 0);

		CStringArray state_list;
		state_list.RemoveAll();
		mlc_state.DeleteAllItems();
		mcb_finish_dest.ResetContent();
		mcb_exception_dest.ResetContent();
		cg.GetStateList(module_name, state_list);
		for (int i = 0; i < state_list.GetCount(); i++)
		{
			if (state_list[i] != "")
			{
				mlc_state.InsertItem(i, state_list[i]);
				mcb_finish_dest.AddString(state_list[i]);
				mcb_exception_dest.AddString(state_list[i]);

			}
		}
		CStringArray module_list;
		cg.GetModuleList(module_list);
		module_list.RemoveAt(pEditCtrl->iItem);
		mlc_dependCooperate.SetComboBoxContext(1, module_list);
		UpdateData(FALSE);

		NM_LISTVIEW EditCtrl;
		LRESULT result;
		EditCtrl.iItem = 0;
		EditCtrl.iSubItem = 0;
		OnNMClickListState((NMHDR*)&EditCtrl, &result);
	}
}


void CDSL4EmbedDlg::OnNMClickListState(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	NM_LISTVIEW* pEditCtrl = (NM_LISTVIEW*)pNMHDR;
	if (pEditCtrl->iItem == -1)//点击到非工作区
		return;
	CString name = mlc_state.GetItemText(pEditCtrl->iItem, 0);
	if (name != state_name)
	{
		if (module_name != "" && state_name != "")
			Save2Xml();
		
		CStringArray state_list;
		state_list.RemoveAll();
		mcb_finish_dest.ResetContent();
		mcb_exception_dest.ResetContent();
		cg.GetStateList(module_name, state_list);
		for (int i = 0; i < state_list.GetCount(); i++)
		{
			if (state_list[i] != "")
			{
				mcb_finish_dest.AddString(state_list[i]);
				mcb_exception_dest.AddString(state_list[i]);
			}
		}
		CStringArray task_list;
		task_list.RemoveAll();
		mcb_state_begin_task.ResetContent();
		mcb_state_begin_task.AddString("NULL");
		cg.GetStateTaskid(module_name, name, task_list);
		for (int i = 0; i < task_list.GetCount(); i++)
		{
			if (task_list[i] != "")
			{
				mcb_state_begin_task.AddString(task_list[i]);
			}
		}
		Sync2UI(name);
		UpdateData(FALSE);
	}
}

void CDSL4EmbedDlg::Save2Xml()
{
	CString str_mid;
	UpdateData(TRUE);

	cg.SaveNewModule(module_name, mlc_state.GetItemText(0, 0));
	cg.SaveState(module_name, state_name);

	mcb_finish_dest.GetWindowText(str_mid);
	cg.SaveStateFinishDest(module_name, state_name, str_mid);
	mcb_exception_dest.GetWindowText(str_mid);
	cg.SaveStateExceptDest(module_name, state_name, str_mid);
	mcb_state_begin_task.GetWindowText(str_mid);
	cg.SaveStateBeginTask(module_name, state_name, str_mid);
	mcb_cfbl.GetWindowText(str_mid);
	cg.SaveStateCFBL(module_name, state_name, str_mid);
	mcb_coop_style.GetWindowText(str_mid);
	cg.SaveStateCooperateStyle(module_name, state_name, str_mid);

	CStringArray mid_list;
	//state exception
	mid_list.RemoveAll();	
	for (int i = 0; i < mlc_businessException.GetItemCount() ; i++)
	{
		mid_list.Add(mlc_businessException.GetItemText(i, 0));
	}
	cg.SaveStateBeFunction(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_businessException.GetItemCount(); i++)
	{
		mid_list.Add(mlc_businessException.GetItemText(i, 1));
	}
	cg.SaveStateBeLevel(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_businessException.GetItemCount(); i++)
	{
		mid_list.Add(mlc_businessException.GetItemText(i, 2));
	}
	cg.SaveStateBeResult(module_name, state_name, mid_list);
	// state coop
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_dependCooperate.GetItemCount(); i++)
	{
		mid_list.Add(mlc_dependCooperate.GetItemText(i, 0));
	}
	cg.SaveStateCoopStep(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_dependCooperate.GetItemCount(); i++)
	{
		mid_list.Add(mlc_dependCooperate.GetItemText(i, 1));
	}
	cg.SaveStateDependModule(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_dependCooperate.GetItemCount(); i++)
	{
		mid_list.Add(mlc_dependCooperate.GetItemText(i, 2));
	}
	cg.SaveStateDependStateMid(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_dependCooperate.GetItemCount(); i++)
	{
		mid_list.Add(mlc_dependCooperate.GetItemText(i, 3));
	}
	cg.SaveStateDependStateDst(module_name, state_name, mid_list);

	// state branch
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_branch.GetItemCount(); i++)
	{
		mid_list.Add(mlc_branch.GetItemText(i, 0));
	}
	cg.SaveStateBid(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_branch.GetItemCount(); i++)
	{
		mid_list.Add(mlc_branch.GetItemText(i, 1));
	}
	cg.SaveStateBtype(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_branch.GetItemCount(); i++)
	{
		mid_list.Add(mlc_branch.GetItemText(i, 2));
	}
	cg.SaveStateBlimit(module_name, state_name, mid_list);
	// state task
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_task.GetItemCount(); i++)
	{
		mid_list.Add(mlc_task.GetItemText(i, 0));
	}
	cg.SaveStateTaskid(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_task.GetItemCount(); i++)
	{
		mid_list.Add(mlc_task.GetItemText(i, 1));
	}
	cg.SaveStateTaskBid(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_task.GetItemCount(); i++)
	{
		mid_list.Add(mlc_task.GetItemText(i, 2));
	}
	cg.SaveStateTaskBloc(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_task.GetItemCount(); i++)
	{
		mid_list.Add(mlc_task.GetItemText(i, 3));
	}
	cg.SaveStateTaskOrderNext(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_task.GetItemCount(); i++)
	{
		mid_list.Add(mlc_task.GetItemText(i, 4));
	}
	cg.SaveStateTaskParallelNext(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_task.GetItemCount(); i++)
	{
		mid_list.Add(mlc_task.GetItemText(i, 5));
	}
	cg.SaveStateTaskConditionRslt(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_task.GetItemCount(); i++)
	{
		mid_list.Add(mlc_task.GetItemText(i, 6));
	}
	cg.SaveStateTaskWorkCondition(module_name, state_name, mid_list);
	mid_list.RemoveAll();
	for (int i = 0; i < mlc_task.GetItemCount(); i++)
	{
		mid_list.Add(mlc_task.GetItemText(i, 7));
	}
	cg.SaveStateTaskWorkPerformance(module_name, state_name, mid_list);

	cg.Save2Xml();
}

void CDSL4EmbedDlg::Sync2UI(CString state)
{
	state_name = state;

	mcb_finish_dest.SelectString(-1, cg.GetStateFinishDest(module_name, state_name));
	mcb_exception_dest.SelectString(-1, cg.GetStateExceptDest(module_name, state_name));
	mcb_state_begin_task.SelectString(-1, cg.GetStateBeginTask(module_name, state_name));
	mcb_cfbl.SelectString(-1, cg.GetStateCFBL(module_name, state_name));
	mcb_coop_style.SelectString(-1, cg.GetStateCooperateStyle(module_name, state_name));

	CStringArray mid_list;
	//state exception
	mlc_businessException.DeleteAllItems();
	mid_list.RemoveAll();
	cg.GetStateBeFunction(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_businessException.InsertItem(i, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateBeLevel(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_businessException.SetItemText(i, 1, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateBeResult(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_businessException.SetItemText(i, 2, mid_list[i]);
	}
	// state coop
	mlc_dependCooperate.DeleteAllItems();
	mid_list.RemoveAll();
	cg.GetStateCoopStep(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_dependCooperate.InsertItem(i, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateDependModule(module_name, state_name, mid_list);
	CStringArray state_list;
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_dependCooperate.SetItemText(i, 1, mid_list[i]);
		mlc_dependCooperate.SetMapEx(i, i, 2);
		mlc_dependCooperate.SetMapEx(i, i, 3);
		
		state_list.RemoveAll();
		cg.GetStateList(mid_list[i], state_list);
		mlc_dependCooperate.SetComboBoxContextEx(i, state_list);
	}
	mid_list.RemoveAll();
	cg.GetStateDependStateMid(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_dependCooperate.SetItemText(i, 2, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateDependStateDst(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_dependCooperate.SetItemText(i, 3, mid_list[i]);
	}

	// state branch
	mlc_branch.DeleteAllItems();
	mid_list.RemoveAll();
	cg.GetStateBid(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_branch.InsertItem(i, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateBtype(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_branch.SetItemText(i, 1, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateBlimit(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_branch.SetItemText(i, 2, mid_list[i]);
	}
	// state task
	mlc_task.DeleteAllItems();
	mid_list.RemoveAll();
	cg.GetStateTaskid(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_task.InsertItem(i, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateTaskBid(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_task.SetItemText(i, 1, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateTaskBloc(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_task.SetItemText(i, 2, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateTaskOrderNext(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_task.SetItemText(i, 3, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateTaskParallelNext(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_task.SetItemText(i, 4, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateTaskConditionRslt(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_task.SetItemText(i, 5, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateTaskWorkCondition(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_task.SetItemText(i, 6, mid_list[i]);
	}
	mid_list.RemoveAll();
	cg.GetStateTaskWorkPerformance(module_name, state_name, mid_list);
	for (int i = 0; i < mid_list.GetCount(); i++)
	{
		mlc_task.SetItemText(i, 7, mid_list[i]);
	}
}


void CDSL4EmbedDlg::OnNMKillfocusListState(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int i = mlc_state.GetSelectionMark();
	mlc_state.SetItemState(i, LVIS_DROPHILITED, LVIS_DROPHILITED);
	state_name = mlc_state.GetItemText(i, 0);
}


void CDSL4EmbedDlg::OnNMKillfocusListModule(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int i = mlc_module.GetSelectionMark();
	mlc_module.SetItemState(i, LVIS_DROPHILITED, LVIS_DROPHILITED);
	module_name = mlc_module.GetItemText(i, 0);
}

void CDSL4EmbedDlg::OnOK()
{
	return;
}

void CDSL4EmbedDlg::OnBnClickedButton_GenerateCode()
{
	// TODO: 在此添加控件通知处理程序代码
	cg.GenerateCode();
	MessageBox("code generate finish!");
}


