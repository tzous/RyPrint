#pragma once
#include "explorer1.h"
#include "XPButton.h"

// CModuleDlg �Ի���

class CModuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModuleDlg)

public:
	CModuleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModuleDlg();

// �Ի�������
	enum { IDD = IDD_MODULE_DIALOG };

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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


	// ״̬��
	CEdit m_edtStatus;
	// �����ڷ���
	CStatic m_grpmain;
	// ƾ֤���ڴ�С
	CRect m_mainRect;

	// ��ǰģʽ 0-δѡ��ģ���ӡ 1-ѡ��ģ���ӡ 2-ģ����ƣ���ģ��δ��ʼ�� 3-ģ��༭״̬
	int m_imode;
	//��ǰƾ֤ģ��
	CBillModule m_currModule;


	// �����ֶ�
	CXPButton m_btnNewItem;
	// ���뱳��
	CXPButton m_btnLoadJpg;
	// ɾ������
	CXPButton m_btnDelJpg;
	// �����
	CXPButton m_btnAdjustLeft;
	// �Ҷ���
	CXPButton m_btnAdjustRight;
	// �϶���
	CXPButton m_btnAdjustTop;
	// �¶���
	CXPButton m_btnAdjustBottom;
	// ��ͬ���
	CXPButton m_btnSameWidth;
	// ��ͬ�߶�
	CXPButton m_btnSameHeight;
	// �½�ģ��
	CXPButton m_btnNewMod;
	// ����ģ��
	CXPButton m_btnSaveMod;
	// ���Դ�ӡ��ť
	CXPButton m_btnTestPrint;
	// Cancel��ť
	CButton m_btnCancel;
	// �뿪�˳����ذ�ť
	CXPButton m_btnExit;

	// ���ð�ť״̬
	int SetButtonStatus(int imode);
	afx_msg void OnBnClickedBtnNewitem();
	afx_msg void OnBnClickedBtnLoadjpg();
	afx_msg void OnBnClickedBtnTestprint();
	afx_msg void OnBnClickedBtnNewmod();
	afx_msg void OnBnClickedBtnSavemod();
	afx_msg void OnBnClickedBtnExit();
	// ���Ƶ�ǰģ��
	int DrawModule(void);

	// ���ð�ť���
	int SetButtonStyles(void);
};
