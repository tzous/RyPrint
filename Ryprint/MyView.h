#pragma once



// CMyView ��ͼ

class CMyView : public CScrollView
{
	//DECLARE_DYNCREATE(CMyView)
	friend class CRyprintDlg;
	friend class CModuleDlg;
protected:
	CMyView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	DECLARE_DYNCREATE(CMyView)
	virtual ~CMyView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual void OnInitialUpdate();     // �����ĵ�һ��

	DECLARE_MESSAGE_MAP()
};


