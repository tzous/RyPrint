#pragma once
#include "ObFont.h"

class CSysdata
{
private:
	CString sSysdb;		//系统数据库路径名

public:
	CString sSysname;	//字体
	int nMaxtypeid;		//系统库中最大类型ID
	int nMaxvoucherid;	//系统库中最大票据ID
	int nLeftmargin;		//打印机默认左边距
	int nTopmargin;		//打印机默认上边距
	CString sPrinter;	//默认打印机
	CObFont cFont;		//默认字体
	BOOL bAutoSave;		//单笔打印后是否自动保存
	int nBatchrow;		// 批量数据起始行

public:
	CSysdata(void);
	~CSysdata(void);

private:
	// 初始化系统数据库文件
	int InitSysData(void);
public:
	// 读取系统数据库
	int loadSysdata(void);
};

