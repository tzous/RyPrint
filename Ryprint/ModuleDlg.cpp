// ModlueDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Ryprint.h"
#include "ModuleDlg.h"
#include "afxdialogex.h"

#include "DlgNewMod.h"

// CModuleDlg 对话框

IMPLEMENT_DYNAMIC(CModuleDlg, CDialogEx)

CModuleDlg::CModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModuleDlg::IDD, pParent)
{

}

CModuleDlg::~CModuleDlg()
{
}

void CModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_hBrowser);
	DDX_Control(pDX, IDC_EDT_STATUS, m_edtStatus);
	DDX_Control(pDX, IDC_GRP_MAIN, m_grpmain);
	DDX_Control(pDX, IDC_BTN_NEWMOD, m_btnNewMod);
	DDX_Control(pDX, IDC_BTN_NEWITEM, m_btnNewItem);
	DDX_Control(pDX, IDC_BTN_LOADJPG, m_btnLoadJpg);
	DDX_Control(pDX, IDC_BTN_SAVEMOD, m_btnSaveMod);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BTN_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_BTN_TESTPRINT, m_btnTestPrint);
	DDX_Control(pDX, IDC_BTN_DELJPG, m_btnDelJpg);
	DDX_Control(pDX, IDC_BTN_ADJUSTLEFT, m_btnAdjustLeft);
	DDX_Control(pDX, IDC_BTN_ADJUSTRIGHT, m_btnAdjustRight);
	DDX_Control(pDX, IDC_BTN_ADJUSTTOP, m_btnAdjustTop);
	DDX_Control(pDX, IDC_BTN_ADJUSTBOTTOM, m_btnAdjustBottom);
	DDX_Control(pDX, IDC_BTN_SAMEWIDTH, m_btnSameWidth);
	DDX_Control(pDX, IDC_BTN_SAMEHEIGHT, m_btnSameHeight);
}


BEGIN_MESSAGE_MAP(CModuleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BTN_NEWITEM, &CModuleDlg::OnBnClickedBtnNewitem)
	ON_BN_CLICKED(IDC_BTN_LOADJPG, &CModuleDlg::OnBnClickedBtnLoadjpg)
	ON_BN_CLICKED(IDC_BTN_TESTPRINT, &CModuleDlg::OnBnClickedBtnTestprint)
	ON_BN_CLICKED(IDC_BTN_NEWMOD, &CModuleDlg::OnBnClickedBtnNewmod)
	ON_BN_CLICKED(IDC_BTN_SAVEMOD, &CModuleDlg::OnBnClickedBtnSavemod)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CModuleDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()

BOOL CModuleDlg::OnInitDialog()
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
	NaviPath= theApp.m_Path + "/data/bills.htm";
	m_hBrowser.Navigate(NaviPath.GetBuffer(),NULL,NULL,NULL,NULL);

	//状态栏初始状态
	m_edtStatus.SetWindowText("欢迎使用票据打印助手!");
	//非编辑状态
	//m_nMode = 0;
    m_nMode = 1;
	m_voucher.InitBillMod("NAMENAME", "TXTXTXT", 210, 145);

	//设置按钮风格
	SetButtonStyles();
	//按钮初始状态
	SetButtonStatus(m_nMode);
		//创建主画板滚动视图

 UINT TargetCtrlID = IDC_GRP_MAIN;
 CWnd *pWnd = this->GetDlgItem(TargetCtrlID);
 CRect RectTargetCtrl;
 pWnd->GetWindowRect(RectTargetCtrl);
 pWnd->DestroyWindow();
 this->ScreenToClient(RectTargetCtrl);
 //在目标位置动态创建CScrollView
pView = (CDesignView*)RUNTIME_CLASS(CDesignView)->CreateObject();
pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW|WS_VSCROLL|WS_HSCROLL, RectTargetCtrl, this, TargetCtrlID);
pView->OnInitialUpdate();
pView->ShowWindow(SW_SHOW);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CModuleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CModuleDlg::OnPaint()
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
HCURSOR CModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CModuleDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	::DestroyMenu(m_hMenu1);
}

void CModuleDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CPoint   pt(RYWINCX, RYWINCY); //定义宽和高  
	lpMMI->ptMinTrackSize = theApp.m_ryini.WinMinSize; //限制最小宽和高  

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}



// CModuleDlg 消息处理程序
// 根据窗口大小改变控件位置,left、right、top、bottom为4个改变维度
int CModuleDlg::MoveCtlWindow(int handler, int cx, int cy,int left, int right, int top, int bottom)
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
int CModuleDlg::MoveCtlWindow(int handler, CRect rect)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(handler);	//控件
	if(pWnd) {
		pWnd->MoveWindow(rect);	//设置控件新大小
	}

	return 0;
}

