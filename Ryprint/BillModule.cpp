#include "StdAfx.h"
#include "BillModule.h"


CBillModule::CBillModule(void)
{
	isInit = FALSE;
	m_Name = "";	//ƾ֤����
	m_Width = 180;		//ƾ֤���
	m_Height = 100;		//ƾ֤�߶�
	isLoadJPG = FALSE;		//�Ƿ��뱳��
	isModified = FALSE;

}


CBillModule::~CBillModule(void)
{
}

// ��ʼ����ƾ֤ģ����Ϣ
int CBillModule::InitBillMod(CString Name, int Width, int Height)
{
	isInit = TRUE;		//�ѳ�ʼ��
	isModified = TRUE;	//ƾ֤��Ϣ�ѱ������Ҫ��ʾ����
	m_Name = Name;	//ƾ֤����
	m_Width = Width;		//ƾ֤���
	m_Height = Height;		//ƾ֤�߶�
	isLoadJPG = FALSE;		//�Ƿ��뱳��

	return 0;
}

//ɾ��ƾ֤��Ϣ
int CBillModule::DelBillMod()
{
	if(!isInit) return 0;	//δ��ʼ�����������
	//�������̲���


	isInit = FALSE;
	isModified = FALSE;
	m_Name = "";	//ƾ֤����
	m_Width = 180;		//ƾ֤���
	m_Height = 100;		//ƾ֤�߶�
	isLoadJPG = FALSE;		//�Ƿ��뱳��


	return 0;
}
//����ƾ֤��Ϣ
int CBillModule::SaveBillMod()
{
	if(!isInit) return 0;
	if(!isModified) return 0;		//���ޱ���������豣��

	//�������̲���

	isModified = FALSE;			//�����豣��״̬

	return 0;
}

//�õ��Ƿ��ѳ�ʼ��״̬
BOOL CBillModule::getIsInit()
{
	return isInit;
}
//�õ��Ƿ��ѱ��״̬
BOOL CBillModule::getIsModified()
{
	if(!isInit) return FALSE;
	return isModified;
}

//CDC * pDC ��ǰ�����豸
//CRect rect ��ǰƾ֤����λ��
void CBillModule::Draw(CDC * pDC,CRect mrect)		//���Ƶ�ǰƾ֤
{
	if(!isInit) return;	//ģ��δ��ʼ�������ܻ���
	CRect rect;
	rect.left = mrect.left+10;
	rect.top = mrect.top+10;
	int w = m_Width*96/25.4;
	int h = m_Height*96/25.4;
	rect.right = rect.left + w;
	rect.bottom = rect.top + h;
	pDC->MoveTo(rect.left,rect.top); 

	//����ƾ֤����
	if(isLoadJPG){
		//���Ʊ���
	}else {
		//���ƿվ���ռλ
		//CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		//CBrush *pOldBrush=pDC->SelectObject(pBrush);
		pDC->Rectangle(rect);
		//pDC->SelectObject(pOldBrush);
	}

}

