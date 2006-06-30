// Document modified at : Wednesday, March 29, 2006 11:12:13 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// RegistryValue.cpp: implementation of the CRegistryValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RegistryValue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegistryValue::CRegistryValue()
{
	Clear();
}

CRegistryValue::~CRegistryValue()
{
	Clear();
}

ULONG CRegistryValue::GetID()
{
	return m_ulID;
}

LPCTSTR CRegistryValue::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CRegistryValue::GetName()
{
	return m_csName;
}

LPCTSTR CRegistryValue::GetValue()
{
	return m_csValue;
}

void CRegistryValue::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CRegistryValue::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CRegistryValue::SetName(LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void CRegistryValue::SetValue(LPCTSTR lpstrValue)
{
	m_csValue = lpstrValue;
	StrForSQL( m_csValue);
}

void CRegistryValue::Set( LPCTSTR lpstrName, LPCTSTR lpstrValue)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
	m_csValue = lpstrValue;
	StrForSQL( m_csValue);
}

BOOL CRegistryValue::FormatXML(CMarkup* pX)
{
	pX->AddElem("REGISTRY");
	pX->IntoElem();
		pX->AddElemNV("NAME",m_csName);
		pX->AddElemNV("REGVALUE",m_csValue);
	pX->OutOfElem();

	return TRUE;
}

void CRegistryValue::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CRegistryValue::GetDeviceName()
{
	return m_csDeviceName;
}

void CRegistryValue::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csName.Empty();		
	m_csValue.Empty();		
}
