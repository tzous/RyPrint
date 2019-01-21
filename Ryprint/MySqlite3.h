#pragma once
#include "sqlite3.h"
#pragma comment(lib, "sqlite3.lib")

class CMySqlite3
{
public:
	CMySqlite3(void);
	~CMySqlite3(void);

private:
	sqlite3 * db;
	BOOL bOpened;
	BOOL bHaveData;
	sqlite3_stmt *stmt;
	const char * Error;
	char * errmsg;
	char **dbResult; //是 char ** 类型，两个*号
	int nRow, nColumn;
	int index;

public:
	// 打开数据库
	int open(CString sdbfile);
	// 关闭数据库
	int close(void);
	// 执行,create,insert,update,delete等无结果集语句
	int execute(CString sql);
	// 执行查询语句，使用fetch_row获取结果
	int query(CString sql);
	// 取一行查询返回数据
	char ** fetch_row(void);
};

