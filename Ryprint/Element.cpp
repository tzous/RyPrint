#include "StdAfx.h"
#include "Element.h"
#include "ZWfun.h"

CElement::CElement(void)
{
	sVal = "Text";			///元素值
    sText = "Text";			//显示文本，与sVal关联

	pStartPoint = CPoint(0,0);		//左上角点
    nWidth = 120;				//宽
    nHeight = 26;				//高
       
    sName = "0";			//元素名称
    eType = ET_TEXT;				//当前元素类别,默认文本text
    //pFont;			//元素字体
    hAlign = HA_LEFT;				//水平对齐0-left、1-center、2-right
    vAlign = VA_CENTER;				//垂直对齐 0-top、1-center、2-bottom
    //以下为元素附加属性
    bTrim = TRUE;				//输入值是否要删除首尾空格
    bPrefix = FALSE;			//是否有前缀
    sPrefixText = "$";		//前缀文本，如人民币符号¥等
    bPostfix = FALSE;			//是否有后缀，如大写金额整
    sPostfixText = "";	//后缀文本
    bMeanCol = FALSE;			//是否均列打印
    nMeanColVal = 0;		//均列打印间隔
    sCheckVal = "√";		//check类型，取值预置为√×*等
    bPrintBorder = FALSE;		//是否打印边框
	ElementChTypes[0] = "文本";
	ElementChTypes[1] = "数字";
	ElementChTypes[2] = "数字大写";
	ElementChTypes[3] = "金额";
	ElementChTypes[4] = "金额大写";
	ElementChTypes[5] = "打勾项";
}


CElement::~CElement(void)
{
}
//设置元素值，同时格式化元素显示文本
void CElement::setVal(CString sval)	
{

	CString s = "";
	CString st = sval.Trim();
	char sret[nMaxElementLen];
	//根据元素类型，设置元素值
	switch(eType){
	case ET_NUM:
		if(st.SpanIncluding("0123456789") == sval) {
			s = st;
		}
		sVal = s;
		sText = s;
		break;
	case ET_NUMCAP:
		if(st.SpanIncluding("0123456789") == sval) {
			s.Format("%s",sret);
		}
		sVal = s;
		CZWfun::numtocap(sret,sVal.GetBuffer());
		sText = sret;		
		break;
	case ET_MONEY:
		if(st.SpanIncluding("0123456789.") == sval) {
			s.Format("%.2f",atof(st.GetBuffer()));
		} else {
			s = "0.00";
		}
		sVal = s;
		sText = s;
		break;
	case ET_MONEYCAP:
		if(st.SpanIncluding("0123456789.") == sval) {
			s.Format("%.2f",atof(st.GetBuffer()));
		} else {
			s = "0.00";
		}
		sVal = s;
		CZWfun::ntoc(sret,sVal.GetBuffer());
		sText = sret;
		break;
	case ET_CHECK:
		if(!st.IsEmpty()) {
			s = sCheckVal;
		}
		sVal = s;
		sText = s;
		break;
	default:	//含ET_TEXT
		if(bTrim) {
			s = st;
		} else {
			s = sval;
		}
		sVal = s;
		sText = s;
		break;
	}


}
//返回元素值
CString CElement::getVal()		
{
	return sVal;
}
//返回显示文本
CString CElement::getText()		
{
	return sText;
}
//返回第num个类型
CString CElement::getElementChType(int num)
{
	int n = num;
	if(n >= nElementTypesNum)
		n = 0;
	return ElementChTypes[n];
}
//返回所有类型，以','隔开
CString CElement::getAllElementChType()
{
	CString s = "";
	for(int i=0;i<nElementTypesNum;i++)
	{
		s = s + ElementChTypes[i]+ ",";
	}
	int len;
	len=s.GetLength();
	s.Left(len-1);
	return s;
}
//返回类型个数
int CElement::getnElementTypesNum()
{
	return nElementTypesNum;
}