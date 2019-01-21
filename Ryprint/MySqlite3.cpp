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


// 打开数据库
int CMySqlite3::open(CString sdbfile)
{
	int result = sqlite3_open( sdbfile.GetBuffer(), &db );
	if( result != SQLITE_OK )
	{
		AfxMessageBox("打开数据库文件失败！");
		return -1;
	}
	bOpened = TRUE;
	return 0;
}


// 关闭数据库
int CMySqlite3::close(void)
{
	if(bOpened) {
		sqlite3_close( db );
		bOpened = FALSE;
	}

	return 0;
}


// 执行,create,insert,update,delete等无结果集语句
int CMySqlite3::execute(CString sql)
{
	CString sError;
	if(!bOpened) {
			sError.Format("需要先打开数据库！");
			AfxMessageBox(sError.GetBuffer());
			return -1;
	}
	int result = sqlite3_prepare(db,sql.GetBuffer(),-1,&stmt,&Error);
	if(result!=SQLITE_OK)
	{
			sqlite3_close( db );
			sError.Format("准备语句失败！Result Code:%d \n ErrorMessage:%s",result,Error);
			AfxMessageBox(sError.GetBuffer());
			return -1;
	}
	result = sqlite3_step(stmt);
	if(result !=SQLITE_DONE)
	{
			sqlite3_close( db );
			sError.Format("创建数据库失败！Result Code:%d \n ErrorMessage:%s",result,Error);
			AfxMessageBox(sError.GetBuffer());
			return -1;
	}

	return 0;
}
  


// 执行查询语句，使用fetch_row获取结果
int CMySqlite3::query(CString sql)
{
	CString sError;
	if(!bOpened) {
			sError.Format("需要先打开数据库！");
			AfxMessageBox(sError.GetBuffer());
			return -1;
	}
	if(bHaveData) {			//如果前一查询数据未取走，则先释放
		sqlite3_free_table( dbResult );
		bHaveData = FALSE;
	}

	int result = sqlite3_get_table( db,sql.GetBuffer(), &dbResult, &nRow,&nColumn, &errmsg );
	if( SQLITE_OK == result )
	{
		//查询成功
		index = nColumn; //dbResult 前面第一行数据是字段名称，从 nColumn索引开始才是真正的数据
		bHaveData = TRUE;
	} else {
		sError.Format("查询失败！Result Code:%d \n ErrorMessage:%s",result,Error);
		AfxMessageBox(sError.GetBuffer());

		return -1;
	}
	return 0;

}


// 取一行查询返回数据
char ** CMySqlite3::fetch_row(void)
{
	CString sError;
	if(!bOpened) {
			sError.Format("需要先打开数据库！");
			AfxMessageBox(sError.GetBuffer());
			return NULL;
	}
	if(!bHaveData) {			//如果没有查询数据，则返回
		return NULL;
	}
	if(index > nColumn * (nRow + 1)) {
		return NULL;
	} 
	int curindex = index;
	index = index + nColumn;

	return &dbResult[curindex];
}
