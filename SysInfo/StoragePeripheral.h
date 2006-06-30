// Document modified at : Wednesday, March 29, 2006 1:43:26 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// StoragePeripheral.h: interface for the CStoragePeripheral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STORAGEPERIPHERAL_H__6D006CB8_0A72_4960_93A3_89E3D1C9A400__INCLUDED_)
#define AFX_STORAGEPERIPHERAL_H__6D006CB8_0A72_4960_93A3_89E3D1C9A400__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS  CStoragePeripheral  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CStoragePeripheral();
	virtual ~CStoragePeripheral();

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
	unsigned __int64 GetSize();
	LPCTSTR GetSizeString();
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
	void Set( LPCTSTR lpstrType, LPCTSTR lpstrManufacturer, LPCTSTR lpstrName, LPCTSTR lpstrModel, LPCTSTR lpstrDescription, unsigned __int64 u64Size = 0);
	void SetDescription( LPCTSTR lpstrDescription);
	void SetModel( LPCTSTR lpstrModel);
	void SetName( LPCTSTR lpstrName);
	void SetType( LPCTSTR lpstrType);
	void SetSize( unsigned __int64 u64Size);
	void SetManufacturer( LPCTSTR lpstrManufacturer);

protected: // Attributes
	ULONG	m_ulID;				// Database record ID
	CString	m_csDeviceID;		// Device unique ID
	CString	m_csDeviceName;		// Device netbios or DNS name
	CString m_csType;			// Storage type (floppy, disk, tape...)
	CString m_csManufacturer;	// Manufacturer
	CString m_csName;			// Name
	CString m_csModel;			// Model
	CString m_csDescription;	// Description
	unsigned __int64 m_u64Size;	// Total size in MB
};
#endif // !defined(AFX_STORAGEPERIPHERAL_H__6D006CB8_0A72_4960_93A3_89E3D1C9A400__INCLUDED_)

