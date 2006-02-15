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

// RegistryValue.h: interface for the CRegistryValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DREGISTRYVALUE_H__D469D12F_9CA7_4E5B_9553_BA13FAF327E5__INCLUDED_)
#define AFX_DREGISTRYVALUE_H__D469D12F_9CA7_4E5B_9553_BA13FAF327E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

#define HKCR_TREE	0	// HKEY_CLASSES_ROOT
#define HKCU_TREE	1	// HKEY_CURRENT_USER
#define HKLM_TREE	2	// HKEY_LOCAL_MACHINE
#define HKU_TREE	3	// HKEY_USERS
#define HKCC_TREE	4	// HKEY_CURRENT_CONFIG
#define HKDD_TRE	5	// HKEY_DYN_DATA (9X only)

#define REGISTRY_ALL_VALUES_OF_KEY	_T( "*") // Get all values of a key

class DLL_CLASS CRegistryValue  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CRegistryValue();
	virtual ~CRegistryValue();

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
	LPCTSTR GetValue();
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
	void Set( LPCTSTR lpstrName, LPCTSTR lpstrValue);
	void SetValue( LPCTSTR lpstrValue);
	void SetName( LPCTSTR lpstrName);
	// Retrieve the informations from a CSV buffer
	BOOL ParseFromCSV( CString &csCSV);

protected: // Attributes
	ULONG	m_ulID;			// Database record ID
	CString	m_csDeviceID;	// Device unique ID
	CString	m_csDeviceName;	// Device netbios or DNS name
	CString m_csName;		// Registry value name
	CString m_csValue;		// Registry value
};

#endif // !defined(AFX_DREGISTRYVALUE_H__D469D12F_9CA7_4E5B_9553_BA13FAF327E5__INCLUDED_)
