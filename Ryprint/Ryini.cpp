#include "StdAfx.h"
#include "Ryini.h"


CRyini::CRyini(void)
{
	//广告条
	AdRect.top = 5;		//距上边像素
	AdRect.left = 5;	//距左边像素
	AdRect.right = 5;   //距右边像素
	AdRect.bottom = 115;	//高度

	//状态条高度
	StatusHeight = 27;	

	//模板信息框
	GrpModuleRect.left = 5;	//距左边像素
	GrpModuleRect.right = 250;	//宽度
	GrpModuleRect.top = AdRect.bottom; //位于广告条下面
	GrpModuleRect.bottom = StatusHeight + 3;	 //位于状态条上

	//功能按钮区
	GrpMenuRect.left = GrpModuleRect.right + 5;	//在模板信息框右
	GrpMenuRect.right = 5;	//距右边像素
	GrpMenuRect.top = AdRect.bottom;	//位于广告条下面
	GrpMenuRect.bottom = 210;		//高度

	//主画板
	GrpMainRect.left = GrpModuleRect.right + 5;		//在模板信息框右
	GrpMainRect.right = 5;	//距右边像素
	GrpMainRect.top = GrpMenuRect.bottom;	//功能按钮区下
	GrpMainRect.bottom = StatusHeight + 3;	 //位于状态条上

	
	//最小窗口
	WinMinSize.x = 980;
	WinMinSize.y = 720;
}


CRyini::~CRyini(void)
{
}


// 读入INI配置
int CRyini::ReadIniFile(CString inifile)
{
//	char Buffer[256];
//	::GetPrivateProfileString("SysWindow","ADLeft","5",Buffer,4,inifile);		// 广告窗口左边距
//	AdRect.left = atoi(Buffer);
//	::GetPrivateProfileString("SysWindow","ADRight","5",Buffer,4,inifile);		// 广告窗口右边距
//	AdRect.right = atoi(Buffer);
//	::GetPrivateProfileString("SysWindow","ADTop","5",Buffer,4,inifile);		// 广告窗口上边距
//	AdRect.top = atoi(Buffer);
//	::GetPrivateProfileString("SysWindow","ADBottom","115",Buffer,4,inifile);		// 广告窗口高
//	AdRect.bottom = atoi(Buffer);

	return 0;
}