void CModuleDlg::OnSize(UINT nType, int cx, int cy)
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
	rect.left = theApp.m_ryini.DesignMenuRect.left;
	rect.right = cx - theApp.m_ryini.DesignMenuRect.right;
	rect.top = theApp.m_ryini.DesignMenuRect.top;
	rect.bottom = theApp.m_ryini.DesignMenuRect.bottom;
	MoveCtlWindow(IDC_GRP_MENU,rect);

	////菜单按钮
	int btnwidth = 32;
	int btnheight=32;
	int stepwidth = 5;

	////新增字段按钮
	rect.left = rect.left + 15;
	rect.right = rect.left + btnwidth;
	rect.top = theApp.m_ryini.DesignMenuRect.top + 10;
	rect.bottom = rect.top + btnheight;
	MoveCtlWindow(IDC_BTN_NEWITEM,rect);

	////导入图片按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_LOADJPG,rect);
	////删除图片按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_DELJPG,rect);
	////左对齐按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_ADJUSTLEFT,rect);
	////右对齐按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_ADJUSTRIGHT,rect);
	////上对齐按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_ADJUSTTOP,rect);
	////下对齐按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_ADJUSTBOTTOM,rect);
	////相同宽度按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_SAMEWIDTH,rect);
	////相同高度按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_SAMEHEIGHT,rect);


	btnwidth = 90;
	btnheight= 20;
	//退出按钮
	rect.top = theApp.m_ryini.DesignMenuRect.top + 18;
	rect.bottom = rect.top + btnheight;
	rect.right =cx - theApp.m_ryini.DesignMenuRect.right  - 10;
	rect.left = rect.right - btnwidth;
	MoveCtlWindow(IDC_BTN_EXIT,rect);
	////测试打印按钮
	rect.right = rect.left - stepwidth;
	rect.left = rect.right - btnwidth;
	MoveCtlWindow(IDC_BTN_TESTPRINT,rect);
	////保存模板按钮
	rect.right = rect.left - stepwidth;
	rect.left = rect.left - btnwidth;
	MoveCtlWindow(IDC_BTN_SAVEMOD,rect);
	////新建模板按钮
	rect.right = rect.left - stepwidth;
	rect.left = rect.left - btnwidth;
	MoveCtlWindow(IDC_BTN_NEWMOD,rect);

	//主窗口分组框
	rect.left = theApp.m_ryini.DesignMainRect.left;
	rect.right = cx - theApp.m_ryini.DesignMainRect.right;
	rect.top = theApp.m_ryini.DesignMainRect.top;
	rect.bottom = cy - theApp.m_ryini.DesignMainRect.bottom;
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
int CModuleDlg::SetButtonStatus(int nEdited)
{
	m_btnCancel.ShowWindow(FALSE);
	m_btnCancel.EnableWindow(TRUE);
	m_btnExit.ShowWindow(TRUE);
	m_btnExit.EnableWindow(TRUE);

	switch(nEdited){
	case 1:
		m_btnNewItem.EnableWindow(TRUE);
		m_btnLoadJpg.EnableWindow(TRUE);
		m_btnDelJpg.EnableWindow(TRUE);
		m_btnAdjustLeft.EnableWindow(TRUE);
		m_btnAdjustRight.EnableWindow(TRUE);
		m_btnAdjustTop.EnableWindow(TRUE);
		m_btnAdjustBottom.EnableWindow(TRUE);
		m_btnSameWidth.EnableWindow(TRUE);
		m_btnSameHeight.EnableWindow(TRUE);
		m_btnNewMod.EnableWindow(TRUE);
		m_btnSaveMod.EnableWindow(TRUE);
		m_btnTestPrint.EnableWindow(TRUE);
		break;
	default:
		m_btnNewItem.EnableWindow(FALSE);
		m_btnLoadJpg.EnableWindow(FALSE);
		m_btnDelJpg.EnableWindow(FALSE);
		m_btnAdjustLeft.EnableWindow(FALSE);
		m_btnAdjustRight.EnableWindow(FALSE);
		m_btnAdjustTop.EnableWindow(FALSE);
		m_btnAdjustBottom.EnableWindow(FALSE);
		m_btnSameWidth.EnableWindow(FALSE);
		m_btnSameHeight.EnableWindow(FALSE);
		m_btnNewMod.EnableWindow(TRUE);
		m_btnSaveMod.EnableWindow(FALSE);
		m_btnTestPrint.EnableWindow(FALSE);
		break;
	}
	return 0;
}


void CModuleDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(::MessageBox(NULL,"确定要退出吗？","程序退出", MB_YESNO) == IDYES)
		CDialogEx::OnCancel();
}

//新增元素
void CModuleDlg::OnBnClickedBtnNewitem()
{
	// TODO: 在此添加控件通知处理程序代码
}



//导入背景
void CModuleDlg::OnBnClickedBtnLoadjpg()
{
	// TODO: 在此添加控件通知处理程序代码
}

//测试打印
void CModuleDlg::OnBnClickedBtnTestprint()
{
	// TODO: 在此添加控件通知处理程序代码
}

