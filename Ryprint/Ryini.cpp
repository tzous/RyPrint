#include "StdAfx.h"
#include "Ryini.h"


CRyini::CRyini(void)
{
	//�����
	AdRect.top = 5;		//���ϱ�����
	AdRect.left = 5;	//���������
	AdRect.right = 5;   //���ұ�����
	AdRect.bottom = 115;	//�߶�

	//״̬���߶�
	StatusHeight = 27;	

	//ģ����Ϣ��
	GrpModuleRect.left = 5;	//���������
	GrpModuleRect.right = 250;	//���
	GrpModuleRect.top = AdRect.bottom; //λ�ڹ��������
	GrpModuleRect.bottom = StatusHeight + 3;	 //λ��״̬����

	//���ܰ�ť��
	GrpMenuRect.left = GrpModuleRect.right + 5;	//��ģ����Ϣ����
	GrpMenuRect.right = 5;	//���ұ�����
	GrpMenuRect.top = AdRect.bottom;	//λ�ڹ��������
	GrpMenuRect.bottom = 210;		//�߶�

	//������
	GrpMainRect.left = GrpModuleRect.right + 5;		//��ģ����Ϣ����
	GrpMainRect.right = 5;	//���ұ�����
	GrpMainRect.top = GrpMenuRect.bottom;	//���ܰ�ť����
	GrpMainRect.bottom = StatusHeight + 3;	 //λ��״̬����

	
	//��С����
	WinMinSize.x = 980;
	WinMinSize.y = 720;
}


CRyini::~CRyini(void)
{
}


