// Document modified at : Saturday, December 06, 2003 1:45:12 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SoundDevice.cpp: implementation of the CSoundDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoundDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSoundDevice::CSoundDevice()
{
	Clear();
}

CSoundDevice::~CSoundDevice()
{
	Clear();
}

ULONG CSoundDevice::GetID()
{
	return m_ulID;
}

LPCTSTR CSoundDevice::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CSoundDevice::GetManufacturer()
{
	return m_csManufacturer;
}

LPCTSTR CSoundDevice::GetName()
{
	return m_csName;
}

LPCTSTR CSoundDevice::GetDescription()
{
	return m_csDescription;
}

void CSoundDevice::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CSoundDevice::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CSoundDevice::SetManufacturer(LPCTSTR lpstrManufacturer)
{
	m_csManufacturer = lpstrManufacturer;
	StrForSQL( m_csManufacturer);
}

void CSoundDevice::SetName(LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void CSoundDevice::SetDescription(LPCTSTR lpstrDescription)
{
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

void CSoundDevice::Set( LPCTSTR lpstrManufacturer, LPCTSTR lpstrName, LPCTSTR lpstrDescription)
{
	m_csManufacturer = lpstrManufacturer;
	StrForSQL( m_csManufacturer);
	m_csName = lpstrName;
	StrForSQL( m_csName);
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

BOOL CSoundDevice::FormatXML(CMarkup* pX)
{
	pX->AddElem("SOUNDS");
	pX->IntoElem();
		pX->AddElemNV("MANUFACTURER",m_csManufacturer);
		pX->AddElemNV("NAME",m_csName);
		pX->AddElemNV("DESCRIPTION",m_csDescription);
	pX->OutOfElem();
	return TRUE;
}

BOOL CSoundDevice::ParseFromCSV(CString &csCSV)
{
	CString		csBuffer = csCSV,
				csTemp;
	int			nPos;

	// Read Computer ID
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Manufacturer
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csManufacturer = csBuffer.Left( nPos);
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
	return TRUE;
}

void CSoundDevice::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CSoundDevice::GetDeviceName()
{
	return m_csDeviceName;
}

void CSoundDevice::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csManufacturer.Empty();
	m_csName.Empty();		
	m_csDescription.Empty();
}
