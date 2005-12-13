// Document modified at : Saturday, December 06, 2003 1:26:14 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// VideoAdapter.cpp: implementation of the CVideoAdapter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "VideoAdapter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVideoAdapter::CVideoAdapter()
{
	Clear();
}

CVideoAdapter::~CVideoAdapter()
{
	Clear();
}

void CVideoAdapter::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CVideoAdapter::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CVideoAdapter::Set(LPCTSTR lpstrDescription, LPCTSTR lpstrChipset, LONG lMemory, LPCTSTR lpstrResolution)
{
	m_csName = lpstrDescription;
	StrForSQL( m_csName);
	m_csChipset = lpstrChipset;
	StrForSQL( m_csChipset);
	if (lMemory == -1)
		m_csMemory = NOT_AVAILABLE;
	else
		m_csMemory.Format( _T( "%lu"), lMemory/ONE_MEGABYTE);
	m_csResolution = lpstrResolution;
	StrForSQL( m_csResolution);
}

void CVideoAdapter::SetName( LPCTSTR lpstrDescription)
{
	m_csName = lpstrDescription;
	StrForSQL( m_csName);
}

void CVideoAdapter::SetChipset( LPCTSTR lpstrChipset)
{
	m_csChipset = lpstrChipset;
	StrForSQL( m_csChipset);
}

void CVideoAdapter::SetMemory( LPCTSTR lpstrMemory)
{
	m_csMemory = lpstrMemory;
	StrForSQL( m_csMemory);
}

void CVideoAdapter::SetMemory( LONG lMemory)
{
	if (lMemory == -1)
		m_csMemory = NOT_AVAILABLE;
	else
		m_csMemory.Format( _T( "%lu"), lMemory/ONE_MEGABYTE);
	StrForSQL( m_csMemory);
}

void CVideoAdapter::SetScreenResolution( LPCTSTR lpstrResolution)
{
	m_csResolution = lpstrResolution;
	StrForSQL( m_csResolution);
}

ULONG CVideoAdapter::GetID()
{
	return m_ulID;
}

LPCTSTR CVideoAdapter::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CVideoAdapter::GetName()
{
	return m_csName;
}

LPCTSTR CVideoAdapter::GetChipset()
{
	return m_csChipset;
}

LPCTSTR CVideoAdapter::GetMemory()
{
	return m_csMemory;
}

LPCTSTR CVideoAdapter::GetScreenResolution()
{
	return m_csResolution;
}

BOOL CVideoAdapter::ParseFromCSV(CString &csCSV)
{
	CString		csBuffer = csCSV,
				csTemp;
	int			nPos;

	// Read Computer ID
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Adapter description
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csName = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Chipset
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csChipset = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Memory
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csMemory = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read resolution (optional)
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csResolution = csBuffer.Left( nPos);
	return TRUE;
}

BOOL CVideoAdapter::FormatXML(CMarkup* pX)
{
	pX->AddElem("VIDEOS");
	pX->IntoElem();
		pX->AddElemNV("NAME",m_csName);
		pX->AddElemNV("CHIPSET",m_csChipset);
		pX->AddElemNV("MEMORY",m_csMemory);
		pX->AddElemNV("RESOLUTION",m_csResolution);
	pX->OutOfElem();
	return TRUE;
}

void CVideoAdapter::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CVideoAdapter::GetDeviceName()
{
	return m_csDeviceName;
}

void CVideoAdapter::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csName.Empty();		
	m_csChipset.Empty();	
	m_csMemory.Empty();		
	m_csResolution.Empty();	
}
