#if !defined(AFX_XPBUTTON_H__44CD5B2A_756E_4939_9261_E0034E0F2DEF__INCLUDED_)
#define AFX_XPBUTTON_H__44CD5B2A_756E_4939_9261_E0034E0F2DEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XPButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXPButton window
enum XPBUTTON_POSITION {XPBUTTON_TEXT,XPBUTTON_PICTURE,XPBUTTON_HORIZONTAL,XPBUTTON_VERTICAL};

class CXPButton : public CButton
{
// Construction
public:
	CXPButton();

	// Attributes
protected:
	//按钮的外边框
	CPen m_BoundryPen;
	
	//鼠标指针置于按钮之上时按钮的内边框
	CPen m_InsideBoundryPenLeft;
	CPen m_InsideBoundryPenRight;
	CPen m_InsideBoundryPenTop;
	CPen m_InsideBoundryPenBottom;
	
	//按钮获得焦点时按钮的内边框
	CPen m_InsideBoundryPenLeftSel;
	CPen m_InsideBoundryPenRightSel;
	CPen m_InsideBoundryPenTopSel;
	CPen m_InsideBoundryPenBottomSel;
	
	//按钮的底色，包括有效和无效两种状态
	CBrush m_FillActive;
	CBrush m_FillInactive;
	
	//按钮的状态
	BOOL m_bOver;	//鼠标位于按钮之上时该值为true，反之为flase
	BOOL m_bTracking;	//在鼠标按下没有释放时该值为true
	BOOL m_bSelected;	//按钮被按下是该值为true
	BOOL m_bFocus;	//按钮为当前焦点所在时该值为true

	//按钮贴图
	BOOL m_bPic;	//有贴图时值为true，反之为false
	int m_nPicWidth;	//贴图宽度
	int m_nPicHeight;	//贴图高度
	CBitmap m_hBmp;	//图片资源
	XPBUTTON_POSITION m_nPosition;	//按钮图片文本类别 0-纯文本 1-纯图片 2-左图右文本 3-上图下文本

	//边框
	BOOL m_bBorder;	//是否有边框


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPButton)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void DoGradientFill(CDC *pDC, CRect* rect);
	virtual void DrawInsideBorder(CDC *pDC, CRect* rect);
	virtual ~CXPButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXPButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	// 设置按钮图片资源
	int SetPicture(UINT nIDResource);
	// 设置贴图大小
	int SetPictureSize(int nPicWidth, int nPicHeight);
	// 设置图片文字显示模式
	int SetPosition(XPBUTTON_POSITION nPosition);
	// 设置是否有边框
	int SetBorder(BOOL bBorder);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPBUTTON_H__44CD5B2A_756E_4939_9261_E0034E0F2DEF__INCLUDED_)
