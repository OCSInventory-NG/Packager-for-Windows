// ModuleRegistry.cpp: implementation of the CModuleRegistry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModuleRegistry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CModuleRegistry::CModuleRegistry(CString commandLine,CDeviceProperties * pC, CString serv, UINT prox, INTERNET_PORT port ) : CModuleApi( commandLine, pC, serv, prox, port ) {
	pXmlResponse = NULL;
	pMyXml = NULL;
}

int CModuleRegistry::response(CMarkup* pXml, CString* pRawResponse)
{
	pXmlResponse = pXml;
	return 0;
}

int CModuleRegistry::inventory(CMarkup* pXml, CDeviceProperties* pPc)
{		
	if( pXmlResponse && CUtils::isActivatedOption(*pXmlResponse,"REGISTRY")) {			
		CUtils::trace("REGISTRY",cmdL);
		AddLog( _T( "Registry Values: function enabled by server...\n"));
		
		int cmpt=1;
		CMapStringToString* pM=NULL;
		
		do 
		{
			CUtils::cleanCm(pM);
			pM=CUtils::getOptionAttributes(*pXmlResponse,cmpt,"REGISTRY","REGTREE","REGKEY","NAME", "");
			
			if ( pM->GetCount() == 0 )
				break;

			CRegistry		myRegistry;
			CRegistryValue  myObject;
			CString	csName,
					csRegKey,
					csRegValue,
					csResult,
					csRegTree;
			int		nRegTree;

			pM->Lookup("REGTREE",csRegTree);
			pM->Lookup("VAL",csRegValue);
			pM->Lookup("REGKEY",csRegKey);
			pM->Lookup("NAME",csName);
			
			nRegTree = _ttoi( csRegTree );

			if (csRegValue == REGISTRY_ALL_VALUES_OF_KEY)
			{
				// Get all values of a key
				myRegistry.GetRegistryMultipleValues( pPc->GetDeviceID(), csName, nRegTree, csRegKey, &(pPc->m_RegistryList));
			}
			else
			{
				// Get single value

				if (myRegistry.GetRegistryValue( nRegTree, csRegKey, csRegValue, csResult))
				{
					// Add result to list
					myObject.SetDeviceID( pPc->GetDeviceID());
					myObject.Set( csName, csResult);
					pPc->m_RegistryList.AddTail( myObject);								
				}
			}
			cmpt++;							
		}
		while(pM->GetCount()>0);

		CUtils::cleanCm(pM);
		AddLog( _T( "Registry Values: scan finished (%d query executed)\n"), cmpt);
	}
	return 0;
}



