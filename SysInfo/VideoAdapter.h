// Document modified at : Wednesday, March 29, 2006 1:46:06 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// VideoAdapter.h: interface for the CVideoAdapter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEOADAPTER_H__DE761F14_8847_11D5_B278_0040055338AF__INCLUDED_)
#define AFX_VIDEOADAPTER_H__DE761F14_8847_11D5_B278_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CVideoAdapter
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CVideoAdapter();
	virtual ~CVideoAdapter();

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
	// Return Video adapter name
	LPCTSTR GetName();
	// Retrun Video adapter chipset
	LPCTSTR GetChipset();
	// Return Video adapter memory
	LPCTSTR GetMemory();
	// Return screen resolution
	LPCTSTR GetScreenResolution();
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
	void SetName( LPCTSTR lpstrDescription);
	void SetChipset( LPCTSTR lpstrChipset);
	void SetMemory( LPCTSTR lpstrMemory);
	void SetMemory( LONG lMemory);
	void SetScreenResolution( LPCTSTR lpstrResolution);
	// Set all the information
	void Set( LPCTSTR lpstrDescription, LPCTSTR lpstrChipset, LONG lMemory, LPCTSTR lpstrResolution);

protected: // Attributes
	ULONG	m_ulID;				// Database record ID
	CString	m_csDeviceID;		// Device unique ID
	CString	m_csDeviceName;		// Device netbios or DNS name
	CString	m_csName;			// Video adpater name
	CString m_csChipset;		// Video adapter chipset
	CString m_csMemory;			// Video adapter memory
	CString	m_csResolution;		// Screen resolution
};
#endif // !defined(AFX_VIDEOADAPTER_H__DE761F14_8847_11D5_B278_0040055338AF__INCLUDED_)

