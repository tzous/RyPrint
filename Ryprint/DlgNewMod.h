#pragma once
#include "afxwin.h"


// CDlgNewMod �Ի���

class CDlgNewMod : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNewMod)

public:
	CDlgNewMod(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgNewMod();

// �Ի�������
	enum { IDD = IDD_DLG_NEWMOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��������
	CEdit m_edtModName;
	CString m_modName;
	// ���ݳߴ�-��
	CEdit m_edtModWidth;
	int m_modWidth;
	// ���ݳߴ�-��
	CEdit m_edtModHeight;
	int m_modHeight;
	virtual void OnOK();
};
