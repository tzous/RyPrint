#pragma once
#include "ObFont.h"

class CSysdata
{
private:
	CString sSysdb;		//ϵͳ���ݿ�·����

public:
	CString sSysname;	//����
	int nMaxtypeid;		//ϵͳ�����������ID
	int nMaxvoucherid;	//ϵͳ�������Ʊ��ID
	int nLeftmargin;		//��ӡ��Ĭ����߾�
	int nTopmargin;		//��ӡ��Ĭ���ϱ߾�
	CString sPrinter;	//Ĭ�ϴ�ӡ��
	CObFont cFont;		//Ĭ������
	BOOL bAutoSave;		//���ʴ�ӡ���Ƿ��Զ�����
	int nBatchrow;		// ����������ʼ��

public:
	CSysdata(void);
	~CSysdata(void);

private:
	// ��ʼ��ϵͳ���ݿ��ļ�
	int InitSysData(void);
public:
	// ��ȡϵͳ���ݿ�
	int loadSysdata(void);
};

