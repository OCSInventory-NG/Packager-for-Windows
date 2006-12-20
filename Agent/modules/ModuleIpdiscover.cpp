
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pierre LEMMET/Pascal DANEK 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// ModuleIpdiscover.cpp: implementation of the CModuleIpdiscover class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModuleIpdiscover.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CModuleIpdiscover::CModuleIpdiscover(CString commandLine,CDeviceProperties * pC, CString serv, UINT prox, INTERNET_PORT port, CString http_u, CString http_w ) : CModuleApi( commandLine, pC, serv, prox, port, http_u, http_w )
{
	pXmlResponse = NULL;
	m_ipdisc_lat = 0;
}

int CModuleIpdiscover::response(CMarkup* pXml, CString* pRawResponse)
{
	pXmlResponse = pXml;
	return 0;
}

UINT threadWork( LPVOID pParam ) {

	CModuleIpdiscover* pIpd = (CModuleIpdiscover*)pParam;
	UINT* pDep = &pIpd->m_currentIp;//vire								
	HRESULT hr;
	ULONG IpCur;
	ULONG ulLen=6;
	ULONG pulMac[2];
	in_addr ipa;
	CString csSent;//, csName;
	BOOL	baliseIp = FALSE;
	hostent *hName = NULL;
	//COCSInventoryApp* pA = (COCSInventoryApp*)AfxGetApp();
	CMarkup * pXml = pIpd->pMyXml; // vire
	ULONG NetNumber = pIpd->m_netNumber; // vire

	memset (pulMac, 0xff, sizeof (pulMac));
	IpCur = *pDep + NetNumber ;							
	//ARP sent to IpCur
	hr = pIpd->lpfn_SendARP(pIpd->lpfn_ntohl(IpCur), 0, pulMac, &ulLen) ;

	if( ulLen > 0 && hr == NO_ERROR && ulLen==6) {
		size_t i, j;
		char * szMac = new char[ulLen*3];
		PBYTE pbHexMac = (PBYTE) pulMac;
		
		// Convert the binary MAC address into human-readable
		for (i = 0, j = 0; i < ulLen - 1; ++i) {
			j += sprintf (szMac + j, "%02X:", pbHexMac[i]);
		}			

		sprintf (szMac + j, "%02X", pbHexMac[i]);

		ipa.S_un.S_addr = pIpd->lpfn_htonl(IpCur);
		csSent = pIpd->lpfn_inet_ntoa(ipa);		

		struct sockaddr_in saIn;
		char szHostName[256];
		char szServInfo[256];
		
		//u_short port;
		//port = 27015;
		// Set up sockaddr_in structure which is passed
		// to the getnameinfo function
		saIn.sin_family = AF_INET;
		saIn.sin_addr.s_addr = inet_addr( csSent );
		//saGNI.sin_port = htons(port);

		// Call getnameinfo
		if( getnameinfo((SOCKADDR *)&saIn, sizeof(sockaddr), szHostName, 256, szServInfo, 256, NI_NUMERICSERV) != 0) {
		  AddLog("getnameinfo(): failed.\n");
		  AddLog("Error #: %ld\n", WSAGetLastError());
		}

		pIpd->m_cs.Lock();
/*
		hName = gethostbyaddr((char*)&ipa.S_un.S_addr, 4, AF_INET);
		if (WSAGetLastError() != 0) {
			csName = "";
			if (WSAGetLastError() == 11001 )
				AddLog("IPDISCOVER: Hostname for %s not found\n", csSent);
			else
				AddLog( _T("IPDISCOVER: ERROR: Error with gethostbyaddr: %i\n"), WSAGetLastError() );
		}
		else{
			csName = hName->h_name;
		}

*/
		pIpd->m_hostFound++;
		pXml->AddElem("H");
		pXml->AddChildElem("I",csSent);
		pXml->AddChildElem("M",szMac);
		pXml->AddChildElem("N",szHostName);

		IpCur = inet_addr(csSent);
		
		AddLog( _T( "\tIPDISCOVER: Computer found: IP:%s MAC:%s NAME:%s\n"),csSent,szMac,szHostName);
		pIpd->m_cs.Unlock();		
		delete [] szMac;
	}
	return 0;
}


