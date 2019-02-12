// ModlueDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Ryprint.h"
#include "ModuleDlg.h"
#include "afxdialogex.h"

#include "DlgNewMod.h"

// CModuleDlg �Ի���

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	//SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��

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
	ShowWindow(SW_MAXIMIZE);	//�������

	//�õ��Ի��򴰿ڴ�С
	GetClientRect(&m_rect);

	//������˵�
	//m_hMenu1=LoadMenu(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MENU1));//������Դ,�����˵�
	//::SetMenu(this->GetSafeHwnd(),m_hMenu1);	//��ӵ��Ի���
		
	//�����		   
	CString NaviPath;
	NaviPath= theApp.m_Path + "/data/bills.htm";
	m_hBrowser.Navigate(NaviPath.GetBuffer(),NULL,NULL,NULL,NULL);

	//״̬����ʼ״̬
	m_edtStatus.SetWindowText("��ӭʹ��Ʊ�ݴ�ӡ����!");
	//�Ǳ༭״̬
	//m_nMode = 0;
    m_nMode = 1;
	m_voucher.InitBillMod("NAMENAME", "TXTXTXT", 210, 145);

	//���ð�ť���
	SetButtonStyles();
	//��ť��ʼ״̬
	SetButtonStatus(m_nMode);
		//���������������ͼ

 UINT TargetCtrlID = IDC_GRP_MAIN;
 CWnd *pWnd = this->GetDlgItem(TargetCtrlID);
 CRect RectTargetCtrl;
 pWnd->GetWindowRect(RectTargetCtrl);
 pWnd->DestroyWindow();
 this->ScreenToClient(RectTargetCtrl);
 //��Ŀ��λ�ö�̬����CScrollView
pView = (CDesignView*)RUNTIME_CLASS(CDesignView)->CreateObject();
pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW|WS_VSCROLL|WS_HSCROLL, RectTargetCtrl, this, TargetCtrlID);
pView->OnInitialUpdate();
pView->ShowWindow(SW_SHOW);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CModuleDlg::OnPaint()
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
HCURSOR CModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CModuleDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	::DestroyMenu(m_hMenu1);
}

void CModuleDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CPoint   pt(RYWINCX, RYWINCY); //�����͸�  
	lpMMI->ptMinTrackSize = theApp.m_ryini.WinMinSize; //������С��͸�  

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}



// CModuleDlg ��Ϣ�������
// ���ݴ��ڴ�С�ı�ؼ�λ��,left��right��top��bottomΪ4���ı�ά��
int CModuleDlg::MoveCtlWindow(int handler, int cx, int cy,int left, int right, int top, int bottom)
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
int CModuleDlg::MoveCtlWindow(int handler, CRect rect)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(handler);	//�ؼ�
	if(pWnd) {
		pWnd->MoveWindow(rect);	//���ÿؼ��´�С
	}

	return 0;
}

