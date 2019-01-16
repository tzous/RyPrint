// DlgNewMod.cpp : 实现文件
//

#include "stdafx.h"
#include "Ryprint.h"
#include "DlgNewMod.h"
#include "afxdialogex.h"


// CDlgNewMod 对话框

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


// CDlgNewMod 消息处理程序


void CDlgNewMod::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	if(m_modName.Trim().IsEmpty()) {
		AfxMessageBox("输入要素不能为空！");
		return;
	}
	if( m_modWidth<10 || m_modWidth>210) {
		AfxMessageBox("单据宽度范围不正确，只能输入10-210之间的数字！");
		return;
	}
	if( m_modHeight<10 || m_modHeight>300) {
		AfxMessageBox("单据高度范围不正确，只能输入10-300之间的数字！");
		return;
	}
	CDialogEx::OnOK();
}
