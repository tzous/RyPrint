// ZWfun.h: interface for the ZWfun class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZWfun_H__B4906CE0_FFDC_4045_948F_1EF630BABF39__INCLUDED_)
#define AFX_ZWfun_H__B4906CE0_FFDC_4045_948F_1EF630BABF39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define BUFSIZE 512	//�ַ������峤��

class CZWfun  
{
private:
//KMP-��ȡģʽ�ַ�����Next����
	void GetModeNext(char * t, int * p);
//KMP-ƥ�䷽��������ֵ����Ŀ���ַ�����ƥ��ɹ���λ��
	int Matching(char * s, char * t, int * p);

public:
	CZWfun();
	virtual ~CZWfun();
	static BOOL IsFileExist(const CString& csFile);	//�ļ��Ƿ����
	BOOL isNumber(const char  * s);
	static int cov_money(char * sj,char * string);//���Сдת��д
	static void ntoc(char *str,char * value);	//���Сдת��д
	static void numtocap(char *s,char * val);	//����ת���ģ�һ��һ�� 
	char * Filter(const char * s,char c);/*�����ַ�����ָ���ַ�*/
	int del_not_c(char *str);/*ɾ���Ǻ����ַ�*/
	int del_space(char *s,int type);	//ɾ�ո�
	char * get_word(char * s,int pt,char type,int len); //��s ��ȡ�õ�pt���ַ���,�ָ���Ϊtype,lenΪ��󳤶� 
	char * get_word2(char * s,int pt,char type,int len);//��s ��ȡ�õ�pt���ַ���,�ָ���Ϊtype,lenΪ��󳤶�,��������ָ�����һ��
	int DateNum(int year,int month);	//�õ�ÿ������

	// ������ǧ��λ
	char * AddComma(double je);
	// �ַ�������
	int mystrcat(char * dst, const char * src);
	// �õ���·���ļ���
	char * GetFileName(CString strFileName);
	// ɾ��SQL�ַ����в��Ϸ����ַ�
	void dowith_sql(CString * strSql);
	// �򵥵��ַ���ƥ��
	int strFind(char * strT,char * strP, int lPos);
	// �ַ���ƥ��KMP�㷨
	int strFindKMP(char * strT,char * strP, int lPos);
	// �ַ���ģ��ƥ��
	BOOL strFindBlur(char * strT,char * strP, int lPos);
	// �õ�Ӧ�ó��������ļ���
	CString GetAppPath(void);
	// ����Ƿ�Ϊ����IP
	int CheckAllowIP(CString AllowIP,CString IP);
	CString MbcsToUtf8(const char *file);	//�ļ���תΪutf-8
};

#endif // !defined(AFX_ZWfun_H__B4906CE0_FFDC_4045_948F_1EF630BABF39__INCLUDED_)
