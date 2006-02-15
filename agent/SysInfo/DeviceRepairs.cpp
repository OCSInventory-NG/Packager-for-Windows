// Document modified at : Wednesday, December 10, 2003 12:06:06 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// DeviceRepairs.cpp: implementation of the CDeviceRepairs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DeviceRepairs.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDeviceRepairs::CDeviceRepairs()
{
	Clear();
}

CDeviceRepairs::~CDeviceRepairs()
{
	Clear();
}

void	CDeviceRepairs::Clear()
{
	m_ulID = 0;
	m_csDeviceID.Empty();
	m_csName.Empty();
	m_dtRequestDate.SetStatus( COleDateTime::invalid);
	m_csRequestDesc.Empty();
	m_dtActionDate.SetStatus( COleDateTime::invalid);
	m_csActionDesc.Empty();
	m_csWaranty.Empty();
	m_csAccount.Empty();
	m_csPrice.Empty();
	m_csComments.Empty();	
}

void	CDeviceRepairs::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void	CDeviceRepairs::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void	CDeviceRepairs::SetName( LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void	CDeviceRepairs::SetRequestDate( LPCTSTR lpstrDate)
{
	m_dtRequestDate.ParseDateTime( lpstrDate);
}

void	CDeviceRepairs::SetRequestDate( COleDateTime dtDate)
{
	m_dtRequestDate = dtDate;
}

void	CDeviceRepairs::SetRequestDescription( LPCTSTR lpstrDesc)
{
	m_csRequestDesc = lpstrDesc;
	StrForSQL( m_csRequestDesc);
}

void	CDeviceRepairs::SetActionDate( LPCTSTR lpstrDate)
{
	m_dtActionDate.ParseDateTime( lpstrDate);
}

void	CDeviceRepairs::SetActionDate( COleDateTime dtDate)
{
	m_dtActionDate = dtDate;
}

void	CDeviceRepairs::SetActionDescription( LPCTSTR lpstrAction)
{
	m_csActionDesc = lpstrAction;
	StrForSQL( m_csActionDesc);
}

void	CDeviceRepairs::SetWaranty( LPCTSTR lpstrWaranty)
{
	m_csWaranty = lpstrWaranty;
	StrForSQL( m_csWaranty);
}


void	CDeviceRepairs::SetAccount( LPCTSTR lpstrAccount)
{
	m_csAccount = lpstrAccount;
	StrForSQL( m_csAccount);
}

void	CDeviceRepairs::SetPrice( LPCTSTR lpstrPrice)
{
	m_csPrice = lpstrPrice;
	StrForSQL( m_csPrice);
}

void	CDeviceRepairs::SetComments( LPCTSTR lpstrComments)
{
	m_csComments = lpstrComments;
	StrForSQL( m_csComments);
}

ULONG	CDeviceRepairs::GetID()
{
	return m_ulID;
}

LPCTSTR	CDeviceRepairs::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR	CDeviceRepairs::GetName()
{
	return m_csName;
}

LPCTSTR CDeviceRepairs::GetRequestDateString()
{
	static CString csDate;

	csDate = m_dtRequestDate.Format( _T( "%Y-%m-%d %H:%M"));
	return csDate;
}

COleDateTime CDeviceRepairs::GetRequestDate()
{
	return m_dtRequestDate;
}

LPCTSTR	CDeviceRepairs::GetRequestDescription()
{
	return m_csRequestDesc;
}

LPCTSTR CDeviceRepairs::GetActionDateString()
{
	static CString csDate;

	csDate = m_dtActionDate.Format( _T( "%Y-%m-%d %H:%M"));
	return csDate;
}

COleDateTime CDeviceRepairs::GetActionDate()
{
	return m_dtActionDate;
}

LPCTSTR	CDeviceRepairs::GetActionDescription()
{
	return m_csActionDesc;
}

LPCTSTR	CDeviceRepairs::GetWaranty()
{
	return m_csWaranty;
}

LPCTSTR	CDeviceRepairs::GetAccount()
{
	return m_csAccount;
}

LPCTSTR	CDeviceRepairs::GetPrice()
{
	return m_csPrice;
}

LPCTSTR	CDeviceRepairs::GetComments()
{
	return m_csComments;
}

void CDeviceRepairs::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CDeviceRepairs::GetDeviceName()
{
	return m_csDeviceName;
}