//新建模板
void CModuleDlg::OnBnClickedBtnNewmod()
{
	if(m_nMode == 1) {
		if(::MessageBox(NULL,"当前模板未保存，是否保存？","保存模板", MB_YESNO) == IDYES) {
			OnBnClickedBtnSavemod();
		}
	}
	//一些初始化屏幕操作
	/*
	*/

	//输入新模板要素
	CDlgNewMod dlgNewMod;
	if(dlgNewMod.DoModal() == IDCANCEL)
		return;
	//AfxMessageBox(dlgNewMod.m_modName);

	//新建模板及后续处理
	m_voucher.InitBillMod(dlgNewMod.m_modName, dlgNewMod.m_modTxt, dlgNewMod.m_modWidth, dlgNewMod.m_modHeight);
	//置新模板编辑状态
	m_nMode = 1;
	SetButtonStatus(m_nMode);
	// 刷新画板
    DrawModule();

}

//保存模板
void CModuleDlg::OnBnClickedBtnSavemod()
{
	AfxMessageBox("保存模板");
	//
	m_nMode = 0;


}


//返回
void CModuleDlg::OnBnClickedBtnExit()
{
	if(m_nMode == 1) {
		if(::MessageBox(NULL,"当前模板未保存，是否保存？","保存模板", MB_YESNO) == IDYES) {
			OnBnClickedBtnSavemod();
		}
	}
	this->OnCancel();

}
// 绘制当前模板
int CModuleDlg::DrawModule(void)
{
	CDC* pDC=GetDC(); 
	return 0;
}


// 设置按钮风格
int CModuleDlg::SetButtonStyles(void)
{
	// 按钮增加元素
	m_btnNewItem.SetPicture(IDB_BITMAP_ADD);
	m_btnNewItem.SetPosition(XPBUTTON_PICTURE);
	m_btnNewItem.SetBorder(FALSE);
	m_btnNewItem.SetPictureSize(32,32);
	// 按钮导入背景
	m_btnLoadJpg.SetPicture(IDB_BITMAP_LOADJPG);
	m_btnLoadJpg.SetPosition(XPBUTTON_PICTURE);
	m_btnLoadJpg.SetBorder(FALSE);
	m_btnLoadJpg.SetPictureSize(32,32);
	// 按钮删除背景
	m_btnDelJpg.SetPicture(IDB_BITMAP_DELJPG);
	m_btnDelJpg.SetPosition(XPBUTTON_PICTURE);
	m_btnDelJpg.SetBorder(FALSE);
	m_btnDelJpg.SetPictureSize(32,32);
	// 按钮左对齐
	m_btnAdjustLeft.SetPicture(IDB_BITMAP_ALEFT);
	m_btnAdjustLeft.SetPosition(XPBUTTON_PICTURE);
	m_btnAdjustLeft.SetBorder(FALSE);
	m_btnAdjustLeft.SetPictureSize(32,32);
	// 按钮右对齐
	m_btnAdjustRight.SetPicture(IDB_BITMAP_ARIGHT);
	m_btnAdjustRight.SetPosition(XPBUTTON_PICTURE);
	m_btnAdjustRight.SetBorder(FALSE);
	m_btnAdjustRight.SetPictureSize(32,32);
	// 按钮上对齐
	m_btnAdjustTop.SetPicture(IDB_BITMAP_ATOP);
	m_btnAdjustTop.SetPosition(XPBUTTON_PICTURE);
	m_btnAdjustTop.SetBorder(FALSE);
	m_btnAdjustTop.SetPictureSize(32,32);
	// 按钮下对齐
	m_btnAdjustBottom.SetPicture(IDB_BITMAP_ABOTTOM);
	m_btnAdjustBottom.SetPosition(XPBUTTON_PICTURE);
	m_btnAdjustBottom.SetBorder(FALSE);
	m_btnAdjustBottom.SetPictureSize(32,32);
	// 按钮相同宽度
	m_btnSameWidth.SetPicture(IDB_BITMAP_SAMEWIDTH);
	m_btnSameWidth.SetPosition(XPBUTTON_PICTURE);
	m_btnSameWidth.SetBorder(FALSE);
	m_btnSameWidth.SetPictureSize(32,32);
	// 按钮相同高度
	m_btnSameHeight.SetPicture(IDB_BITMAP_SAMEHEIGHT);
	m_btnSameHeight.SetPosition(XPBUTTON_PICTURE);
	m_btnSameHeight.SetBorder(FALSE);
	m_btnSameHeight.SetPictureSize(32,32);

	// 新建模板按钮
	m_btnNewMod.SetPicture(IDB_BITMAP_NEW);
	m_btnNewMod.SetPosition(XPBUTTON_HORIZONTAL);
	m_btnNewMod.SetPictureSize(16,16);
	// 保存模板按钮
	m_btnSaveMod.SetPicture(IDB_BITMAP_SAVE);
	m_btnSaveMod.SetPosition(XPBUTTON_HORIZONTAL);
	m_btnSaveMod.SetPictureSize(16,16);
	// 测试打印按钮
	m_btnTestPrint.SetPicture(IDB_BITMAP_PRINT);
	m_btnTestPrint.SetPosition(XPBUTTON_HORIZONTAL);
	m_btnTestPrint.SetPictureSize(16,16);
	// 返回离开按钮
	m_btnExit.SetPicture(IDB_BITMAP_CANCEL);
	m_btnExit.SetPosition(XPBUTTON_HORIZONTAL);
	m_btnExit.SetPictureSize(16,16);

	return 0;
}