int CModuleIpdiscover::inventory(CMarkup* pXml, CDeviceProperties* pPc)
{
	if( ! pXml )
		return 1;

	pMyXml = pXml;

	CString forcedIpdisc = CUtils::getParamValue(cmdL,"ipdisc");

	//TODO verifier pXMl <>null, + mettre =null ds constructeur
	if( pXmlResponse && ((CUtils::isActivatedOption(*pXmlResponse,"IPDISCOVER")) || forcedIpdisc.GetLength()>0 )) {
		CUtils::trace("IPDISCOVER",cmdL);
	// Update Didier LIROULET: To allow running under Win 95 or NT4 without iphlpapi.dll
		// Load the IPHLPAPI 32 bit and winsock 2 DLL
		HINSTANCE	hDllIpHlpApi,	hDllWS2;
		hDllIpHlpApi = LoadLibrary( _T( "iphlpapi.dll"));
		hDllWS2 = LoadLibrary( _T( "ws2_32.dll"));
		if ((hDllIpHlpApi == NULL) || (hDllWS2 == NULL))
		{
			// Tell the user that we could not find a usable WinSock DLL.                                  
			AddLog( _T( "IPDISCOVER: Failed to load <iphlpapi.dll> or <ws2_32.dll> !\n"));
		}
		else
		{
			// Load the SendARP, htonl, ntol, inet_addr and inet_ntoa functions
			if (((*(FARPROC*)&lpfn_SendARP = GetProcAddress( hDllIpHlpApi, _T( "SendARP"))) == NULL) ||
				((*(FARPROC*)&lpfn_htonl = GetProcAddress( hDllWS2, _T( "htonl"))) == NULL) ||
				((*(FARPROC*)&lpfn_ntohl = GetProcAddress( hDllWS2, _T( "ntohl"))) == NULL) ||
				((*(FARPROC*)&lpfn_inet_addr = GetProcAddress( hDllWS2, _T( "inet_addr"))) == NULL) ||
				((*(FARPROC*)&lpfn_inet_ntoa = GetProcAddress( hDllWS2, _T( "inet_ntoa"))) == NULL))
			{
				// Tell the user that we could not find a usable SetupAPI DLL or wsock32 DLL.                                  
				AddLog( _T( "IPDISCOVER: Failed to load <SendARP> function from iphlpapi.dll or <htonl/ntol/inet_addr/inet_ntoa> functions from ws2_32.dll !\n"));
			}
			else
			{						
				CMapStringToString* pM=NULL;	
				CString		nbr,mask,ipdisc_lat_server;
				int ipdisc_lat_cmdl;

				pM=CUtils::getOptionAttributes(*pXmlResponse,1,"IPDISCOVER", "IPDISC_LAT", "");
				pM->Lookup("VAL",nbr);
				pM->Lookup("IPDISC_LAT",ipdisc_lat_server);

				/* Allow to set the desired latency in command line (MISCELLANEOUS in services.ini)
				It overloads the server settings */
				
				ipdisc_lat_cmdl = atoi( CUtils::getParamValue(cmdL,"ipdisc_lat").GetBuffer(NULL) );
				
				m_ipdisc_lat = ipdisc_lat_cmdl?ipdisc_lat_cmdl:atoi(ipdisc_lat_server);
				
				if( !m_ipdisc_lat )
					m_ipdisc_lat = IPDISCOVER_DEFAULT_LATENCY;

				if( forcedIpdisc.GetLength() == 0 )
					AddLog( _T( "IPDISCOVER: function required by HTTP server...\n"));
				else {
					nbr = forcedIpdisc;
					AddLog( _T( "IPDISCOVER: function forced by /ipdisc flag\n"));
				}
				
				mask=pPc->m_NetworkList.GetMaskByNetNumber(nbr);		
				CUtils::cleanCm(pM);
				ULONG   IpCur=1;
				CObArray handles;
				DWORD errcode;

				if(mask.GetLength() == 0) {
					AddLog( _T("IPDISCOVER: ERROR: No mask is available for the given network number: %s\n"),nbr);
				}
				else {
					pXml->AddElem("IPDISCOVER");
					pXml->IntoElem();
					AddLog( _T("IPDISCOVER: Scanning to detect IP enabled hosts for the given network number: %s with %i ms between each request\n"),nbr,m_ipdisc_lat);
					ULONG   ipMsk, maxIp;	
					CString csSent, csIncrIp;
					BOOL	baliseIp = FALSE;
					BOOL	fastIp = CUtils::IsRequired(cmdL, "fastip");
					DOUBLE waitedMaxThreads = 0;
					UINT maxWaitTime = CUtils::IsRequired(cmdL, "nowait") ? 60 : 3600;

					ipMsk = lpfn_htonl( lpfn_inet_addr(mask));

					m_netNumber = lpfn_ntohl(lpfn_inet_addr (nbr));
					maxIp = ~ipMsk;		
					
					m_hostFound = 0;							
					//launching threads
					do {
						//cleaning dead threads
						int thdCount=0;
						while( thdCount < handles.GetSize() ) {
							GetExitCodeThread( ((CWinThread*)handles.GetAt(thdCount))->m_hThread, &errcode );
							if( errcode != STILL_ACTIVE ) {																			
								delete (CWinThread*)handles.GetAt(thdCount);
								handles.RemoveAt(thdCount);
								thdCount--;
							}
							thdCount++;
						}

						//too many threads for too long (1 hour)
						if( waitedMaxThreads > (maxWaitTime * 1000) ) {
							AddLog("IPDISCOVER: ERROR: Waited %s seconds with max threads, skipping ipdiscover\n",maxWaitTime);
							return -1;
						}

						//too many threads ?
						if( handles.GetSize()> (fastIp?MAX_FASTIP_THREADS:MAX_THREADS)-4) {
							Sleep(1);
							waitedMaxThreads += 1;
							continue;
						}

						m_currentIp = IpCur;
						CWinThread* pT;								
						pT = AfxBeginThread((AFX_THREADPROC)threadWork, LPVOID(this), THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
						handles.Add((CObject*)pT);
						pT->m_bAutoDelete = FALSE;
						pT->ResumeThread();
						IpCur++;
						if( !fastIp )
							Sleep( m_ipdisc_lat );
					}
					while( IpCur < maxIp && IpCur <= NB_IP_MAX );
						
					UINT timeWaited = 0;
					UINT timeToWait = 60;
					UINT maxTimeToWait = 300000;
					BOOL allThreadsDead ;

					// waiting for threads to die
					do  {
						DWORD errcode;
						allThreadsDead = TRUE;
												
						int thdCount=0;
						while( thdCount < handles.GetSize() ) {								
							GetExitCodeThread( ((CWinThread*)handles.GetAt(thdCount))->m_hThread, &errcode );
							if( errcode == STILL_ACTIVE ) {
								//A thread still alive after %u msecs, waiting %u msecs more\n",  timeWaited, timeToWait);
								allThreadsDead = FALSE;
								break;
							}
							else {																		
								//A thread died after %u msecs\n",  timeWaited);
								delete (CWinThread*)handles.GetAt(thdCount);
								handles.RemoveAt(thdCount);
								thdCount--;
							}
							thdCount++;
						}
						Sleep(timeToWait);
						timeWaited += timeToWait;
					}
					while(!allThreadsDead && timeWaited < maxTimeToWait );

					//cleaning living threads
					if( timeWaited >= maxTimeToWait ) {
						for( int thdCount=0; thdCount < handles.GetSize(); thdCount++) {
							((CWinThread*)handles.GetAt(thdCount))->SuspendThread();
							delete (CWinThread*)handles.GetAt(thdCount);
							handles.RemoveAt(thdCount);
							AddLog("IPDISCOVER: ERROR: Thread still alive after %u msecs, thread killed\n",  timeWaited);
						}
					}
					else
						AddLog("IPDISCOVER: waited %u mseconds for the threads to die\n", timeWaited);
					
					AddLog( _T("IPDISCOVER: NETWORK scan finished, %u hosts found, %u scanned\n"),m_hostFound,IpCur);
					pXml->OutOfElem();
				}

				FreeLibrary( hDllIpHlpApi);
				FreeLibrary( hDllWS2);
			}
		}
	}
	else
		AddLog( _T( "IPDISCOVER: function not required by HTTP server...\n"));
	return 0;
}
