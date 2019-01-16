#pragma once
#include "afxwin.h"


// CDlgNewMod 对话框

class CDlgNewMod : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNewMod)

public:
	CDlgNewMod(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNewMod();

// 对话框数据
	enum { IDD = IDD_DLG_NEWMOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 单据名称
	CEdit m_edtModName;
	CString m_modName;
	// 单据尺寸-宽
	CEdit m_edtModWidth;
	int m_modWidth;
	// 单据尺寸-高
	CEdit m_edtModHeight;
	int m_modHeight;
	virtual void OnOK();
};
