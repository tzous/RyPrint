
// Ryprint.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRyprintApp:
// �йش����ʵ�֣������ Ryprint.cpp
//

class CRyprintApp : public CWinApp
{
public:
	CRyprintApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

	//����
public:
	CString m_Path;
	CString m_iniFile;
	CRyini m_ryini;

};

extern CRyprintApp theApp;