#include "StdAfx.h"
#include "Misc.h"

extern CRyprintApp theApp;

CSysdata::CSysdata(void)
{
	sSysname = "简单套打助手";
	nMaxtypeid = 0;
	nMaxvoucherid = 0;
	nLeftmargin = 11;
	nTopmargin = 11;
	sPrinter = ""; 
	bAutoSave = FALSE;
	nBatchrow = 2;	// 批量数据第一行为字段标题，批量数据起始行为第二行
	sSysdb = theApp.m_dataPath + "/sysdata.db";
	
}


CSysdata::~CSysdata(void)
{
}



// 初始化系统数据库文件
int CSysdata::InitSysData(void)
{
	return 0;
}


// 读取系统数据库
int CSysdata::loadSysdata(void)
{
	if(!CMisc::IsFileExist(sSysdb)) {
		InitSysData();
	}
	return 0;
}
