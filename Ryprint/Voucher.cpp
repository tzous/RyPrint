#include "StdAfx.h"
#include "Voucher.h"


CVoucher::CVoucher(void)
{
	bBackGround = FALSE;		//是否导入背景图
	sName = "";			//凭证名称
    sText = "";			//显示的凭证中文名称
    nWidth = 180;				//凭证宽度，毫米
    nHeight = 100;			//凭证高度，毫米
    nDpi = 96;				//屏幕dpi
    nPixelWidth = 850;		//凭证宽度，像素
    nPixelHeight = 377;		//凭证高度，像素
    nType = 0;				//凭证分类
    //List<CElement> pElements;	//凭证元素，使用字典保存，元素在表中的序号作为key
    sBackGround = "";		//凭证背景,base64编码

}


CVoucher::~CVoucher(void)
{
}

void CVoucher::setWidth(int width)				//凭证宽度，毫米
{
	nWidth = width;
	nPixelWidth = (int)(width * nDpi / 25.4);
}
int CVoucher::getWidth()				//凭证宽度，毫米
{
	return nWidth;
}
int CVoucher::getPixelWidth()		//凭证宽度，像素
{
	return nPixelWidth;
}
void CVoucher::setHeight(int height)			//凭证高度，毫米
{
	nHeight = height;
	nPixelHeight = (int)(height * nDpi /25.4);
}
int CVoucher::getHeight()			//凭证高度，毫米
{
	return nHeight;
}
int CVoucher::getPixelHeight()		//凭证高度，像素
{
	return nPixelHeight;
}
