#pragma once

// CObFont ����Ŀ��

class CObFont : public CObject
{  
	
	DECLARE_SERIAL( CObFont )
private:
	LOGFONT lf;			//����ṹ
public:	
	CObFont();
	CObFont(CString &s_logfont);
	CObFont(CFont &font);
	virtual ~CObFont();
	virtual void Serialize(CArchive &archive);
	LOGFONT GetLogFont() const;
	BOOL SetLogFont(CFont *pfont);
#ifdef _DEBUG
	virtual void Dump( CDumpContext& dumpSite ) const;
	virtual void AssertValid() const;
#endif
	void StringToLogfont(CString &s_logfont,LOGFONT &lfont);
	void LogfontToString(LOGFONT &lfont,CString &s_logfont);
	void fromString(CString &s_logfont);
	CString toString();

};

/*
LOGFONT�ṹ�Ķ������£�
typedef struct tagLOGFONT {
LONG lfHeight;
LONG lfWidth;
LONG lfEscapement;
LONG lfOrientation;
LONG lfWeight;
BYTE lfItalic;
BYTE lfUnderline;
BYTE lfStrikeOut;
BYTE lfCharSet;
BYTE lfOutPrecision;
BYTE lfClipPrecision;
BYTE lfQuality;
BYTE lfPitchAndFamily;
TCHAR lfFaceName[LF_FACESIZE];
} LOGFONT;

LOGFONT�ṹ�и�����Ա�ĺ������£�
lfHeight����������ĸ߶ȡ�
lfWidth�����������ƽ����ȡ�
LfEscapement���趨�ַ���������ˮƽ�ߵļнǣ��н�����0.1��Ϊ��λ��
lfOrientation���趨ÿһ���ַ��ĵ�����ˮƽ�ߵļнǣ��н�����0.1��Ϊ��λ��
lfWeight����������Ĵ�ϸ����ȡֵ��ΧΪ0��1000��ͨ��400Ϊ������ϸ��700Ϊ�֣����ȡֵΪ0����ѡ��Ĭ�ϴ�ϸ��
lfItalic�����ΪTRUE��������Ϊб�塣
lfUnderline�����ΪTRUE����������»��ߡ�
lfStrikeOut�����ΪTRUE���������ɾ���ߡ�
lfCharSet��ָ���ַ�����
LfOutPrecision��ָ�����ʱ����ľ��ȡ�
lfClipPrecision��ָ�����ʱ���屻�ü��ľ��ȡ�
lfQuality��ָ�����������
lfPitchAndFamily�����������б�Ⱥ��������͡�
lfFaceName[LF_FACESIZE]����������������
*/
