
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pierre LEMMET/Pascal DANEK 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// ModuleRegistry.h: interface for the CModuleRegistry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODULEREGISTRY_H__F2A5E1E4_AB44_4B40_8C28_08DE1EEC3817__INCLUDED_)
#define AFX_MODULEREGISTRY_H__F2A5E1E4_AB44_4B40_8C28_08DE1EEC3817__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModuleApi.h"

class CModuleRegistry : public CModuleApi  
{
private:
	CMarkup* pXmlResponse; // Prolog response from the server
	CMarkup* pMyXml;
public:
	CModuleRegistry(CString commandLine,CDeviceProperties * pC, CString serv, UINT prox, INTERNET_PORT port, CString http_user, CString http_pwd );
	virtual ~CModuleRegistry() {};
		
	int response(CMarkup* pXml, CString* pRawResponse=NULL);
	int inventory(CMarkup* pXml, CDeviceProperties* pPc);	

};

#endif // !defined(AFX_MODULEREGISTRY_H__F2A5E1E4_AB44_4B40_8C28_08DE1EEC3817__INCLUDED_)
