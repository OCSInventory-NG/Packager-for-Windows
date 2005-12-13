// Document modified at : Sunday, January 04, 2004 7:31:44 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SystemController.cpp: implementation of the CSystemController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemController.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemController::CSystemController()
{
	Clear();
}

CSystemController::~CSystemController()
{
	Clear();
}

ULONG CSystemController::GetID()
{
	return m_ulID;
}

LPCTSTR CSystemController::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CSystemController::GetManufacturer()
{
	return m_csManufacturer;
}

LPCTSTR CSystemController::GetType()
{
	return m_csType;
}

LPCTSTR CSystemController::GetName()
{
	return m_csName;
}

LPCTSTR CSystemController::GetHardwareVersion()
{
	return m_csHardwareVersion;
}

LPCTSTR CSystemController::GetCaption()
{
	return m_csCaption;
}

LPCTSTR CSystemController::GetDescription()
{
	return m_csDescription;
}

void CSystemController::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CSystemController::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CSystemController::SetManufacturer(LPCTSTR lpstrManufacturer)
{
	m_csManufacturer = lpstrManufacturer;
	StrForSQL( m_csManufacturer);
}

void CSystemController::SetType(LPCTSTR lpstrType)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
}

void CSystemController::SetHardwareVersion(LPCTSTR lpstrVersion)
{
	m_csHardwareVersion = lpstrVersion;
	StrForSQL( m_csHardwareVersion);
}

void CSystemController::SetName(LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void CSystemController::SetCaption(LPCTSTR lpstrCaption)
{
	m_csCaption = lpstrCaption;
	StrForSQL( m_csCaption);
}

void CSystemController::SetDescription(LPCTSTR lpstrDescription)
{
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

void CSystemController::Set( LPCTSTR lpstrType, LPCTSTR lpstrManufacturer, LPCTSTR lpstrName, LPCTSTR lpstrVersion, LPCTSTR lpstrCaption, LPCTSTR lpstrDescription)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
	m_csManufacturer = lpstrManufacturer;
	StrForSQL( m_csManufacturer);
	m_csName = lpstrName;
	StrForSQL( m_csName);
	m_csHardwareVersion = lpstrVersion;
	StrForSQL( m_csHardwareVersion);
	m_csCaption = lpstrCaption;
	StrForSQL( m_csCaption);
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

BOOL CSystemController::FormatXML(CMarkup* pX)
{
	pX->AddElem("CONTROLLERS");
	pX->IntoElem();
		pX->AddElemNV("MANUFACTURER",m_csManufacturer);
		pX->AddElemNV("NAME",m_csName);
		pX->AddElemNV("CAPTION",m_csCaption);
		pX->AddElemNV("DESCRIPTION",m_csDescription);
		pX->AddElemNV("VERSION",m_csHardwareVersion);
		pX->AddElemNV("TYPE",m_csType);
	pX->OutOfElem();
	return TRUE;
}

BOOL CSystemController::ParseFromCSV(CString &csCSV)
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
	// Read Caption
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csCaption = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Hardware Version
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csHardwareVersion = csBuffer.Left( nPos);
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

void CSystemController::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CSystemController::GetDeviceName()
{
	return m_csDeviceName;
}

void CSystemController::Clear()
{
	m_ulID = 0;				
	m_csDeviceID.Empty();		
	m_csDeviceName.Empty();		
	m_csType.Empty();			
	m_csManufacturer.Empty();	
	m_csName.Empty();			
	m_csHardwareVersion.Empty();
	m_csCaption.Empty();		
	m_csDescription.Empty();	
}
