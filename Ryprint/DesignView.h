#pragma once

#include "Voucher.h"

class CModuleDlg;

// CDesignView ��ͼ

class CDesignView : public CScrollView
{
	friend class CModuleDlg;
protected:
	CDesignView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	CVoucher* m_pVoucher;			//��ǰƱ��

protected:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual void OnInitialUpdate();     // �����ĵ�һ��
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
	virtual void OnActivateFrame(UINT nState, CFrameWnd* pDeactivateFrame);
	DECLARE_MESSAGE_MAP()
};


