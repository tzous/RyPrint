// ObFont.cpp : 实现文件
//

#include "stdafx.h"
#include "Ryprint.h"
#include "ObFont.h"


// CObFont

CObFont::CObFont()
{

	CFont *font=NULL;
	
	font = new CFont();
	font->CreateFont(12,0,0,0,400,0,0,0,
		DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"Fixedsys"); 		
	
	font->GetLogFont(&lf);
	
	delete font; 
}

CObFont::CObFont(CString &s_logfont)
{
	fromString(s_logfont);
}

CObFont::CObFont(CFont &font)
{
	font.GetLogFont(&lf);
}

CObFont::~CObFont()
{
}

IMPLEMENT_SERIAL(CObFont, CObject, 0)

// CObFont 成员函数
void CObFont::Serialize(CArchive &archive)
{
	CObject::Serialize(archive);
	if (archive.IsStoring())			
		archive.Write(&lf, sizeof(lf));	
	else	
		archive.Read(&lf, sizeof(lf));	
}
 
LOGFONT CObFont::GetLogFont() const 
{
	return lf;
} 
 
BOOL CObFont::SetLogFont(CFont *pfont)
{	
	if (pfont !=NULL)
	{
		pfont->GetLogFont(&lf); 
	}
	
	return TRUE;
}
 
#ifdef _DEBUG
void CObFont::Dump( CDumpContext& dumpSite ) const
{
	CObject::Dump(dumpSite);
	
	//dumpSite ;
}
 
void CObFont::AssertValid() const
{
	// check base class first
	CObject::AssertValid();
	
	// check data members.
}	
#endif //_DEBUG
 
void CObFont::StringToLogfont(CString &s_logfont,LOGFONT &lfont)
{
 sscanf( s_logfont,
  "%ld,%ld,%ld,%ld,%ld,%u,%u,%u,%u,%u,%u,%u,%u,%s",
  &lfont.lfHeight,&lfont.lfWidth,&lfont.lfEscapement,&lfont.lfOrientation,&lfont.lfWeight,
  &lfont.lfItalic,&lfont.lfUnderline,&lfont.lfStrikeOut,&lfont.lfCharSet,
  &lfont.lfOutPrecision,&lfont.lfClipPrecision,&lfont.lfQuality,&lfont.lfPitchAndFamily,
  &lfont.lfFaceName);
}

void CObFont::LogfontToString(LOGFONT &lfont,CString &s_logfont)
{
 s_logfont.Format(
  "%ld,%ld,%ld,%ld,%ld,%u,%u,%u,%u,%u,%u,%u,%u,%s",
  lfont.lfHeight,lfont.lfWidth,lfont.lfEscapement,lfont.lfOrientation,lfont.lfWeight,
  lfont.lfItalic,lfont.lfUnderline,lfont.lfStrikeOut,lfont.lfCharSet,
  lfont.lfOutPrecision,lfont.lfClipPrecision,lfont.lfQuality,lfont.lfPitchAndFamily,
  lfont.lfFaceName);
}
void CObFont::fromString(CString &s_logfont)
{
 sscanf( s_logfont,
  "%ld,%ld,%ld,%ld,%ld,%u,%u,%u,%u,%u,%u,%u,%u,%s",
  &lf.lfHeight,&lf.lfWidth,&lf.lfEscapement,&lf.lfOrientation,&lf.lfWeight,
  &lf.lfItalic,&lf.lfUnderline,&lf.lfStrikeOut,&lf.lfCharSet,
  &lf.lfOutPrecision,&lf.lfClipPrecision,&lf.lfQuality,&lf.lfPitchAndFamily,
  lf.lfFaceName);
}
CString CObFont::toString()
{
  CString s_logfont;
  s_logfont.Format(
  "%ld,%ld,%ld,%ld,%ld,%u,%u,%u,%u,%u,%u,%u,%u,%s",
  lf.lfHeight,lf.lfWidth,lf.lfEscapement,lf.lfOrientation,lf.lfWeight,
  lf.lfItalic,lf.lfUnderline,lf.lfStrikeOut,lf.lfCharSet,
  lf.lfOutPrecision,lf.lfClipPrecision,lf.lfQuality,lf.lfPitchAndFamily,
  lf.lfFaceName);
  return s_logfont;
}

