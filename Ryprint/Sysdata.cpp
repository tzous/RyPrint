#include "StdAfx.h"
#include "Misc.h"

#include "MySqlite3.h"


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
	sdbfile = "";	
	
}


CSysdata::~CSysdata(void)
{
}



// 初始化系统数据库文件
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
    //本系统名称,当前最大类别编号,当前最大凭证编号,x偏移,y偏移,默认打印机,默认字体,打印记录是否自动保存
	CObFont font;
	
	sql.Format("INSERT INTO sysparm (sysname,maxtypeid,maxvoucherid,leftmargin,topmargin,printer,defaultfont,autosave,batchprint) \
                values ('%s',%d,%d,%d,%d,'%s','%s','%s','%s')" ,"简单凭证打印",3, 5, 11, 11, "",  font.toString(), "False", "True") ;
    mySqlite3.execute(sql);
    //类别编号，类别名称，父类别编号
    sql.Format("INSERT INTO types (tid,tname,ptid) \
                values (%d,'%s',%d)",1,"常用", 0);
    mySqlite3.execute(sql);
    sql.Format("INSERT INTO types (tid,tname,ptid) \
                values (%d,'%s',%d)",2,"农行", 0) ;
    mySqlite3.execute(sql);
    sql.Format("INSERT INTO types (tid,tname,ptid) \
                values (%d,'%s',%d)" ,3,"其他", 0) ;
    mySqlite3.execute(sql);

	return 0;
}


// 读取系统数据库
int CSysdata::loadSysdata(void)
{
	if(!CMisc::IsFileExist(sdbfile)) {
		int ret = InitSysData();
		if(ret != 0) return ret;
	}

	return 0;
}
// 读取系统数据库
int CSysdata::loadSysdata(CString sFile)
{
	sdbfile = sFile;
	return loadSysdata();
}

//设置当前系统数据库路径
int CSysdata::SetDbPath(CString sPath)
{
	sdbfile = sPath + "/sysdata.db";
	return 0;
}
