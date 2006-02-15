// Document modified at : Saturday, December 06, 2003 1:33:38 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// NetworkAdapter.cpp: implementation of the CNetworkAdapter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NetworkAdapter.h"
#include <ipifcons.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetworkAdapter::CNetworkAdapter()
{
	Clear();
}

CNetworkAdapter::~CNetworkAdapter()
{
	Clear();
}

LPCSTR CNetworkAdapter::GetNetNumber()
{
	return m_csNetNumber;
}


ULONG CNetworkAdapter::GetID()
{
	return m_ulID;
}

LPCTSTR CNetworkAdapter::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CNetworkAdapter::GetType()
{
	return m_csType;
}

LPCTSTR CNetworkAdapter::GetDescription()
{
	return m_csDescription;
}

LPCTSTR CNetworkAdapter::GetSpeed()
{
	return m_csSpeed;
}

ULONG CNetworkAdapter::GetByteSpeed()
{
	return m_ulSpeed;
}

LPCTSTR CNetworkAdapter::GetMACAddress()
{
	return m_csHWAddr;
}

LPCTSTR CNetworkAdapter::GetIPAddress()
{
	return m_csIPAddr;
}

LPCTSTR CNetworkAdapter::GetTypeMIB()
{
	return m_csTypeMIB;
}

LPCTSTR CNetworkAdapter::GetOperationalStatus()
{
	return m_csOperStatus;
}

LPCTSTR CNetworkAdapter::GetIPNetMask()
{
	return m_csIPNetMask;
}

LPCTSTR CNetworkAdapter::GetGateway()
{
	return m_csGateway;
}

LPCTSTR CNetworkAdapter::GetDhcpServer()
{
	return m_csDhcpServer;
}

LONG CNetworkAdapter::GetIfIndex()
{
	return m_lIndex;
}

BOOL CNetworkAdapter::ParseFromCSV(CString &csCSV)
{
	CString		csBuffer = csCSV,
				csTemp;
	int			nPos;

	// Read Computer ID
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read description
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csDescription = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Type
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csType = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read TypeMIB
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csTypeMIB = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Speed
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	SetSpeed( csBuffer.Left( nPos));
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read MAC Address
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csHWAddr = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Operational status
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csOperStatus = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read IP Address
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csIPAddr = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read IP Net Mask
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csIPNetMask = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read gateways
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csGateway = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read DHCP Server
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csDhcpServer = csBuffer.Left( nPos);
	return TRUE;
}

void CNetworkAdapter::SetNetNumber( LPCSTR nbr )
{
	m_csNetNumber = nbr;
	StrForSQL( m_csNetNumber);
}

void CNetworkAdapter::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CNetworkAdapter::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CNetworkAdapter::SetDescription( LPCTSTR lpstrDescription)
{
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

void CNetworkAdapter::SetType( LPCTSTR lpstrType)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
}

void CNetworkAdapter::SetTypeMIB( LPCTSTR lpstrMIBType)
{
	m_csTypeMIB = lpstrMIBType;
	StrForSQL( m_csTypeMIB);
}

void CNetworkAdapter::SetSpeed( LPCTSTR lpstrSpeed)
{
	CString csBuffer = lpstrSpeed;

	m_csSpeed = lpstrSpeed;
	StrForSQL( m_csSpeed);
	// Recalculate byte speed
	if (csBuffer.Find( _T( " Gb/s")) >= 0)
	{
		csBuffer.TrimRight( _T( " Gb/s"));
		m_ulSpeed = _tcstoul( csBuffer, NULL, 10) * 1000000000;
		return;
	}
	if (csBuffer.Find( _T( " Mb/s")) >= 0)
	{
		csBuffer.TrimRight( _T( " Mb/s"));
		m_ulSpeed = _tcstoul( csBuffer, NULL, 10) * 1000000;
		return;
	}
	if (csBuffer.Find( _T( " Kb/s")) >= 0)
	{
		csBuffer.TrimRight( _T( " Kb/s"));
		m_ulSpeed = _tcstoul( csBuffer, NULL, 10) * 1000;
		return;
	}
	csBuffer.TrimRight( _T( " b/s"));
	m_ulSpeed = _tcstoul( csBuffer, NULL, 10);
}

