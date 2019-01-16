// ModlueDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Ryprint.h"
#include "ModlueDlg.h"
#include "afxdialogex.h"

#include "DlgNewMod.h"

// CModlueDlg 对话框

IMPLEMENT_DYNAMIC(CModlueDlg, CDialogEx)

CModlueDlg::CModlueDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModlueDlg::IDD, pParent)
{

}

CModlueDlg::~CModlueDlg()
{
}

void CModlueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_hBrowser);
	DDX_Control(pDX, IDC_EDT_STATUS, m_edtStatus);
	DDX_Control(pDX, IDC_GRP_MAIN, m_grpmain);
	DDX_Control(pDX, IDC_BTN_NEWMOD, m_btnNewMod);
	DDX_Control(pDX, IDC_BTN_NEWITEM, m_btnNewItem);
	DDX_Control(pDX, IDC_BTN_DELITEM, m_btnDelItem);
	DDX_Control(pDX, IDC_BTN_LOADJPG, m_btnLoadJpg);
	DDX_Control(pDX, IDC_BTN_SAVEMOD, m_btnSaveMod);
	DDX_Control(pDX, IDC_BTN_DELMOD, m_btnDelMod);
	DDX_Control(pDX, IDC_BTN_ITEMATTR, m_btnModifyItem);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BTN_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_BTN_TESTPRINT, m_btnTestPrint);
}


BEGIN_MESSAGE_MAP(CModlueDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BTN_NEWITEM, &CModlueDlg::OnBnClickedBtnNewitem)
	ON_BN_CLICKED(IDC_BTN_DELITEM, &CModlueDlg::OnBnClickedBtnDelitem)
	ON_BN_CLICKED(IDC_BTN_ITEMATTR, &CModlueDlg::OnBnClickedBtnItemattr)
	ON_BN_CLICKED(IDC_BTN_LOADJPG, &CModlueDlg::OnBnClickedBtnLoadjpg)
	ON_BN_CLICKED(IDC_BTN_TESTPRINT, &CModlueDlg::OnBnClickedBtnTestprint)
	ON_BN_CLICKED(IDC_BTN_NEWMOD, &CModlueDlg::OnBnClickedBtnNewmod)
	ON_BN_CLICKED(IDC_BTN_SAVEMOD, &CModlueDlg::OnBnClickedBtnSavemod)
	ON_BN_CLICKED(IDC_BTN_DELMOD, &CModlueDlg::OnBnClickedBtnDelmod)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CModlueDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()

BOOL CModlueDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	ShowWindow(SW_MAXIMIZE);	//启动最大化

	//得到对话框窗口大小
	GetClientRect(&m_rect);

	//添加主菜单
	//m_hMenu1=LoadMenu(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MENU1));//导入资源,创建菜单
	//::SetMenu(this->GetSafeHwnd(),m_hMenu1);	//添加到对话框
		
	//广告条		   
	CString NaviPath;
	NaviPath= theApp.m_Path + "/bills.htm";
	m_hBrowser.Navigate(NaviPath.GetBuffer(),NULL,NULL,NULL,NULL);

	//按钮初始状态
	SetButtonStatus(0);
	//状态栏初始状态
	m_edtStatus.SetWindowText("欢迎使用票据打印助手!");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CModlueDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CModlueDlg::OnPaint()
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
		DrawModule();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CModlueDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CModlueDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	::DestroyMenu(m_hMenu1);
}

void CModlueDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CPoint   pt(RYWINCX, RYWINCY); //定义宽和高  
	lpMMI->ptMinTrackSize = theApp.m_ryini.WinMinSize; //限制最小宽和高  

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}



// CModlueDlg 消息处理程序
// 根据窗口大小改变控件位置,left、right、top、bottom为4个改变维度
int CModlueDlg::MoveCtlWindow(int handler, int cx, int cy,int left, int right, int top, int bottom)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(handler);	//控件
	if(pWnd) {
		CRect rect;	
		pWnd->GetWindowRect(&rect);		//获取控件变化前大小
		ScreenToClient(&rect);			//将控件大小转换为对话框中的区域坐标
		// cx/m_rect.Width() 为对话框横向变化比例因子
		if(left == 1) rect.left = rect.left * cx/m_rect.Width();
		if(right == 1) rect.right = rect.right * cx/m_rect.Width();
		if(top == 1) rect.top = rect.top * cy/m_rect.Height();
		if(bottom == 1) rect.bottom = rect.bottom * cy/m_rect.Height();
		pWnd->MoveWindow(rect);	//设置控件新大小
	}

	return 0;
}

