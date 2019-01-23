// ZWfun.cpp: implementation of the ZWfun class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ZWfun.h"
#include ".\zwfun.h"
#include <locale>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZWfun::CZWfun()
{

}

CZWfun::~CZWfun()
{

}
//�ļ��Ƿ����
BOOL CZWfun::IsFileExist(const CString& csFile)
{
    DWORD dwAttrib = GetFileAttributes(csFile);
    return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

//���Сдת��д
void CZWfun::ntoc(char *str, char *value)
{
	static char *s1[]={"��","Ҽ","��","��","��","��","½","��","��","��"};
	static char *s2[]={"Ǫ","��","ʰ","��","Ǫ","��","ʰ","��","Ǫ","��","ʰ","Ԫ","��","��"};
	int i=0,j=0,k=0;
	char s[15];
	sprintf(s,"%014.0f",atof(value)*100);
	strcpy(str,"");
	for(i=0;s[i]=='0';i++);
	while(i<14)
	{
		j=s[i]-48;
		if(j==0)
		{
			if(i==3||i==7||i==11||i==13)
			{
				if(i==3||i==11)
				{
					strcat(str,s2[i]);
					k=0;
				}
				if(i==7&&(k!=3))
				{
					strcat(str,s2[i]);
					k=0;
				}
				if(i==7&&k==3) k=1;
				if(i==13) strcat(str,"��");
			}
			else k++;
		}
		else
		{
			if(k>0)
			{
				strcat(str,s1[0]);
				k=0;
			}
			strcat(str,s1[j]);
			strcat(str,s2[i]);
		}
		i++;
	}
	return;

}
//����Сдת��д��һ��һ��
void CZWfun::numtocap(char *s,char *val)
{
	const char *s1[]={"��","Ҽ","��","��","��","��","½","��","��","��"};

	int i=0;
	s[0] = '\0';
	for(i=0; val[i] != '\0' && i < BUFSIZE/4;i++) {
		char ch = val[i];
		if(!isdigit(ch)) ch = '0';
		strcat(s,s1[ch - '0']);
	}
	return;
}
//���Сдת��д
int CZWfun::cov_money(char *sj, char *string)
{
  register int i;
  static char *number[]={"��","Ҽ","��","��","��","��","½","��","��","��"};
  static char *mon[]={"��","Ǫ","��","ʰ","��","Ǫ","��","ʰ","��","Ǫ","��","ʰ","Ԫ","��","��"};
  int length;
  int flag=1;
  while(*sj=='0'||*sj==' ') sj++;		/*ȥ������ǰ��0*/
  string[0]='\0';		/*��ʼ�������ַ���*/
  length=strlen(sj);
  if(length==0)			/*��ֵΪ0*/
  {
	strcpy(string,number[0]);
	strcat(string,mon[14]);
	return 0;
  }
  if(length>15)			/*�糬������Χ*/
	return(-1);
  for(i=0;i<length;i++)
	if(!isdigit(sj[i]))
 		return(-1);
  for(i=15-length;i<15;i++)
  {
	if(sj[i-15+length]-48!=0)	/*�����ַ���*/
 	{
 		strcat(string,number[sj[i-15+length]-48]);
 		strcat(string,mon[i]);
 	}
	else				/*���λΪ��*/
 	{
  		if(i==5)		/*����ǧ��λ*/
   		{
    			if(sj[i-15+length+1]-48==0&&sj[i-15+length+2]-48==0)
    				flag=0;
   		}
  		else
    			if(i==12||(i==8&&flag)||i==4)	/*0��Ԫ,��,��*/
   		 		strcat(string,mon[i]);
			else
  			if(sj[i-15+length+1]-48!=0&&sj[i-15+length+1]!='\x0')
  				strcat(string,number[sj[i-15+length]-48]);
	}
  }
  if(sj[length-1]-48==0)
	strcat(string,"��\0");
  else
 	strcat(string,"\0");
  return(0);

}
/*ɾ���Ǻ����ַ�*/
int CZWfun::del_not_c(char *str)
{
        int     len;
        int     i,j;
       
        len = strlen(str);
	for(i=0,j=0;str[j] !='\0';j++) 
	{
		if(str[j] < 0)
		{
			if(i%2==0&&(unsigned char)str[j]>175&&(unsigned char)str[j]<248)
				str[i++] = str[j];
			else if(i%2==1&&(unsigned char)str[j]>160&&(unsigned char)str[j]<256)
				str[i++] = str[j];
		}
	}
	if(i % 2 == 1)
		i --;
	for(;i<len;i++)
		str[i] = ' ';
	str[len] = '\0';
	return(0);

}
/* Truncate space in the string.
** Return : >0 success -1  fail
** Entry  : str - input string
**          type - truncate type (1-front space   2-last space   9-all space)
** Outlet : str - output string with space truncated
*/

int CZWfun::del_space(char *s, int type)
{
	       int     len;
        int     i,j;
       
        len = strlen(s);
	switch(type) {
	case 1:
		for(i=0;s[i]!='\0'&&(s[i]==' '||s[i]=='\t');i++);
		if(s[i] == '\0') {
			s[0] = '\0';
			return(0);
		}
		for(j=0;s[i]!='\0';i++,j++)
			s[j] = s[i];
		s[j] = 0;
		break;
	case 2:
        	i = len - 1;
        	while(i >= 0) {
              		if((s[i] == ' '||s[i]=='\t')) {
              			s[i] = 0;
              			i --;
			}
			else
				break;
        	} 
		break;
	case 9:
		for(i=0,j=0;s[j] !='\0';j++) {
			if((s[j]!=' '&&s[i]!='\t'))
				s[i++] = s[j];
		}
		s[i] = '\0';
		break;
	default:
		return(-1);
	}
        len = strlen(s);
	return   len;
}/*�����ַ�����ָ���ַ�*/
char * CZWfun::Filter(const char *s, char c)
{
	static char str[BUFSIZE];
	int	i,j;
	memset(str,0,BUFSIZE);
	if(strlen(s) >= BUFSIZE)
		memcpy(str,s,BUFSIZE-1);
	else
		strcpy(str,s);
	i =0;
	j = 0;
	while(str[i]!='\0')
	{
		if(str[i] != c)
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return str;
}
/*��s ��ȡ�õ�pt���ַ���,�ָ���Ϊtype,lenΪ��󳤶� */
char * CZWfun::get_word(char *s, int pt, char type, int len)
{
	int i,j;
	static char str[512];

	memset(str,0,512);
	for(i=0,j=0;s[i]!='\0'&&s[i]!='\n'&& j<pt;i++)
	{
		if(s[i] == type)
			j++;
	}
	if((s[i] == '\0' ||s[i]!='\n')&& j<pt)
		return(str);
	for(j=0;s[i]!='\0'&&s[i]!='\n'&& s[i]!=type && j<len;i++,j++)
		str[j] = s[i];
	return(str);
}

/*��s ��ȡ�õ�pt���ַ���,�ָ���Ϊtype,lenΪ��󳤶� */
/*��������ָ�����һ��*/
char * CZWfun::get_word2(char *s, int pt, char type, int len)
{
	int i,j;
	static char str[BUFSIZE];

	memset(str,0,BUFSIZE);
	for(i=0,j=0;s[i]!='\0'&&s[i]!='\n'&& j<pt;i++)
	{
		if(s[i] == type && s[i+1] != type)
			j++;
	}
	if((s[i] == '\0' ||s[i]!='\n')&& j<pt)
		return(NULL);
	for(j=0;s[i]!='\0'&&s[i]!='\n'&& s[i]!=type && j<len;i++,j++)
		str[j] = s[i];
	return(str);

}

BOOL CZWfun::isNumber(const char *s)
{
	CString ss = "0123456789.";
	CString t,r;
	t = Filter(s,' ');
	r = Filter(t,',');
	char str[128];
	strcpy(str,r.GetBuffer(127));
	if(!isdigit(str[0]) && str[0] != '-')
		return FALSE;
	for(int i=1;str[i] != '\0';i++)
	{
		if(!strchr(ss,str[i]))
			return FALSE;
	}
	return TRUE;
}
int CZWfun::DateNum(int year,int month)
{
	if(month == 2) {
		if((year%4==0&&year%100!=0)||year%400==0)
			return 29;
		else
			return 28;
	}
	switch(month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
	}
	return 0;
}

// ������ǧ��λ
char * CZWfun::AddComma(double je)
{
	char s[128];
	static char str[128];
	sprintf(s,"%.2f",je);
	int len = strlen(s);
	int l = (len-3)%3;
	int i,j;
	for(i=0,j=0;i<len;i++,j++) {
		if(i!=0 && (i-l)%3 == 0 && i<len-3) {
			str[j++] = ',';
		} 
		str[j] =s[i];
	}
	str[j] = '\0';
	return str;
}

// �ַ�������
int CZWfun::mystrcat(char * dst, const char * src)
{
	char * cp = dst; 
	while( *cp ) 
		cp++; /* find end of dst */ 
		while( *cp++ = *src++ ) ; /* Copy src to end of dst */ 
	return 0;
}

// �õ���·���ļ���
char * CZWfun::GetFileName(CString strFileName)
{
	static char sName[256];
	memset(sName,0,256);
	if(strFileName.GetLength() > 0) 
		  strncpy(sName,(strFileName.Right(strFileName.GetLength()-strFileName.ReverseFind('\\')-1)).GetBuffer(),255);  

	return sName;
}
// ɾ��SQL�ַ����в��Ϸ����ַ�
void CZWfun::dowith_sql(CString * strSql)
{
	strSql->Replace("\'","");
	strSql->Replace("\"","");
	strSql->Replace(" ","");
	strSql->Replace("=","");
	strSql->Replace("%20","");
	strSql->Replace(";","");
	strSql->Replace("(","");
	strSql->Replace(")","");
	strSql->Replace("/*","");
	strSql->Replace("*/","");
	strSql->Replace("%","");
	strSql->Replace("+","");
	strSql->Replace(">","");
	strSql->Replace("<","");
	strSql->Replace("--","");
	strSql->Replace("[","");
	strSql->Replace("]","");
	strSql->Replace("|","");
	strSql->Replace("&","");
	return ;
}
// �򵥵��ַ���ƥ�� -- ���ص�һ���ַ����ı��������е�λ��
int CZWfun::strFind( char * strT,char * strP,int lPos)
{
	int i, j;
	int lP,lT;
	lP = strlen(strP);
	lT = strlen(strT);
	i = lPos;
	while(i <= lT-lP) {
		j = 0;
		while(strT[i+j] == strP[j] && j < lP) {
			j++;
		}
		if(j == lP)
			return i;
		i++;
	}
	return -1;
}

//KMP-��ȡģʽ�ַ�����Next����
void CZWfun::GetModeNext(char * t, int * p)
{
	p[1] = 0;//����ȷ����һ��Next�����Ԫ�ء�
	int i = 1;
	int j = 0;
	while (i < strlen(t))
	{
		if (t[i] == t[j])
		{
			i++;
			j++;
			p[i] = j;
		}
		else if (t[i] != t[j])
		{
			i++;
			p[i] = 0;
			j = 0;

		}
	}
}

 //KMP-ƥ�䷽��������ֵ����Ŀ���ַ�����ƥ��ɹ���λ��
int CZWfun::Matching(char * s, char * t, int* p)
{
	int i = 0;
	int j = 0;
	int indext = -1;

	while (j < strlen(t) && i < strlen(s))
	{
		if (s[i] == t[j] || j == 0)
		{
			i++;
			j++;
		}
		else
		{
			j = p[j];
		}
	}
	if (j == strlen(t))//��ʾƥ��ɹ�
	{
		indext = i - strlen(t) ;//��ȡƥ��ɹ���λ�� -- ��һ���ַ�λ��Ϊ0
		return indext;
	}
	return indext;
}
 
// �ַ���ƥ��KMP�㷨 -���ص�һ���ַ����ı��������е�λ��
int CZWfun::strFindKMP(char * strT,char * strP, int lPos)
{
	int size = strlen(strT);
	int * p = new int[size];//����NEXT����
	GetModeNext(strP, p);//���û�ȡNext����ķ���
	int indext = Matching(strT, strP, p);//����ƥ��ķ���

	return indext;
}
// �ַ���ģ��ƥ��
BOOL CZWfun::strFindBlur(char * strT,char * strP, int lPos)
{
	int i, j;
	int lP,lT;
	lP = strlen(strP);
	lT = strlen(strT);
	i = lPos;
	j = 0;
	while(i < lT && j < lP) {
		if(strT[i] == strP[j]) {
			j++;
		}
		i++;
	}
	if(j == lP)
		return TRUE;
	return FALSE;
}

// �õ�Ӧ�ó��������ļ���
CString CZWfun::GetAppPath(void)
{
	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);	//�õ�Ӧ�ó���·��
	sPath.ReleaseBuffer ();
	int nPos;
	nPos=sPath.ReverseFind ('\\');
	sPath=sPath.Left(nPos);
	return sPath;
}
// ����Ƿ�Ϊ����IP
int CZWfun::CheckAllowIP(CString AllowIP,CString IP)
{
	CZWfun zwf;
	int ret = -1;
	int y[4];

	sscanf(IP.GetBuffer(),"%d.%d.%d.%d",&y[0],&y[1],&y[2],&y[3]);
	for(int i=0;i<20;i++) {	//���20��������;�ֿ���ÿ������ΪIP��ַ��ʽ��ͨ���Ϊ*�������������ܻ��
		CString sRule = zwf.get_word2(AllowIP.GetBuffer(),i,';',20);
		if(sRule.GetLength() == 0) break;
		bool bMatch = true;
		for(int j=0;j<4&&bMatch;j++) {
			char s[4];
			sprintf(s,"%s",zwf.get_word(sRule.GetBuffer(),j,'.',3));
			if(s[0] != '\0') {
				if(zwf.isNumber(s)) {
					if(y[j] != atoi(s)) bMatch = false;
				}			
			} else
				j = 4;
		}
		if(bMatch) {
			ret = 0;
			break;
		}
	}

	return ret;
}
//�ļ���תΪutf-8
CString CZWfun::MbcsToUtf8(const char *file)
{
    CString str;
    WCHAR   *pwchar=0;
    CHAR    *pchar=0;
    int len=0;
    int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
    len=MultiByteToWideChar(codepage, 0, file, -1, NULL,0);
    pwchar=new WCHAR[len];
    if(pwchar!=0)
    {
        len = MultiByteToWideChar(codepage, 0, file, -1, pwchar, len);
        if( len!=0 ) 
        {
            len = WideCharToMultiByte(CP_UTF8, 0, pwchar, -1, 0, 0, 0, 0);
            pchar=new CHAR[len];
            if(pchar!=0)
            {
                len = WideCharToMultiByte(CP_UTF8, 0, pwchar, -1, pchar, len,0, 0);
                if(len!=0)                 
                {
                    str=pchar;                    
                }
                delete pchar;
            }
            delete pwchar; 
        }
    }
    return str;
}