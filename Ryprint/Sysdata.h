#pragma once
#include "ObFont.h"
#include <list>
using namespace std;

class CSysdata
{
private:
	CString sdbfile;	//系统数据库文件全路径名

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

	typedef struct sysdata_type {
		int tid;
        CString tname;
		int ptid;
	}CSysType;
	list<CSysType> systypes;	//系统类别表
	typedef struct sysdata_voucher {
		int vid;
        CString vname;
        CString vtext;
        int tid;
	}CSysVoucher;
	list<CSysVoucher> sysvouchers;	//系统单据模板信息表

public:
	CSysdata(void);
	~CSysdata(void);

private:
	// 初始化系统数据库文件
	int InitSysData(void);
public:
	// 读取系统数据库
	int loadSysdata(void);
	int loadSysdata(CString sFile);
	//设置当前系统数据库路径
	int SetDbPath(CString sPath);
};

