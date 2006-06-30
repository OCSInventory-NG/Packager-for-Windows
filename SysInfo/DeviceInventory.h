// Document modified at : Wednesday, March 29, 2006 1:27:57 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// DeviceInventory.h: interface for the CDeviceInventory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICEINVENTORY_H__33A17558_0395_46A4_B753_2074A72345D4__INCLUDED_)
#define AFX_DEVICEINVENTORY_H__33A17558_0395_46A4_B753_2074A72345D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

class DLL_CLASS CDeviceInventory  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CDeviceInventory();
	virtual ~CDeviceInventory();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////
	ULONG GetID();
	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Return a string with the device NetBIOS name
	LPCTSTR	GetDeviceName();
	LPCTSTR	GetName();
	LPCTSTR	GetProvider();
	COleDateTime GetCommandDate();
	LPCTSTR	GetCommandDateString();
	LPCTSTR	GetCommandNumber();
	COleDateTime GetReceptionDate();
	LPCTSTR	GetReceptionDateString();
	LPCTSTR	GetBillNumber();
	LPCTSTR	GetWaranty();
	LPCTSTR	GetAccount();
	LPCTSTR	GetPrice();
	LPCTSTR	GetInventoryNumber();
	LPCTSTR	GetSerialNumber();
	LPCTSTR	GetComments();

	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////

	void SetID( ULONG ulID);
	// Set the device unique ID
	void SetDeviceID( LPCTSTR lpstrDeviceID);
	// Set the device NetBIOS name
	void SetDeviceName( LPCTSTR lpstrName);
	void SetName( LPCTSTR lpstrName);
	void SetProvider( LPCTSTR lpstrProvider);
	void SetCommandDate( COleDateTime dtDate);
	void SetCommandDate( LPCTSTR lpstrDate);
	void SetCommandNumber( LPCTSTR lpstrNumber);
	void SetReceptionDate( COleDateTime dtDate);
	void SetReceptionDate( LPCTSTR lpstrDate);
	void SetBillNumber( LPCTSTR lpstrNumber);
	void SetWaranty( LPCTSTR lpstrWaranty);
	void SetAccount( LPCTSTR lpstrAccount);
	void SetPrice( LPCTSTR lpstrPrice);
	void SetInventoryNumber( LPCTSTR lpstrInventory);
	void SetSerialNumber( LPCTSTR lpstrSN);
	void SetComments( LPCTSTR lpstrComments);

	void Clear();

protected: // Attributes
	ULONG		m_ulID;			// Unique ID
	CString		m_csDeviceID;	// Device unique ID
	CString		m_csDeviceName;	// Device netbios or DNS name
	CString		m_csName;		// Object Name
	CString		m_csProvider;	// Object provider
	COleDateTime m_dtCommandDate;// Object command date
	CString		m_csCommandNumber;// Object command number
	COleDateTime m_dtReceptionDate;// Object reception date
	CString		m_csBillNumber;	// Object billing informations
	CString		m_csWaranty;	// Object Waranty
	CString		m_csAccount;	// Object account
	CString		m_csPrice;		// Object price
	CString		m_csInventory;	// Object inventory number
	CString		m_csSN;			// Object serial number
	CString		m_csComments;	// Object comments
};
#endif // !defined(AFX_DEVICEINVENTORY_H__33A17558_0395_46A4_B753_2074A72345D4__INCLUDED_)

