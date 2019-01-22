#pragma once
#include "explorer1.h"
#include "XPButton.h"

// CModuleDlg 对话框

class CModuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModuleDlg)

public:
	CModuleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModuleDlg();

// 对话框数据
	enum { IDD = IDD_MODULE_DIALOG };

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:
	// 主菜单
	HMENU m_hMenu1;
	// 广告条
	CExplorer1 m_hBrowser;
	// 对话框主窗口大小
	CRect m_rect;
	// 根据窗口大小改变控件位置,left、right、top、bottom为4个改变维度
	int MoveCtlWindow(int handler, int cx, int cy,int left, int right, int top, int bottom);
	// 根据窗口大小改变控件位置，rect为新的窗口位置
	int MoveCtlWindow(int handler, CRect rect);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);


	// 状态栏
	CEdit m_edtStatus;
	// 主窗口分组
	CStatic m_grpmain;
	// 凭证窗口大小
	CRect m_mainRect;

	// 当前模式 0-未选中模板打印 1-选中模板打印 2-模板设计，但模板未初始化 3-模板编辑状态
	int m_imode;
	//当前凭证模板
	CBillModule m_currModule;


	// 新增字段
	CXPButton m_btnNewItem;
	// 导入背景
	CXPButton m_btnLoadJpg;
	// 删除背景
	CXPButton m_btnDelJpg;
	// 左对齐
	CXPButton m_btnAdjustLeft;
	// 右对齐
	CXPButton m_btnAdjustRight;
	// 上对齐
	CXPButton m_btnAdjustTop;
	// 下对齐
	CXPButton m_btnAdjustBottom;
	// 相同宽度
	CXPButton m_btnSameWidth;
	// 相同高度
	CXPButton m_btnSameHeight;
	// 新建模板
	CXPButton m_btnNewMod;
	// 保存模板
	CXPButton m_btnSaveMod;
	// 测试打印按钮
	CXPButton m_btnTestPrint;
	// Cancel按钮
	CButton m_btnCancel;
	// 离开退出返回按钮
	CXPButton m_btnExit;

	// 设置按钮状态
	int SetButtonStatus(int imode);
	afx_msg void OnBnClickedBtnNewitem();
	afx_msg void OnBnClickedBtnLoadjpg();
	afx_msg void OnBnClickedBtnTestprint();
	afx_msg void OnBnClickedBtnNewmod();
	afx_msg void OnBnClickedBtnSavemod();
	afx_msg void OnBnClickedBtnExit();
	// 绘制当前模板
	int DrawModule(void);

	// 设置按钮风格
	int SetButtonStyles(void);
};
