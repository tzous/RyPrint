#if !defined(AFX_CElement_H__B4906CE0_FFDC_4045_948F_1EF630BABF39__INCLUDED_)
#define AFX_CElement_H__B4906CE0_FFDC_4045_948F_1EF630BABF39__INCLUDED_
#pragma once
#include "ObFont.h"

#define nMaxElementLen  512		//元素最大宽度
enum ElementTypes {ET_TEXT,ET_NUM, ET_NUMCAP, ET_MONEY, ET_MONEYCAP, ET_CHECK};	//所有元素类别

class CElement
{
public:
	CElement(void);
	~CElement(void);

private:
        CString sVal;			///元素值
        CString sText;			//显示文本，与sVal关联
		static const int nElementTypesNum = 6;		//元素类型种类
		//所有元素类别中文名称
		CString ElementChTypes[6]; 	//所有元素类别中文名称

public:	
	    CPoint pStartPoint;		//左上角点
        int nWidth;				//宽
        int nHeight;				//高
       
        CString sName;			//元素名称
        ElementTypes eType;				//当前元素类别,默认文本text
        CObFont pFont;			//元素字体
        HALIGN hAlign;				//水平对齐0-left、1-center、2-right
        VALIGN vAlign;				//垂直对齐 0-top、1-center、2-bottom
        //以下为元素附加属性
        BOOL bTrim;				//输入值是否要删除首尾空格
        BOOL bPrefix;			//是否有前缀
        CString sPrefixText;		//前缀文本，如人民币符号¥等
        BOOL bPostfix;			//是否有后缀，如大写金额整
        CString sPostfixText;	//后缀文本
        BOOL bMeanCol;			//是否均列打印
        int nMeanColVal;		//均列打印间隔
        CString sCheckVal;		//check类型，取值预置为√×*等
        BOOL bPrintBorder;		//是否打印边框

		void setVal(CString sval);	//设置元素值，同时格式化元素显示文本
		CString getVal();		//返回元素值
		CString getText();		//返回显示文本
		CString getElementChType(int num);	//返回第num个类型
		CString getAllElementChType();	//返回所有类型，以','隔开
		int getnElementTypesNum();		//返回类型个数
};

#endif