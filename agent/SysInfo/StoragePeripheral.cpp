// Document modified at : Saturday, December 06, 2003 1:47:18 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// StoragePeripheral.cpp: implementation of the CStoragePeripheral class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StoragePeripheral.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStoragePeripheral::CStoragePeripheral()
{
	Clear();
}

CStoragePeripheral::~CStoragePeripheral()
{
	Clear();
}

ULONG CStoragePeripheral::GetID()
{
	return m_ulID;
}

LPCTSTR CStoragePeripheral::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CStoragePeripheral::GetManufacturer()
{
	return m_csManufacturer;
}

LPCTSTR CStoragePeripheral::GetType()
{
	return m_csType;
}

LPCTSTR CStoragePeripheral::GetModel()
{
	return m_csModel;
}

LPCTSTR CStoragePeripheral::GetDescription()
{
	return m_csDescription;
}

LPCTSTR CStoragePeripheral::GetName()
{
	return m_csName;
}

unsigned __int64 CStoragePeripheral::GetSize()
{
	return m_u64Size;
}

LPCTSTR CStoragePeripheral::GetSizeString()
{
	static CString csBuffer;

	if (m_u64Size > 0)
		csBuffer.Format( _T( "%I64u MB"), m_u64Size);
	else
		csBuffer.Empty();
	return csBuffer;
}

void CStoragePeripheral::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CStoragePeripheral::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CStoragePeripheral::SetManufacturer(LPCTSTR lpstrManufacturer)
{
	m_csManufacturer = lpstrManufacturer;
	StrForSQL( m_csManufacturer);
}

void CStoragePeripheral::SetType(LPCTSTR lpstrType)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
}

void CStoragePeripheral::SetName(LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void CStoragePeripheral::SetModel(LPCTSTR lpstrModel)
{
	m_csModel = lpstrModel;
	StrForSQL( m_csModel);
}

void CStoragePeripheral::SetDescription(LPCTSTR lpstrDescription)
{
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

void CStoragePeripheral::SetSize( unsigned __int64 u64Size)
{
	m_u64Size = u64Size;
}

void CStoragePeripheral::Set( LPCTSTR lpstrType, LPCTSTR lpstrManufacturer, LPCTSTR lpstrName, LPCTSTR lpstrModel, LPCTSTR lpstrDescription, unsigned __int64 u64Size)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
	m_csManufacturer = lpstrManufacturer;
	StrForSQL( m_csManufacturer);
	m_csName = lpstrName;
	StrForSQL( m_csName);
	m_csModel = lpstrModel;
	StrForSQL( m_csModel);
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
	m_u64Size = u64Size;
}

BOOL CStoragePeripheral::FormatXML(CMarkup* pX)
{
	pX->AddElem("STORAGES");
	pX->IntoElem();
		pX->AddElemNV("MANUFACTURER",m_csManufacturer);
		pX->AddElemNV("NAME",m_csModel);
		pX->AddElemNV("MODEL",m_csName);
		pX->AddElemNV("DESCRIPTION",m_csDescription);
		pX->AddElemNV("TYPE",m_csType);
		pX->AddElemNV("DISKSIZE",(long)m_u64Size);
	pX->OutOfElem();
	return TRUE;
}

BOOL CStoragePeripheral::ParseFromCSV(CString &csCSV)
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
	// Read Model
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csModel = csBuffer.Left( nPos);
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
	// Read type
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csType = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Size
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_u64Size = _tcstoul( csBuffer.Left( nPos), NULL, 10);
	return TRUE;
}

void CStoragePeripheral::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CStoragePeripheral::GetDeviceName()
{
	return m_csDeviceName;
}

void CStoragePeripheral::Clear()
{
	m_ulID = 0;				
	m_csDeviceID.Empty();		
	m_csDeviceName.Empty();		
	m_csType.Empty();			
	m_csManufacturer.Empty();	
	m_csName.Empty();			
	m_csModel.Empty();			
	m_csDescription.Empty();	
	m_u64Size = 0;			
}
