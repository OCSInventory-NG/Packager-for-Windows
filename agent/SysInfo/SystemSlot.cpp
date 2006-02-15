// Document modified at : Monday, December 29, 2003 10:25:16 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SystemSlot.cpp: implementation of the CSystemSlot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemSlot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemSlot::CSystemSlot()
{
	Clear();
}

CSystemSlot::~CSystemSlot()
{
	Clear();
}

ULONG CSystemSlot::GetID()
{
	return m_ulID;
}

LPCTSTR CSystemSlot::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CSystemSlot::GetName()
{
	return m_csName;
}

LPCTSTR CSystemSlot::GetDescription()
{
	return m_csDescription;
}

LPCTSTR CSystemSlot::GetSlotDesignation()
{
	return m_csDesignation;
}

LPCTSTR CSystemSlot::GetUsage()
{
	return m_csUsage;
}

LPCTSTR CSystemSlot::GetStatus()
{
	return m_csStatus;
}

BOOL CSystemSlot::IsShared()
{
	return m_bShared;
}

void CSystemSlot::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CSystemSlot::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CSystemSlot::SetName(LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void CSystemSlot::SetDescription(LPCTSTR lpstrDescription)
{
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

void CSystemSlot::SetSlotDesignation(LPCTSTR lpstrDesignation)
{
	m_csDesignation = lpstrDesignation;
	StrForSQL( m_csDesignation);
}

void CSystemSlot::SetUsage(DWORD dwUsage)
{
	switch (dwUsage)
	{
	case SYSTEMSLOT_USAGE_RESERVED:
		m_csUsage = _T( "Reserved");
		break;
	case SYSTEMSLOT_USAGE_OTHER:
		m_csUsage = _T( "Other");
		break;
	case SYSTEMSLOT_USAGE_AVAILABLE:
		m_csUsage = _T( "Available");
		break;
	case SYSTEMSLOT_USAGE_INUSE:
		m_csUsage = _T( "In Use");
		break;
	case SYSTEMSLOT_USAGE_UNKNWOWN:
		m_csUsage = _T( "Unknown");
		break;
	default:
		m_csUsage.Format( _T( "%s (%lu)"), NOT_AVAILABLE, dwUsage);
		break;
	}
}

void CSystemSlot::SetUsage(LPCTSTR lpstrUsage)
{
	m_csUsage = lpstrUsage;
	StrForSQL( m_csUsage);
}

void CSystemSlot::SetStatus(LPCTSTR lpstrStatus)
{
	m_csStatus = lpstrStatus;
	StrForSQL( m_csStatus);
}

void CSystemSlot::SetShared( BOOL bShared)
{
	m_bShared = bShared;
}

void CSystemSlot::Set( LPCTSTR lpstrName, LPCTSTR lpstrDescription, LPCTSTR lpstrDesignation, LPCTSTR lpstrUsage, LPCTSTR lpstrStatus, BOOL bShared)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
	m_csDesignation = lpstrDesignation;
	StrForSQL( m_csDesignation);
	m_csUsage = lpstrUsage;
	StrForSQL( m_csUsage);
	m_csStatus = lpstrStatus;
	StrForSQL( m_csStatus);
	m_bShared = bShared;
}

BOOL CSystemSlot::FormatXML(CMarkup* pX)
{
	pX->AddElem("SLOTS");
	pX->IntoElem();
		pX->AddElemNV("NAME",m_csName);
		pX->AddElemNV("DESCRIPTION",m_csDescription);
		pX->AddElemNV("DESIGNATION",m_csDesignation);
		pX->AddElemNV("PURPOSE",m_csUsage);
		pX->AddElemNV("STATUS",m_csStatus);
		pX->AddElemNV("SHARED",m_bShared? 1 : 0);
	pX->OutOfElem();
	return TRUE;
}

BOOL CSystemSlot::ParseFromCSV(CString &csCSV)
{
	CString		csBuffer = csCSV,
				csTemp;
	int			nPos;

	// Read Computer ID
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Name
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csName = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Description
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csDescription = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Slot Designation
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csDesignation = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Usage
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csUsage = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Status
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csStatus = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read shared
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_bShared = _tcstoul( csBuffer.Left( nPos), NULL, 10);
	return TRUE;
}

void CSystemSlot::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CSystemSlot::GetDeviceName()
{
	return m_csDeviceName;
}

void CSystemSlot::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csName.Empty();		
	m_csDescription.Empty();
	m_csDesignation.Empty();
	m_csUsage.Empty();		
	m_csStatus.Empty();		
	m_bShared = FALSE;		
}