void CNetworkAdapter::SetSpeed( ULONG lSpeed)
{
	m_ulSpeed = lSpeed;
	
	if (lSpeed >= 1000000000)
		m_csSpeed.Format( _T( "%lu Gb/s"), lSpeed / 1000000000);
	else
	{
		if (lSpeed >= 1000000)
			m_csSpeed.Format( _T( "%lu Mb/s"), lSpeed / 1000000);
		else
		{
			if (lSpeed >= 1000)
				m_csSpeed.Format( _T( "%lu Kb/s"), lSpeed / 1000);
			else
				m_csSpeed.Format( _T( "%lu b/s"), lSpeed);
		}
	}

}

void CNetworkAdapter::SetMACAddress( LPCTSTR lpstrMAC)
{
	m_csHWAddr = lpstrMAC;
	StrForSQL( m_csHWAddr);
}

void CNetworkAdapter::SetStatus( LPCTSTR lpstrStatus)
{
	m_csOperStatus = lpstrStatus;
	StrForSQL( m_csOperStatus);
}

void CNetworkAdapter::SetStatus( LONG lOperStatus)
{
	switch (lOperStatus)
	{
	case 1: // Up
		m_csOperStatus = _T( "Up");
		break;
	case 2: // Down
		m_csOperStatus = _T( "Down");
		break;
	case 3: // Testing
		m_csOperStatus = _T( "Testing");
		break;
	default: // Unknown
		m_csOperStatus = _T( "N/A");
		break;
	}
}

void CNetworkAdapter::SetIpHelperStatus( LONG lOperStatus)
{
	switch (lOperStatus)
	{
	case MIB_IF_OPER_STATUS_NON_OPERATIONAL:
	case MIB_IF_OPER_STATUS_UNREACHABLE:
	case MIB_IF_OPER_STATUS_DISCONNECTED:
		m_csOperStatus = _T( "Down");
		break;
	case MIB_IF_OPER_STATUS_CONNECTING:
		m_csOperStatus = _T( "Testing");
		break;
	case MIB_IF_OPER_STATUS_CONNECTED:
	case MIB_IF_OPER_STATUS_OPERATIONAL:
		m_csOperStatus = _T( "Up");
		break;
	default: // Unknown
		m_csOperStatus = _T( "N/A");
		break;
	}
}

void CNetworkAdapter::SetIPAddress( LPCTSTR lpstrIP)
{
	m_csIPAddr = lpstrIP;
	StrForSQL( m_csIPAddr);
}

void CNetworkAdapter::SetIPNetMask( LPCTSTR lpstrNetMask)
{
	m_csIPNetMask = lpstrNetMask;
	StrForSQL( m_csIPNetMask);
}

void CNetworkAdapter::SetGateway( LPCTSTR lpstrGateway)
{
	m_csGateway = lpstrGateway;
	StrForSQL( m_csGateway);
}

void CNetworkAdapter::SetDhcpServer( LPCTSTR lpstrDhcpServer)
{
	m_csDhcpServer = lpstrDhcpServer;
	StrForSQL( m_csDhcpServer);
}

void CNetworkAdapter::SetIfIndex( LONG lIndex)
{
	m_lIndex = lIndex;
}

BOOL CNetworkAdapter::FormatXML(CMarkup* pX)
{
	pX->AddElem("NETWORKS");
	pX->IntoElem();
		pX->AddElemNV("DESCRIPTION",m_csDescription);
		pX->AddElemNV("TYPE",m_csType);
		pX->AddElemNV("TYPEMIB",m_csTypeMIB);
		pX->AddElemNV("SPEED",m_csSpeed);
		pX->AddElemNV("MACADDR",m_csHWAddr);
		pX->AddElemNV("STATUS",m_csOperStatus);
		pX->AddElemNV("IPADDRESS",m_csIPAddr);
		pX->AddElemNV("IPMASK",m_csIPNetMask);
		pX->AddElemNV("IPGATEWAY",m_csGateway);
		pX->AddElemNV("IPSUBNET",m_csNetNumber);
		pX->AddElemNV("IPDHCP",m_csDhcpServer);
	pX->OutOfElem();		
	return TRUE;
}

void CNetworkAdapter::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CNetworkAdapter::GetDeviceName()
{
	return m_csDeviceName;
}

void CNetworkAdapter::Clear()
{
	m_ulID = 0;			
	m_csNetNumber.Empty();
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_lIndex = -1;		
	m_csDescription.Empty();
	m_csType.Empty();		
	m_csTypeMIB.Empty();	
	m_csSpeed.Empty();		
	m_ulSpeed = 0;		
	m_csHWAddr.Empty();		
	m_csOperStatus.Empty();	
	m_csIPAddr.Empty();		
	m_csIPNetMask.Empty();	
	m_csGateway.Empty();	
	m_csDhcpServer.Empty();	
}
