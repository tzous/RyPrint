#include "StdAfx.h"
#include "Voucher.h"


CVoucher::CVoucher(void)
{
	bBackGround = FALSE;		//�Ƿ��뱳��ͼ
	sName = "";			//ƾ֤����
    sText = "";			//��ʾ��ƾ֤��������
    nWidth = 180;				//ƾ֤��ȣ�����
    nHeight = 100;			//ƾ֤�߶ȣ�����
    nDpi = 96;				//��Ļdpi
    nPixelWidth = 850;		//ƾ֤��ȣ�����
    nPixelHeight = 377;		//ƾ֤�߶ȣ�����
    nType = 0;				//ƾ֤����
    //List<CElement> pElements;	//ƾ֤Ԫ�أ�ʹ���ֵ䱣�棬Ԫ���ڱ��е������Ϊkey
    sBackGround = "";		//ƾ֤����,base64����

}


CVoucher::~CVoucher(void)
{
}

void CVoucher::setWidth(int width)				//ƾ֤��ȣ�����
{
	nWidth = width;
	nPixelWidth = (int)(width * nDpi / 25.4);
}
int CVoucher::getWidth()				//ƾ֤��ȣ�����
{
	return nWidth;
}
int CVoucher::getPixelWidth()		//ƾ֤��ȣ�����
{
	return nPixelWidth;
}
void CVoucher::setHeight(int height)			//ƾ֤�߶ȣ�����
{
	nHeight = height;
	nPixelHeight = (int)(height * nDpi /25.4);
}
int CVoucher::getHeight()			//ƾ֤�߶ȣ�����
{
	return nHeight;
}
int CVoucher::getPixelHeight()		//ƾ֤�߶ȣ�����
{
	return nPixelHeight;
}
