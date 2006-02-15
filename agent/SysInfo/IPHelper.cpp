// Document modified at : Tuesday, November 25, 2003 1:40:04 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
// IPHelper.cpp: implementation of the CIPHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NetworkAdapter.h"
#include "NetworkAdapterList.h"
#include "debuglog.h"
#include "IPHelper.h"
#include <Snmp.h>
#include "snmpapi.h"
#include <iphlpapi.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIPHelper::CIPHelper()
{

}

CIPHelper::~CIPHelper()
{

}

BOOL CIPHelper::GetNetworkAdapters(CNetworkAdapterList *pList)
{
    HINSTANCE			hDll;
	DWORD				(WINAPI *lpfnGetAdaptersInfo)( PIP_ADAPTER_INFO myInfo, ULONG *pLength);
	DWORD				(WINAPI *lpfnGetIfTable)( PMIB_IFTABLE pIfTable, PULONG pdwSize, BOOL bOrder);
	PMIB_IFTABLE		pIfTable;
	PMIB_IFROW			pIfEntry;
	PIP_ADAPTER_INFO	pAdapterInfo;
	ULONG				ulLength = 0;
	LPBYTE				pData = NULL;
	UINT				uIndex = 0;
	DWORD				dwIndex;
	CNetworkAdapter		cAdapter;
	PIP_ADDR_STRING		pAddressList;
	CString				csMAC,
						csAddress,
						csNetMask,
						csGateway,
						csDhcpServer;

	AddLog( _T( "IpHlpAPI GetNetworkAdapters...\n"));
	// Reset network adapter list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
    // Load the IpHlpAPI dll and get the addresses of necessary functions
    if ((hDll = LoadLibrary(_T( "iphlpapi.dll"))) < (HINSTANCE) HINSTANCE_ERROR) 
	{
		// Cannot load IpHlpAPI MIB
 		AddLog( _T( "IpHlpAPI GetNetworkAdapters: Failed because unable to load <iphlpapi.dll> !\n"));
		hDll = NULL;
        return FALSE;
    }
	if ((*(FARPROC*)&lpfnGetIfTable = GetProcAddress( hDll, _T( "GetIfTable"))) == NULL)
	{
		// Tell the user that we could not find a usable IpHlpAPI DLL.                                  
		FreeLibrary( hDll);
		AddLog( _T( "IpHlpAPI GetNetworkAdapters: Failed because unable to load <iphlpapi.dll> !\n"));
		return FALSE;
	}
	if ((*(FARPROC*)&lpfnGetAdaptersInfo = GetProcAddress( hDll, _T( "GetAdaptersInfo"))) == NULL)
	{
		// Tell the user that we could not find a usable IpHlpAPI DLL.                                  
		FreeLibrary( hDll);
		AddLog( _T( "IpHlpAPI GetNetworkAdapters: Failed because unable to load <iphlpapi.dll> !\n"));
		return FALSE;
	}
	// Call GetIfTable to get memory size
	AddLog( _T( "IpHlpAPI GetNetworkAdapters: Calling GetIfTable to determine network adapter properties..."));
	pIfTable = NULL;
	ulLength = 0;
	switch( lpfnGetIfTable( pIfTable, &ulLength, TRUE))
	{
	case NO_ERROR: // No error => no adapters
		FreeLibrary( hDll);
		AddLog( _T( "Failed because no network adapters !\n"));
		return FALSE;
	case ERROR_NOT_SUPPORTED: // Not supported
		FreeLibrary( hDll);
		AddLog( _T( "Failed because OS not support GetIfTable API function !\n" ));
		return FALSE;
	case ERROR_BUFFER_OVERFLOW: // We must allocate memory
	case ERROR_INSUFFICIENT_BUFFER:
		break;
	default:
		FreeLibrary( hDll);
		AddLog( _T( "Failed because unknown error !\n" ));
		return FALSE;
	}
	if ((pData = (LPBYTE) malloc( ulLength+1)) == NULL)
	{
		FreeLibrary( hDll);
		AddLog( _T( "Failed because memory error !\n" ));
		return FALSE;
	}
	// Recall GetIfTable
	pIfTable = (PMIB_IFTABLE) pData;
	switch( lpfnGetIfTable( pIfTable, &ulLength, TRUE))
	{
	case NO_ERROR: // No error
		break;
	case ERROR_NOT_SUPPORTED: // Not supported
		free( pData);
		FreeLibrary( hDll);
		AddLog( _T( "Failed because OS not support GetIfTable API function !\n" ));
		return FALSE;
	case ERROR_BUFFER_OVERFLOW: // We have allocated needed memory, but not sufficient
	case ERROR_INSUFFICIENT_BUFFER:
		free( pData);
		FreeLibrary( hDll);
		AddLog( _T( "Failed because memory error !\n" ));
		return FALSE;
	default:
		free( pData);
		FreeLibrary( hDll);
		AddLog( _T( "Failed because unknown error !\n" ));
		return FALSE;
	}
	// Call GetIfEntry for each interface
	for (dwIndex = 0; dwIndex < pIfTable->dwNumEntries; dwIndex ++)
	{
		pIfEntry = &(pIfTable->table[dwIndex]);
		// Get the Index
		cAdapter.SetIfIndex( pIfEntry->dwIndex);
		// Get the type
		cAdapter.SetType( GetAdapterType( pIfEntry->dwType));
		// Get the MIB type
		cAdapter.SetTypeMIB( GetIfType( pIfEntry->dwType));
		// Get the description
		_tcsncpy( csAddress.GetBuffer( pIfEntry->dwDescrLen), (LPCTSTR) pIfEntry->bDescr,
										(size_t) pIfEntry->dwDescrLen);
		csAddress.ReleaseBuffer( (int) pIfEntry->dwDescrLen);
		cAdapter.SetDescription( csAddress);
		// Get MAC Address 
		csMAC.Format( _T("%02X:%02X:%02X:%02X:%02X:%02X"),
					   pIfEntry->bPhysAddr[0], pIfEntry->bPhysAddr[1],
					   pIfEntry->bPhysAddr[2], pIfEntry->bPhysAddr[3],
					   pIfEntry->bPhysAddr[4], pIfEntry->bPhysAddr[5]);
		cAdapter.SetMACAddress( csMAC);
		// Get the Speed
		cAdapter.SetSpeed( pIfEntry->dwSpeed);
		// Get the status
		cAdapter.SetIpHelperStatus( pIfEntry->dwOperStatus);
		cAdapter.SetIPAddress(  _T(""));
		cAdapter.SetIPNetMask(  _T(""));
		cAdapter.SetGateway(  _T(""));
		cAdapter.SetDhcpServer(  _T(""));
			
		if (!IsLoopback( pIfEntry->dwType))
		{
			uIndex ++;
			pList->AddTail( cAdapter);
		}
	}
	free( pData);
	// Call GetAdptersInfo with length to 0 to get size of required buffer
	AddLog( _T( "OK\nIpHlpAPI GetNetworkAdapters: Calling GetAdapterInfo to determine IP Infos..."));
	pAdapterInfo = NULL;
	switch( lpfnGetAdaptersInfo( pAdapterInfo, &ulLength))
	{
	case NO_ERROR: // No error => no adapters
	case ERROR_NO_DATA:
		FreeLibrary( hDll);
		AddLog( _T( "Failed because no network adapters !\n"));
		return FALSE;
	case ERROR_NOT_SUPPORTED: // Not supported
		FreeLibrary( hDll);
		AddLog( _T( "Failed because OS not support GetAdaptersInfo API function !\n" ));
		return FALSE;
	case ERROR_BUFFER_OVERFLOW: // We must allocate memory
		break;
	default:
		FreeLibrary( hDll);
		AddLog( _T( "Failed because unknown error !\n" ));
		return FALSE;
	}
	if ((pData = (LPBYTE) malloc( ulLength+1)) == NULL)
	{
		FreeLibrary( hDll);
		AddLog( _T( "Failed because memory error !\n" ));
		return FALSE;
	}
	// Recall GetAdptersInfo
	pAdapterInfo = (PIP_ADAPTER_INFO) pData;
	switch( lpfnGetAdaptersInfo( pAdapterInfo, &ulLength))
	{
	case 0: // No error
		break;
	case ERROR_NO_DATA: // No adapters
		free( pData);
		FreeLibrary( hDll);
		AddLog( _T( "Failed because no network adapters !\n"));
		return FALSE;
	case ERROR_NOT_SUPPORTED: // Not supported
		free( pData);
		FreeLibrary( hDll);
		AddLog( _T( "Failed because OS not support GetAdaptersInfo API function !\n" ));
		return FALSE;
	case ERROR_BUFFER_OVERFLOW: // We have allocated needed memory, but not sufficient
		free( pData);
		FreeLibrary( hDll);
		AddLog( _T( "Failed because memory error !\n" ));
		return FALSE;
	default:
		free( pData);
		FreeLibrary( hDll);
		AddLog( _T( "Failed because unknown error !\n" ));
		return FALSE;
	}
	// Unload library
	FreeLibrary( hDll);
	// Now parse the infos
	while (pAdapterInfo != NULL)
	{
		// Get MAC Address 
		csMAC.Format( _T("%02X:%02X:%02X:%02X:%02X:%02X"),
					   pAdapterInfo->Address[0], pAdapterInfo->Address[1],
					   pAdapterInfo->Address[2], pAdapterInfo->Address[3],
					   pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
		// Get IP addresses and NetMasks
		pAddressList = &(pAdapterInfo->IpAddressList);
		csAddress = _T("");
		csNetMask = _T("");
		do
		{
			csAddress += pAddressList->IpAddress.String;
			csNetMask += pAddressList->IpMask.String;
			pAddressList = pAddressList->Next;
			if( pAddressList != NULL )
			{
				csAddress += _T( ",");
				csNetMask += _T( ",");
			}
		}
		while( pAddressList != NULL );
		// Get Gateways
		pAddressList = &(pAdapterInfo->GatewayList);
		csGateway = _T("");
		do
		{
			csGateway += pAddressList->IpAddress.String;
			pAddressList = pAddressList->Next;
			if( pAddressList != NULL )
				csGateway += _T( ",");
		}
		while( pAddressList != NULL );
		// Get DHCP server
		pAddressList = &(pAdapterInfo->DhcpServer);
		csDhcpServer = _T("");
		do
		{
			csDhcpServer += pAddressList->IpAddress.String;
			pAddressList = pAddressList->Next;
			if( pAddressList != NULL )
				csDhcpServer += _T( ",");
		}
		while( pAddressList != NULL );

		// Update network number
		in_addr ipa;
		ULONG   ipAdr, ipMsk, nbRez;		
			
		ipAdr = ntohl(inet_addr ( csAddress ));
		ipMsk = ntohl(inet_addr ( csNetMask ));
		nbRez = ipAdr & ipMsk ;

		ipa.S_un.S_addr = htonl(nbRez);
		LPCSTR csRez = inet_ntoa(ipa);
		//

		// Update adapter in the list
		pList->SetIpAddrEntry( csMAC, csAddress, csNetMask, csGateway, csDhcpServer,csRez);
		pAdapterInfo = pAdapterInfo->Next;
	}
	// Free memory
	free( pData);
	AddLog( _T( "OK\n"));
	if (uIndex > 0)
	{
		AddLog( _T( "IpHlpAPI GetNetworkAdapters: OK (%u objects).\n"), uIndex);
		return TRUE;
	}
	AddLog( _T( "IpHlpAPI GetNetworkAdapters: Failed because no network adapter object !\n"));
	return FALSE;
}
