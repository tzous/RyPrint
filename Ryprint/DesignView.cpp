// DesignView.cpp : 实现文件
//

#include "stdafx.h"
#include "Ryprint.h"
#include "DesignView.h"


// CDesignView

IMPLEMENT_DYNCREATE(CDesignView, CScrollView)

CDesignView::CDesignView()
{
	m_pVoucher = NULL;

}

CDesignView::~CDesignView()
{
}


BEGIN_MESSAGE_MAP(CDesignView, CScrollView)
END_MESSAGE_MAP()


// CDesignView 绘图

void CDesignView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CDesignView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码

CBitmap BK;
BK.LoadBitmap(IDB_BITMAP1); //需要添加一位图用于显示
CDC MemDC;
MemDC.CreateCompatibleDC(pDC);
MemDC.SelectObject(&BK);
BITMAP bm;
BK.GetBitmap(&bm);

pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);

CRect m_Rect;
GetClientRect(&m_Rect);
m_Rect.bottom += 100;
CSize sizeTotal;
// TODO: calculate the total size of this view
sizeTotal.cx = bm.bmWidth;
sizeTotal.cy = bm.bmHeight;
SetScrollSizes(MM_TEXT, sizeTotal);

}


// CDesignView 诊断

#ifdef _DEBUG
void CDesignView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CDesignView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDesignView 消息处理程序
int CDesignView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
    // TODO: Add your message handler code here and/or call default

    return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CDesignView::OnDestroy()
{
    CWnd::OnDestroy();

    // TODO: Add your message handler code here
}

void CDesignView::PostNcDestroy()
{
    // TODO: Add your specialized code here and/or call the base class

    CWnd::PostNcDestroy();
}

void CDesignView::OnActivateFrame(UINT nState, CFrameWnd* pDeactivateFrame)
{
    // TODO: Add your specialized code here and/or call the base class

    CView::OnActivateFrame(nState, pDeactivateFrame);
}