// 根据窗口大小改变控件位置，rect为新的窗口位置
int CModlueDlg::MoveCtlWindow(int handler, CRect rect)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(handler);	//控件
	if(pWnd) {
		pWnd->MoveWindow(rect);	//设置控件新大小
	}

	return 0;
}

void CModlueDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码
	if(nType == 1) return;		//如果窗口最小化

	CRect rect;	
	//广告条
	rect.left = theApp.m_ryini.AdRect.left;
	rect.right = cx - theApp.m_ryini.AdRect.right;
	rect.top = theApp.m_ryini.AdRect.top;
	rect.bottom = theApp.m_ryini.AdRect.bottom;

	MoveCtlWindow(IDC_EXPLORER1,rect);


	//菜单按钮分组框
	rect.left = theApp.m_ryini.AdRect.left;
	rect.right = cx - theApp.m_ryini.GrpMenuRect.right;
	rect.top = theApp.m_ryini.GrpMenuRect.top;
	rect.bottom = theApp.m_ryini.GrpMenuRect.bottom;
	MoveCtlWindow(IDC_GRP_MENU,rect);

	////菜单按钮
	int btnwidth = 70;
	int btnheight=25;
	int stepwidth = 5;

	////新增字段按钮
	rect.left = theApp.m_ryini.AdRect.left + 15;
	rect.right = rect.left + btnwidth;
	rect.top = theApp.m_ryini.GrpMenuRect.top + 20;
	rect.bottom = rect.top + btnheight;
	MoveCtlWindow(IDC_BTN_NEWITEM,rect);
	////修改字段属性按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_ITEMATTR,rect);

	////删除字段属性按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_DELITEM,rect);

	////导入图片按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_LOADJPG,rect);
	////测试打印按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_TESTPRINT,rect);


	//退出按钮
	rect.left =cx - theApp.m_ryini.GrpMenuRect.right - btnwidth - 10;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_EXIT,rect);

	////删除模板按钮
	rect.right =cx - theApp.m_ryini.GrpMenuRect.right - btnwidth - 10 - stepwidth;
	rect.left = rect.right -btnwidth;
	MoveCtlWindow(IDC_BTN_DELMOD,rect);

	////保存模板按钮
	rect.right = rect.left - stepwidth;
	rect.left = rect.right -btnwidth;
	MoveCtlWindow(IDC_BTN_SAVEMOD,rect);

	////新建模板按钮
	rect.right = rect.left - stepwidth;
	rect.left = rect.right -btnwidth;
	MoveCtlWindow(IDC_BTN_NEWMOD,rect);

	//主窗口分组框
	rect.left = theApp.m_ryini.AdRect.left;
	rect.right = cx - theApp.m_ryini.GrpMainRect.right;
	rect.top = theApp.m_ryini.GrpMainRect.top;
	rect.bottom = cy - theApp.m_ryini.GrpMainRect.bottom;
	m_mainRect.SetRect(rect.left,rect.top+8,rect.right,rect.bottom);	//保存凭证主窗口大小
	MoveCtlWindow(IDC_GRP_MAIN,rect);

	//状态条
	rect.left = 0;
	rect.right = cx ;	
	rect.top = cy - theApp.m_ryini.StatusHeight;
	rect.bottom = cy;

	MoveCtlWindow(IDC_EDT_STATUS,rect);

	GetClientRect(&m_rect);

	
}
// 设置按钮状态
int CModlueDlg::SetButtonStatus(int imode)
{
	m_btnCancel.ShowWindow(FALSE);
	m_btnCancel.EnableWindow(TRUE);
	m_btnExit.ShowWindow(TRUE);
	m_btnExit.EnableWindow(TRUE);

	switch(imode){
	case 1:
		m_btnNewItem.EnableWindow(TRUE);
		m_btnModifyItem.EnableWindow(TRUE);
		m_btnDelItem.EnableWindow(TRUE);
		m_btnLoadJpg.EnableWindow(TRUE);
		m_btnTestPrint.EnableWindow(TRUE);
		m_btnNewMod.EnableWindow(TRUE);
		m_btnSaveMod.EnableWindow(TRUE);
		m_btnDelMod.EnableWindow(TRUE);
		break;
	default:
		m_btnNewItem.EnableWindow(FALSE);
		m_btnModifyItem.EnableWindow(FALSE);
		m_btnDelItem.EnableWindow(FALSE);
		m_btnLoadJpg.EnableWindow(FALSE);
		m_btnTestPrint.EnableWindow(FALSE);
		m_btnNewMod.EnableWindow(TRUE);
		m_btnSaveMod.EnableWindow(FALSE);
		m_btnDelMod.EnableWindow(FALSE);
		break;
	}
	return 0;
}


void CModlueDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(::MessageBox(NULL,"确定要退出吗？","程序退出", MB_YESNO) == IDYES)
		CDialogEx::OnCancel();
}

//新增元素
void CModlueDlg::OnBnClickedBtnNewitem()
{
	// TODO: 在此添加控件通知处理程序代码
}

//删除元素
void CModlueDlg::OnBnClickedBtnDelitem()
{
	// TODO: 在此添加控件通知处理程序代码
}

//修改元素
void CModlueDlg::OnBnClickedBtnItemattr()
{
	// TODO: 在此添加控件通知处理程序代码
}

//导入背景
void CModlueDlg::OnBnClickedBtnLoadjpg()
{
	// TODO: 在此添加控件通知处理程序代码
}

//测试打印
void CModlueDlg::OnBnClickedBtnTestprint()
{
	// TODO: 在此添加控件通知处理程序代码
}

//新建模板
void CModlueDlg::OnBnClickedBtnNewmod()
{
	if(m_currModule.getIsModified() > 0) {
		if(::MessageBox(NULL,"当前模板未保存，是否保存？","保存模板", MB_YESNO) == IDYES) {
			OnBnClickedBtnSavemod();
		}
	}
	//输入新模板要素
	CDlgNewMod dlgNewMod;
	if(dlgNewMod.DoModal() == IDCANCEL)
		return;
	AfxMessageBox(dlgNewMod.m_modName);

	//新建模板及后续处理
	m_currModule.InitBillMod(dlgNewMod.m_modName, dlgNewMod.m_modWidth, dlgNewMod.m_modHeight);
	//置新模板编辑状态

	m_imode = 1;			//按钮状态
	SetButtonStatus(m_imode);
	//画初始模板占位框
    DrawModule();

}

//保存模板
void CModlueDlg::OnBnClickedBtnSavemod()
{
	AfxMessageBox("保存模板");
	m_currModule.SaveBillMod();

}

//删除模板
void CModlueDlg::OnBnClickedBtnDelmod()
{
	if(::MessageBox(NULL,"是否删除当前模板？","删除模板", MB_YESNO) == IDNO)
		return;
	
	m_imode = 0;
	SetButtonStatus(m_imode);
	//删除模板及后续处理
	m_currModule.DelBillMod();
	
	//DrawModule();

}

//返回
void CModlueDlg::OnBnClickedBtnExit()
{
	if(m_currModule.getIsModified()) {
		if(::MessageBox(NULL,"当前模板未保存，是否保存？","保存模板", MB_YESNO) == IDYES) {
			OnBnClickedBtnSavemod();
		}
	}
	this->OnCancel();

}
// 绘制当前模板
int CModlueDlg::DrawModule(void)
{
	CDC* pDC=GetDC(); 
	if(m_currModule.getIsInit()) {
		m_currModule.Draw(pDC,m_mainRect);	//画当前凭证
	} else {	//用背景色填充凭证模板窗口
		pDC->MoveTo(m_mainRect.left,m_mainRect.top); 
		CBrush brush(RGB(240,240,240) );

		pDC->FillRect(m_mainRect,&brush); 
		//绘制空矩形占位
		//CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		//CBrush *pOldBrush=pDC->SelectObject(&brush);
		//pDC->Rectangle(m_mainRect);
		//pDC->SelectObject(pOldBrush);
	}
	
	return 0;
}