void CModuleDlg::OnSize(UINT nType, int cx, int cy)
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


	//�˵���ť�����
	rect.left = theApp.m_ryini.DesignMenuRect.left;
	rect.right = cx - theApp.m_ryini.DesignMenuRect.right;
	rect.top = theApp.m_ryini.DesignMenuRect.top;
	rect.bottom = theApp.m_ryini.DesignMenuRect.bottom;
	MoveCtlWindow(IDC_GRP_MENU,rect);

	////�˵���ť
	int btnwidth = 32;
	int btnheight=32;
	int stepwidth = 5;

	////�����ֶΰ�ť
	rect.left = rect.left + 15;
	rect.right = rect.left + btnwidth;
	rect.top = theApp.m_ryini.DesignMenuRect.top + 10;
	rect.bottom = rect.top + btnheight;
	MoveCtlWindow(IDC_BTN_NEWITEM,rect);

	////����ͼƬ��ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_LOADJPG,rect);
	////ɾ��ͼƬ��ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_DELJPG,rect);
	////����밴ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_ADJUSTLEFT,rect);
	////�Ҷ��밴ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_ADJUSTRIGHT,rect);
	////�϶��밴ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_ADJUSTTOP,rect);
	////�¶��밴ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_ADJUSTBOTTOM,rect);
	////��ͬ��Ȱ�ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_SAMEWIDTH,rect);
	////��ͬ�߶Ȱ�ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_SAMEHEIGHT,rect);


	btnwidth = 90;
	btnheight= 20;
	//�˳���ť
	rect.top = theApp.m_ryini.DesignMenuRect.top + 18;
	rect.bottom = rect.top + btnheight;
	rect.right =cx - theApp.m_ryini.DesignMenuRect.right  - 10;
	rect.left = rect.right - btnwidth;
	MoveCtlWindow(IDC_BTN_EXIT,rect);
	////���Դ�ӡ��ť
	rect.right = rect.left - stepwidth;
	rect.left = rect.right - btnwidth;
	MoveCtlWindow(IDC_BTN_TESTPRINT,rect);
	////����ģ�尴ť
	rect.right = rect.left - stepwidth;
	rect.left = rect.left - btnwidth;
	MoveCtlWindow(IDC_BTN_SAVEMOD,rect);
	////�½�ģ�尴ť
	rect.right = rect.left - stepwidth;
	rect.left = rect.left - btnwidth;
	MoveCtlWindow(IDC_BTN_NEWMOD,rect);

	//�����ڷ����
	rect.left = theApp.m_ryini.DesignMainRect.left;
	rect.right = cx - theApp.m_ryini.DesignMainRect.right;
	rect.top = theApp.m_ryini.DesignMainRect.top;
	rect.bottom = cy - theApp.m_ryini.DesignMainRect.bottom;
	m_mainRect.SetRect(rect.left,rect.top+8,rect.right,rect.bottom);	//����ƾ֤�����ڴ�С
	MoveCtlWindow(IDC_GRP_MAIN,rect);

	//״̬��
	rect.left = 0;
	rect.right = cx ;	
	rect.top = cy - theApp.m_ryini.StatusHeight;
	rect.bottom = cy;

	MoveCtlWindow(IDC_EDT_STATUS,rect);

	GetClientRect(&m_rect);

	
}
// ���ð�ť״̬
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
	// TODO: �ڴ����ר�ô����/����û���
	if(::MessageBox(NULL,"ȷ��Ҫ�˳���","�����˳�", MB_YESNO) == IDYES)
		CDialogEx::OnCancel();
}

//����Ԫ��
void CModuleDlg::OnBnClickedBtnNewitem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



//���뱳��
void CModuleDlg::OnBnClickedBtnLoadjpg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//���Դ�ӡ
void CModuleDlg::OnBnClickedBtnTestprint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�½�ģ��
void CModuleDlg::OnBnClickedBtnNewmod()
{
	if(m_nMode == 1) {
		if(::MessageBox(NULL,"��ǰģ��δ���棬�Ƿ񱣴棿","����ģ��", MB_YESNO) == IDYES) {
			OnBnClickedBtnSavemod();
		}
	}
	//һЩ��ʼ����Ļ����
	/*
	*/

	//������ģ��Ҫ��
	CDlgNewMod dlgNewMod;
	if(dlgNewMod.DoModal() == IDCANCEL)
		return;
	//AfxMessageBox(dlgNewMod.m_modName);

	//�½�ģ�弰��������
	m_voucher.InitBillMod(dlgNewMod.m_modName, dlgNewMod.m_modTxt, dlgNewMod.m_modWidth, dlgNewMod.m_modHeight);
	//����ģ��༭״̬
	m_nMode = 1;
	SetButtonStatus(m_nMode);
	// ˢ�»���
    DrawModule();

}

//����ģ��
void CModuleDlg::OnBnClickedBtnSavemod()
{
	AfxMessageBox("����ģ��");
	//
	m_nMode = 0;


}


//����
void CModuleDlg::OnBnClickedBtnExit()
{
	if(m_nMode == 1) {
		if(::MessageBox(NULL,"��ǰģ��δ���棬�Ƿ񱣴棿","����ģ��", MB_YESNO) == IDYES) {
			OnBnClickedBtnSavemod();
		}
	}
	this->OnCancel();

}
// ���Ƶ�ǰģ��
int CModuleDlg::DrawModule(void)
{
	CDC* pDC=GetDC(); 
	return 0;
}


