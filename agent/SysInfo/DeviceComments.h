// Document modified at : Tuesday, December 09, 2003 11:27:54 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// DeviceComments.h: interface for the CDeviceComments class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICECOMMENTS_H__E0B141F6_7074_4D6B_8CD1_81CDDABC95E3__INCLUDED_)
#define AFX_DEVICECOMMENTS_H__E0B141F6_7074_4D6B_8CD1_81CDDABC95E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CDeviceComments  
{
// Methods
public:
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CDeviceComments();
	virtual ~CDeviceComments();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////
	ULONG GetID();
	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Return a string with the device NetBIOS name
	LPCTSTR GetDeviceName();
	LPCTSTR GetName();
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
	void SetComments( LPCTSTR lpstrComments);

	void Clear();

protected: // Attributes
	ULONG	m_ulID;			// Unique ID
	CString	m_csDeviceID;	// Device unique ID
	CString	m_csDeviceName;	// Device netbios or DNS name
	CString	m_csName;		// Comment name
	CString	m_csComments;	// Comments
};

#endif // !defined(AFX_DEVICECOMMENTS_H__E0B141F6_7074_4D6B_8CD1_81CDDABC95E3__INCLUDED_)
