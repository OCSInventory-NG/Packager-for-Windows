// Document modified at : Wednesday, March 29, 2006 11:13:16 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// SystemPort.cpp: implementation of the CSystemPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemPort.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemPort::CSystemPort()
{
	Clear();
}

CSystemPort::~CSystemPort()
{
	Clear();
}

ULONG CSystemPort::GetID()
{
	return m_ulID;
}

LPCTSTR CSystemPort::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CSystemPort::GetType()
{
	return m_csType;
}

LPCTSTR CSystemPort::GetName()
{
	return m_csName;
}

LPCTSTR CSystemPort::GetCaption()
{
	return m_csCaption;
}

LPCTSTR CSystemPort::GetDescription()
{
	return m_csDescription;
}

void CSystemPort::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CSystemPort::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CSystemPort::SetType(LPCTSTR lpstrType)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
}

void CSystemPort::SetName(LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void CSystemPort::SetCaption(LPCTSTR lpstrCaption)
{
	m_csCaption = lpstrCaption;
	StrForSQL( m_csCaption);
}

void CSystemPort::SetDescription(LPCTSTR lpstrDescription)
{
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

void CSystemPort::Set( LPCTSTR lpstrType, LPCTSTR lpstrName, LPCTSTR lpstrCaption, LPCTSTR lpstrDescription)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
	m_csName = lpstrName;
	StrForSQL( m_csName);
	m_csCaption = lpstrCaption;
	StrForSQL( m_csCaption);
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

BOOL CSystemPort::FormatXML(CMarkup* pX)
{
	pX->AddElem("PORTS");
	pX->IntoElem();
		pX->AddElemNV("TYPE",m_csType);
		pX->AddElemNV("NAME",m_csName);
		pX->AddElemNV("CAPTION",m_csCaption);
		pX->AddElemNV("DESCRIPTION",m_csDescription);
	pX->OutOfElem();
	return TRUE;
}

void CSystemPort::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CSystemPort::GetDeviceName()
{
	return m_csDeviceName;
}

void CSystemPort::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csType.Empty();		
	m_csName.Empty();		
	m_csCaption.Empty();	
	m_csDescription.Empty();
}
