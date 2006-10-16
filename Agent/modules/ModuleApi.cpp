
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pierre LEMMET/Pascal DANEK 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// ModuleApi.cpp: implementation of the CModuleApi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ocsinventory.h"
#include "ModuleApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModuleApi::CModuleApi(CString commandLine)
{
	cmdL = commandLine;
}

CModuleApi::~CModuleApi()
{

}

int CModuleApi::start()
{
	return 0;
}

int CModuleApi::prolog(CMarkup* pXml)
{
	return 0;
}

int CModuleApi::response(CMarkup* pXml, CString* pRawResponse)
{
	return 0;
}

int CModuleApi::inventory(CMarkup* pXml, CDeviceProperties* pPc)
{
	return 0;
}

int CModuleApi::end()
{
	return 0;
}
