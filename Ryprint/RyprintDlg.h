
// RyprintDlg.h : 头文件
//

#pragma once
#include "explorer1.h"
#include "atltypes.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "MyView.h"
#include "XPButton.h"		//自绘按钮类
#include "MyDocument.h"
#include "ModuleDlg.h"

// CRyprintDlg 对话框
class CRyprintDlg : public CDialogEx
{
// 构造
public:
	CRyprintDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RYPRINT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnOK();

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


	// 模板分组框
	CStatic m_grpmodule;
	// 状态栏
	CEdit m_edtStatus;
	// 主窗口分组
	CStatic m_grpmain;
	// 凭证窗口大小
	CRect m_mainRect;

	// 单据查询关键字
	CEdit m_queryString;
	// 当前模式 0-未选中模板打印 1-选中模板打印 2-模板设计，但模板未初始化 3-模板编辑状态
	int m_imode;

	// 设置按钮状态
	int SetButtonStatus(int imode);
	// 离开退出返回事件
	afx_msg void OnBnClickedBtnExit();
	// 根据关键字查询模板
	int QueryModules(CString strQuery);
	//点击模板查询按钮事件
	afx_msg void OnBnClickedBtnQueryModule();
	//退出系统
	virtual void OnCancel();
	// 绘制当前模板
	int DrawModule(void);
	//主画板滚动视图
	CMyView* pView;
	//主画板文档
	CCreateContext pContext;
	CModuleDlg m_moduleDlg;

	// 按钮类别管理
	CXPButton m_btnModgrps;
	// 按钮模板导入
	CXPButton m_btnModload;
	// 按钮模板导出
	CXPButton m_btnModexport;
	// 按钮新建模板
	CXPButton m_btnModnew;
	// 按钮模板修改
	CXPButton m_btnModmodify;
	// 按钮模板删除
	CXPButton m_btn_Moddel;
	// 按钮查
	CXPButton m_btnQuery;
	// 按钮单笔打印
	CXPButton m_btnPrintbill;
	// 按钮重新录入
	CXPButton m_btnReset;
	// 按钮保存数据
	CXPButton m_btnSavedata;
	// 按钮数据仓库
	CXPButton m_btnDatalist;
	// 按钮批量打印
	CXPButton m_btnPrintbatch;
	// 按钮打印设置
	CXPButton m_btnSetup;
	// 设置按钮风格
	int SetButtonStyles(void);
	afx_msg void OnBnClickedBtnModnew();
};
