
// RyprintDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Ryprint.h"
#include "RyprintDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DlgNewMod.h"
#include "ModlueDlg.h"

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CRyprintDlg �Ի���




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
	DDX_Control(pDX, IDC_BTN_QUERY_MODULE, m_btnQuery);
}

BEGIN_MESSAGE_MAP(CRyprintDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CRyprintDlg ��Ϣ�������

BOOL CRyprintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);	//�������

	//�õ��Ի��򴰿ڴ�С
	GetClientRect(&m_rect);

	//������˵�
	m_hMenu1=LoadMenu(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MENU1));//������Դ,�����˵�
	::SetMenu(this->GetSafeHwnd(),m_hMenu1);	//��ӵ��Ի���
		
	//�����		   
	CString NaviPath;
	NaviPath= theApp.m_Path + "/bills.htm";
	m_hBrowser.Navigate(NaviPath.GetBuffer(),NULL,NULL,NULL,NULL);

	//��ť��ʼ״̬
	SetButtonStatus(0);
	//״̬����ʼ״̬
	m_edtStatus.SetWindowText("��ӭʹ��Ʊ�ݴ�ӡ����!");
	//ģ���б����÷�񼰶�ȡ

	//��ʼ��ģ����
	QueryModules("");

	//���������������ͼ
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
	//���밴ťͼ��
	LoadBtnIcon();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRyprintDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
		DrawModule();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRyprintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRyprintDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	::DestroyMenu(m_hMenu1);
}



void CRyprintDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();

}


// ���ݴ��ڴ�С�ı�ؼ�λ��,left��right��top��bottomΪ4���ı�ά��
int CRyprintDlg::MoveCtlWindow(int handler, int cx, int cy,int left, int right, int top, int bottom)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(handler);	//�ؼ�
	if(pWnd) {
		CRect rect;	
		pWnd->GetWindowRect(&rect);		//��ȡ�ؼ��仯ǰ��С
		ScreenToClient(&rect);			//���ؼ���Сת��Ϊ�Ի����е���������
		// cx/m_rect.Width() Ϊ�Ի������仯��������
		if(left == 1) rect.left = rect.left * cx/m_rect.Width();
		if(right == 1) rect.right = rect.right * cx/m_rect.Width();
		if(top == 1) rect.top = rect.top * cy/m_rect.Height();
		if(bottom == 1) rect.bottom = rect.bottom * cy/m_rect.Height();
		pWnd->MoveWindow(rect);	//���ÿؼ��´�С
	}

	return 0;
}

// ���ݴ��ڴ�С�ı�ؼ�λ�ã�rectΪ�µĴ���λ��
int CRyprintDlg::MoveCtlWindow(int handler, CRect rect)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(handler);	//�ؼ�
	if(pWnd) {
		pWnd->MoveWindow(rect);	//���ÿؼ��´�С
	}

	return 0;
}

void CRyprintDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(nType == 1) return;		//���������С��

	CRect rect;	
	//�����
	rect.left = theApp.m_ryini.AdRect.left;
	rect.right = cx - theApp.m_ryini.AdRect.right;
	rect.top = theApp.m_ryini.AdRect.top;
	rect.bottom = theApp.m_ryini.AdRect.bottom;

	MoveCtlWindow(IDC_EXPLORER1,rect);

	//ģ������
	rect.left = theApp.m_ryini.GrpModuleRect.left;
	rect.right = theApp.m_ryini.GrpModuleRect.right;
	rect.top = theApp.m_ryini.GrpModuleRect.top;
	rect.bottom = cy - theApp.m_ryini.GrpModuleRect.bottom;
	MoveCtlWindow(IDC_GRP_MODULES,rect);
	////ģ�����
	rect.left = theApp.m_ryini.GrpModuleRect.left+5;
	rect.right = rect.left+75;
	rect.top = theApp.m_ryini.GrpModuleRect.top+15;
	rect.bottom = theApp.m_ryini.GrpModuleRect.top+35;
	MoveCtlWindow(IDC_BTN_MODGRPS,rect);

	//// ģ�嵼��
	rect.left = rect.right + 5;
	rect.right = rect.left+75;;
	MoveCtlWindow(IDC_BTN_MODLOAD,rect);

	//// ģ�嵼��
	rect.left = rect.right + 5;
	rect.right = rect.left+75;;
	MoveCtlWindow(IDC_BTN_MODEXPORT,rect);


	///�½�ģ��
	rect.left = theApp.m_ryini.GrpModuleRect.left + 5;
	rect.right = rect.left + 75;
	rect.top = rect.bottom + 9;
	rect.bottom = rect.top + 20;
	MoveCtlWindow(IDC_BTN_MODNEW,rect);

	////�޸�ģ��
	rect.left = rect.right + 5;
	rect.right = rect.left+75;;
	MoveCtlWindow(IDC_BTN_MODMODIFY,rect);


	////ɾ��ģ��
	rect.left = rect.right + 5;
	rect.right = rect.left+75;;
	MoveCtlWindow(IDC_BTN_MODDEL,rect);


	////ƾ֤����
	rect.left = theApp.m_ryini.GrpModuleRect.left+5;
	rect.right = rect.left+60;
	rect.top =  rect.bottom + 9;
	rect.bottom = rect.top + 20;
	MoveCtlWindow(IDC_STATIC_MODULE,rect);
	////ƾ֤���������
	rect.left = rect.right + 5;
	rect.right = rect.left + 140;
	MoveCtlWindow(IDC_EDIT_MODULE,rect);
	////ƾ֤���Ұ�ť
	rect.left = rect.right + 5;
	rect.right = theApp.m_ryini.GrpModuleRect.right-5;
	MoveCtlWindow(IDC_BTN_QUERY_MODULE,rect);
	////ģ���б�ؼ�
	rect.left = theApp.m_ryini.GrpModuleRect.left+2;
	rect.right = theApp.m_ryini.GrpModuleRect.right-2;
	rect.top = rect.bottom + 9;
	rect.bottom = cy - theApp.m_ryini.GrpModuleRect.bottom-2;
	MoveCtlWindow(IDC_MODULE_LIST,rect);

	//�˵���ť�����
	rect.left = theApp.m_ryini.GrpMenuRect.left;
	rect.right = cx - theApp.m_ryini.GrpMenuRect.right;
	rect.top = theApp.m_ryini.GrpMenuRect.top;
	rect.bottom = theApp.m_ryini.GrpMenuRect.bottom;
	MoveCtlWindow(IDC_GRP_MENU,rect);

	////�˵���ť
	int btnwidth = 64;
	int btnheight= 64;
	int stepwidth = 15;
	////���ݴ�ӡ��ť
	rect.left = theApp.m_ryini.GrpMenuRect.left + 15;
	rect.right = rect.left + btnwidth;
	rect.top = theApp.m_ryini.GrpMenuRect.top + 18;
	rect.bottom = rect.top + btnheight;
	MoveCtlWindow(IDC_BTN_PRINT_BILL,rect);
	////����¼�밴ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_RESET,rect);
	////�������ݰ�ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_SAVEDATA,rect);
	////���ݲֿⰴť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_DATALIST,rect);

	////������ӡ��ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_PRINT_BILLS,rect);
	////��ӡ���ð�ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_SETUP,rect);


	//�����ڷ����
	rect.left = theApp.m_ryini.GrpMainRect.left;
	rect.right = cx - theApp.m_ryini.GrpMainRect.right;
	rect.top = theApp.m_ryini.GrpMainRect.top;
	rect.bottom = cy - theApp.m_ryini.GrpMainRect.bottom;
	m_mainRect.SetRect(rect.left,rect.top+8,rect.right,rect.bottom);	//����ƾ֤�����ڴ�С
	MoveCtlWindow(IDC_GRP_MAIN,rect);
	MoveCtlWindow(IDC_MAIN_BOARD,rect);
	//pView->MoveWindow(rect);

	//״̬��
	rect.left = 0;
	rect.right = cx ;	
	rect.top = cy - theApp.m_ryini.StatusHeight;
	rect.bottom = cy;

	MoveCtlWindow(IDC_EDT_STATUS,rect);

	GetClientRect(&m_rect);


}

void CRyprintDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CPoint   pt(RYWINCX, RYWINCY); //�����͸�  
	lpMMI->ptMinTrackSize = theApp.m_ryini.WinMinSize; //������С��͸�  

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}




// ���ð�ť״̬
int CRyprintDlg::SetButtonStatus(int imode)
{
	return 0;
}

//���ģ����ư�ť
void CRyprintDlg::OnBnClickedBtnDesignModule()
{
	CModlueDlg modlueDlg;
	modlueDlg.DoModal();

}


void CRyprintDlg::OnCancel()
{
	if(::MessageBox(NULL,"ȷ��Ҫ�˳���","�����˳�", MB_YESNO) == IDYES)
		CDialogEx::OnCancel();
}

//�˳�
void CRyprintDlg::OnBnClickedBtnExit()
{
	this->OnCancel();
}

// ���ݹؼ��ֲ�ѯģ��
int CRyprintDlg::QueryModules(CString strQuery)
{
	//��ȡģ���б����
	return 0;
}

// ��ѯģ�尴ť
void CRyprintDlg::OnBnClickedBtnQueryModule()
{
	CString strQuery;
	m_queryString.GetWindowText(strQuery);
	QueryModules(strQuery);
}


// ���Ƶ�ǰģ��
int CRyprintDlg::DrawModule(void)
{
	CDC* pDC=GetDC(); 
	if(m_currModule.getIsInit()) {
		m_currModule.Draw(pDC,m_mainRect);	//����ǰƾ֤
	} else {	//�ñ���ɫ���ƾ֤ģ�崰��
		pDC->MoveTo(m_mainRect.left,m_mainRect.top); 
		CBrush brush(RGB(240,240,240) );

		pDC->FillRect(m_mainRect,&brush); 
		//���ƿվ���ռλ
		//CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		//CBrush *pOldBrush=pDC->SelectObject(&brush);
		//pDC->Rectangle(m_mainRect);
		//pDC->SelectObject(pOldBrush);
		MoveCtlWindow(IDC_MAIN_BOARD,m_mainRect);
	}
	
	return 0;
}




// ���밴ťͼ��
int CRyprintDlg::LoadBtnIcon(void)
{

	return 0;
}
