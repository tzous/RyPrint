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
	char **dbResult; //�� char ** ���ͣ�����*��
	int nRow, nColumn;
	int index;

public:
	// �����ݿ�
	int open(CString sdbfile);
	// �ر����ݿ�
	int close(void);
	// ִ��,create,insert,update,delete���޽�������
	int execute(CString sql);
	// ִ�в�ѯ��䣬ʹ��fetch_row��ȡ���
	int query(CString sql);
	// ȡһ�в�ѯ��������
	char ** fetch_row(void);
};

