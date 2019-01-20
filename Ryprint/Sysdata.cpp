#include "StdAfx.h"
#include "Misc.h"

extern CRyprintApp theApp;

CSysdata::CSysdata(void)
{
	sSysname = "���״�����";
	nMaxtypeid = 0;
	nMaxvoucherid = 0;
	nLeftmargin = 11;
	nTopmargin = 11;
	sPrinter = ""; 
	bAutoSave = FALSE;
	nBatchrow = 2;	// �������ݵ�һ��Ϊ�ֶα��⣬����������ʼ��Ϊ�ڶ���
	sSysdb = theApp.m_dataPath + "/sysdata.db";
	
}


CSysdata::~CSysdata(void)
{
}



// ��ʼ��ϵͳ���ݿ��ļ�
int CSysdata::InitSysData(void)
{
	return 0;
}


// ��ȡϵͳ���ݿ�
int CSysdata::loadSysdata(void)
{
	if(!CMisc::IsFileExist(sSysdb)) {
		InitSysData();
	}
	return 0;
}
