// Document modified at : Saturday, December 06, 2003 1:41:34 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// Modem.cpp: implementation of the CModem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Modem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModem::CModem()
{
	Clear();
}

CModem::~CModem()
{
	Clear();
}

ULONG CModem::GetID()
{
	return m_ulID;
}

LPCTSTR CModem::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CModem::GetType()
{
	return m_csType;
}

LPCTSTR CModem::GetName()
{
	return m_csName;
}

LPCTSTR CModem::GetModel()
{
	return m_csModel;
}

LPCTSTR CModem::GetDescription()
{
	return m_csDescription;
}

void CModem::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CModem::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CModem::SetType(LPCTSTR lpstrType)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
}

void CModem::SetName(LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void CModem::SetModel(LPCTSTR lpstrModel)
{
	m_csModel = lpstrModel;
	StrForSQL( m_csModel);
}

void CModem::SetDescription(LPCTSTR lpstrDescription)
{
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

void CModem::Set( LPCTSTR lpstrType, LPCTSTR lpstrName, LPCTSTR lpstrModel, LPCTSTR lpstrDescription)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
	m_csName = lpstrName;
	StrForSQL( m_csName);
	m_csModel = lpstrModel;
	StrForSQL( m_csModel);
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

BOOL CModem::FormatXML(CMarkup* pX)
{
	pX->AddElem("MODEMS");
	pX->IntoElem();
		pX->AddElemNV("NAME",m_csName);
		pX->AddElemNV("MODEL",m_csModel);
		pX->AddElemNV("DESCRIPTION",m_csDescription);
		pX->AddElemNV("TYPE",m_csType);
	pX->OutOfElem();
	return TRUE;
}

BOOL CModem::ParseFromCSV(CString &csCSV)
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
	// Read Model
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csModel = csBuffer.Left( nPos);
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

void CModem::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CModem::GetDeviceName()
{
	return m_csDeviceName;
}

void CModem::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csType.Empty();		
	m_csName.Empty();		
	m_csModel.Empty();		
	m_csDescription.Empty();
}
