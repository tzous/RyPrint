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
	BOOL bBackGround;		//是否导入背景图
    int nWidth;				//凭证宽度，毫米
    int nHeight;			//凭证高度，毫米
    int nPixelWidth;		//凭证宽度，像素
    int nPixelHeight;		//凭证高度，像素

public:
	CString sName;			//凭证名称
    CString sText;			//显示的凭证中文名称
    int nDpi;				//屏幕dpi
    int nType;				//凭证分类
    list<CElement> pElements;	//凭证元素，使用字典保存，元素在表中的序号作为key
    CString sBackGround;		//凭证背景,base64编码

    void setWidth(int width);				//凭证宽度，毫米
    int getWidth();				//凭证宽度，毫米
    int getPixelWidth();		//凭证宽度，像素
    void setHeight(int height);			//凭证高度，毫米
    int getHeight();			//凭证高度，毫米
    int getPixelHeight();		//凭证高度，像素

};

#endif