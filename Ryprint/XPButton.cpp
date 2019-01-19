// XPButton.cpp : implementation file
//

#include "stdafx.h"
#include "XPButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXPButton

CXPButton::CXPButton()
{
	m_BoundryPen.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(0, 0, 0));
	m_InsideBoundryPenLeft.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(200, 200, 200)); 
	m_InsideBoundryPenRight.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(50, 50, 50));
	m_InsideBoundryPenTop.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(200, 200, 200));
	m_InsideBoundryPenBottom.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(50, 50, 50));
	
	m_FillActive.CreateSolidBrush(RGB(222, 223, 236));
	m_FillInactive.CreateSolidBrush(RGB(222, 223, 236));
	
	m_InsideBoundryPenLeftSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(200, 200, 200)); 
	m_InsideBoundryPenTopSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(50, 50, 50));
	m_InsideBoundryPenRightSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(200, 200, 200));
	m_InsideBoundryPenBottomSel.CreatePen(PS_INSIDEFRAME | PS_SOLID, 1, RGB(50, 50, 50));
	
	m_bOver = m_bSelected = m_bTracking = m_bFocus = FALSE;
	m_bPic = FALSE;
	m_nPosition = XPBUTTON_TEXT;
	m_bBorder = TRUE;
	m_nPicWidth = 16;
	m_nPicHeight = 16;

}

CXPButton::~CXPButton()
{
	m_BoundryPen.DeleteObject();
	m_InsideBoundryPenLeft.DeleteObject();
	m_InsideBoundryPenRight.DeleteObject();
	m_InsideBoundryPenTop.DeleteObject();
	m_InsideBoundryPenBottom.DeleteObject();
	
	m_FillActive.DeleteObject();
	m_FillInactive.DeleteObject();
	
	m_InsideBoundryPenLeftSel.DeleteObject();
	m_InsideBoundryPenTopSel.DeleteObject();
	m_InsideBoundryPenRightSel.DeleteObject();
	m_InsideBoundryPenBottomSel.DeleteObject();
	
}


BEGIN_MESSAGE_MAP(CXPButton, CButton)
	//{{AFX_MSG_MAP(CXPButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXPButton message handlers

//添加Owner Draw属性
void CXPButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}

void CXPButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}
	
	CButton::OnMouseMove(nFlags, point);
}


LRESULT CXPButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bOver = FALSE;
	m_bTracking = FALSE;
	InvalidateRect(NULL, FALSE);
	return 0;
}

LRESULT CXPButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bOver = TRUE;
	InvalidateRect(NULL);
	return 0;
}


void CXPButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//从lpDrawItemStruct获取控件的相关信息
	CRect rect =  lpDrawItemStruct->rcItem;
	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	int nSaveDC=pDC->SaveDC();
	UINT state = lpDrawItemStruct->itemState;
	POINT pt ;
	TCHAR strText[MAX_PATH + 1];
	::GetWindowText(m_hWnd, strText, MAX_PATH);
	
	//画按钮的外边框，它是一个半径为5的圆角矩形
	pt.x = 5;
	pt.y = 5;
	CPen* hOldPen = pDC->SelectObject(&m_BoundryPen);
	if(m_bBorder) {
		pDC->RoundRect(&rect, pt);
	}
	
	//获取按钮的状态
	if (state & ODS_FOCUS)
	{
		m_bFocus = TRUE;
		m_bSelected = TRUE;
	}
	else
	{
		m_bFocus = FALSE;
		m_bSelected = FALSE;
	}
	
	
	if (state & ODS_SELECTED || state & ODS_DEFAULT)
	{
		m_bFocus = TRUE;
	}

	
	pDC->SelectObject(hOldPen);
	
	rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
	
	//根据按钮的状态填充按钮的底色
	CBrush* pOldBrush;
	if (m_bOver)
	{
		pOldBrush = pDC->SelectObject(&m_FillActive);
		DoGradientFill(pDC, &rect);
	}
	else
	{
		pOldBrush = pDC->SelectObject(&m_FillInactive);
		DoGradientFill(pDC, &rect);
	}
	
	//根据按钮的状态绘制内边框
	if (m_bOver || m_bSelected)
		DrawInsideBorder(pDC, &rect);
				
	pDC->SelectObject(pOldBrush);
	
	//按钮贴图
	if(m_bPic) {
		CRect picrect;
		BOOL bBitBlt = TRUE;
		switch(m_nPosition) {
		case XPBUTTON_TEXT: bBitBlt = FALSE;
			break;
		case XPBUTTON_PICTURE: picrect = rect;
			break;
		case XPBUTTON_HORIZONTAL: picrect.top = rect.top + 1;
			picrect.left = rect.left + 2;
			break;
		case XPBUTTON_VERTICAL: picrect.top = rect.top + 2;
			picrect.left = (rect.right + rect.left - m_nPicWidth)/2;
			break;
		}
		if(bBitBlt){
			CDC MemDC;
			MemDC.CreateCompatibleDC(pDC);
			MemDC.SelectObject(&m_hBmp);
			BITMAP bm;
			m_hBmp.GetBitmap(&bm);
			TransparentBlt(lpDrawItemStruct->hDC,picrect.left, picrect.top,m_nPicWidth,m_nPicHeight,MemDC.m_hDC,0,0,bm.bmWidth,bm.bmHeight,RGB(255,255,255));
		}
	}

	//显示按钮的文本
	if (strText!=NULL )
	{
		CFont* hFont = GetFont();
		CFont* hOldFont = pDC->SelectObject(hFont);
		CSize szExtent = pDC->GetTextExtent(strText, lstrlen(strText));
		CPoint pt( rect.CenterPoint().x - szExtent.cx / 2, rect.CenterPoint().y - szExtent.cy / 2);
		if (state & ODS_SELECTED) 
			pt.Offset(1, 1);
		int nMode = pDC->SetBkMode(TRANSPARENT);
		BOOL bDrawText = TRUE;
		switch(m_nPosition) {
		case XPBUTTON_PICTURE:bDrawText = FALSE;
			break;
		case XPBUTTON_HORIZONTAL:
			pt.Offset(m_nPicWidth/4,0);
			break;
		case XPBUTTON_VERTICAL:
			pt.Offset(0,m_nPicHeight/2);
			break;
		}
		if(bDrawText) {
			if (state & ODS_DISABLED)
				pDC->DrawState(pt, szExtent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
			else
				pDC->DrawState(pt, szExtent, strText, DSS_NORMAL, TRUE, 0, (HBRUSH)NULL);
		}
		pDC->SelectObject(hOldFont);
		pDC->SetBkMode(nMode);
	}
	
	
	pDC->RestoreDC(nSaveDC);
}

