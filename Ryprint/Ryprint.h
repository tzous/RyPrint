
// Ryprint.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Ryini.h"
#include "Sysdata.h"

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
	CString m_Path;		//����·��
	CRyini m_ryini;		//�������ò���
	CString m_dataPath;		//ϵͳ����Ŀ¼
	CString m_tmplPath;		//ģ����Ŀ¼
	CSysdata m_sysData;		//ϵͳ���ݿ�


};

extern CRyprintApp theApp;