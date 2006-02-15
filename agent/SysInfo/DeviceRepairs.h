// Document modified at : Wednesday, December 10, 2003 12:05:18 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// DeviceRepairs.h: interface for the CDeviceRepairs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICEREPAIRS_H__D469D12F_9CA7_4E5B_9553_BA13FAF327E5__INCLUDED_)
#define AFX_DEVICEREPAIRS_H__D469D12F_9CA7_4E5B_9553_BA13FAF327E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CDeviceRepairs  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CDeviceRepairs();
	virtual ~CDeviceRepairs();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////
	ULONG GetID();
	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Return a string with the device NetBIOS name
	LPCTSTR GetDeviceName();
	LPCTSTR	GetName();
	LPCTSTR	GetRequestDateString();
	COleDateTime GetRequestDate();
	LPCTSTR	GetRequestDescription();
	LPCTSTR	GetActionDateString();
	COleDateTime GetActionDate();
	LPCTSTR	GetActionDescription();
	LPCTSTR	GetWaranty();
	LPCTSTR	GetAccount();
	LPCTSTR	GetPrice();
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
	void SetRequestDate( LPCTSTR lpstrDate);
	void SetRequestDate( COleDateTime dtDate);
	void SetRequestDescription( LPCTSTR lpstrDesc);
	void SetActionDate( LPCTSTR lpstrDate);
	void SetActionDate( COleDateTime dtDate);
	void SetActionDescription( LPCTSTR lpstrAction);
	void SetWaranty( LPCTSTR lpstrWaranty);
	void SetAccount( LPCTSTR lpstrAccount);
	void SetPrice( LPCTSTR lpstrPrice);
	void SetComments( LPCTSTR lpstrComments);

	void Clear();

protected: // Attributes
	ULONG		m_ulID;			// Unique ID
	CString		m_csDeviceID;	// Device unique ID
	CString		m_csDeviceName;	// Device netbios or DNS name
	CString		m_csName;		// Repair Name
	COleDateTime m_dtRequestDate;// Repair request date
	CString		m_csRequestDesc; // Repair request description
	COleDateTime m_dtActionDate; // Repair intervention date
	CString		m_csActionDesc;	// Repair intervention description
	CString		m_csWaranty;	// Waranty description
	CString		m_csAccount;	// Repair account
	CString		m_csPrice;		// Repair price
	CString		m_csComments;	// Repair comments
};

#endif // !defined(AFX_DEVICEREPAIRS_H__D469D12F_9CA7_4E5B_9553_BA13FAF327E5__INCLUDED_)
