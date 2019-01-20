#pragma once

// CObFont 命令目标

class CObFont : public CObject
{  
	
	DECLARE_SERIAL( CObFont )
private:
	LOGFONT lf;			//字体结构
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
LOGFONT结构的定义如下：
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

LOGFONT结构中各个成员的含义如下：
lfHeight：设置字体的高度。
lfWidth：设置字体的平均宽度。
LfEscapement：设定字符串底线与水平线的夹角，夹角是以0.1度为单位。
lfOrientation：设定每一个字符的底线与水平线的夹角，夹角是以0.1度为单位。
lfWeight：设置字体的粗细，其取值范围为0～1000，通常400为正常粗细，700为粗，如果取值为0，则选择默认粗细。
lfItalic：如果为TRUE，则字体为斜体。
lfUnderline：如果为TRUE，则字体带下划线。
lfStrikeOut：如果为TRUE，则字体带删除线。
lfCharSet：指定字符集。
LfOutPrecision：指定输出时字体的精度。
lfClipPrecision：指定输出时字体被裁剪的精度。
lfQuality：指定输出质量。
lfPitchAndFamily：设置字体的斜度和字体类型。
lfFaceName[LF_FACESIZE]：设置字体字样。
*/
