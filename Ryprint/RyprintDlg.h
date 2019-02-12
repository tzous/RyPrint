
// RyprintDlg.h : ͷ�ļ�
//

#pragma once
#include "explorer1.h"
#include "atltypes.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "MyView.h"
#include "XPButton.h"		//�Ի水ť��
#include "MyDocument.h"
#include "ModuleDlg.h"

// CRyprintDlg �Ի���
class CRyprintDlg : public CDialogEx
{
// ����
public:
	CRyprintDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RYPRINT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
public:
	// ���˵�
	HMENU m_hMenu1;
	// �����
	CExplorer1 m_hBrowser;
	// �Ի��������ڴ�С
	CRect m_rect;
	// ���ݴ��ڴ�С�ı�ؼ�λ��,left��right��top��bottomΪ4���ı�ά��
	int MoveCtlWindow(int handler, int cx, int cy,int left, int right, int top, int bottom);
	// ���ݴ��ڴ�С�ı�ؼ�λ�ã�rectΪ�µĴ���λ��
	int MoveCtlWindow(int handler, CRect rect);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);


	// ģ������
	CStatic m_grpmodule;
	// ״̬��
	CEdit m_edtStatus;
	// �����ڷ���
	CStatic m_grpmain;
	// ƾ֤���ڴ�С
	CRect m_mainRect;

	// ���ݲ�ѯ�ؼ���
	CEdit m_queryString;
	// ��ǰģʽ 0-δѡ��ģ���ӡ 1-ѡ��ģ���ӡ 2-ģ����ƣ���ģ��δ��ʼ�� 3-ģ��༭״̬
	int m_imode;

	// ���ð�ť״̬
	int SetButtonStatus(int imode);
	// �뿪�˳������¼�
	afx_msg void OnBnClickedBtnExit();
	// ���ݹؼ��ֲ�ѯģ��
	int QueryModules(CString strQuery);
	//���ģ���ѯ��ť�¼�
	afx_msg void OnBnClickedBtnQueryModule();
	//�˳�ϵͳ
	virtual void OnCancel();
	// ���Ƶ�ǰģ��
	int DrawModule(void);
	//�����������ͼ
	CMyView* pView;
	//�������ĵ�
	CCreateContext pContext;
	CModuleDlg m_moduleDlg;

	// ��ť������
	CXPButton m_btnModgrps;
	// ��ťģ�嵼��
	CXPButton m_btnModload;
	// ��ťģ�嵼��
	CXPButton m_btnModexport;
	// ��ť�½�ģ��
	CXPButton m_btnModnew;
	// ��ťģ���޸�
	CXPButton m_btnModmodify;
	// ��ťģ��ɾ��
	CXPButton m_btn_Moddel;
	// ��ť��
	CXPButton m_btnQuery;
	// ��ť���ʴ�ӡ
	CXPButton m_btnPrintbill;
	// ��ť����¼��
	CXPButton m_btnReset;
	// ��ť��������
	CXPButton m_btnSavedata;
	// ��ť���ݲֿ�
	CXPButton m_btnDatalist;
	// ��ť������ӡ
	CXPButton m_btnPrintbatch;
	// ��ť��ӡ����
	CXPButton m_btnSetup;
	// ���ð�ť���
	int SetButtonStyles(void);
	afx_msg void OnBnClickedBtnModnew();
};
