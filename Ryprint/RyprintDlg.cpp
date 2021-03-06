
// RyprintDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Ryprint.h"
#include "RyprintDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DlgNewMod.h"

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRyprintDlg 对话框




CRyprintDlg::CRyprintDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRyprintDlg::IDD, pParent)
	, m_imode(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRyprintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_hBrowser);
	DDX_Control(pDX, IDC_GRP_MODULES, m_grpmodule);
	DDX_Control(pDX, IDC_EDT_STATUS, m_edtStatus);
	DDX_Control(pDX, IDC_GRP_MAIN, m_grpmain);
	DDX_Control(pDX, IDC_EDIT_MODULE, m_queryString);
	DDX_Control(pDX, IDC_BTN_MODGRPS, m_btnModgrps);
	DDX_Control(pDX, IDC_BTN_MODLOAD, m_btnModload);
	DDX_Control(pDX, IDC_BTN_MODEXPORT, m_btnModexport);
	DDX_Control(pDX, IDC_BTN_MODNEW, m_btnModnew);
	DDX_Control(pDX, IDC_BTN_MODMODIFY, m_btnModmodify);
	DDX_Control(pDX, IDC_BTN_MODDEL, m_btn_Moddel);
	DDX_Control(pDX, IDC_BTN_QUERY_MODULE, m_btnQuery);
	DDX_Control(pDX, IDC_BTN_PRINT_BILL, m_btnPrintbill);
	DDX_Control(pDX, IDC_BTN_RESET, m_btnReset);
	DDX_Control(pDX, IDC_BTN_SAVEDATA, m_btnSavedata);
	DDX_Control(pDX, IDC_BTN_DATALIST, m_btnDatalist);
	DDX_Control(pDX, IDC_BTN_PRINT_BILLS, m_btnPrintbatch);
	DDX_Control(pDX, IDC_BTN_SETUP, m_btnSetup);
}

BEGIN_MESSAGE_MAP(CRyprintDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BTN_MODNEW, &CRyprintDlg::OnBnClickedBtnModnew)
END_MESSAGE_MAP()


// CRyprintDlg 消息处理程序

BOOL CRyprintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);	//启动最大化

	//得到对话框窗口大小
	GetClientRect(&m_rect);

	//添加主菜单
	m_hMenu1=LoadMenu(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MENU1));//导入资源,创建菜单
	::SetMenu(this->GetSafeHwnd(),m_hMenu1);	//添加到对话框
		
	//广告条		   
	CString NaviPath;
	NaviPath= theApp.m_Path + "/data/bills.htm";
	m_hBrowser.Navigate(NaviPath.GetBuffer(),NULL,NULL,NULL,NULL);


	//状态栏初始状态
	m_edtStatus.SetWindowText("欢迎使用票据打印助手!");
	//模板列表设置风格及读取

	//初始化模板树
	QueryModules("");
	//按钮初始状态
	SetButtonStatus(0);
	// 设置按钮风格
	SetButtonStyles();

	//创建主画板滚动视图
CWnd* pFrameWnd = this;
pContext.m_pCurrentDoc = new CMyDocument;

