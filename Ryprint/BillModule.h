#pragma once
//ƾ֤ģ��
class CBillModule
{
public:
	CBillModule(void);
	~CBillModule(void);

private:
	BOOL isInit;		//�Ƿ��ѳ�ʼ�������ɻ��ƣ�
	BOOL isLoadJPG;		//�Ƿ��뱳��
	BOOL isModified;	//�Ƿ��ѱ��

public:
	CString m_Name;	//ƾ֤����
	int m_Width;		//ƾ֤���,��λ����
	int m_Height;		//ƾ֤�߶ȣ���λ����


	void Draw(CDC * pDC,CRect mrect);		//���Ƶ�ǰƾ֤
	// ��ʼ����ƾ֤ģ����Ϣ
	int InitBillMod(CString Name, int Width, int Height);
	//ɾ��ƾ֤��Ϣ
	int DelBillMod();
	//����ƾ֤��Ϣ
	int SaveBillMod();
	//�õ��Ƿ��ѳ�ʼ��״̬
	BOOL getIsInit();
	//�õ��Ƿ��ѱ��״̬
	BOOL getIsModified();
};

