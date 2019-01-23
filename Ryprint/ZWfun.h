// ZWfun.h: interface for the ZWfun class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZWfun_H__B4906CE0_FFDC_4045_948F_1EF630BABF39__INCLUDED_)
#define AFX_ZWfun_H__B4906CE0_FFDC_4045_948F_1EF630BABF39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define BUFSIZE 512	//字符串缓冲长度

class CZWfun  
{
private:
//KMP-获取模式字符串的Next数组
	void GetModeNext(char * t, int * p);
//KMP-匹配方法，返回值是在目标字符串中匹配成功的位置
	int Matching(char * s, char * t, int * p);

public:
	CZWfun();
	virtual ~CZWfun();
	static BOOL IsFileExist(const CString& csFile);	//文件是否存在
	BOOL isNumber(const char  * s);
	static int cov_money(char * sj,char * string);//金额小写转大写
	static void ntoc(char *str,char * value);	//金额小写转大写
	static void numtocap(char *s,char * val);	//数字转中文（一对一） 
	char * Filter(const char * s,char c);/*过滤字符串中指定字符*/
	int del_not_c(char *str);/*删除非汉字字符*/
	int del_space(char *s,int type);	//删空格
	char * get_word(char * s,int pt,char type,int len); //从s 中取得第pt个字符串,分隔符为type,len为最大长度 
	char * get_word2(char * s,int pt,char type,int len);//从s 中取得第pt个字符串,分隔符为type,len为最大长度,多个连续分隔符算一个
	int DateNum(int year,int month);	//得到每月天数

	// 给金额加千分位
	char * AddComma(double je);
	// 字符串连接
	int mystrcat(char * dst, const char * src);
	// 得到无路径文件名
	char * GetFileName(CString strFileName);
	// 删除SQL字符串中不合法的字符
	void dowith_sql(CString * strSql);
	// 简单的字符串匹配
	int strFind(char * strT,char * strP, int lPos);
	// 字符串匹配KMP算法
	int strFindKMP(char * strT,char * strP, int lPos);
	// 字符串模糊匹配
	BOOL strFindBlur(char * strT,char * strP, int lPos);
	// 得到应用程序所在文件夹
	CString GetAppPath(void);
	// 检查是否为允许IP
	int CheckAllowIP(CString AllowIP,CString IP);
	CString MbcsToUtf8(const char *file);	//文件名转为utf-8
};

#endif // !defined(AFX_ZWfun_H__B4906CE0_FFDC_4045_948F_1EF630BABF39__INCLUDED_)
