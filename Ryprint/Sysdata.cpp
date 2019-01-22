#include "StdAfx.h"
#include "Misc.h"

#include "MySqlite3.h"


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
	sdbfile = "";	
	
}


CSysdata::~CSysdata(void)
{
}



// ��ʼ��ϵͳ���ݿ��ļ�
int CSysdata::InitSysData(void)
{
	if(CMisc::IsFileExist(sdbfile)) 
		return 0;
	CMySqlite3 mySqlite3;
	int result;
	result = mySqlite3.open(sdbfile);
	if(result < 0) return -1;

	CString sql;

	sql.Format("CREATE TABLE sysparm \
                (sysname           TEXT    PRIMARY KEY NOT NULL, \
                maxtypeid INT NOT NULL,\
                maxvoucherid INT NOT NULL,\
                leftmargin INT NOT NULL,\
                topmargin INT NOT NULL,\
                printer TEXT,\
                defaultfont TEXT,\
                autosave TEXT,\
                batchprint TEXT);"); 
	result = mySqlite3.execute(sql);
	sql.Format("CREATE TABLE types \
                (tid           int    PRIMARY KEY NOT NULL, \
                tname            TEXT     NOT NULL, \
                ptid        INT NOT NULL);");
	result = mySqlite3.execute(sql);
    sql.Format("CREATE TABLE vouchers \
                (vid           int    PRIMARY KEY NOT NULL, \
                vname            TEXT     NOT NULL, \
                vtext            TEXT     NOT NULL, \
                tid        INT NOT NULL);");
	result = mySqlite3.execute(sql);
    //��ϵͳ����,��ǰ��������,��ǰ���ƾ֤���,xƫ��,yƫ��,Ĭ�ϴ�ӡ��,Ĭ������,��ӡ��¼�Ƿ��Զ�����
	CObFont font;
	
	sql.Format("INSERT INTO sysparm (sysname,maxtypeid,maxvoucherid,leftmargin,topmargin,printer,defaultfont,autosave,batchprint) \
                values ('%s',%d,%d,%d,%d,'%s','%s','%s','%s')" ,"��ƾ֤��ӡ",3, 5, 11, 11, "",  font.toString(), "False", "True") ;
    mySqlite3.execute(sql);
    //����ţ�������ƣ��������
    sql.Format("INSERT INTO types (tid,tname,ptid) \
                values (%d,'%s',%d)",1,"����", 0);
    mySqlite3.execute(sql);
    sql.Format("INSERT INTO types (tid,tname,ptid) \
                values (%d,'%s',%d)",2,"ũ��", 0) ;
    mySqlite3.execute(sql);
    sql.Format("INSERT INTO types (tid,tname,ptid) \
                values (%d,'%s',%d)" ,3,"����", 0) ;
    mySqlite3.execute(sql);

	return 0;
}


// ��ȡϵͳ���ݿ�
int CSysdata::loadSysdata(void)
{
	if(!CMisc::IsFileExist(sdbfile)) {
		int ret = InitSysData();
		if(ret != 0) return ret;
	}

	return 0;
}
// ��ȡϵͳ���ݿ�
int CSysdata::loadSysdata(CString sFile)
{
	sdbfile = sFile;
	return loadSysdata();
}

//���õ�ǰϵͳ���ݿ�·��
int CSysdata::SetDbPath(CString sPath)
{
	sdbfile = sPath + "/sysdata.db";
	return 0;
}
