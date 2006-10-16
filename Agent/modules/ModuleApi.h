
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pierre LEMMET/Pascal DANEK 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// ModuleApi.h: interface for the CModuleApi class.
//
//////////////////////////////////////////////////////////////////////
#include "../../include/xml/Markup.h"
#include "sysinfo.h"
#include "../../include/_common/utils.h"
#if !defined(AFX_MODULEAPI_H__DA72A25D_CAB9_4FE9_AAA5_5040338C8C4C__INCLUDED_)
#define AFX_MODULEAPI_H__DA72A25D_CAB9_4FE9_AAA5_5040338C8C4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CModuleApi : public CObject  
{
public:	
	CString cmdL; // the command line
	CDeviceProperties * pC; // the PC
	UINT proxy;
	CString server;
	INTERNET_PORT port;
	CString http_u;
	CString http_w;

	// CModuleApi constructor.
	// commandLine: command line
	CModuleApi(CString commandLine, CDeviceProperties * pD, CString serv, UINT prox, INTERNET_PORT prt, CString http_user, CString http_pwd) 
	{ 
		cmdL = commandLine; 
		pC = pD; 
		server = serv; 
		proxy = prox; 
		port = prt; 
		http_u = http_user; 
		http_w = http_pwd; 
	}

	// CModuleApi destructor.
	virtual ~CModuleApi() {}

	// Launched at the beginning of agent execution
	virtual int start(){return 0;}

	// Launched before the prolog sending.
	// pXml: A pointer to the structure containing the XML that will be sent to the server. 
	virtual int prolog(CMarkup* pXml){return 0;}

	// Launched right after the prolog reception, ONLY if the server successfully sent a response.
	// pXml: A pointer to the XML structure containing the server answer for the prolog.
	// pRawResponse: A pointer to the string containing the server answer for the prolog.
	virtual int response(CMarkup* pXml, CString* pRawResponse=NULL){return 0;}

	// Launched just after the inventory and before it is sent to the server, ONLY if an inventory is asked 
	// by the server
	// pXml: A pointer to the XML structure containing the inventory.
	// pPc: A pointer to the DeviceProperties object containing all information.
	virtual int inventory(CMarkup* pXml, CDeviceProperties* pPc) {return 0;}
	
	// Launched at the end of agent execution
	virtual int end() {return 0;}
};

#endif // !defined(AFX_MODULEAPI_H__DA72A25D_CAB9_4FE9_AAA5_5040338C8C4C__INCLUDED_)
