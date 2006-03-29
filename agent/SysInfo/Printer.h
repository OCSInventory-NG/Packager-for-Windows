// Document modified at : Wednesday, March 29, 2006 1:38:24 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// PrinterInfo.h: interface for the CPrinter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTER_H__EB59F013_89CE_11D5_B284_0040055338AF__INCLUDED_)
#define AFX_PRINTER_H__EB59F013_89CE_11D5_B284_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CPrinter  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CPrinter();
	virtual ~CPrinter();

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
	// Return the printer name
	LPCTSTR GetName();
	// Return the printer driver
	LPCTSTR GetDriver();
	// Return the printer port
	LPCTSTR GetPort();
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
	void SetName( LPCTSTR lpstrName);
	void SetDriver( LPCTSTR lpstrDriver);
	void SetPort( LPCTSTR lpstrPort);
	// Set all the printer informations
	void Set( LPCTSTR lpstrName, LPCTSTR lpstrDriver, LPCTSTR lpstrPort);
	// Retrieve the informations from a CSV buffer

protected: // Attributes
	ULONG	m_ulID;			// Database record ID
	CString	m_csDeviceID;	// Device unique ID
	CString	m_csDeviceName;	// Device netbios or DNS name
	CString m_csName;		// Printer name
	CString m_csDriver;		// Printer driver
	CString m_csPort;		// Printer port
};
#endif // !defined(AFX_PRINTER_H__EB59F013_89CE_11D5_B284_0040055338AF__INCLUDED_)

