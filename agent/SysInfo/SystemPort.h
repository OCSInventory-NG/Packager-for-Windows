// Document modified at : Sunday, January 04, 2004 5:46:36 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SystemPort.h: interface for the CSystemPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMPORT_H__FC47C324_9B26_4C73_945F_5E7761E676F9__INCLUDED_)
#define AFX_SYSTEMPORT_H__FC47C324_9B26_4C73_945F_5E7761E676F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

#define SYSTEM_PORT_SERIAL		_T( "Serial")
#define SYSTEM_PORT_PARALLEL	_T( "Parallel")

class DLL_CLASS CSystemPort  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSystemPort();
	virtual ~CSystemPort();

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
	LPCTSTR GetName();
	LPCTSTR GetType();
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
	void Set( LPCTSTR lpstrType, LPCTSTR lpstrName, LPCTSTR lpstrCaption, LPCTSTR lpstrDescription);
	void SetDescription( LPCTSTR lpstrDescription);
	void SetName( LPCTSTR lpstrName);
	void SetCaption( LPCTSTR lpstrCaption);
	void SetType( LPCTSTR lpstrType);
	// Retrieve the informations from a CSV buffer
	BOOL ParseFromCSV( CString &csCSV);

protected: // Attributes
	ULONG	m_ulID;			// Database record ID
	CString	m_csDeviceID;	// Device unique ID
	CString	m_csDeviceName;	// Device netbios or DNS name
	CString m_csType;		// Port type (serial, parallel...)
	CString m_csName;		// Port name
	CString m_csCaption;	// Caption
	CString m_csDescription;// Description
};

#endif // !defined(AFX_SYSTEMPORT_H__FC47C324_9B26_4C73_945F_5E7761E676F9__INCLUDED_)