pContext.m_pNewViewClass = RUNTIME_CLASS(CMyView);
pView = (CMyView *)((CFrameWnd*)pFrameWnd)->CreateView(&pContext,IDC_MAIN_BOARD );
ASSERT(pView);
pView->m_nMapMode = MM_TEXT;
pView->ShowWindow(SW_NORMAL);
/*
CRect rectWindow;
GetWindowRect(rectWindow);
rectWindow.right -= 30;
rectWindow.bottom -= 100;
pView->MoveWindow(rectWindow);
*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRyprintDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRyprintDlg::OnPaint()
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
HCURSOR CRyprintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRyprintDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	::DestroyMenu(m_hMenu1);
}



void CRyprintDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();

}


// 根据窗口大小改变控件位置,left、right、top、bottom为4个改变维度
int CRyprintDlg::MoveCtlWindow(int handler, int cx, int cy,int left, int right, int top, int bottom)
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
int CRyprintDlg::MoveCtlWindow(int handler, CRect rect)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(handler);	//控件
	if(pWnd) {
		pWnd->MoveWindow(rect);	//设置控件新大小
	}

	return 0;
}

void CRyprintDlg::OnSize(UINT nType, int cx, int cy)
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

	//模板分组框
	rect.left = theApp.m_ryini.GrpModuleRect.left;
	rect.right = theApp.m_ryini.GrpModuleRect.right;
	rect.top = theApp.m_ryini.GrpModuleRect.top;
	rect.bottom = cy - theApp.m_ryini.GrpModuleRect.bottom;
	MoveCtlWindow(IDC_GRP_MODULES,rect);
	////模板类别
	rect.left = theApp.m_ryini.GrpModuleRect.left+5;
	rect.right = rect.left+75;
	rect.top = theApp.m_ryini.GrpModuleRect.top+15;
	rect.bottom = theApp.m_ryini.GrpModuleRect.top+35;
	MoveCtlWindow(IDC_BTN_MODGRPS,rect);

	//// 模板导入
	rect.left = rect.right + 5;
	rect.right = rect.left+75;;
	MoveCtlWindow(IDC_BTN_MODLOAD,rect);

	//// 模板导出
	rect.left = rect.right + 5;
	rect.right = rect.left+75;;
	MoveCtlWindow(IDC_BTN_MODEXPORT,rect);


	///新建模板
	rect.left = theApp.m_ryini.GrpModuleRect.left + 5;
	rect.right = rect.left + 75;
	rect.top = rect.bottom + 9;
	rect.bottom = rect.top + 20;
	MoveCtlWindow(IDC_BTN_MODNEW,rect);

	////修改模板
	rect.left = rect.right + 5;
	rect.right = rect.left+75;;
	MoveCtlWindow(IDC_BTN_MODMODIFY,rect);


	////删除模板
	rect.left = rect.right + 5;
	rect.right = rect.left+75;;
	MoveCtlWindow(IDC_BTN_MODDEL,rect);


	////凭证名称
	rect.left = theApp.m_ryini.GrpModuleRect.left+5;
	rect.right = rect.left+60;
	rect.top =  rect.bottom + 9;
	rect.bottom = rect.top + 20;
	MoveCtlWindow(IDC_STATIC_MODULE,rect);
	////凭证名称输入框
	rect.left = rect.right + 5;
	rect.right = rect.left + 140;
	MoveCtlWindow(IDC_EDIT_MODULE,rect);
	////凭证查找按钮
	rect.left = rect.right + 5;
	rect.right = theApp.m_ryini.GrpModuleRect.right-5;
	MoveCtlWindow(IDC_BTN_QUERY_MODULE,rect);
	////模板列表控件
	rect.left = theApp.m_ryini.GrpModuleRect.left+2;
	rect.right = theApp.m_ryini.GrpModuleRect.right-2;
	rect.top = rect.bottom + 9;
	rect.bottom = cy - theApp.m_ryini.GrpModuleRect.bottom-2;
	MoveCtlWindow(IDC_MODULE_LIST,rect);

	//菜单按钮分组框
	rect.left = theApp.m_ryini.GrpMenuRect.left;
	rect.right = cx - theApp.m_ryini.GrpMenuRect.right;
	rect.top = theApp.m_ryini.GrpMenuRect.top;
	rect.bottom = theApp.m_ryini.GrpMenuRect.bottom;
	MoveCtlWindow(IDC_GRP_MENU,rect);

	////菜单按钮
	int btnwidth = 64;
	int btnheight= 64;
	int stepwidth = 15;
	////单据打印按钮
	rect.left = theApp.m_ryini.GrpMenuRect.left + 15;
	rect.right = rect.left + btnwidth;
	rect.top = theApp.m_ryini.GrpMenuRect.top + 18;
	rect.bottom = rect.top + btnheight;
	MoveCtlWindow(IDC_BTN_PRINT_BILL,rect);
	////重新录入按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_RESET,rect);
	////保存数据按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_SAVEDATA,rect);
	////数据仓库按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_DATALIST,rect);

	////批量打印按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_PRINT_BILLS,rect);
	////打印设置按钮
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_SETUP,rect);


	//主窗口分组框
	rect.left = theApp.m_ryini.GrpMainRect.left;
	rect.right = cx - theApp.m_ryini.GrpMainRect.right;
	rect.top = theApp.m_ryini.GrpMainRect.top;
	rect.bottom = cy - theApp.m_ryini.GrpMainRect.bottom;
	m_mainRect.SetRect(rect.left,rect.top+8,rect.right,rect.bottom);	//保存凭证主窗口大小
	MoveCtlWindow(IDC_GRP_MAIN,rect);
	MoveCtlWindow(IDC_MAIN_BOARD,rect);
	//pView->MoveWindow(rect);

	//状态条
	rect.left = 0;
	rect.right = cx ;	
	rect.top = cy - theApp.m_ryini.StatusHeight;
	rect.bottom = cy;

	MoveCtlWindow(IDC_EDT_STATUS,rect);

	GetClientRect(&m_rect);


}

void CRyprintDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CPoint   pt(RYWINCX, RYWINCY); //定义宽和高  
	lpMMI->ptMinTrackSize = theApp.m_ryini.WinMinSize; //限制最小宽和高  

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}




// 设置按钮状态
int CRyprintDlg::SetButtonStatus(int imode)
{
	return 0;
}




void CRyprintDlg::OnCancel()
{
	if(::MessageBox(NULL,"确定要退出吗？","程序退出", MB_YESNO) == IDYES)
		CDialogEx::OnCancel();
}

//退出
void CRyprintDlg::OnBnClickedBtnExit()
{
	this->OnCancel();
}

// 根据关键字查询模板
int CRyprintDlg::QueryModules(CString strQuery)
{
	//读取模板列表操作
	return 0;
}

// 查询模板按钮
void CRyprintDlg::OnBnClickedBtnQueryModule()
{
	CString strQuery;
	m_queryString.GetWindowText(strQuery);
	QueryModules(strQuery);
}


// 绘制当前模板
int CRyprintDlg::DrawModule(void)
{
	CDC* pDC=GetDC(); 
	pDC->MoveTo(m_mainRect.left,m_mainRect.top); 
		CBrush brush(RGB(240,240,240) );

		pDC->FillRect(m_mainRect,&brush); 
		//绘制空矩形占位
		//CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		//CBrush *pOldBrush=pDC->SelectObject(&brush);
		//pDC->Rectangle(m_mainRect);
		//pDC->SelectObject(pOldBrush);
		MoveCtlWindow(IDC_MAIN_BOARD,m_mainRect);
	return 0;
}


// 设置按钮风格
int CRyprintDlg::SetButtonStyles(void)
{
	// 单笔打印按钮
	m_btnPrintbill.SetPicture(IDB_BITMAP_PRINT);
	m_btnPrintbill.SetPictureSize(32,32);
	m_btnPrintbill.SetPosition(XPBUTTON_VERTICAL);
	m_btnPrintbill.SetBorder(FALSE);
	// 按钮重新录入
	m_btnReset.SetPicture(IDB_BITMAP_REFRESH);
	m_btnReset.SetPictureSize(32,32);
	m_btnReset.SetPosition(XPBUTTON_VERTICAL);
	m_btnReset.SetBorder(FALSE);
	// 按钮保存数据
	m_btnSavedata.SetPicture(IDB_BITMAP_SAVE);
	m_btnSavedata.SetPictureSize(32,32);
	m_btnSavedata.SetPosition(XPBUTTON_VERTICAL);
	m_btnSavedata.SetBorder(FALSE);
	// 按钮数据仓库
	m_btnDatalist.SetPicture(IDB_BITMAP_ADDRESS);
	m_btnDatalist.SetPictureSize(32,32);
	m_btnDatalist.SetPosition(XPBUTTON_VERTICAL);
	m_btnDatalist.SetBorder(FALSE);
	// 按钮批量打印
	m_btnPrintbatch.SetPicture(IDB_BITMAP_COPIER);
	m_btnPrintbatch.SetPictureSize(32,32);
	m_btnPrintbatch.SetPosition(XPBUTTON_VERTICAL);
	m_btnPrintbatch.SetBorder(FALSE);
	// 按钮打印设置
	m_btnSetup.SetPicture(IDB_BITMAP_SETUP);
	m_btnSetup.SetPictureSize(32,32);
	m_btnSetup.SetPosition(XPBUTTON_VERTICAL);
	m_btnSetup.SetBorder(FALSE);
	// 新建模板按钮
	m_btnModnew.SetPicture(IDB_BITMAP_NEW);
	m_btnModnew.SetPosition(XPBUTTON_HORIZONTAL);
	// 修改模板按钮
	m_btnModmodify.SetPicture(IDB_BITMAP_EDIT);
	m_btnModmodify.SetPosition(XPBUTTON_HORIZONTAL);
	// 删除模板按钮
	m_btn_Moddel.SetPicture(IDB_BITMAP_DEL);
	m_btn_Moddel.SetPosition(XPBUTTON_HORIZONTAL);
	// 按钮查
	m_btnQuery.SetPicture(IDB_BITMAP_QUERY);
	m_btnQuery.SetPosition(XPBUTTON_PICTURE);


	return 0;
}

//点击新建模板按钮

void CRyprintDlg::OnBnClickedBtnModnew()
{
	
	m_moduleDlg.DoModal();

}