// ���ð�ť���
int CModuleDlg::SetButtonStyles(void)
{
	// ��ť����Ԫ��
	m_btnNewItem.SetPicture(IDB_BITMAP_ADD);
	m_btnNewItem.SetPosition(XPBUTTON_PICTURE);
	m_btnNewItem.SetBorder(FALSE);
	m_btnNewItem.SetPictureSize(32,32);
	// ��ť���뱳��
	m_btnLoadJpg.SetPicture(IDB_BITMAP_LOADJPG);
	m_btnLoadJpg.SetPosition(XPBUTTON_PICTURE);
	m_btnLoadJpg.SetBorder(FALSE);
	m_btnLoadJpg.SetPictureSize(32,32);
	// ��ťɾ������
	m_btnDelJpg.SetPicture(IDB_BITMAP_DELJPG);
	m_btnDelJpg.SetPosition(XPBUTTON_PICTURE);
	m_btnDelJpg.SetBorder(FALSE);
	m_btnDelJpg.SetPictureSize(32,32);
	// ��ť�����
	m_btnAdjustLeft.SetPicture(IDB_BITMAP_ALEFT);
	m_btnAdjustLeft.SetPosition(XPBUTTON_PICTURE);
	m_btnAdjustLeft.SetBorder(FALSE);
	m_btnAdjustLeft.SetPictureSize(32,32);
	// ��ť�Ҷ���
	m_btnAdjustRight.SetPicture(IDB_BITMAP_ARIGHT);
	m_btnAdjustRight.SetPosition(XPBUTTON_PICTURE);
	m_btnAdjustRight.SetBorder(FALSE);
	m_btnAdjustRight.SetPictureSize(32,32);
	// ��ť�϶���
	m_btnAdjustTop.SetPicture(IDB_BITMAP_ATOP);
	m_btnAdjustTop.SetPosition(XPBUTTON_PICTURE);
	m_btnAdjustTop.SetBorder(FALSE);
	m_btnAdjustTop.SetPictureSize(32,32);
	// ��ť�¶���
	m_btnAdjustBottom.SetPicture(IDB_BITMAP_ABOTTOM);
	m_btnAdjustBottom.SetPosition(XPBUTTON_PICTURE);
	m_btnAdjustBottom.SetBorder(FALSE);
	m_btnAdjustBottom.SetPictureSize(32,32);
	// ��ť��ͬ���
	m_btnSameWidth.SetPicture(IDB_BITMAP_SAMEWIDTH);
	m_btnSameWidth.SetPosition(XPBUTTON_PICTURE);
	m_btnSameWidth.SetBorder(FALSE);
	m_btnSameWidth.SetPictureSize(32,32);
	// ��ť��ͬ�߶�
	m_btnSameHeight.SetPicture(IDB_BITMAP_SAMEHEIGHT);
	m_btnSameHeight.SetPosition(XPBUTTON_PICTURE);
	m_btnSameHeight.SetBorder(FALSE);
	m_btnSameHeight.SetPictureSize(32,32);

	// �½�ģ�尴ť
	m_btnNewMod.SetPicture(IDB_BITMAP_NEW);
	m_btnNewMod.SetPosition(XPBUTTON_HORIZONTAL);
	m_btnNewMod.SetPictureSize(16,16);
	// ����ģ�尴ť
	m_btnSaveMod.SetPicture(IDB_BITMAP_SAVE);
	m_btnSaveMod.SetPosition(XPBUTTON_HORIZONTAL);
	m_btnSaveMod.SetPictureSize(16,16);
	// ���Դ�ӡ��ť
	m_btnTestPrint.SetPicture(IDB_BITMAP_PRINT);
	m_btnTestPrint.SetPosition(XPBUTTON_HORIZONTAL);
	m_btnTestPrint.SetPictureSize(16,16);
	// �����뿪��ť
	m_btnExit.SetPicture(IDB_BITMAP_CANCEL);
	m_btnExit.SetPosition(XPBUTTON_HORIZONTAL);
	m_btnExit.SetPictureSize(16,16);

	return 0;
}
