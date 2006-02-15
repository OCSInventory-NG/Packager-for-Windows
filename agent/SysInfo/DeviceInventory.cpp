// Document modified at : Wednesday, December 10, 2003 12:05:56 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// DeviceInventory.cpp: implementation of the CDeviceInventory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DeviceInventory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDeviceInventory::CDeviceInventory()
{
	Clear();
}

CDeviceInventory::~CDeviceInventory()
{
	Clear();
}

void	CDeviceInventory::Clear()
{
	m_ulID = 0;
	m_csDeviceID.Empty();
	m_csName.Empty();
	m_csProvider.Empty();
	m_dtCommandDate.SetStatus( COleDateTime::invalid);
	m_csCommandNumber.Empty();
	m_dtReceptionDate.SetStatus( COleDateTime::invalid);
	m_csBillNumber.Empty();
	m_csWaranty.Empty();
	m_csAccount.Empty();
	m_csPrice.Empty();
	m_csInventory.Empty();
	m_csSN.Empty();
	m_csComments.Empty();	
}

void	CDeviceInventory::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void	CDeviceInventory::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void	CDeviceInventory::SetName( LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void	CDeviceInventory::SetProvider( LPCTSTR lpstrProvider)
{
	m_csProvider = lpstrProvider;
	StrForSQL( m_csProvider);
}

void	CDeviceInventory::SetCommandDate( COleDateTime dtDate)
{
	m_dtCommandDate = dtDate;
}

void	CDeviceInventory::SetCommandDate( LPCTSTR lpstrDate)
{
	m_dtCommandDate.ParseDateTime( lpstrDate);
}

void	CDeviceInventory::SetCommandNumber( LPCTSTR lpstrNumber)
{
	m_csCommandNumber = lpstrNumber;
	StrForSQL( m_csCommandNumber);
}

void	CDeviceInventory::SetReceptionDate( COleDateTime dtDate)
{
	m_dtReceptionDate = dtDate;
}

void	CDeviceInventory::SetReceptionDate( LPCTSTR lpstrDate)
{
	m_dtReceptionDate.ParseDateTime( lpstrDate);
}

void	CDeviceInventory::SetBillNumber( LPCTSTR lpstrNumber)
{
	m_csBillNumber = lpstrNumber;
	StrForSQL( m_csBillNumber);
}

void	CDeviceInventory::SetWaranty( LPCTSTR lpstrWaranty)
{
	m_csWaranty = lpstrWaranty;
	StrForSQL( m_csWaranty);
}

void	CDeviceInventory::SetInventoryNumber( LPCTSTR lpstrInventory)
{
	m_csInventory = lpstrInventory;
	StrForSQL( m_csInventory);
}

void	CDeviceInventory::SetSerialNumber( LPCTSTR lpstrSN)
{
	m_csSN = lpstrSN;
	StrForSQL( m_csSN);
}

void	CDeviceInventory::SetAccount( LPCTSTR lpstrAccount)
{
	m_csAccount = lpstrAccount;
	StrForSQL( m_csAccount);
}

void	CDeviceInventory::SetPrice( LPCTSTR lpstrPrice)
{
	m_csPrice = lpstrPrice;
	StrForSQL( m_csPrice);
}

void	CDeviceInventory::SetComments( LPCTSTR lpstrComments)
{
	m_csComments = lpstrComments;
	StrForSQL( m_csComments);
}

ULONG	CDeviceInventory::GetID()
{
	return m_ulID;
}

LPCTSTR	CDeviceInventory::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR	CDeviceInventory::GetName()
{
	return m_csName;
}

LPCTSTR	CDeviceInventory::GetProvider()
{
	return m_csProvider;
}

COleDateTime CDeviceInventory::GetCommandDate()
{
	return m_dtCommandDate;
}

LPCTSTR	CDeviceInventory::GetCommandDateString()
{
	static CString csDate;

	csDate = m_dtCommandDate.Format( _T( "%Y-%m-%d"));
	return csDate;
}

LPCTSTR	CDeviceInventory::GetCommandNumber()
{
	return m_csCommandNumber;
}

COleDateTime CDeviceInventory::GetReceptionDate()
{
	return m_dtReceptionDate;
}

LPCTSTR	CDeviceInventory::GetReceptionDateString()
{
	static CString csDate;

	csDate = m_dtReceptionDate.Format( _T( "%Y-%m-%d"));
	return csDate;
}

LPCTSTR	CDeviceInventory::GetBillNumber()
{
	return m_csBillNumber;
}

LPCTSTR	CDeviceInventory::GetWaranty()
{
	return m_csWaranty;
}

LPCTSTR	CDeviceInventory::GetInventoryNumber()
{
	return m_csInventory;
}

LPCTSTR	CDeviceInventory::GetSerialNumber()
{
	return m_csSN;
}

LPCTSTR	CDeviceInventory::GetAccount()
{
	return m_csAccount;
}

LPCTSTR	CDeviceInventory::GetPrice()
{
	return m_csPrice;
}

LPCTSTR	CDeviceInventory::GetComments()
{
	return m_csComments;
}

void CDeviceInventory::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CDeviceInventory::GetDeviceName()
{
	return m_csDeviceName;
}
