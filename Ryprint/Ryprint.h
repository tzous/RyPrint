
// Ryprint.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "Ryini.h"
#include "Sysdata.h"

// CRyprintApp:
// 有关此类的实现，请参阅 Ryprint.cpp
//

class CRyprintApp : public CWinApp
{
public:
	CRyprintApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

	//属性
public:
	CString m_Path;		//程序路径
	CRyini m_ryini;		//界面配置参数
	CString m_dataPath;		//系统数据目录
	CString m_tmplPath;		//模板存放目录
	CSysdata m_sysData;		//系统数据库


};

extern CRyprintApp theApp;