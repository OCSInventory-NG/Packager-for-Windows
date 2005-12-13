// Document modified at : Saturday, January 03, 2004 11:32:46 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// NetworkAdapter.h: interface for the CNetworkAdapter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKADAPTER_H__E2E36333_7E8A_11D5_B270_0040055338AF__INCLUDED_)
#define AFX_NETWORKADAPTER_H__E2E36333_7E8A_11D5_B270_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CNetworkAdapter  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CNetworkAdapter();
	virtual ~CNetworkAdapter();

	void Clear();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////
	LPCTSTR GetNetNumber();
	// Return the database record ID
	ULONG GetID();
	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Return a string with the device NetBIOS name
	LPCTSTR GetDeviceName();
	// Return the adapter index in the MIB
	LONG GetIfIndex();
	// Return the adapter description in the MIB
	LPCTSTR GetDescription();
	// Return the adapter common type
	LPCTSTR GetType();
	// Return the adapter type in the MIB
	LPCTSTR GetTypeMIB();
	// Return the adapter speed in the MIB in byte/s
	ULONG GetByteSpeed();
	// Return the adapter speed in the MIB in string format
	LPCTSTR GetSpeed();
	// Return the adapter MAC address in the MIB
	LPCTSTR GetMACAddress();
	// Return the adapter status in the MIB
	LPCTSTR GetOperationalStatus();
	// Return the adapter IP Address in the MIB
	LPCTSTR GetIPAddress();
	// Return the adapter IP Netmask in the MIB
	LPCTSTR GetIPNetMask();
	// Return the adapter IP Gateway
	LPCTSTR GetGateway();
	// Return the adapter IP DCHP Server
	LPCTSTR GetDhcpServer();
	// Format informations in a XML string
	BOOL FormatXML( CMarkup* pX );

	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////

	void SetNetNumber( LPCSTR nbr);
	void SetID( ULONG ulID);
	// Set the device unique ID
	void SetDeviceID( LPCTSTR lpstrDeviceID);
	// Set the device NetBIOS name
	void SetDeviceName( LPCTSTR lpstrName);
	void SetIfIndex( LONG lIndex);
	void SetDescription( LPCTSTR lpstrDescription);
	void SetType( LPCTSTR lpstrType);
	void SetTypeMIB( LPCTSTR lpstrMIBType);
	void SetSpeed( ULONG lSpeed);
	void SetSpeed( LPCTSTR lpstrSpeed);
	void SetMACAddress( LPCTSTR lpstrMAC);
	void SetStatus( LPCTSTR lpstrStatus);
	void SetStatus( LONG lOperStatus);
	void SetIpHelperStatus( LONG lOperStatus);
	void SetIPAddress( LPCTSTR lpstrIP);
	void SetIPNetMask( LPCTSTR lpstrNetMask);
	void SetGateway( LPCTSTR lpstrGateway);
	void SetDhcpServer( LPCTSTR lpstrDhcpServer);
	// Retrieve the informations from a CSV buffer
	BOOL ParseFromCSV( CString &csCSV);

protected: // Attributes
	CString	m_csNetNumber;
	ULONG	m_ulID;				// Database record ID
	CString	m_csDeviceID;		// Device unique ID
	CString	m_csDeviceName;		// Device netbios or DNS name
	LONG	m_lIndex;			// Network Adapter index in the MIB
	CString	m_csDescription;	// Network Adapter description
	CString	m_csType;			// Network Adapter type (Ethernet, Token Ring, RNIS, modem...)
	CString	m_csTypeMIB;		// Network Adapter type extracted from MIB
	CString	m_csSpeed;			// Network Adapter speed in string format
	ULONG   m_ulSpeed;			// Network Adapter speed in bit/s
	CString	m_csHWAddr;			// Network Adapter MAC address
	CString	m_csOperStatus;		// Network Adapter operational status (up, down, testing)
	CString	m_csIPAddr;			// Network Adapter IP Address if available (ex "192.3.4.1" or "Unavailable")
	CString	m_csIPNetMask;		// Network Adapter IP Net Mask if available (ex "255.255.255.0" or "Unavailable")
	CString	m_csGateway;		// Network Adapter Gateways if available (ex "192.3.4.1" or "Unavailable")
	CString m_csDhcpServer;		// Network Adapter DHCP server used if available (ex "192.3.4.1" or "Unavailable")
};

#endif // !defined(AFX_NETWORKADAPTER_H__E2E36333_7E8A_11D5_B270_0040055338AF__INCLUDED_)