//绘制按钮的底色
void CXPButton::DoGradientFill(CDC *pDC, CRect* rect)
{
	CBrush brBk[64];
	int nWidth = rect->Width();	
	int nHeight = rect->Height();
	CRect rct;
	int i = 0;
	for (i = 0; i < 64; i ++)
	{
		if (m_bOver)
		{
			if (m_bFocus)
				brBk[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 3)));
			else
				brBk[i].CreateSolidBrush(RGB(255 - (i / 4), 255 - (i / 4), 255 - (i / 5)));
		}
		else
		{
			if (m_bFocus)
				brBk[i].CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 4)));
			else
				brBk[i].CreateSolidBrush(RGB(255 - (i / 3), 255 - (i / 3), 255 - (i / 5)));
		}
	}
	
	for (i = rect->top; i <= nHeight + 2; i ++) 
	{
		rct.SetRect(rect->left, i, nWidth + 2, i + 1);
		pDC->FillRect(&rct, &brBk[((i * 63) / nHeight)]);
	}
	
	for (i = 0; i < 64; i ++)
		brBk[i].DeleteObject();
}


//绘制按钮的内边框
void CXPButton::DrawInsideBorder(CDC *pDC, CRect* rect)
{
	/*
	CPen *pLeft, *pRight, *pTop, *pBottom;
	
	if (m_bSelected && !m_bOver)
	{
		pLeft = & m_InsideBoundryPenLeftSel;
		pRight = &m_InsideBoundryPenRightSel;
		pTop = &m_InsideBoundryPenTopSel;
		pBottom = &m_InsideBoundryPenBottomSel;
	}
	else
	{
		pLeft = &m_InsideBoundryPenLeft;
		pRight = &m_InsideBoundryPenRight;
		pTop = &m_InsideBoundryPenTop;
		pBottom = &m_InsideBoundryPenBottom;
	}
	
	CPoint oldPoint = pDC->MoveTo(rect->left , rect->bottom );
	CPen* pOldPen = pDC->SelectObject(pLeft);
	pDC->LineTo(rect->left , rect->top);
	pDC->SelectObject(pRight);
	pDC->MoveTo(rect->right, rect->bottom );
	pDC->LineTo(rect->right, rect->top);
	pDC->SelectObject(pTop);
	pDC->MoveTo(rect->left , rect->top);
	pDC->LineTo(rect->right , rect->top);
	pDC->SelectObject(pBottom);
	pDC->MoveTo(rect->left, rect->bottom);
	pDC->LineTo(rect->right, rect->bottom);
	pDC->SelectObject(pOldPen);
	pDC->MoveTo(oldPoint);

	*/
	CBrush brBk, *pOldbrush;
	if (m_bSelected && !m_bOver) {
		brBk.CreateSolidBrush(RGB(240, 240, 240));
	}
	else {
		brBk.CreateSolidBrush(RGB(225, 225, 225));
	}
	pOldbrush = pDC->SelectObject(&brBk);
	pDC->FillRect(rect, &brBk);
	pDC->SelectObject(pOldbrush);
	brBk.DeleteObject();

	if (m_bSelected && !m_bOver)
		DrawFocusRect(pDC->m_hDC,rect);
}




// 设置按钮图片资源
int CXPButton::SetPicture(UINT nIDResource)
{
	m_hBmp.LoadBitmap(nIDResource);
	m_bPic = TRUE;
	return 0;
}

// 设置贴图大小
int CXPButton::SetPictureSize(int nPicWidth, int nPicHeight)
{
	m_nPicWidth = nPicWidth;
	m_nPicHeight = nPicHeight;
	return 0;
}


// 设置图片文字显示模式
int CXPButton::SetPosition(XPBUTTON_POSITION nPosition)
{
	m_nPosition = nPosition;
	return 0;
}

// 设置是否有边框
int CXPButton::SetBorder(BOOL bBorder) 
{
	m_bBorder = bBorder;
	return 0;
}