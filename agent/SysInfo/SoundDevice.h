// Document modified at : Saturday, January 03, 2004 11:32:48 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SoundDevice.h: interface for the CSoundDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDDEVICE_H__ACFCECE1_8559_4161_8305_B8E69BF21C25__INCLUDED_)
#define AFX_SOUNDDEVICE_H__ACFCECE1_8559_4161_8305_B8E69BF21C25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CSoundDevice  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSoundDevice();
	virtual ~CSoundDevice();

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
	LPCTSTR GetDescription();
	LPCTSTR GetName();
	LPCTSTR GetManufacturer();
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
	void Set( LPCTSTR lpstrManufacturer, LPCTSTR lpstrName, LPCTSTR lpstrDescription);
	void SetDescription( LPCTSTR lpstrDescription);
	void SetName( LPCTSTR lpstrName);
	void SetManufacturer( LPCTSTR lpstrManufacturer);
	// Retrieve the informations from a CSV buffer
	BOOL ParseFromCSV( CString &csCSV);

protected: // Attributes
	ULONG	m_ulID;				// Database record ID
	CString	m_csDeviceID;		// Device unique ID
	CString	m_csDeviceName;		// Device netbios or DNS name
	CString m_csManufacturer;	// Sound Device Manufacturer
	CString m_csName;			// Sound Device name
	CString m_csDescription;	// Sound Device description
};

#endif // !defined(AFX_SOUNDDEVICE_H__ACFCECE1_8559_4161_8305_B8E69BF21C25__INCLUDED_)
