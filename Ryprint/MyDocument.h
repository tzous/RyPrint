#pragma once

// CMyDocument �ĵ�
class CRypringDlg;
class CModuleDlg;

class CMyDocument : public CDocument
{
	//DECLARE_DYNCREATE(CMyDocument)
	friend class CRypringDlg;
	friend class CModuleDlg;

public:
	CMyDocument();
	DECLARE_DYNCREATE(CMyDocument)
	virtual ~CMyDocument();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // Ϊ�ĵ� I/O ��д
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};
