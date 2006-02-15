// Document modified at : Saturday, January 03, 2004 11:32:46 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// Monitor.h: interface for the CMonitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITOR_H__1838430C_16FA_4069_A2C2_4B338DF7308C__INCLUDED_)
#define AFX_MONITOR_H__1838430C_16FA_4069_A2C2_4B338DF7308C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CMonitor  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CMonitor();
	virtual ~CMonitor();

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
	LPCTSTR GetCaption();
	LPCTSTR GetType();
	LPCTSTR GetManufacturer();
	LPCTSTR GetSerial();
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
	void Set( LPCTSTR lpstrManufacturer, LPCTSTR lpstrType, LPCTSTR lpstrCaption, LPCTSTR lpstrDescription, LPCSTR lpstrSerial);
	void SetDescription( LPCTSTR lpstrDescription);
	void SetCaption( LPCTSTR lpstrCaption);
	void SetType( LPCTSTR lpstrType);
	void SetManufacturer( LPCTSTR lpstrManufacturer);
	void SetSerial( LPCTSTR lpstrSerial);
	// Retrieve the informations from a CSV buffer
	BOOL ParseFromCSV( CString &csCSV);

protected: // Attributes
	ULONG	m_ulID;				// Database record ID
	CString	m_csDeviceID;		// Device unique ID
	CString	m_csDeviceName;		// Device netbios or DNS name
	CString m_csManufacturer;	// Monitor manufacturer
	CString m_csType;			// Monitor type
	CString m_csCaption;		// Caption
	CString m_csDescription;	// Description
	CString m_csSerial;			// Serial
};

#endif // !defined(AFX_MONITOR_H__1838430C_16FA_4069_A2C2_4B338DF7308C__INCLUDED_)
