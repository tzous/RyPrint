#include "StdAfx.h"
#include "Misc.h"


CMisc::CMisc(void)
{
}


CMisc::~CMisc(void)
{
}

BOOL CMisc::IsFileExist(const CString& csFile)
{
    DWORD dwAttrib = GetFileAttributes(csFile);
    return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}
