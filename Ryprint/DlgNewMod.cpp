// DlgNewMod.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Ryprint.h"
#include "DlgNewMod.h"
#include "afxdialogex.h"


// CDlgNewMod �Ի���

IMPLEMENT_DYNAMIC(CDlgNewMod, CDialogEx)

CDlgNewMod::CDlgNewMod(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgNewMod::IDD, pParent)
	, m_modName(_T(""))
	, m_modWidth(0)
	, m_modHeight(0)
{

}

CDlgNewMod::~CDlgNewMod()
{
}

void CDlgNewMod::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MODNAME, m_edtModName);
	DDX_Control(pDX, IDC_EDIT_MODWIDTH, m_edtModWidth);
	DDX_Control(pDX, IDC_EDIT_MODHEIGHT, m_edtModHeight);
	DDX_Text(pDX, IDC_EDIT_MODNAME, m_modName);
	DDX_Text(pDX, IDC_EDIT_MODWIDTH, m_modWidth);
	DDX_Text(pDX, IDC_EDIT_MODHEIGHT, m_modHeight);
}


BEGIN_MESSAGE_MAP(CDlgNewMod, CDialogEx)
END_MESSAGE_MAP()


// CDlgNewMod ��Ϣ�������


void CDlgNewMod::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	if(m_modName.Trim().IsEmpty()) {
		AfxMessageBox("����Ҫ�ز���Ϊ�գ�");
		return;
	}
	if( m_modWidth<10 || m_modWidth>210) {
		AfxMessageBox("���ݿ�ȷ�Χ����ȷ��ֻ������10-210֮������֣�");
		return;
	}
	if( m_modHeight<10 || m_modHeight>300) {
		AfxMessageBox("���ݸ߶ȷ�Χ����ȷ��ֻ������10-300֮������֣�");
		return;
	}
	CDialogEx::OnOK();
}
