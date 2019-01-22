#pragma once
#include "ObFont.h"
#include "List.h"

class CSysdata
{
private:
	CString sdbfile;	//ϵͳ���ݿ��ļ�ȫ·����

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

	typedef struct sysdata_type {
		int tid;
        CString tname;
		int ptid;
	}CSysType;
	List<CSysType> systypes;	//ϵͳ����
	typedef struct sysdata_voucher {
		int vid;
        CString vname;
        CString vtext;
        int tid;
	}CSysVoucher;
	List<CSysVoucher> sysvouchers;	//ϵͳ����ģ����Ϣ��

public:
	CSysdata(void);
	~CSysdata(void);

private:
	// ��ʼ��ϵͳ���ݿ��ļ�
	int InitSysData(void);
public:
	// ��ȡϵͳ���ݿ�
	int loadSysdata(void);
	int loadSysdata(CString sFile);
	//���õ�ǰϵͳ���ݿ�·��
	int SetDbPath(CString sPath);
};

