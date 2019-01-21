#include "StdAfx.h"
#include "MySqlite3.h"


CMySqlite3::CMySqlite3(void)
{
	db = NULL;
	bOpened = FALSE;
	stmt = NULL;
	Error = NULL;
	errmsg = NULL;
	bHaveData = FALSE;

}

CMySqlite3::~CMySqlite3(void)
{
	if(bHaveData) {
		sqlite3_free_table( dbResult );
	}
	if(bOpened) {
		sqlite3_close( db );
	}
}


// �����ݿ�
int CMySqlite3::open(CString sdbfile)
{
	int result = sqlite3_open( sdbfile.GetBuffer(), &db );
	if( result != SQLITE_OK )
	{
		AfxMessageBox("�����ݿ��ļ�ʧ�ܣ�");
		return -1;
	}
	bOpened = TRUE;
	return 0;
}


// �ر����ݿ�
int CMySqlite3::close(void)
{
	if(bOpened) {
		sqlite3_close( db );
		bOpened = FALSE;
	}

	return 0;
}


// ִ��,create,insert,update,delete���޽�������
int CMySqlite3::execute(CString sql)
{
	CString sError;
	if(!bOpened) {
			sError.Format("��Ҫ�ȴ����ݿ⣡");
			AfxMessageBox(sError.GetBuffer());
			return -1;
	}
	int result = sqlite3_prepare(db,sql.GetBuffer(),-1,&stmt,&Error);
	if(result!=SQLITE_OK)
	{
			sqlite3_close( db );
			sError.Format("׼�����ʧ�ܣ�Result Code:%d \n ErrorMessage:%s",result,Error);
			AfxMessageBox(sError.GetBuffer());
			return -1;
	}
	result = sqlite3_step(stmt);
	if(result !=SQLITE_DONE)
	{
			sqlite3_close( db );
			sError.Format("�������ݿ�ʧ�ܣ�Result Code:%d \n ErrorMessage:%s",result,Error);
			AfxMessageBox(sError.GetBuffer());
			return -1;
	}

	return 0;
}
  


// ִ�в�ѯ��䣬ʹ��fetch_row��ȡ���
int CMySqlite3::query(CString sql)
{
	CString sError;
	if(!bOpened) {
			sError.Format("��Ҫ�ȴ����ݿ⣡");
			AfxMessageBox(sError.GetBuffer());
			return -1;
	}
	if(bHaveData) {			//���ǰһ��ѯ����δȡ�ߣ������ͷ�
		sqlite3_free_table( dbResult );
		bHaveData = FALSE;
	}

	int result = sqlite3_get_table( db,sql.GetBuffer(), &dbResult, &nRow,&nColumn, &errmsg );
	if( SQLITE_OK == result )
	{
		//��ѯ�ɹ�
		index = nColumn; //dbResult ǰ���һ���������ֶ����ƣ��� nColumn������ʼ��������������
		bHaveData = TRUE;
	} else {
		sError.Format("��ѯʧ�ܣ�Result Code:%d \n ErrorMessage:%s",result,Error);
		AfxMessageBox(sError.GetBuffer());

		return -1;
	}
	return 0;

}


// ȡһ�в�ѯ��������
char ** CMySqlite3::fetch_row(void)
{
	CString sError;
	if(!bOpened) {
			sError.Format("��Ҫ�ȴ����ݿ⣡");
			AfxMessageBox(sError.GetBuffer());
			return NULL;
	}
	if(!bHaveData) {			//���û�в�ѯ���ݣ��򷵻�
		return NULL;
	}
	if(index > nColumn * (nRow + 1)) {
		return NULL;
	} 
	int curindex = index;
	index = index + nColumn;

	return &dbResult[curindex];
}
