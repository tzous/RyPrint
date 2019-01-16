// MyView.cpp : 实现文件
//

#include "stdafx.h"
#include "Ryprint.h"
#include "MyView.h"


// CMyView

IMPLEMENT_DYNCREATE(CMyView, CScrollView)

CMyView::CMyView()
{

}

CMyView::~CMyView()
{
}


BEGIN_MESSAGE_MAP(CMyView, CScrollView)
END_MESSAGE_MAP()


// CMyView 绘图

void CMyView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CMyView::OnDraw(CDC* pDC)
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


// CMyView 诊断

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyView 消息处理程序
