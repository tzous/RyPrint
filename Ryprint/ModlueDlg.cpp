// ModlueDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Ryprint.h"
#include "ModlueDlg.h"
#include "afxdialogex.h"

#include "DlgNewMod.h"

// CModlueDlg �Ի���

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
	NaviPath= theApp.m_Path + "/bills.htm";
	m_hBrowser.Navigate(NaviPath.GetBuffer(),NULL,NULL,NULL,NULL);

	//��ť��ʼ״̬
	SetButtonStatus(0);
	//״̬����ʼ״̬
	m_edtStatus.SetWindowText("��ӭʹ��Ʊ�ݴ�ӡ����!");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CModlueDlg::OnPaint()
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
HCURSOR CModlueDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CModlueDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	::DestroyMenu(m_hMenu1);
}

void CModlueDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CPoint   pt(RYWINCX, RYWINCY); //�����͸�  
	lpMMI->ptMinTrackSize = theApp.m_ryini.WinMinSize; //������С��͸�  

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}



// CModlueDlg ��Ϣ�������
// ���ݴ��ڴ�С�ı�ؼ�λ��,left��right��top��bottomΪ4���ı�ά��
int CModlueDlg::MoveCtlWindow(int handler, int cx, int cy,int left, int right, int top, int bottom)
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
int CModlueDlg::MoveCtlWindow(int handler, CRect rect)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(handler);	//�ؼ�
	if(pWnd) {
		pWnd->MoveWindow(rect);	//���ÿؼ��´�С
	}

	return 0;
}

void CModlueDlg::OnSize(UINT nType, int cx, int cy)
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
	rect.left = theApp.m_ryini.AdRect.left;
	rect.right = cx - theApp.m_ryini.GrpMenuRect.right;
	rect.top = theApp.m_ryini.GrpMenuRect.top;
	rect.bottom = theApp.m_ryini.GrpMenuRect.bottom;
	MoveCtlWindow(IDC_GRP_MENU,rect);

	////�˵���ť
	int btnwidth = 70;
	int btnheight=25;
	int stepwidth = 5;

	////�����ֶΰ�ť
	rect.left = theApp.m_ryini.AdRect.left + 15;
	rect.right = rect.left + btnwidth;
	rect.top = theApp.m_ryini.GrpMenuRect.top + 20;
	rect.bottom = rect.top + btnheight;
	MoveCtlWindow(IDC_BTN_NEWITEM,rect);
	////�޸��ֶ����԰�ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_ITEMATTR,rect);

	////ɾ���ֶ����԰�ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_DELITEM,rect);

	////����ͼƬ��ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_LOADJPG,rect);
	////���Դ�ӡ��ť
	rect.left = rect.right + stepwidth;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_TESTPRINT,rect);


	//�˳���ť
	rect.left =cx - theApp.m_ryini.GrpMenuRect.right - btnwidth - 10;
	rect.right = rect.left + btnwidth;
	MoveCtlWindow(IDC_BTN_EXIT,rect);

	////ɾ��ģ�尴ť
	rect.right =cx - theApp.m_ryini.GrpMenuRect.right - btnwidth - 10 - stepwidth;
	rect.left = rect.right -btnwidth;
	MoveCtlWindow(IDC_BTN_DELMOD,rect);

	////����ģ�尴ť
	rect.right = rect.left - stepwidth;
	rect.left = rect.right -btnwidth;
	MoveCtlWindow(IDC_BTN_SAVEMOD,rect);

	////�½�ģ�尴ť
	rect.right = rect.left - stepwidth;
	rect.left = rect.right -btnwidth;
	MoveCtlWindow(IDC_BTN_NEWMOD,rect);

	//�����ڷ����
	rect.left = theApp.m_ryini.AdRect.left;
	rect.right = cx - theApp.m_ryini.GrpMainRect.right;
	rect.top = theApp.m_ryini.GrpMainRect.top;
	rect.bottom = cy - theApp.m_ryini.GrpMainRect.bottom;
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
	// TODO: �ڴ����ר�ô����/����û���
	if(::MessageBox(NULL,"ȷ��Ҫ�˳���","�����˳�", MB_YESNO) == IDYES)
		CDialogEx::OnCancel();
}

//����Ԫ��
void CModlueDlg::OnBnClickedBtnNewitem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//ɾ��Ԫ��
void CModlueDlg::OnBnClickedBtnDelitem()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�޸�Ԫ��
void CModlueDlg::OnBnClickedBtnItemattr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//���뱳��
void CModlueDlg::OnBnClickedBtnLoadjpg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//���Դ�ӡ
void CModlueDlg::OnBnClickedBtnTestprint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�½�ģ��
void CModlueDlg::OnBnClickedBtnNewmod()
{
	if(m_currModule.getIsModified() > 0) {
		if(::MessageBox(NULL,"��ǰģ��δ���棬�Ƿ񱣴棿","����ģ��", MB_YESNO) == IDYES) {
			OnBnClickedBtnSavemod();
		}
	}
	//������ģ��Ҫ��
	CDlgNewMod dlgNewMod;
	if(dlgNewMod.DoModal() == IDCANCEL)
		return;
	AfxMessageBox(dlgNewMod.m_modName);

	//�½�ģ�弰��������
	m_currModule.InitBillMod(dlgNewMod.m_modName, dlgNewMod.m_modWidth, dlgNewMod.m_modHeight);
	//����ģ��༭״̬

	m_imode = 1;			//��ť״̬
	SetButtonStatus(m_imode);
	//����ʼģ��ռλ��
    DrawModule();

}

//����ģ��
void CModlueDlg::OnBnClickedBtnSavemod()
{
	AfxMessageBox("����ģ��");
	m_currModule.SaveBillMod();

}

//ɾ��ģ��
void CModlueDlg::OnBnClickedBtnDelmod()
{
	if(::MessageBox(NULL,"�Ƿ�ɾ����ǰģ�壿","ɾ��ģ��", MB_YESNO) == IDNO)
		return;
	
	m_imode = 0;
	SetButtonStatus(m_imode);
	//ɾ��ģ�弰��������
	m_currModule.DelBillMod();
	
	//DrawModule();

}

//����
void CModlueDlg::OnBnClickedBtnExit()
{
	if(m_currModule.getIsModified()) {
		if(::MessageBox(NULL,"��ǰģ��δ���棬�Ƿ񱣴棿","����ģ��", MB_YESNO) == IDYES) {
			OnBnClickedBtnSavemod();
		}
	}
	this->OnCancel();

}
// ���Ƶ�ǰģ��
int CModlueDlg::DrawModule(void)
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
	}
	
	return 0;
}
