#pragma once

#include "Voucher.h"

class CModuleDlg;

// CDesignView 视图

class CDesignView : public CScrollView
{
	friend class CModuleDlg;
protected:
	CDesignView();           // 动态创建所使用的受保护的构造函数
	DECLARE_DYNCREATE(CDesignView)
	virtual ~CDesignView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	CVoucher* m_pVoucher;			//当前票据

protected:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnInitialUpdate();     // 构造后的第一次
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
	virtual void OnActivateFrame(UINT nState, CFrameWnd* pDeactivateFrame);
	DECLARE_MESSAGE_MAP()
};


