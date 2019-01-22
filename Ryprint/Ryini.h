#pragma once
class CRyini
{
public:
	CRyini(void);
	~CRyini(void);


public:
	CRect AdRect;
	CRect GrpModuleRect;
	CRect GrpMainRect;
	CRect GrpMenuRect;
	CRect DesignMainRect;
	CRect DesignMenuRect;

	int StatusHeight;

	CPoint WinMinSize;
};

