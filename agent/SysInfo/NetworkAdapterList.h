// Document modified at : Tuesday, March 28, 2006 7:54:32 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// NetworkAdapterList.h: interface for the CNetworkAdapterList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKADAPTERLIST_H__DE761F11_8847_11D5_B278_0040055338AF__INCLUDED_)
#define AFX_NETWORKADAPTERLIST_H__DE761F11_8847_11D5_B278_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"
#include <Winsock2.h>
#include <iphlpapi.h>

class DLL_CLASS CNetworkAdapterList : public CList<CNetworkAdapter, CNetworkAdapter&> 
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CNetworkAdapterList();
	virtual ~CNetworkAdapterList();

	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////
	CString GetMaskByGateway(CString gtw);
	CString GetIpByGateway(CString gtw);
	CString GetMaskByNetNumber(CString nbr);

	// Set the IP address and net mask for the adapter lIfIndex in the list
	BOOL SetIpAddrEntry( LONG lIfIndex, LPCTSTR lpstrIPAddr, LPCTSTR lpstrIPNetMask, LPCSTR lpstrNetNumber);
	// Didier LIROULET 2005-10-17 BEGIN
	// Set the gateway for the adapter lIfIndex in the list
	BOOL SetIpRouteEntry( LONG lIfIndex, LPCTSTR lpstrGateway);
	// Didier LIROULET 2005-10-17 END
	// Set the adapter infos IP @, net mask, gateways and DCHP server by the adapter MAC @ in the list
	BOOL SetIpAddrEntry(LPCTSTR lpstrMAC, LPCTSTR lpstrIPAddr, LPCTSTR lpstrIPNetMask, LPCTSTR lpstrGateway, LPCTSTR lpstrDhcpServer, LPCSTR lpstrNetNumber);
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
};
#endif // !defined(AFX_NETWORKADAPTERLIST_H__DE761F11_8847_11D5_B278_0040055338AF__INCLUDED_)

