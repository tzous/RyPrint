#pragma once
//凭证模板
class CBillModule
{
public:
	CBillModule(void);
	~CBillModule(void);

private:
	BOOL isInit;		//是否已初始化（即可绘制）
	BOOL isLoadJPG;		//是否导入背景
	BOOL isModified;	//是否已变更

public:
	CString m_Name;	//凭证名称
	int m_Width;		//凭证宽度,单位毫米
	int m_Height;		//凭证高度，单位毫米


	void Draw(CDC * pDC,CRect mrect);		//绘制当前凭证
	// 初始化新凭证模板信息
	int InitBillMod(CString Name, int Width, int Height);
	//删除凭证信息
	int DelBillMod();
	//保存凭证信息
	int SaveBillMod();
	//得到是否已初始化状态
	BOOL getIsInit();
	//得到是否已变更状态
	BOOL getIsModified();
};

