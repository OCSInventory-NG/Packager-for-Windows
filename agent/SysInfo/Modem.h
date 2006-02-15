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

// Modem.h: interface for the CModem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEM_H__13BBD121_3DC4_4C39_8023_2409A47F8704__INCLUDED_)
#define AFX_MODEM_H__13BBD121_3DC4_4C39_8023_2409A47F8704__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CModem  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CModem();
	virtual ~CModem();

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
	LPCTSTR GetModel();
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
	void Set( LPCTSTR lpstrType, LPCTSTR lpstrName, LPCTSTR lpstrModel, LPCTSTR lpstrDescription);
	void SetDescription( LPCTSTR lpstrDescription);
	void SetModel( LPCTSTR lpstrModel);
	void SetName( LPCTSTR lpstrName);
	void SetType( LPCTSTR lpstrType);
	// Retrieve the informations from a CSV buffer
	BOOL ParseFromCSV( CString &csCSV);

protected: // Attributes
	ULONG	m_ulID;			// Database record ID
	CString	m_csDeviceID;	// Device unique ID
	CString	m_csDeviceName;	// Device netbios or DNS name
	CString m_csType;		// Modem type (external, internal...)
	CString m_csName;		// Modem name
	CString m_csModel;		// Model
	CString m_csDescription;// Description
};

#endif // !defined(AFX_MODEM_H__13BBD121_3DC4_4C39_8023_2409A47F8704__INCLUDED_)
