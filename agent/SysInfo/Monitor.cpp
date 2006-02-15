// Document modified at : Saturday, December 06, 2003 1:43:12 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// Monitor.cpp: implementation of the CMonitor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Monitor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonitor::CMonitor()
{

}

CMonitor::~CMonitor()
{

}

ULONG CMonitor::GetID()
{
	return m_ulID;
}

LPCTSTR CMonitor::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CMonitor::GetManufacturer()
{
	return m_csManufacturer;
}

LPCTSTR CMonitor::GetType()
{
	return m_csType;
}

LPCTSTR CMonitor::GetCaption()
{
	return m_csCaption;
}

LPCTSTR CMonitor::GetDescription()
{
	return m_csDescription;
}

LPCTSTR CMonitor::GetSerial()
{
	return m_csSerial;
}

void CMonitor::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CMonitor::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CMonitor::SetManufacturer(LPCTSTR lpstrManufacturer)
{
	m_csManufacturer = lpstrManufacturer;
	StrForSQL( m_csManufacturer);
}

void CMonitor::SetType(LPCTSTR lpstrType)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
}

void CMonitor::SetCaption(LPCTSTR lpstrCaption)
{
	m_csCaption = lpstrCaption;
	StrForSQL( m_csCaption);
}

void CMonitor::SetDescription(LPCTSTR lpstrDescription)
{
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

void CMonitor::SetSerial(LPCTSTR lpstrSerial)
{
	m_csSerial = lpstrSerial;
	StrForSQL( m_csSerial);
}

void CMonitor::Set( LPCTSTR lpstrManufacturer, LPCTSTR lpstrType, LPCTSTR lpstrCaption, LPCTSTR lpstrDescription, LPCSTR lpstrSerial)
{
	m_csManufacturer = lpstrManufacturer;
	StrForSQL( m_csManufacturer);
	m_csType = lpstrType;
	StrForSQL( m_csType);
	m_csCaption = lpstrCaption;
	StrForSQL( m_csCaption);
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
	m_csSerial = lpstrSerial;
	StrForSQL( m_csSerial);
}

BOOL CMonitor::FormatXML(CMarkup* pX)
{
	pX->AddElem("MONITORS");
	pX->IntoElem();
		pX->AddElemNV("MANUFACTURER",m_csManufacturer);
		pX->AddElemNV("CAPTION",m_csCaption);
		pX->AddElemNV("DESCRIPTION",m_csDescription);
		pX->AddElemNV("TYPE",m_csType);
		pX->AddElemNV("SERIAL",m_csSerial);
	pX->OutOfElem();
	return TRUE;
}

BOOL CMonitor::ParseFromCSV(CString &csCSV)
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
	// Read Caption
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csCaption = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Description
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csDescription = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read type
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csType = csBuffer.Left( nPos);
	return TRUE;
}

void CMonitor::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CMonitor::GetDeviceName()
{
	return m_csDeviceName;
}

void CMonitor::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csManufacturer.Empty();
	m_csType.Empty();		
	m_csCaption.Empty();	
	m_csDescription.Empty();
	m_csSerial.Empty();
}
