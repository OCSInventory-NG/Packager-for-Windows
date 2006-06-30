// Document modified at : Wednesday, March 29, 2006 1:45:26 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SystemSlot.h: interface for the CSystemSlot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMSLOT_H__C9C1C41A_5FCD_412A_AD56_6BAC3EA69E30__INCLUDED_)
#define AFX_SYSTEMSLOT_H__C9C1C41A_5FCD_412A_AD56_6BAC3EA69E30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

#define SYSTEMSLOT_USAGE_RESERVED	0
#define SYSTEMSLOT_USAGE_OTHER		1
#define SYSTEMSLOT_USAGE_UNKNWOWN	2
#define SYSTEMSLOT_USAGE_AVAILABLE	3
#define SYSTEMSLOT_USAGE_INUSE		4


class DLL_CLASS CSystemSlot  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSystemSlot();
	virtual ~CSystemSlot();

	void Clear();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	// Return the database record ID
	ULONG GetID();
	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Return a string with the device NetBIOS name
	LPCTSTR GetDeviceName();
	LPCTSTR GetName();
	LPCTSTR GetDescription();
	LPCTSTR GetSlotDesignation();
	LPCTSTR GetUsage();
	LPCTSTR GetStatus();
	BOOL IsShared();
	// Format informations in a XML string
	BOOL FormatXML( CMarkup* pX );

	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////

	void SetID( ULONG ulID);
	// Set the device unique ID
	void SetDeviceID( LPCTSTR lpstrDeviceID);
	// Set the device NetBIOS name
	void SetDeviceName( LPCTSTR lpstrName);
	void Set( LPCTSTR lpstrName, LPCTSTR lpstrDescription, LPCTSTR lpstrDesignation, LPCTSTR lpstrUsage, LPCTSTR lpstrStatus, BOOL bShared);
	void SetName( LPCTSTR lpstrName);
	void SetDescription( LPCTSTR lpstrDescription);
	void SetSlotDesignation( LPCTSTR lpstrDesignation);
	void SetUsage( LPCTSTR lpstrUsage);
	void SetUsage( DWORD dwUsage);
	void SetStatus( LPCTSTR lpstrStatus);
	void SetShared( BOOL bShared);

protected: // Attributes
	ULONG	m_ulID;			// Database record ID
	CString	m_csDeviceID;	// Device unique ID
	CString	m_csDeviceName;	// Device netbios or DNS name
	CString m_csName;		// Slot name
	CString m_csDescription;// Slot description
	CString m_csDesignation;// Slot designation (ISA1, PCI1, PCI2, AGP1...)
	CString m_csUsage;		// Usage (available, in use...)
	CString m_csStatus;		// Status (OK, failure...)
	BOOL	m_bShared;		// Shared with another slot (example ISA and PCI)
};
#endif // !defined(AFX_SYSTEMSLOT_H__C9C1C41A_5FCD_412A_AD56_6BAC3EA69E30__INCLUDED_)

