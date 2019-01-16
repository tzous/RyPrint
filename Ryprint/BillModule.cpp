#include "StdAfx.h"
#include "BillModule.h"


CBillModule::CBillModule(void)
{
	isInit = FALSE;
	m_Name = "";	//凭证名称
	m_Width = 180;		//凭证宽度
	m_Height = 100;		//凭证高度
	isLoadJPG = FALSE;		//是否导入背景
	isModified = FALSE;

}


CBillModule::~CBillModule(void)
{
}

// 初始化新凭证模板信息
int CBillModule::InitBillMod(CString Name, int Width, int Height)
{
	isInit = TRUE;		//已初始化
	isModified = TRUE;	//凭证信息已变更，需要提示保存
	m_Name = Name;	//凭证名称
	m_Width = Width;		//凭证宽度
	m_Height = Height;		//凭证高度
	isLoadJPG = FALSE;		//是否导入背景

	return 0;
}

//删除凭证信息
int CBillModule::DelBillMod()
{
	if(!isInit) return 0;	//未初始化，无需操作
	//其他磁盘操作


	isInit = FALSE;
	isModified = FALSE;
	m_Name = "";	//凭证名称
	m_Width = 180;		//凭证宽度
	m_Height = 100;		//凭证高度
	isLoadJPG = FALSE;		//是否导入背景


	return 0;
}
//保存凭证信息
int CBillModule::SaveBillMod()
{
	if(!isInit) return 0;
	if(!isModified) return 0;		//如无变更，则无需保存

	//其他磁盘操作

	isModified = FALSE;			//置无需保存状态

	return 0;
}

//得到是否已初始化状态
BOOL CBillModule::getIsInit()
{
	return isInit;
}
//得到是否已变更状态
BOOL CBillModule::getIsModified()
{
	if(!isInit) return FALSE;
	return isModified;
}

//CDC * pDC 当前窗口设备
//CRect rect 当前凭证分组位置
void CBillModule::Draw(CDC * pDC,CRect mrect)		//绘制当前凭证
{
	if(!isInit) return;	//模板未初始化，不能绘制
	CRect rect;
	rect.left = mrect.left+10;
	rect.top = mrect.top+10;
	int w = m_Width*96/25.4;
	int h = m_Height*96/25.4;
	rect.right = rect.left + w;
	rect.bottom = rect.top + h;
	pDC->MoveTo(rect.left,rect.top); 

	//绘制凭证背景
	if(isLoadJPG){
		//绘制背景
	}else {
		//绘制空矩形占位
		//CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		//CBrush *pOldBrush=pDC->SelectObject(pBrush);
		pDC->Rectangle(rect);
		//pDC->SelectObject(pOldBrush);
	}

}

