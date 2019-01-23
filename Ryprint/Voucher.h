#if !defined(AFX_CVoucher_H__B4906CE0_FFDC_4045_948F_1EF630BABF39__INCLUDED_)
#define AFX_CVoucher_H__B4906CE0_FFDC_4045_948F_1EF630BABF39__INCLUDED_
#pragma once
#include "Element.h"
#include <list>
using namespace std;
class CVoucher
{
public:
	CVoucher(void);
	~CVoucher(void);

private:
	BOOL bBackGround;		//�Ƿ��뱳��ͼ
    int nWidth;				//ƾ֤��ȣ�����
    int nHeight;			//ƾ֤�߶ȣ�����
    int nPixelWidth;		//ƾ֤��ȣ�����
    int nPixelHeight;		//ƾ֤�߶ȣ�����

public:
	CString sName;			//ƾ֤����
    CString sText;			//��ʾ��ƾ֤��������
    int nDpi;				//��Ļdpi
    int nType;				//ƾ֤����
    list<CElement> pElements;	//ƾ֤Ԫ�أ�ʹ���ֵ䱣�棬Ԫ���ڱ��е������Ϊkey
    CString sBackGround;		//ƾ֤����,base64����

    void setWidth(int width);				//ƾ֤��ȣ�����
    int getWidth();				//ƾ֤��ȣ�����
    int getPixelWidth();		//ƾ֤��ȣ�����
    void setHeight(int height);			//ƾ֤�߶ȣ�����
    int getHeight();			//ƾ֤�߶ȣ�����
    int getPixelHeight();		//ƾ֤�߶ȣ�����

};

#endif